#include<fstream>
#include<iostream>
#include<windows.h>
#include "header.h"

using namespace std;

void extractingData(string imageFile)
{
    /** image read and copy information **/

    struct BitMapHeader bitmapheader;
    struct DIBHeader dibheader;
    struct RGB rgb;
    struct bmpColorTable bmpcolortable;
    struct BMPSignature bmpsignature;

    ifstream inputFile;

    inputFile.open(imageFile,ios::binary);

    inputFile.read((char *)&bmpsignature,sizeof(bmpsignature));
    inputFile.read((char *)&bitmapheader,sizeof(bitmapheader));
    inputFile.read((char *)&dibheader,sizeof(dibheader));
    inputFile.read((char *)&rgb,sizeof(rgb));


    int height=dibheader.height;
    int width=dibheader.width;

    int*** pixels2 = new int** [height];
    for(int i = 0; i<height; i++)
    {
        pixels2[i] = new int* [width];
        for(int j = 0; j<width; j++)
        {
            pixels2[i][j] = new int[3];
        }
    }

    inputFile.seekg(bitmapheader.imageOffset,ios::beg);

    for(int i=0; i<height; i++)
    {
        for(int j=0; j<width; j++)
        {
            unsigned char color[3];
            inputFile.read(reinterpret_cast<char*>(color),3);
            pixels2[i][j][0] = static_cast<float>(color[2]); //red
            pixels2[i][j][1] = static_cast<float>(color[1]); //green
            pixels2[i][j][2] = static_cast<float>(color[0]); //blue
        }
    }


    /** doing pixel decimal value to binary and extracting info **/
    int p=0;

    bool ok=false;

    int a,b,c,d;
    int tempBin[32];
    for(a=0; a<height; a++)
    {
        for(b=0; b<width; b++)
        {
            d=0;
            while(d<3)
            {
                if(p==32)
                {
                    ok=true;
                    break;
                }
                int quotient=pixels2[a][b][d];
               // cout<<"*"<<quotient<<"\n";
                int remainder;
                int binary[8];
                int k=7;
                while(quotient)
                {
                    remainder=quotient%2;
                    binary[k]=remainder;
                    k--;
                    quotient/=2;
                }

                while(k>=0)
                {
                    binary[k]=0;
                    k--;
                }

                tempBin[p]=binary[7];
                p++;

                /** bin to int, leaving the stego image as it is **/
                int power=0;
                pixels2[a][b][d]=0;
                //cout<<"show now"<<" "<<pixels[i][j][c]<<"\n";
                for(int t=0; t<8; t++)
                {
                    pixels2[a][b][d]+=(binary[t]*pow(2,(7-t)));
                }

                d++;
            }
            if(ok)
                break;
        }
        if(ok)
            break;
    }

    int countOfBits=binaryToDecimal(tempBin,32);
   // cout<<countOfBits<<" size \n";
    //cout<<"a b d"<<a<<b<<" "<<d<<"\n";

   // cout<<"show "<<countOfBits<<"\n";
    if(countOfBits<=0 or countOfBits>((height*width*3)-32))
        cout<<"No message is hidden in this image\n\n";

    else{
    /** retrieving data **/
    bool cnt=true;
    ok=false;
    p=0;
    vector<int>binaryValue;
    int octet=0;
    countOfBits/=8;
    int decimalValueArray[countOfBits]={0};
    int track=0;
    vector<char>storeCharacter;
    countOfBits*=8;


    for(int i=a; i<height; i++)
    {
        for(int j=b; j<width; j++)
        {
            if(cnt==true and d!=0)
            {
                c=d;
                cnt=false;
            }
            else
            {
                c=0;
            }
            while(c<3)
            {
                if(p==countOfBits)
                {
                    ok=true;
                    break;
                }

                int quotient=pixels2[i][j][c];
              //  cout<<"#extracting "<<quotient<<" ";
                int remainder;
                int binary[8];
                int k=7;
                while(quotient)
                {
                    remainder=quotient%2;
                    binary[k]=remainder;
                    k--;
                    quotient/=2;
                }

                while(k>=0)
                {
                    binary[k]=0;
                    k--;
                }

                binaryValue.push_back(binary[7]);
                p++;
                octet++;

                /** keep the stego image as it is **/
                pixels2[i][j][c]=0;

                for(int t=0; t<8; t++)
                {
                    pixels2[i][j][c]+=(binary[t]*pow(2,(7-t)));
                }

                if(octet==8)
                {
                    octet=0;
                    /*for(int t=0;t<binaryValue.size();t++)
                    {
                        cout<<binaryValue[t]<<" ";
                    }
                    puts("");*/

                    for(int t=0; t<8; t++)
                    {
                        decimalValueArray[track]+=(binaryValue[t]*pow(2,(7-t)));
                    }

                    //cout<<decimalValueArray[track]<<" value\n";
                    char ch=decimalValueArray[track];
                    storeCharacter.push_back(ch);
                    track++;
                    binaryValue.clear();
                }
                //cout<<" vector size "<<binaryValue.size()<<"\n";
                c++;
            }
            if(ok)
                break;
        }
        if(ok)
            break;
    }

    string hiddenMessage;

    for(int i=0; i<storeCharacter.size(); i++)
    {
        hiddenMessage+=storeCharacter[i];
    }

    puts("The hidden message : ");

    cout<<hiddenMessage<<"\n";
    cout<<"\n\n";
    }
}
