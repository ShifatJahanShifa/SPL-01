#include<bits/stdc++.h>
#include<ctime>

#include "header.h"

using namespace std;

vector<int> decimalToBinary(int decimalValue)
{
  //  cout<<decimalValue<<"\n";
    int storeBianry[32];
    int k=31;
    int remainder;

    while(decimalValue)
    {
        remainder=decimalValue%2;
        storeBianry[k]=remainder;
        decimalValue/=2;
        k--;
    }

    while(k>=0)
    {
        storeBianry[k]=0;
        k--;
    }

    /*for(int i=0;i<32;i++)
        cout<<storeBianry[i]<<" ";
        puts("");*/

    vector<int>result;

    for(int i=0;i<32;i++)
        result.push_back(storeBianry[i]);

    return result;
}
