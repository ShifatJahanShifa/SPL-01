#include<bits/stdc++.h>
#include<ctime>
using namespace std;

int main()
{
    puts("please open the text file");

    FILE *fp=fopen("text.txt","rb");
    if(fp==NULL)
    {
        puts("sorry, couldn't open the file");
        exit(1);
    }

    FILE *fp1=fopen("sample.txt","wb");

}
