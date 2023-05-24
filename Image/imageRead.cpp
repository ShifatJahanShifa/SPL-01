#include<bits/stdc++.h>
using namespace std;

struct BitMapHeader{
    char name[2];   /// this should be equal BM
    unsigned int Size;   /// os sizeof(int)=4 bytes
    int garbage;    /// this is not required
    unsigned int imageOffset;    /// from where the image starts

};

struct DIBHeader{
    unsigned int headerSize;   /// header size
    unsigned int height;
    unsigned int width;
    unsigned short int colorPlanes;
    unsigned short int bitsPerPixel;
    unsigned int compression;
    unsigned int imageSize;

};
void openbmpfile()
{
    FILE *fp=fopen("bmpPic.bmp","rb");
    /// first h
    struct BitMapHeader bmpheader;
    //printf("%d\n",sizeof(struct BitMapHeader));

    fread(bmpheader.name,2,1,fp);
    fread(&bmpheader.Size,3*sizeof(int),1,fp);
    printf("size: %d\n",bmpheader.Size);
    printf("offset: %d\n",bmpheader.imageOffset);
    //fread(&bmpheader,sizeof(struct BitMapHeader),1,fp);/// where to store
    printf("first two characters: %c%c \n",bmpheader.name[0],bmpheader.name[1]);



    /// second h
    struct DIBHeader dibheader;
    fread(&dibheader,sizeof(struct DIBHeader),1,fp);
    printf("header size: %d\nwidth: %d\nheight: %d",dibheader.headerSize,dibheader.width,dibheader.height);
    printf("\ncolorplanes: %d\nbitspersecond: %d\ncompression: %d\nimagesize: %d\n",dibheader.colorPlanes,dibheader.bitsPerPixel,dibheader.compression,dibheader.imageSize);
    fclose(fp);  /// dekhbo
}
int main()
{
   // printf("%d \n",sizeof(unsigned short int));
    openbmpfile();
}

