#include<bits/stdc++.h>
#include<ctime>

#include "header.h"

using namespace std;

vector<int> textToBinary(string textFile)
{
    /** file opening **/
    FILE *fp1=fopen(textFile.c_str(),"r");

    /** checking text file size **/
    long long int textFileSize;

    string text;
    int countCharacter=0;
    char ch;
    while((ch=fgetc(fp1)!=EOF))
    {
       countCharacter++;
    }

    textFileSize=countCharacter*8;

    /*cout<<"text file size in bits"<<"\n";
    cout<<"size: "<<textFileSize<<"\n";
    cout<<"total character: "<<countCharacter<<"\n";*/


    /** section of conversion **/
    rewind(fp1);
   // cout<<ftell(fp)<<"\n";
    int decimal=0;
    int index=0;
    int quotient;
    int remainder;
    int i;
    vector<int>bits;

    while((ch=fgetc(fp1))!=EOF)
    {
        decimal=ch;
        quotient=decimal;
        i=7;

        while(quotient)
        {
            remainder=quotient%2;
            bits.push_back(remainder);
            i--;
            quotient/=2;
        }

        while(i>=0)
        {
            bits.push_back(0);
            i--;
        }
    }

    return bits;
}

