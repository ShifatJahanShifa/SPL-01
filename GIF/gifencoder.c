#include "gifencoder.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#ifdef _WIN32
#include <io.h>
#else
#include <unistd.h>
#endif

/* helper to write a little-endian 16-bit number portably */

#define writeNum(fd, n) write((fd), (uint8_t []) {(n) & 0xFF, (n) >> 8}, 2)
/*writeNum(fileDescriptor, n)
{
    write((fileDescriptor), (uint8_t []) {(n) & 0xFF, (n) >> 8}, 2);
}*/


// defined 16 colors
static uint8_t vga[0x30] =
{
    0x00, 0x00, 0x00,
    0xAA, 0x00, 0x00,
    0x00, 0xAA, 0x00,
    0xAA, 0x55, 0x00,
    0x00, 0x00, 0xAA,
    0xAA, 0x00, 0xAA,
    0x00, 0xAA, 0xAA,
    0xAA, 0xAA, 0xAA,
    0x55, 0x55, 0x55,
    0xFF, 0x55, 0x55,
    0x55, 0xFF, 0x55,
    0xFF, 0xFF, 0x55,
    0x55, 0x55, 0xFF,
    0xFF, 0x55, 0xFF,
    0x55, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF,
};

struct Node
{
    uint16_t key;
    struct Node *children[];
};
typedef struct Node Node;

static Node *newNode(uint16_t key, int degree)
{
    Node *node = calloc(1, sizeof(*node) + degree * sizeof(Node *));

    if (node)
        node->key = key;

    return node;
}

static Node *newTrie(int degree, int *nkeys)
{
    Node *root = newNode(0, degree);

    /* Creating nodes for single pixels. */
    for (*nkeys = 0; *nkeys < degree; (*nkeys)++)
       {
           root->children[*nkeys] = newNode(*nkeys, degree);
       }

    *nkeys += 2; /* skipping clear code and stop code */

    return root;
}


/* a recursive function to delete trie nodes*/
static void deleteTrie(Node *root, int degree)
{
    if (!root)
        return;

    for (int i = 0; i < degree; i++)
        deleteTrie(root->children[i], degree);

    free(root);
}


void writeAndStore(int s, uint8_t *destination, int fileDescriptor, const uint8_t *source, size_t n)
{
    write(fileDescriptor, source, n);

    if (s) {
        memcpy(destination, source, n);
        destination += n;
    }
}


static void putLoop(GIF *gif, uint16_t loop);

GIF *newGif(
    const char *fileName, uint16_t width, uint16_t height,
    uint8_t *palette, int depth, int backgroundIndex, int loop)
{
    int i, red, green, blue, v;
    int storeGct, customGct;  // global color table


    /* if the image background is transparent, then for one layer, one buffer is needed
        otherwise, the image is not transparent and layer is one, then buffer =two*/
    int numberOFbuffers = backgroundIndex < 0 ? 2 : 1;

    GIF *gif = calloc(1, sizeof(*gif) + numberOFbuffers*width*height);

    if (!gif)
        return NULL;

    gif->widthOfScreen = width;
    gif->heightOfScreen = height;
    gif->backgroundIndex = backgroundIndex;
    gif->frame = (uint8_t *) &gif[1];
    gif->back = &gif->frame[width*height];

#ifdef _WIN32
    gif->fileDescriptor = creat(fileName, S_IWRITE);
#else
    gif->fileDescriptor = creat(fileName, 0666);
#endif
    if (gif->fileDescriptor == -1)
        free(gif);

        /* opening in binary mode */
#ifdef _WIN32
    setmode(gif->fileDescriptor, O_BINARY);
#endif

    write(gif->fileDescriptor, "GIF89a", 6);  // gif file signature
    writeNum(gif->fileDescriptor, width);
    writeNum(gif->fileDescriptor, height);
    storeGct = customGct = 0;

    /* taking decision of using GCT or SCT */
    if (palette)
    {
        if (depth < 0)
            storeGct = 1;
        else
            customGct = 1;
    }

    /* for making positive */
    if (depth < 0)
        depth = -depth;

    gif->depth = depth > 1 ? depth : 2;

    write(gif->fileDescriptor,
          (uint8_t []){0xF0 | (depth-1), (uint8_t) backgroundIndex, 0x00}, 3);


    if (customGct)
    {
        write(gif->fileDescriptor, palette, 3 << depth);   // writing 3 byte data
    }
    else if (depth <= 4)
    {
        writeAndStore(storeGct, palette, gif->fileDescriptor, vga, 3 << depth);
    }
    else
    {
        writeAndStore(storeGct, palette, gif->fileDescriptor, vga, sizeof(vga));
        i = 0x10;

        /* creating all possible combination of red, green, blue color */
        for (red = 0; red < 6; red++)
        {
            for (green = 0; green < 6; green++)
            {
                for (blue = 0; blue < 6; blue++)
                {
                    writeAndStore(storeGct, palette, gif->fileDescriptor,
                                    ((uint8_t []){red*51, green*51, blue*51}), 3);

                    if (++i == 1 << depth)
                        goto doneGct;
                }
            }
        }

        /* spreading pixel value of gray scale between the remaining color table */

        for (i = 1; i <= 24; i++)
        {
            v = i * 0xFF / 25;
            writeAndStore(storeGct, palette, gif->fileDescriptor,
                            ((uint8_t []){v, v, v}), 3);
        }
    }

doneGct:
    if (loop >= 0 && loop <= 0xFFFF)
        putLoop(gif, (uint16_t) loop);

    return gif;

}

