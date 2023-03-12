#include<bits/stdc++.h>
#include<ctime>

#include "header.h"

using namespace std;

int binaryToDecimal(int binArray[],int length)
{
    int decimalValue=0;

   /* for(int i=0;i<length;i++)
        cout<<binArray[i]<<" ";*/

    for(int t=0; t<length; t++)
    {
        if(binArray[t])
            decimalValue+=(binArray[t]*pow(2,(31-t)));
    }

    return decimalValue;
}

