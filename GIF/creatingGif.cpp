#include "gifencoder.h"
#include "header.h"
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<bits/stdc++.h>
#include <Windows.h>
#include<time.h>

using namespace std;

int creatingGif(string GIFFile)
{
    srand(time(0));
    int num1=rand()%8+1;
    string pixelFile="";
    // switch case

    switch(num1)
    {
    case 1:
        pixelFile="pixel1.bin";
        break;

    case 2:
        pixelFile="pixel2.bin";
        break;

    case 3:
        pixelFile="pixel3.bin";
        break;

    case 4:
        pixelFile="pixel4.bin";
        break;

    case 5:
        pixelFile="pixel5.bin";
        break;

    case 6:
        pixelFile="pixel6.bin";
        break;

    case 7:
        pixelFile="pixel7.bin";
        break;

    case 8:
        pixelFile="pixel8.bin";
        break;
    }

    gif(pixelFile,GIFFile);



    // showing the gif from system

    string file_path = "C:\\Users\\HP\\Desktop\\SPL-01\\last try\\"+GIFFile;

    // Building the command to open the file with the Windows Photos app.
    string command = "start \"\" \"" + file_path+"\"";

    // Using the system command to execute the command and open the file with the Windows Photos app.
    system(command.c_str());

    // Waiting for 1 minute
    Sleep(1000);

    return 1;
}
