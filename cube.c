#include "donut.h"
// printf("\x1b[H");    this returns cursor to home

//some globals
float luminosity[50][50];
float zbuffer[50][50];
char screen[50][50];

const int K2 = 10;
const int screenWidth = 50;
const int screenHeight = screenWidth;

double twoPi = 6.28318530718;

double A = 0;
double B = 0;

int constface = 0;
int face = 0;
const float cubeLen = 5;
double spacing = 0.05;
double K1 = screenWidth * K2 / (8- cubeLen);

int main(int argc, char *argv[])
{
    while (true)
    {

        printf("\x1b[2J");
        //printf("new");
        //memset here
        for (int i = 0; i < screenWidth; i++)
        {
            for (int j = 0; j < screenHeight; j++)
            {
                zbuffer[i][j] = 0;
            }
        }
        for (int i = 0; i < screenWidth; i++)
        {
            for (int j = 0; j < screenHeight; j++)
            {
                screen[i][j] = ' ';
            }
        }
        float cosA = cos(A), cosB = cos(B), sinA = sin(A), sinB = sin(B);
        while (constface < 3)
        {
            while (face < 2)
            {
                for (float a = 0; a < cubeLen; a += spacing)
                {

                    double pos[3];

                    for (float b = 0; b < cubeLen; b += spacing)
                    {
                        pos[constface] = face * cubeLen;
                        pos[(constface + 1) % 3] = a;
                        pos[(constface + 2) % 3] = b;
                    }

                    double xp = pos[0];
                    double yp = pos[1];
                    double zp = pos[2];

                    double cont = (yp * cosA - zp * sinA);

                    double x = xp * cosB - sinB * cont;
                    double y = xp * sinB + cosB * cont;
                    double z = yp * sinA + zp * cosA + K2;

                    float invz = 1 / z;
                    int screenX = (int)(screenWidth / 2 + K1 * invz * x), screenY = (int)(screenHeight / 2 - K1 * invz * y);
                    //x-y
                    float L = 0;
                    float F = (2 * face - 1);
                    if (constface == 0)
                    {
                        L = sinB * F;
                        ;
                    }
                    else if (constface == 1)
                    {
                        L = F * (cosB * cosA - sinA);
                    }
                    else
                    {
                        L =  F * sinA * sinB + F * cosA;
                    }

                    if (L > 0)
                    {
                        if (zbuffer[screenX][screenY] < invz)
                        {
                            zbuffer[screenX][screenY] = invz;
                            int luminance_index = (int)(L * 8);
                            screen[screenX][screenY] = ".,-~:;=!*#$@"[luminance_index];
                        }
                    }
                }
                face++;
            }
            constface++;
            face = 0;
        }
        constface = 0;

        printf("\x1b[H");
        for (int i = 0; i < screenWidth; i++)
        {
            for (int j = 0; j < screenHeight; j++)
            {
                putchar(screen[i][j]);
                luminosity[i][j] = 0;
            }
            printf("\n");
            //printf("%i", i);
        }
        // A += 0.16;
        // B += 0.02;
    }

    printf("DONUT.C TERMINATED");

    return 0;
}