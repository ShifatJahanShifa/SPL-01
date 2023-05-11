#include "gifencoder.h"
#include "header.h"
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<bits/stdc++.h>
#include <Windows.h>

using namespace std;

int creatingGif(string pixelFile)
{
    string file1="GIF.gif";

    gif(pixelFile,file1);


    // showing the gif from system

    std::wstring gifFilePath = L"C:\\Users\\HP\\Desktop\\SPL-01\\last try\\GIF.gif";

    // Opening the GIF file in the default Photos app.
    ShellExecuteW(NULL, L"open", L"explorer.exe", gifFilePath.c_str(), NULL, SW_SHOWDEFAULT);

    // Waiting for 1 minute
    Sleep(1000);

    return 1;
}
