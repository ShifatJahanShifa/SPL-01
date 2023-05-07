#include "gifencoder.h"
//#include "header.h"
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<bits/stdc++.h>
using namespace std;

void gif(string pixelFileName,string gifFile)
{
    int i, j;
    int widthOfScreen = 120, heightOfScreen = 130;


    //FILE *fp=NULL;
    FILE *fp=fopen(pixelFileName.c_str(),"rb");

    uint8_t colors[24];
    //srand(time(0));
    //int num=rand()%3+1;


    if (fp == NULL)
    {
        perror("Error opening file");
        //return EXIT_FAILURE;
    }

    fread(colors, sizeof(uint8_t), 24, fp);

    fclose(fp);

    GIF *gif = newGif(
                    gifFile.c_str(),
                    widthOfScreen, heightOfScreen, /* canvas size */
                    colors,    /* color pallete */
                    3,              /* palette depth == log2(# of colors) */
                   -1,             /* no transparency */
                    0               /* infinite loop , won't stop*/
                    );

    /* drawing some frames */

    srand(time(0));
    int num1=rand()%8+1;

//   printf("%d\n",num1);
    for (i = 0; i < 8; i++)
    {
        for (j = 0; j < widthOfScreen*heightOfScreen; j++)
            gif->frame[j] = (i*3 + j) / 6 % num1;
        addFrame(gif, 5);
    }

    /* closing the GIF */
    closeGif(gif);

}


