#include<fstream>
#include<iostream>

#include "header.h"

using namespace std;

int hidingData(string imageFile,string textFile)
{
    /** text file to binary stream **/

    vector<int> binaryStream=textToBinary(textFile);
    //cout<<binaryStream.size()<<"\n";


    /** image read and copy information **/

    struct BitMapHeader bitmapheader;
    struct DIBHeader dibheader;
    struct RGB rgb;
    struct bmpColorTable bmpcolortable;
    struct BMPSignature bmpsignature;

    ifstream inputFile;
    ofstream outputFile;

    inputFile.open(imageFile,ios::binary);
    outputFile.open("stegoBMP.bmp",ios::binary);

    inputFile.read((char *)&bmpsignature,sizeof(bmpsignature));
    inputFile.read((char *)&bitmapheader,sizeof(bitmapheader));
    inputFile.read((char *)&dibheader,sizeof(dibheader));
    inputFile.read((char *)&rgb,sizeof(rgb));

    outputFile.write((char *)&bmpsignature,sizeof(bmpsignature));
    outputFile.write((char *)&bitmapheader,sizeof(bitmapheader));
    outputFile.write((char *)&dibheader,sizeof(dibheader));
    outputFile.write((char *)&rgb,sizeof(rgb));

    int height=dibheader.height;
    int width=dibheader.width;

    //cout<<"height "<<height<<" and width "<<width<<"\n";

    int*** pixels = new int** [height];
    for(int i = 0; i<height; i++)
    {
        pixels[i] = new int* [width];
        for(int j = 0; j<width; j++)
        {
            pixels[i][j] = new int[3];
        }
    }

    inputFile.seekg(bitmapheader.imageOffset,ios::beg);
    outputFile.seekp(bitmapheader.imageOffset,ios::beg);

    for(int i=0; i<height; i++)
    {
        for(int j=0; j<width; j++)
        {
            unsigned char color[3];
            inputFile.read(reinterpret_cast<char*>(color),3);
            pixels[i][j][0] = static_cast<float>(color[2]); //red
            pixels[i][j][1] = static_cast<float>(color[1]); //green
            pixels[i][j][2] = static_cast<float>(color[0]); //blue
        }
    }


    /** doing pixel decimal value to bin and embedding text binary value together **/
    int p=0;
    int sizeOfStream=binaryStream.size();
    sizeOfStream--;
    bool ok=false;

    for(int i=0; i<height; i++)
    {
        for(int j=0; j<width; j++)
        {
            int c=0;
            while(c<3)
            {
                 if(p==sizeOfStream)
                 {
                     ok=true;
                     break;
                 }
                int quotient=pixels[i][j][c];
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

                binary[7]=binaryStream[p];
                p++;

                /** bin to int **/
                int power=0;
                pixels[i][j][c]=0;
                //cout<<"show now"<<" "<<pixels[i][j][c]<<"\n";
                for(int t=0; t<8; t++)
                {
                    pixels[i][j][c]+=(binary[t]*pow(2,(7-t)));
                }

                c++;
            }
            if(ok) break;
        }
        if(ok) break;
    }


    /** writing the image **/
     for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            unsigned char color[3];
            color[0] = static_cast<unsigned char>(pixels[i][j][2]);
            color[1] = static_cast<unsigned char>(pixels[i][j][1]);
            color[2] = static_cast<unsigned char>(pixels[i][j][0]);
            outputFile.write(reinterpret_cast<char*>(color),3);
        }
    }

    inputFile.read((char*)&bmpcolortable,sizeof(bmpcolortable));
    outputFile.write((char*)&bmpcolortable,sizeof(bmpcolortable));

    inputFile.close();
    outputFile.close();

    return 1;
}
