#include "gifenc.h"
//#include "header.h"
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
//#include "gifenc.c"

void gif()
{
    int i, j;
    int widthOfScreen = 120, heightOfScreen = 130;


    FILE *fp=NULL;

    uint8_t colors[24];
    srand(time(0));
    int num=rand()%3+1;

    //printf("%d\n",num);
    //  num=2;

    switch(num)
    {
    case 1:
        fp = fopen("pixel1.BIN", "rb");
        break;

    case 2:
        fp = fopen("pixel2.BIN", "rb");
        break;

    case 3:
        fp = fopen("pixel3.BIN", "rb");
        break;
    }



    if (fp == NULL)
    {
        perror("Error opening file");
        //return EXIT_FAILURE;
    }

    fread(colors, sizeof(uint8_t), 24, fp);

    fclose(fp);

    GIF *gif = newGif(
                   "GIF.gif",  widthOfScreen, heightOfScreen, /* canvas size */colors,
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


