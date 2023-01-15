#include<stdio.h>
#include<stdlib.h>
//#include <iomanip>
//#include <fstream>
//#pragma pack (push,2)


struct BitMapHeader{
    char name[2];   /// this should be equal BM
    unsigned int Size;   /// os sizeof(int)=4 bytes,
    unsigned short int reserved1;    /// this is not required
    unsigned short int reserved2;    /// this is not required
    unsigned int imageOffset;    /// from where the image starts
    /*unsigned int fileSize{0}; //filesize in byte
    unsigned short reserved1{0}; //reserved
    unsigned short reserved2{0}; //reserved
    unsigned int dataOffset{0}; //start of pixel data*/
};

struct DIBHeader{
    unsigned int headerSize;   /// header size
    unsigned int height;
    unsigned int width;
    unsigned short int colorPlanes;
    unsigned short int bitsPerPixel;
    unsigned int compression;
    unsigned int imageSize;
   /* unsigned int temp[4];

    unsigned int headerSize{0}; //headersize in byte
    unsigned int width{0}; //image width in px
    unsigned int height{0}; //image height in px
    unsigned short planes{1};  //number of planes
    unsigned short bpPixels{0}; //number of bits per pixel
    unsigned int compression{0}; //compression type 0 is uncompressed
    unsigned int imageSize{0};*/
    unsigned int pixelPerMeterX; //pixel per meter along x axis
    unsigned int pixelPerMeterY; //pixel per meter along y axis
    unsigned int colorsInColorTable; //number of colors in color table
    unsigned int importantcolorCount; //number of colors used

   /* unsigned short int res{0};
    unsigned short int pad{0};
    unsigned short int orig{0};
    unsigned short int haft{0};
    unsigned int hp1{0};
    unsigned int hp2{0};
    unsigned int ce{0};
    unsigned int iden{0};*/


};

/*struct RGB{
    unsigned int blue{0x000000ff};
    unsigned int green{0x0000ff00};
    unsigned int red{0x00ff0000 };
    unsigned int alpha{0xff000000}; //alpha channel bitmask
    unsigned int color{0x73524742};    //color space type usually sRGB default
};

//contains bmp color table information
struct bmpColorTable
{
    unsigned int colorDefinition[256];
};
//#pragma pack(pop)*/

struct RGB{           /// pixel information
    unsigned char blue;
    unsigned char green;
    unsigned char red;
    //unsigned char others;

};

struct Image{          /// image info
    int height;
    int width;
    struct RGB **rgb;
};

struct Image readImage(FILE *fp,int height,int width)
{
    struct Image pic;
    //width-=50;
   // height-=100;
    pic.height=height;
    pic.width=width;
    pic.rgb=(struct RGB**) malloc(height*sizeof(void*));

    printf("height: %d  %d \n",height,width);

    for(int i=height-1;i>=0;i--)
    {
        pic.rgb[i]=(struct RGB*) malloc(width*sizeof(struct RGB));
        fread(pic.rgb[i],width,sizeof(struct RGB),fp);
    }

    return pic;
}

void freeImage(struct Image pic)
{
    for(int i=pic.height-1;i>=0;i--)
    {
        free(pic.rgb[i]);
    }

    free(pic.rgb);
}

int writeimage(struct BitMapHeader bmpheader,struct DIBHeader dibheader,struct Image pic)
{
    FILE *fp1=fopen("copyplz.bmp","w");

    if(fp1==NULL)
    {
        puts("sorry! we couldn't open the image file");
        fclose(fp1);
        exit(1);
    }

    /// bmp header
    fwrite(bmpheader.name,2,1,fp1);
    fwrite(&bmpheader.Size,3*sizeof(int),1,fp1);

    /// bidheader
    fwrite(&dibheader,sizeof(struct DIBHeader),1,fp1);
    //pic.width-=10;
     printf("height: %d  %d \n",pic.height,pic.width);

    for(int i=pic.height-1;i>=50;i--)
    {
        fwrite(pic.rgb[i],pic.width,sizeof(struct RGB),fp1);
    }

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

    printf("first two characters: %c%c \n",bmpheader.name[0],bmpheader.name[1]);
    printf("size of the bmp file: %d\n",bmpheader.Size);
    printf("offset: %d\n",bmpheader.imageOffset);


    /// second h
    struct DIBHeader dibheader;
    fread(&dibheader,sizeof(struct DIBHeader),1,fp);

    /*if(dibheader.compression!=0 || dibheader.bitsPerPixel!=24 || dibheader.colorPlanes!=1)
    {
        puts("sorry! we are not working with this type image");
        fclose(fp);
        exit(1);
    }*/

    printf("header size: %d\nwidth: %d\nheight: %d",dibheader.headerSize,dibheader.width,dibheader.height);
    printf("\ncolorplanes: %d\nbitsperpixel: %d\ncompression: %d\nimagesize: %d\n",dibheader.colorPlanes,dibheader.bitsPerPixel,dibheader.compression,dibheader.imageSize);
   // dibheader.height-=50;;
    fseek(fp,bmpheader.imageOffset,SEEK_SET);
    struct Image image=readImage(fp,dibheader.height,dibheader.width);
    writeimage(bmpheader,dibheader,image);

    fclose(fp);
    freeImage(image);
}
int main()
{
    openbmpfile();

    return 0;
}

