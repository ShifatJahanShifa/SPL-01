#include<bits/stdc++.h>
#include<iostream>
#include<fstream>
#include<time.h>

#include "header.h"

using namespace std;

int main()
{
    cout<<"*******************************\n\n";
    cout<<"Welcome to Image Steganography";
    cout<<"\n\n";
    cout<<"*******************************\n\n";
    cout<<"Here are our supported features";
    cout<<"\n\n";
    cout<<"data hiding";
    cout<<"\n";
    cout<<"data extracting";
    cout<<"\n\n";


    /** showing additional info **/


    bool continueLoop=true;

    while(continueLoop)
    {
        cout<<"select an option to proceed: \n\n";
        cout<<"option 1: data hiding\n";
        cout<<"option 2: data extracting\n";
        cout<<"option 3: quit\n";

        int choice;
        cin>>choice;

        if(choice==1)
        {
            string imageFileName;
            string textFileName;

            cout<<"provide image file name";
            cout<<"\n";

            cin>>imageFileName;
            string extendedImageFileName=addImageFileExtension(imageFileName);

            cout<<"provide text file name";
            cout<<"\n";

            cin>>textFileName;
            string extendedTextFileName=addTextFileExtension(textFileName);


            /** checking opening issue of image file**/   //  limitation
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

            if(hidingData(extendedImageFileName,extendedTextFileName))
            {
                puts("stego image is ready");
            }

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

        }
        else if(choice==3)
        {
            continueLoop=false;
        }
        else
        {
            cout<<"Invalid option";
            cout<<"\n\n";
            continue;
        }
    }

}
