#pragma once

/** this is for built-in header file section **/

#include<iostream>
#include<ctime>


/** this is for source file section **/

#include "BmpStructure.cpp"
//#include "gifenc.h"

using namespace std;

int checkingImageFormat(string fileName);
int checkingTextFile(string imageFile,string textFile);
string addImageFileExtension(string imageFileName);
string addTextFileExtension(string textFileName);
int hidingData(string imageFile,string textFile);
vector<int> textToBinary(string textFile);
void extractingData(string imageFile);
vector<int> decimalToBinary(int decimalValue);
int binaryToDecimal(int binArray[],int length);
void gif();
