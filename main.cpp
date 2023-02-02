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
    cout<<"## caution : these features are applicable for only .bmp image file.";
    cout<<"\n\n";


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

            cout<<"provide text file name";
            cout<<"\n";
            cin>>textFileName;



            /** checking for valid format of image file **/
            cout<<"\nchecking for valid format of image file.";
            cout<<"please wait.\n\n";


            if(checkingImageFormat(imageFileName))
            {
                cout<<"The image format is correct.";
                cout<<"\n";
            }
            else
            {
                cout<<"sorry, the image format is not correct.";
                cout<<"redirecting to the option menu.\n\n";
                continue;
            }


            /** checking opening issue **/
            ifstream inputFile;
            inputFile.open(imageFileName,ios:: binary);

            if(!inputFile)
            {
                cout<<"couldn't locate the file\n";
                cout<<"redirecting to the option menu\n\n";
                continue;
            }
            else
            {
                cout<<"your source image file is ready to be cover media.";
                cout<<"\n\n";
            }

            inputFile.close();


            /** checking if the text file is compatible for steganography **/

            ifstream inputfile1;
            inputfile1.open(textFileName,ios:: binary);

            if(!inputfile1)
            {
                cout<<"couldn't locate the file\n";
                cout<<"redirecting to the option menu\n\n";
                continue;
            }


            if(checkingTextFile(imageFileName,textFileName))
            {
                cout<<"possible to hide the text file within provided image file.";
                cout<<"\n";
            }
            else
            {
                cout<<"not possible to hide the text file within provided image file.";
                cout<<"redirecting to the option menu.\n\n";
                continue;
            }

            inputfile1.close();

        }
        else if(choice==2)
        {

        }
        else
        {
            continueLoop=false;
        }
    }

}
