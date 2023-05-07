#include<cstdlib>
#include<bits/stdc++.h>
#include"header.h"

using namespace std;

void openingImage(string fileName){

// Replace "path/to/animated.gif" with the actual path to the animated GIF file.
     string file_path = "C:\\Users\\HP\\Desktop\\test\\";

    // Build the command to open the file with the Windows Photos app.
    string command = "start " + file_path+fileName;

    // Use the system command to execute the command and open the file with the Windows Photos app.
    system(command.c_str());
}
