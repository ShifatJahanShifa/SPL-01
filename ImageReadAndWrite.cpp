#include<bits/stdc++.h>
#include <iomanip>
#include <fstream>
#include "BmpStructure.cpp"
using namespace std;

struct Image readImage(FILE *fp,int height,int width)
{
    struct Image pic;
    pic.height=height;
    pic.width=width;

    long int pos=ftell(fp);
    printf("current position of pointer while writing = %ld\n",pos);

    /// allocating memory
    pic.rgb=(struct RGB**) malloc(height*sizeof(void*));
    for(int i=0;i<height;i++)
    {
        pic.rgb[i] = (struct RGB*)malloc(width * sizeof(struct RGB));
        if(pic.rgb[i] == NULL)
        {
            cout << "Error allocating memory" << endl;
            exit(1);
        }
        size_t elements_read = fread(pic.rgb[i], sizeof(struct RGB),width, fp);

        /// for debugging purposes
       /* if(elements_read < width)
        {
            printf("%d\n",elements_read);

            cout << "Error reading image" << endl;
           // exit(1);
        }*/

    }

    return pic;
}


void freeImage(struct Image &pic)
{
    for(int i=0;i<pic.height;i++)
    {
        free(pic.rgb[i]);
    }

    free(pic.rgb);

    pic.rgb = NULL;
    pic.height = 0;
    pic.width = 0;
}


int writeImage(struct BitMapHeader bmpheader,struct DIBHeader dibheader,struct Image pic)
{
    FILE *fp1=fopen("CopyFirstImage.bmp","wb");

    if(fp1==NULL)
    {
        puts("sorry! we couldn't open the image file");
        fclose(fp1);
        exit(1);
    }

    /// bmp header writing
    fwrite(bmpheader.name,2,1,fp1);
    fwrite(&bmpheader.Size,3*sizeof(int),1,fp1);

    /// dib header writing
    fwrite(&dibheader,sizeof(struct DIBHeader),1,fp1);

    /// taking to the right position
    fseek(fp1,bmpheader.imageOffset,SEEK_SET);

    size_t elements_written;
    for(int i = 0; i <pic.height; i++)
    {
        elements_written = fwrite(pic.rgb[i], sizeof(struct RGB), pic.width, fp1);
        if(elements_written < pic.width)
        {
            cout << "Error writing image" << endl;
            exit(1);
        }
    }

    printf("byte of written: %d\n",elements_written);

    fclose(fp1);

    return 0;
}


void openbmpfile()
{
    FILE *fp=fopen("bmpPic.bmp","rb");

    if(fp==NULL)
    {
        puts("sorry! we couldn't find the image file");
        fclose(fp);
        exit(1);
    }

    /// first header
    struct BitMapHeader bmpheader;
    fread(bmpheader.name,2,1,fp);
    fread(&bmpheader.Size,3*sizeof(int),1,fp);

    if(bmpheader.name[0]!='B' || bmpheader.name[1]!='M')
    {
        puts("sorry! we are not working with this type bmp image");
        fclose(fp);
        exit(1);
    }

    puts("here are the information of BitMapHeader of the bmp file");
    printf("first two characters: %c%c \n",bmpheader.name[0],bmpheader.name[1]);
    printf("size of the bmp file: %d\n",bmpheader.Size);
    printf("offset: %d\n",bmpheader.imageOffset);


    /// second header
    struct DIBHeader dibheader;
    fread(&dibheader,sizeof(struct DIBHeader),1,fp);

    if(dibheader.compression!=0 || dibheader.bitsPerPixel!=24 || dibheader.colorPlanes!=1)
    {
        puts("sorry! we are not working with this type image");
        fclose(fp);
        exit(1);
    }

    puts("here are the information of DIBHeader of the bmp file");
    printf("header size: %d\nwidth: %d\nheight: %d",dibheader.headerSize,dibheader.width,dibheader.height);
    printf("\ncolorplanes: %d\nbitsperpixel: %d\ncompression: %d\nimagesize: %d\n",dibheader.colorPlanes,dibheader.bitsPerPixel,dibheader.compression,dibheader.imageSize);
    printf("DIB header size: %d\n",sizeof(struct DIBHeader));

    fseek(fp,bmpheader.imageOffset,SEEK_SET);
    long int pos=ftell(fp);
    printf("current position of pointer while reading= %ld\n",pos);

    /// return a copy of the image info
    struct Image image=readImage(fp,dibheader.height,dibheader.width);
    fclose(fp);

    /// write the image into another file
    writeImage(bmpheader,dibheader,image);

    /// freeing the memory space
    freeImage(image);
}

int main()
{
    puts("let's read a bmp file and make a copy of it( *-* )");
    openbmpfile();

    return 0;
}
