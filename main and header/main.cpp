#include<bits/stdc++.h>
#include<iostream>
#include<fstream>
#include<time.h>
#include <cstdlib>
#include "header.h"
#include<time.h>
#include <thread>
#include<windows.h>
#include<wincon.h>
#include<sstream>

using namespace std;

int main()
{

    system("color ED");

    cout<<"**********************************************";
    cout<<"**************************************************************************\n\n";
    cout<<"\t\t\t\t  Welcome to Invisible Ink & Animated Frame Encoder";
    cout<<"\n\n";
    cout<<"**********************************************";
    cout<<"**************************************************************************\n\n";

    cout<<"\t\t\t\t\t Here are my project features:\n";
    cout<<"\t\t\t\t\t_______________________________";
    cout<<"\n\n";
    cout<<"\t---------------\t\t";
    cout<<"\t      -------------------\t\t";
    cout<<"\t     ---------------\t\t";
    cout<<"\n";
    cout<<"\t| Data Hiding |\t\t";
    cout<<"\t      | Data Extracting |\t\t";
    cout<<"\t     | GIF Encoder |\t\t";
    cout<<"\n";
    cout<<"\t---------------\t\t";
    cout<<"\t      -------------------\t\t";
    cout<<"\t     ---------------\t\t";
    cout<<"\n\n";

    bool continueLoop=true;

    while(continueLoop)
    {
        cout<<"select an option to proceed: \n\n";
        cout<<"option 1: data hiding\n";
        cout<<"option 2: data extracting\n";
        cout<<"option 3: GIF encoder\n";
        cout<<"option 4: quit\n";

        int choice;
        cin>>choice;

        if(choice==1)
        {
            string imageFileName;
            string textFileName;
            string extendedTextFileName;

            cout<<"provide image file name";
            cout<<"\n";

            cin>>imageFileName;
            string extendedImageFileName=addImageFileExtension(imageFileName);

            // option for text file
            bool looping=true;

            while(looping)
            {
                cout<<"how do you want to provide hidden data?";
                cout<<"\n";
                cout<<"write now or provide text file name";
                cout<<"\n\n";
                cout<<"press 1 for writing now";
                cout<<"\n";
                cout<<"press 2 for providing text file name";
                cout<<"\n";

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
                cout<<"couldn't find the image file in storage\n";
                cout<<"redirecting to the option menu\n\n";
                continue;
            }

            inputFile.close();


            if(!checkingImageFormat(extendedImageFileName))
            {
                cout<<"sorry, the image format is not correct.\n";
                cout<<"redirecting to the option menu.\n\n";
                continue;
            }

            openingImage(extendedImageFileName);

            /** checking if the text file is compatible for steganography **/   // correction

            ifstream inputfile1;
            inputfile1.open(extendedTextFileName,ios:: binary);

            if(!inputfile1)
            {
                cout<<"couldn't load the text file\n";
                cout<<"redirecting to the option menu\n\n";
                continue;
            }


            if(!checkingTextFile(extendedImageFileName,extendedTextFileName))
            {
                cout<<"not possible to hide the text file within provided image file.";
                cout<<"redirecting to the option menu.\n\n";
                continue;
            }

            inputfile1.close();

            string stegoImage;
            if((stegoImage=hidingData(extendedImageFileName,extendedTextFileName))!=" ")
            {
                puts("stego image is ready");
                cout<<"\n\n";
            }
            else
            {
                puts("failed to create stego image");
                continue;
            }

            Sleep(4000);
            openingImage(stegoImage);

        }
        else if(choice==2)
        {
            string stegoImageFileName;

            cout<<"provide stego image file name";
            cout<<"\n";

            cin>>stegoImageFileName;
            string extendedStegoImageFileName=addImageFileExtension(stegoImageFileName);

            ifstream inputFile;

            inputFile.open(extendedStegoImageFileName,ios:: binary);

            if(!inputFile)
            {
                cout<<"couldn't find the image file in storage\n";
                cout<<"redirecting to the option menu\n\n";
                continue;
            }

            inputFile.close();


            if(!checkingImageFormat(extendedStegoImageFileName))
            {
                cout<<"sorry, the image format is not correct.\n";
                cout<<"redirecting to the option menu.\n\n";
                continue;
            }

            extractingData(extendedStegoImageFileName);
            Sleep(8000);

        }
        else if(choice==3)
        {
            string pixelFileName;

            cout<<"provide pixel file name";
            cout<<"\n";

            cin>>pixelFileName;
            string extendedPixelFileName=addPixelFileExtension(pixelFileName);

            FILE *fp=NULL;
            fp = fopen(extendedPixelFileName.c_str(), "rb");

            if(fp==NULL)
            {
                cout<<"couldn't find the pixel file in storage\n";
                cout<<"redirecting to the option menu\n\n";
                continue;
            }

            cout<<"showing the GIF file";
            cout<<"\n\n\n";

            creatingGif(extendedPixelFileName);

            fclose(fp);

        }
        else if(choice==4)
        {
            continueLoop=false;
        }
        else
        {
            cout<<"Invalid option";
            cout<<"\n\n";

            return EXIT_FAILURE;
        }

        system("cls");
    }
}
