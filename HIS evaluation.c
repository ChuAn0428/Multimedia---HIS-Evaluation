/////////////////////////////////////
// CSCI 558 Multimedia - Evaluating HIS of photos
// Author: Chu-An Tsai
// 02/20/2020
/////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define DATASIZE 166000
#define H 332
#define W 500
#define PI 3.1415926
#define MIN(a,b) ((a)<(b)?(a):(b))

FILE *file_id1, *file_idI, *file_idS, *file_idH;
unsigned char imgR[H][W], imgG[H][W], imgB[H][W], outdataI[H][W], outdataS[H][W], outdataH[H][W];
int i, j;
float sumI, sumS, sumH = 0.0;

int main( )
{
    file_id1 = fopen("photo1.raw","rb");
    //file_id1 = fopen("photo2.raw","rb");
    fread(imgR, 1, DATASIZE, file_id1);
    fread(imgG, 1, DATASIZE, file_id1);
    fread(imgB, 1, DATASIZE, file_id1);
    fclose(file_id1);

    for (i=0; i<H; i++)
    {
        for (j=0; j<W; j++)
        {
            float r, g, b, tempI, tempS, tempH, Hup, Hdown = 0.0;

            // Normalization
            r = imgR[i][j]/255.0;
            g = imgG[i][j]/255.0;
            b = imgB[i][j]/255.0;

            // Intensity
            tempI = (r+g+b)/3;

            // Saturation
            if ((r==g) && (g==b))
            {
                tempS = 0;
            }
            else
            {
                tempS = 1 - ((3*(MIN(MIN(r,g),b)))/(r+g+b));
            }

            // Hue
            Hup = 0.5*((r-g)+(r-b));
            Hdown = sqrt((r-g)*(r-g)+(r-b)*(g-b));

            if (Hdown==0)
            {
                tempH = 0;
            }
            else
            {
                 if (g>=b)
                 {
                     tempH = acos((Hup/Hdown))*180/PI;
                 }
                 else
                 {
                     tempH = 360 - (acos((Hup/Hdown))*180/PI);
                 }
            }

            // Convert to [0, 255]
            tempI = tempI*255;
            tempS = tempS*255;
            tempH = tempH/360*255;

            outdataI[i][j] = tempI;
            sumI = sumI + tempI;
            outdataS[i][j] = tempS;
            sumS = sumS + tempS;
            outdataH[i][j] = tempH;
            sumH = sumH + tempH;
        }
    }

    // Average HIS 
    printf("Average Intensity = %f\n", (sumI/DATASIZE));
    printf("Average Saturation = %f\n", (sumS/DATASIZE));
    printf("Average Hue = %f\n", (sumH/DATASIZE));

    // RAW image for Intensity
    file_idI = fopen("I1.raw","wb");
    //file_idI = fopen("I2.raw","wb");
    fwrite(outdataI, 1, DATASIZE, file_idI);
    fclose(file_idI);

    // RAW image for Saturation
    file_idS = fopen("S1.raw","wb");
    //file_idS = fopen("S2.raw","wb");
    fwrite(outdataS, 1, DATASIZE, file_idS);
    fclose(file_idS);

    // RAW image for Hue
    file_idH = fopen("H1.raw","wb");
    //file_idH = fopen("H2.raw","wb");
    fwrite(outdataH, 1, DATASIZE, file_idH);
    fclose(file_idH);

    return 0;
}
