#include "donut.h"
// printf("\x1b[H");    this returns cursor to home

//some globals
float luminosity[80][80];
float zbuffer[80][80];
char screen[80][80];

float thetaStep = 0.07;
float psiStep = 0.02;
const int r=1;
const int R=2;
const int K2 = 5;
const int screenWidth = 50;
const int screenHeight = screenWidth;

double K1 = screenWidth*K2*3/(8*(r+R));

double twoPi = 6.28318530718;

double A = 0;
double B = 0; 


int main(int argc, char *argv[])
{
    while (true) {
        
        printf("\x1b[2J");
        //printf("new");
        //memset here
        for (int i=0; i < screenWidth; i++) {
                 for (int j=0; j < screenHeight; j++) {
                    zbuffer[i][j]=0;              
            }
        }
        for (int i=0; i < screenWidth; i++) {
                 for (int j=0; j < screenHeight; j++) {
                    screen[i][j]= ' ';              
            }
        }
        for (float theta = 0; theta < twoPi; theta += thetaStep) {
        
            float sintheta = sin(theta), costheta = cos(theta);
            
            for (float psi = 0; psi < twoPi; psi += psiStep) {
                float sinpsi = sin(psi), cospsi = cos(psi);
                float cosA = cos(A), cosB = cos(B), sinA = sin(A), sinB = sin(B);
                float conx = R + r*costheta, cony = r*sintheta;

                float x = conx*(cosB*cospsi + sinA*sinB*sinpsi)-cosA*sinB*cony;
                float y = conx*(cospsi*sinB - cosB*sinA*sinpsi)+cosA*cosB*cony;
                float z = K2 + cosA*conx*sinpsi + cony*sinA;

                float invz = 1/z;
                int screenX = (int)(screenWidth/2 + K1*invz*x), screenY = (int)(screenHeight/2 - K1*invz*y);
                

                float L = cospsi*costheta*sinB - cosA*costheta*sinpsi - sinA*sintheta + cosB*(cosA*sintheta - costheta*sinA*sinpsi);

                if (L > 0) {
                    if (zbuffer[screenX][screenY] < invz) {
                        zbuffer[screenX][screenY] = invz;
                        int luminance_index = (int)(L*8);
                        screen[screenX][screenY] = ".,-~:;=!*#$@"[luminance_index];
                    }
                }


            }
            
        }
        printf("\x1b[H"); 
            for (int i=0; i < screenWidth; i++) {
                for (int j=0; j < screenHeight; j++) {
                    
                        putchar(screen[i][j]);
                        luminosity[i][j] = 0;  
                              
                }
                printf("\n");
            //printf("%i", i);
            
        }
        A += 0.04;
        B += 0.02;
    }

    printf("DONUT.C TERMINATED");
    
    return 0;
    
} 