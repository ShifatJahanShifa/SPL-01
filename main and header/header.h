#pragma once

/** this is for built-in header file section **/

#include<iostream>
#include<ctime>


/** this is for source file section **/

#include "BmpStructure.cpp"
//#include "checkingImageFormat.cpp"
//#include "checkingTextFile.cpp"


using namespace std;


int checkingImageFormat(string fileName);
int checkingTextFile(string imageFile,string textFile);
