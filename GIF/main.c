#include "gifenc.h"

int main()
{
    int i, j;
    int widthOfScreen = 120, heightOfScreen = 130;

    /* create a GIF */
    GIF *gif = newGif(
                   "GIF.gif",  /* file name */
                   widthOfScreen, heightOfScreen,           /* canvas size */
                   (uint8_t [])    /* palette */
    {
        //0x11, 0x11, 0x11, /* 0 -> black */
        //0xF1, 0x00, 0x00, /* 1 -> red */
        //0x00, 0xF4, 0x00, /* 2 -> green */
        //0x00, 0x00, 0xFA, /* 3 -> blue */
        //0xC8, 0xC8, 0xC8, /* cyan */

              0xFF, 0xFF, 0xFF, /* 0 -> white */
              0x00, 0x00, 0x00, /* 1 -> black */
              0xFF, 0x00, 0x00, /* 2 -> red */
              0x00, 0xFF, 0x00, /* 3 -> green */
              0x00, 0x00, 0xFF, /* 4 -> blue */
              0xFF, 0xFF, 0x00, /* 5 -> yellow */
              0xFF, 0x00, 0xFF, /* 6 -> magenta */
              0x00, 0xFF, 0xFF  /* 7 -> cyan */

    },
                    3,              /* palette depth == log2(# of colors) */
                    -1,             /* no transparency */
                    0               /* infinite loop , won't stop*/
               );

    /* drawing some frames */
    for (i = 0; i < 8; i++)
    {
        for (j = 0; j < widthOfScreen*heightOfScreen; j++)
            gif->frame[j] = (i*3 + j) / 6 % 8;
        addFrame(gif, 10);
    }

    /* closing the GIF */
    closeGif(gif);

    return 0;
}