static void putLoop(GIF *gif, uint16_t loop)
{
    write(gif->fileDescriptor, (uint8_t []){'!', 0xFF, 0x0B}, 3);
    write(gif->fileDescriptor, "NETSCAPE2.0", 11);   // escaping
    write(gif->fileDescriptor, (uint8_t []){0x03, 0x01}, 2);
    writeNum(gif->fileDescriptor, loop);
    write(gif->fileDescriptor, "\0", 1); // ending
}


/* Adding packed key to buffer, updating offset and partial.
 *   gif->offset holds position to put next *bit*  unit part
 *   gif->partial holds bits to include in next byte  large part */


static void putKey(GIF *gif, uint16_t key, int keySize)   // gif,degree,keysize=4
{
    int byteOffset, bitOffset, bitsToWrite;
    byteOffset = gif->offset / 8;
    bitOffset = gif->offset % 8;
    gif->partial |= ((uint32_t) key) << bitOffset;
    bitsToWrite = bitOffset + keySize;

    while (bitsToWrite >= 8)
    {
        gif->buffer[byteOffset++] = gif->partial & 0xFF;

        if (byteOffset == 0xFF)
        {
            write(gif->fileDescriptor, "\xFF", 1);
            write(gif->fileDescriptor, gif->buffer, 0xFF);
            byteOffset = 0;
        }

        gif->partial >>= 8;
        bitsToWrite -= 8;
    }

    gif->offset = (gif->offset + keySize) % (0xFF * 8);  // updating bits offset

}


/* end of writing compression value for one frame */

static void endKey(GIF *gif)
{
    int byteOffset;
    byteOffset = gif->offset / 8;

    if (gif->offset % 8)
        gif->buffer[byteOffset++] = gif->partial & 0xFF;

    if (byteOffset)
    {
        write(gif->fileDescriptor, (uint8_t []){byteOffset}, 1);
        write(gif->fileDescriptor, gif->buffer, byteOffset);
    }

    write(gif->fileDescriptor, "\0", 1);
    gif->offset = gif->partial = 0;
}

