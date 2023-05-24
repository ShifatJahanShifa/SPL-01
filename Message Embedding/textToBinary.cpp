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
        int tempArray[8];

        while(quotient)
        {
            remainder=quotient%2;
            tempArray[i]=remainder;
            i--;
            quotient/=2;
        }

        while(i>=0)
        {
            tempArray[i]=0;
            i--;
        }

       //cout<<ch<<" ";
        for(int t=0;t<8;t++)
        {
            bits.push_back(tempArray[t]);
        }
    }

    return bits;
}

