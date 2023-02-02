#include<bits/stdc++.h>
#include<fstream>
#include<iostream>

#include "header.h"

using namespace std;

int checkingTextFile(string imageFile,string textFile)
{
    /********* at first gaining image height and width **********/

    FILE *fp=fopen(imageFile.c_str(),"rb");
    if (fp == NULL)
    {
        printf("Error opening file %s", imageFile.c_str());
        return 0;
    }


    /********** first header ************/
    struct BitMapHeader bmpheader;

    fread(bmpheader.name,2,1,fp);
    fread(&bmpheader.Size,3*sizeof(int),1,fp);

    //printf("size: %d\n",bmpheader.Size);
    //printf("offset: %d\n",bmpheader.imageOffset);
    //fread(&bmpheader,sizeof(struct BitMapHeader),1,fp);/// where to store
    // printf("first two characters: %c%c \n",bmpheader.name[0],bmpheader.name[1]);


    /************second header **************/
    struct DIBHeader dibheader;

    fread(&dibheader,sizeof(struct DIBHeader),1,fp);

    //printf("header size: %d\nwidth: %d\nheight: %d",dibheader.headerSize,dibheader.width,dibheader.height);
    // printf("\ncolorplanes: %d\nbitspersecond: %d\ncompression: %d\nimagesize: %d\n",dibheader.colorPlanes,dibheader.bitsPerPixel,dibheader.compression,dibheader.imageSize);

    fclose(fp);


    /**********text file section ***********/

    FILE *fp1=fopen(textFile.c_str(),"r");
    if(fp1==NULL)
    {
        printf("Error opening file %s", imageFile.c_str());
        return 0;
    }

    /*********** checking text file size ************/
    long long int textFileSize;
    int countCharacter=0;
    char ch;

    while((ch=fgetc(fp1)!=EOF))
    {
        countCharacter++;
    }

    fclose(fp1);


    textFileSize=countCharacter*8;

    cout<<"text file size in bits"<<"\n";
    cout<<"size: "<<textFileSize<<"\n";
    cout<<"total character: "<<countCharacter<<"\n";



    /************* checking available space in bits for hiding these text file.***************/

    if((dibheader.height * dibheader.width *3)>textFileSize)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
