#include<iostream>
#include<cstdio>
#pragma pack (push,1)


struct BitMapHeader{
    char name[2];   /// this should be equal BM
    unsigned int Size;   /// os sizeof(int)=4 bytes,
    unsigned short int reserved1;    /// this is not required
    unsigned short int reserved2;    /// this is not required
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
    unsigned int xResolutionPPM;
    unsigned int yResolutionPPM;
    unsigned int numberOfColors;
    unsigned int importantColors;
};

#pragma pack(pop)
using namespace std;

struct RGB{           /// pixel information
    unsigned char blue;
    unsigned char green;
    unsigned char red;
    unsigned char others[8];

};

struct Image{          /// image info
    int height;
    int width;
    struct RGB **rgb;
    //struct RGB ;
};

struct Image readImage(FILE *fp,int size1,int height,int width)
{
    struct Image pic;
    pic.height=height;
    pic.width=width;
    //pic.rgb=(struct RGB**) malloc(height*sizeof(void*));
    int *data=new int(size1);
    for(int i=0;i<size1;i++)
    {
        //pic.rgb[i]=(struct RGB*) malloc(width*sizeof(struct RGB));

        //fread(pic.rgb[i],width,sizeof(struct RGB),fp);
        data[i]=fgetc(fp);
    }

    return pic;
}

void freeImage(struct Image pic)
{
    for(int i=pic.height-1;i>-1;i--)
    {
        free(pic.rgb[i]);
    }

    free(pic.rgb);
}

void writeimage(struct BitMapHeader bmpheader,struct DIBHeader dibheader,struct Image pic)
{
    FILE *fp1=fopen("copym.bmp","wb");

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

    for(int i=pic.height-1;i>-1;i--)
    {
        fwrite(pic.rgb[i],pic.width,sizeof(struct RGB),fp1);
    }

    fclose(fp1);
}

void openbmpfile()
{
    FILE *fp=fopen("bmpPic.bmp","rb");
    FILE *fp1=fopen("out.bmp","w");

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

    if(dibheader.compression!=0 || dibheader.bitsPerPixel!=24 || dibheader.colorPlanes!=1)
    {
        puts("sorry! we are not working with this type image");
        fclose(fp);
        exit(1);
    }

    printf("header size: %d\nwidth: %d\nheight: %d",dibheader.headerSize,dibheader.width,dibheader.height);
    printf("\ncolorplanes: %d\nbitsperpixel: %d\ncompression: %d\nimagesize: %d\n",dibheader.colorPlanes,dibheader.bitsPerPixel,dibheader.compression,dibheader.imageSize);

    /// bmp header
    fwrite(bmpheader.name,2,1,fp1);
    fwrite(&bmpheader.Size,3*sizeof(int),1,fp1);

    /// bidheader
    fwrite(&dibheader,sizeof(struct DIBHeader),1,fp1);

    fseek(fp,bmpheader.imageOffset,SEEK_SET);

    int *data=new int(dibheader.imageSize);
    for(int i=0;i<dibheader.imageSize;i++)
    {
        data[i]=fgetc(fp);
    }
    for(int i=0;i<dibheader.imageSize;i++)
    {
        fputc(data[i],fp1);
    }
    fclose(fp);
    fclose(fp1);
   /* struct Image image=readImage(fp,dibheader.imageSize,dibheader.height,dibheader.width);
    writeimage(bmpheader,dibheader,image);

    fclose(fp);
    freeImage(image);*/
}
int main()
{
    openbmpfile();

    return 0;
}

