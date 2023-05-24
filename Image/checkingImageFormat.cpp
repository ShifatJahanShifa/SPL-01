#include<bits/stdc++.h>
#include<fstream>
#include<iomanip>
#include "header.h"

using namespace std;

int checkingImageFormat(string imageFile)
{
    ifstream inputFile;
    inputFile.open(imageFile.c_str(),ios::binary);


    struct BMPSignature bmpsignature;
    struct BitMapHeader bitmapheader;
    struct DIBHeader dibheader;

    inputFile.read((char *)&bmpsignature,sizeof(bmpsignature));
    inputFile.read((char *)&bitmapheader,sizeof(bitmapheader));
    inputFile.read((char *)&dibheader,sizeof(dibheader));

    inputFile.close();


    /** case 01 **/
    /** checking whether a bmp image or not **/

    if(bmpsignature.name[0]!='B' or bmpsignature.name[1]!='M')
    {
        return 0;
    }


    /** case 02 **/
    /** checking colorplanes, bitsperpixel and compression value.
        for bmp 24 bit color,
            -> colorplanes=1,
            -> bitsperpixel=24,
            -> compression value=0
    **/

    if(dibheader.colorPlanes!=1 or dibheader.bitsPerPixel!=24 or dibheader.compression!=0)
    {
        return 0;
    }

    return 1;
}
