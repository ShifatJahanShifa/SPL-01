#include<bits/stdc++.h>
#include<ctime>

//#include "ImageReadAndWrite.cpp"

using namespace std;

int main()
{
    /// file opening
    puts("please open the text file");

    FILE *fp=fopen("text.txt","r");
    if(fp==NULL)
    {
        puts("sorry, couldn't open the file");
        exit(1);
    }


    /// checking text file size
    long long int textFileSize;

    string text;
    int countCharacter=0;
    char ch;
    while((ch=fgetc(fp)!=EOF))
    {
       countCharacter++;
    }

    textFileSize=countCharacter*8;

    cout<<"text file size in bits"<<"\n";
    cout<<textFileSize<<"\n";
    cout<<countCharacter<<"\n";


    /// checking available space in bits for hiding these text file.
    /**if((image.height * image.width *3)>textFileSize)
    {
        cout<<"possible to hide the text file."<<"\n";
    }
    else
    {
        cout<<"not possible to hide the text file within this image size."<<"\n";
    }
    **/
   /// FILE *fp1=fopen("sample.txt","wb");


    /// section of conversion
    rewind(fp);
    cout<<ftell(fp)<<"\n";
    int decimal;
    int index=0;
    int quotient;
    int remainder;

    char binary[countCharacter][8];

    while((ch=fgetc(fp))!=EOF)
    {
        decimal=ch;
        cout<<decimal<<"\n";
        quotient=decimal;

        int i=7;
        while(quotient)
        {
            remainder=quotient%2;
            binary[index][i]='0'+remainder;
            i--;
            quotient/=2;
        }

        if(i>-1)
        {
            binary[index][i]='0';
            i--;
        }

        index++;
    }

    for(int i=0;i<countCharacter;i++)
    {
        for(int j=0;j<8;j++)
            cout<<binary[i][j]<<" ";

        cout<<"\n";
    }

}
