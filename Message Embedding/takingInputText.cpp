#include<bits/stdc++.h>
#include "header.h"

using namespace std;

void processInputText(string textFile)
{
    FILE *fp=fopen(textFile.c_str(),"w");
    if(fp==NULL)
    {
        printf("Error in creating file %s", textFile.c_str());
        return exit(1);
    }

    getchar();

    string text;
    getline(cin,text);

   // char* s;
    //s=text;

    const char* s = text.c_str();

    while(*s)
    {
        if(fputc(*s,fp)==EOF)
        {
            cout<<"error in writing file";
            cout<<"\n";
            EXIT_FAILURE;
        }
        s++;
    }

    fclose(fp);

}

