#include<bits/stdc++.h>
#include<fstream>
#include<iostream>

#include "header.h"

using namespace std;

int checkingTextFile(string imageFile,string textFile)
{
    /** gaining image height and width **/
    ifstream inputFile;
    inputFile.open(imageFile.c_str(),ios::binary);

    struct BMPSignature bmpsignature;
    struct BitMapHeader bitmapheader;
    struct DIBHeader dibheader;

    inputFile.read((char *)&bmpsignature,sizeof(bmpsignature));
    inputFile.read((char *)&bitmapheader,sizeof(bitmapheader));
    inputFile.read((char *)&dibheader,sizeof(dibheader));

    int imageHeight=dibheader.height;
    int imageWidth=dibheader.width;


    /** text file section **/

    FILE *fp1=fopen(textFile.c_str(),"r");
    if(fp1==NULL)
    {
        printf("Error opening file %s", textFile.c_str());
        return 0;
    }

    /** checking text file size **/
    long long int textFileSize;
    int countCharacter=0;
    char ch;

    while((ch=fgetc(fp1)!=EOF))
    {
        countCharacter++;
    }

    fclose(fp1);


    textFileSize=countCharacter*8;

    /** checking available space in bits for hiding these text file.**/

    if((imageHeight * imageWidth *3)>(textFileSize+32))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
