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

    cout<<"\t\t\t\t\t   Here are my project features:\n";
    cout<<"\t\t\t\t\t  _______________________________";
    cout<<"\n\n\n";

    cout<<"          \t--------------------------\t\t\t";
    cout<<"        --------------------------\n";
    cout<<"          \t|      Invisible Ink     |\t\t\t";
    cout<<"        | Animated Frame Encoder | \n";
    cout<<"          \t--------------------------\t\t\t";
    cout<<"        --------------------------\n";

    cout<<"             \t   |                  |\t\t\t\t\t\t     |\n";
    cout<<"             \t   |                  |\t\t\t\t\t\t     |\n";
    cout<<"             \t   |                  |\t\t\t\t\t\t     |\n";
    cout<<"             \t   |                  |\t\t\t\t\t\t     |\n";

    cout<<"          ---------------      ";
    cout<<" -------------------\t\t\t";
    cout<<"    --------------------\n";
    cout<<"          | Data Hiding |     ";
    cout<<"  | Data Extracting |\t\t\t";
    cout<<"    |    GIF Encoder   |\n";
    cout<<"          ---------------      ";
    cout<<" -------------------\t\t\t";
    cout<<"    --------------------\n";

    bool continueLoop=true;

    while(continueLoop)
    {
        cout<<"\nSelect an option to proceed: \n\n";
        cout<<"press 1 for part I:  Invisible Ink\n";
        cout<<"press 2 for part II: Animated Frame Encoder\n";
        cout<<"press 0 to quit\n";

        int option;
        cin>>option;

        if(option==1)
        {
            cout<<"press 1 for Data Hiding\n";
            cout<<"press 2 for Data Extracting\n";
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
                openingImage(extendedImageFileName);

                // option for text file
                bool looping=true;

                while(looping)
                {
                    cout<<"How do you want to provide hidden data?";
                    cout<<"\n";
                    cout<<"\t--------------------\t\t\t---------------------------\n";
                    cout<<"\t|     Write Now    |\t\t\t|  Provide Text File Name |\n";
                    cout<<"\t--------------------\t\t\t---------------------------\n";
                    cout<<"\n";
                    cout<<"press 1 for Writing Now";
                    cout<<"\n";
                    cout<<"press 2 for Providing Text File Name";
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

                // openingImage(extendedImageFileName);

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
                Sleep(25000);

            }
        }
        else if(option==2)
        {
            string GIFFileName;

            cout<<"provide a name for your GIF file";
            cout<<"\n";

            cin>>GIFFileName;
            string extendedGIFFileName=addGIFFileExtension(GIFFileName);


            cout<<"Showing the GIF file";
            cout<<"\n\n\n";

            creatingGif(extendedGIFFileName);

        }
        else if(option==0)
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
