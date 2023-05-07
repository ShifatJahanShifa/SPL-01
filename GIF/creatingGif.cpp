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
    string file1="GIF1.gif";
    string file2="GIF2.gif";
    string file3="GIF3.gif";
    string file4="GIF4.gif";
    string file5="GIF5.gif";

    gif(pixelFile,file1);
    gif(pixelFile,file2);
    gif(pixelFile,file3);
    gif(pixelFile,file4);
    gif(pixelFile,file5);


    // showing the gif from system
    // Replace the following file paths with the paths of the five GIF files you want to view.
    std::wstring gifFilePaths[5] = {
        L"C:\\Users\\HP\\Desktop\\SPL-01\\last try\\GIF1.gif",
        L"C:\\Users\\HP\\Desktop\\SPL-01\\last try\\GIF2.gif",
        L"C:\\Users\\HP\\Desktop\\SPL-01\\last try\\GIF3.gif",
        L"C:\\Users\\HP\\Desktop\\SPL-01\\last try\\GIF4.gif",
        L"C:\\Users\\HP\\Desktop\\SPL-01\\last try\\GIF5.gif",
    };

    // Loop through the GIF file paths and open each one in the default Photos app.
    for (int i = 0; i < 5; i++)
    {
        ShellExecuteW(NULL, L"open", L"explorer.exe", gifFilePaths[i].c_str(), NULL, SW_SHOWDEFAULT);

        // Wait for 1 minute before opening the next GIF file.
        Sleep(1000);
    }

    // Enter the message loop.
    MSG msg;
    /*while (GetMessageW(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }*/

    return 1;
}
