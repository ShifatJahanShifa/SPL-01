#include<bits/stdc++.h>
#include "header.h"

using namespace std;


/** case 01 **/
int checkingImageFormat(string fileName)
{
    string subName;
    char ch;
    int i=fileName.size()-1;

    while(fileName[i]!='.')
    {
        subName+=fileName[i];
        i--;
    }

    reverse(subName.begin(),subName.end());

    if(subName=="bmp")
    {
        return 1;
    }
    else
    {
        cout<<"not a bmp image file.";
        cout<<"\n";
        return 0;
    }
}