static void putImage(GIF *gif, uint16_t w, uint16_t h, uint16_t x, uint16_t y)
{
    int nkeys, keySize, i, j;
    Node *node, *child, *root;
    int degree = 1 << gif->depth;  // depth^2

    write(gif->fileDescriptor, ",", 1);
    writeNum(gif->fileDescriptor, x);
    writeNum(gif->fileDescriptor, y);
    writeNum(gif->fileDescriptor, w);
    writeNum(gif->fileDescriptor, h);

    write(gif->fileDescriptor, (uint8_t []){0x00, gif->depth}, 2);

    root = node = newTrie(degree, &nkeys);

    keySize = gif->depth + 1;

    putKey(gif, degree, keySize); /* clear code */

    for (i = y; i < y+h; i++)
    {
        for (j = x; j < x+w; j++)
        {
            uint8_t pixel = gif->frame[i*gif->widthOfScreen+j] & (degree - 1);
            child = node->children[pixel];
            if (child)
            {
                node = child;
            }
            else
            {
                putKey(gif, node->key, keySize);
                if (nkeys < 0x1000)
                {
                    if (nkeys == (1 << keySize))
                        keySize++;
                    node->children[pixel] = newNode(nkeys++, degree);
                }
                else
                {
                    putKey(gif, degree, keySize); /* clear code */
                    deleteTrie(root, degree);
                    root = node = newTrie(degree, &nkeys);
                    keySize = gif->depth + 1;
                }
                node = root->children[pixel];
            }
        }
    }

    putKey(gif, node->key, keySize);
    putKey(gif, degree + 1, keySize); /* stop code */
    endKey(gif);
    deleteTrie(root, degree);

}

/* bounding box */
static int getBoundingBox(GIF *gif, uint16_t *w, uint16_t *h, uint16_t *x, uint16_t *y)
{
    int i, j, k;
    int left, right, top, bottom;
    uint8_t back;

    left = gif->widthOfScreen;
    right = 0;
    top = gif->heightOfScreen;
    bottom = 0;

    k = 0;
    for (i = 0; i < gif->heightOfScreen; i++)
    {
        for (j = 0; j < gif->widthOfScreen; j++, k++)
        {
            /* from back array as no background index is stored */
            back = gif->backgroundIndex >= 0 ? gif->backgroundIndex : gif->back[k];
            if (gif->frame[k] != back)
            {
                if (j < left)
                    left    = j;
                if (j > right)
                    right   = j;
                if (i < top)
                    top     = i;
                if (i > bottom)
                    bottom  = i;

            }
        }
    }

    if (left != gif->widthOfScreen && top != gif->heightOfScreen)
    {
        *x = left;
        *y = top;
        *w = right - left + 1;
        *h = bottom - top + 1;
        return 1;
    }
    else
    {
        return 0;
    }
}

static void addGraphicsControlExtension(GIF *gif, uint16_t delay)
{
    uint8_t flags = ((gif->backgroundIndex >= 0 ? 2 : 1) << 2) + 1;

    write(gif->fileDescriptor, (uint8_t []){'!', 0xF9, 0x04, flags}, 4);  // 4 byte block

    /* writing delay */
    writeNum(gif->fileDescriptor, delay);

    /* writing background index stored previously, no transparency */
    write(gif->fileDescriptor, (uint8_t []){(uint8_t) gif->backgroundIndex, 0x00}, 2);

}

void addFrame(GIF *gif, uint16_t delay)   // second function for drawing each frame
{
    uint16_t w, h, x, y;
    uint8_t *temp;

    if (delay || (gif->backgroundIndex >= 0))
        addGraphicsControlExtension(gif, delay);

    if (gif->numberOfFrames == 0)
    {
        w = gif->widthOfScreen;
        h = gif->heightOfScreen;
        x = y = 0;
    }
    else if (!getBoundingBox(gif, &w, &h, &x, &y))
    {
        /* image's not changed; saving one pixel just to add delay */
        /* no bounding box is needed */
        w = h = 1;
        x = y = 0;
    }

    putImage(gif, w, h, x, y);

    gif->numberOfFrames++;

    if (gif->backgroundIndex < 0)
    {
        temp = gif->back;
        gif->back = gif->frame;
        gif->frame = temp;
    }
}


/* trailer */
void closeGif(GIF* gif)
{
    write(gif->fileDescriptor, ";", 1);
    close(gif->fileDescriptor);
    free(gif);
}




