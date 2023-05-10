#include<bits/stdc++.h>
#include<iostream>
#include<fstream>
#include<time.h>
#include <cstdlib>
#include "header.h"
#include<time.h>
#include <thread>
#include<windows.h>


using namespace std;

int main()
{
    // here beautifying the console output
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD savedAttributes;

    // Save the current console attributes
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    savedAttributes = consoleInfo.wAttributes;

    // Set the console text color to red
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);

    //SetConsoleTextAttribute(hConsole, savedAttributes);
    cout<<"**********************************************";
    cout<<"**************************************************************************\n\n";
    cout<<"\t\t\t\t\t\tWelcome to Steg-Gif";
    cout<<"\n\n\n";
    cout<<"**********************************************";
    cout<<"**************************************************************************\n\n";

    SetConsoleTextAttribute(hConsole, savedAttributes);
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
    cout<<"Here are my project features:";
    cout<<"\n\n";
    cout<<"# data hiding";
    cout<<"\n";
    cout<<"# data extracting";
    cout<<"\n";
    cout<<"# GIF encoder";
    cout<<"\n\n";
    SetConsoleTextAttribute(hConsole, savedAttributes);

    bool continueLoop=true;

    while(continueLoop)
    {
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
        cout<<"select an option to proceed: \n\n";
        cout<<"option 1: data hiding\n";
        cout<<"option 2: data extracting\n";
        cout<<"option 3: GIF encoder\n";
        cout<<"option 4: quit\n";
        SetConsoleTextAttribute(hConsole, savedAttributes);
        int choice;
        cin>>choice;

        if(choice==1)
        {
            string imageFileName;
            string textFileName;
            string extendedTextFileName;

            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
            cout<<"provide image file name";
            cout<<"\n";
            SetConsoleTextAttribute(hConsole, savedAttributes);

            cin>>imageFileName;
            string extendedImageFileName=addImageFileExtension(imageFileName);


            // option for text file
            bool looping=true;
            while(looping)
            {
                SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                cout<<"how do you want to provide hidden data?";
                cout<<"\n";
                cout<<"write now or provide text file name";
                cout<<"\n\n";
                cout<<"press 1 for writing now";
                cout<<"\n";
                cout<<"press 2 for providing text file name";
                cout<<"\n";
                SetConsoleTextAttribute(hConsole, savedAttributes);

                int pressingValue;
                cin>>pressingValue;

                if(pressingValue==1)
                {
                    extendedTextFileName="input.txt";
                    processInputText(extendedTextFileName);
                }
                else if(pressingValue==2)
                {
                    cin>>textFileName;
                    extendedTextFileName=addTextFileExtension(textFileName);
                }
                else
                {
                    continue;
                }
                looping=false;
            }

            /** checking opening issue of image file**/
            ifstream inputFile;
            inputFile.open(extendedImageFileName,ios:: binary);

            if(!inputFile)
            {
                SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY);
                cout<<"couldn't find the image file in storage\n";
                cout<<"redirecting to the option menu\n\n";
                SetConsoleTextAttribute(hConsole,savedAttributes);
                continue;
            }

            inputFile.close();


            if(!checkingImageFormat(extendedImageFileName))
            {
                SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY);
                cout<<"sorry, the image format is not correct.\n";
                cout<<"redirecting to the option menu.\n\n";
                SetConsoleTextAttribute(hConsole, savedAttributes);
                continue;
            }

            //SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
            //cout<<"before hiding data";
            //cout<<"\n";
            openingImage(extendedImageFileName);
            //SetConsoleTextAttribute(hConsole, savedAttributes);

            /** checking if the text file is compatible for steganography **/   // correction

            ifstream inputfile1;
            inputfile1.open(extendedTextFileName,ios:: binary);

            if(!inputfile1)
            {
                SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY);
                cout<<"couldn't load the text file\n";
                cout<<"redirecting to the option menu\n\n";
                SetConsoleTextAttribute(hConsole, savedAttributes);
                continue;
            }


            if(!checkingTextFile(extendedImageFileName,extendedTextFileName))
            {
                SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY);
                cout<<"not possible to hide the text file within provided image file.";
                cout<<"redirecting to the option menu.\n\n";
                SetConsoleTextAttribute(hConsole, savedAttributes);
                continue;
            }

            inputfile1.close();

            if(hidingData(extendedImageFileName,extendedTextFileName))
            {
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                puts("stego image is ready");
                cout<<"\n\n";
                SetConsoleTextAttribute(hConsole, savedAttributes);
            }
            else
            {
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                puts("failed to create stego image");
                SetConsoleTextAttribute(hConsole, savedAttributes);
                continue;
            }

            Sleep(4000);

            //SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
            //cout<<"after data hiding";
            //cout<<"\n";
            //SetConsoleTextAttribute(hConsole, savedAttributes);

            openingImage(extendedImageFileName);
        }
        else if(choice==2)
        {
            string stegoImageFileName;

            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
            cout<<"provide stego image file name";
            cout<<"\n";
            SetConsoleTextAttribute(hConsole, savedAttributes);

            cin>>stegoImageFileName;
            string extendedStegoImageFileName=addImageFileExtension(stegoImageFileName);

            ifstream inputFile;

            inputFile.open(extendedStegoImageFileName,ios:: binary);

            if(!inputFile)
            {
                SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY);
                cout<<"couldn't find the image file in storage\n";
                cout<<"redirecting to the option menu\n\n";
                SetConsoleTextAttribute(hConsole, savedAttributes);
                continue;
            }

            inputFile.close();


            if(!checkingImageFormat(extendedStegoImageFileName))
            {
                SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY);
                cout<<"sorry, the image format is not correct.\n";
                cout<<"redirecting to the option menu.\n\n";
                SetConsoleTextAttribute(hConsole, savedAttributes);
                continue;
            }

            extractingData(extendedStegoImageFileName);

        }
        else if(choice==3)
        {
            string pixelFileName;

            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
            cout<<"provide pixel file name";
            cout<<"\n";
            SetConsoleTextAttribute(hConsole, savedAttributes);

            cin>>pixelFileName;
            string extendedPixelFileName=addPixelFileExtension(pixelFileName);

            FILE *fp=NULL;
            fp = fopen(extendedPixelFileName.c_str(), "rb");

            if(fp==NULL)
            {
                SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY);
                cout<<"couldn't find the pixel file in storage\n";
                cout<<"redirecting to the option menu\n\n";
                SetConsoleTextAttribute(hConsole, savedAttributes);
                continue;
            }

            SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
            cout<<"showing the gif file";
            cout<<"\n\n\n";
            SetConsoleTextAttribute(hConsole, savedAttributes);
            creatingGif(extendedPixelFileName);

            fclose(fp);
        }
        else if(choice==4)
        {
            continueLoop=false;
        }
        else
        {
            SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
            cout<<"Invalid option";
            cout<<"\n\n";
            SetConsoleTextAttribute(hConsole, savedAttributes);

            return EXIT_FAILURE;
        }
        system("cls");
    }
}
