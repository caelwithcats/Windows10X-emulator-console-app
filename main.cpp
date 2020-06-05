#include <windows.h>
#include <iostream>
#include <cmath>
#include <string>
#include <stdio.h>
#include "bitmapLib/EasyBMP.h"

using namespace std;

#define PI 3.14
#define PRODUCT_NAME "Windows";
#define PRODUCT_VER "10X";
void DrwLine(int LineHeight, int Vertical, int Border, int Horizontal, COLORREF COLOURV, bool Gradient, HDC* console);
void DrwImage(std::string imagePath, int percent, int yC, int xC, HDC* console);
void DrwWSOD(HDC* console);

int main() 
{
    //Get current console handle
    HWND myconsole = GetConsoleWindow();
    //Get a handle to console
    HDC mydc = GetDC(myconsole);

    int Vertical =10;
    int Border = 10;
    int LineHeight = 100;
    int CornerRadius = 10;
    int Size = 4;
    
    //Choose any colour
    COLORREF COLOUR= RGB(255,255,255);
    bool isCorner = false;

    DrwLine(LineHeight * Size, Vertical * Size, Border * Size,0 * Size, COLOUR,true,&mydc);
    DrwLine(100 * Size, 10 * Size, 200 * Size,0 * Size, COLOUR,true, &mydc);
    DrwLine(LineHeight * Size, 200 * Size,0 * Size, Border * Size, COLOUR,true, &mydc);
    DrwLine(10 * Size, 10 * Size, 100 * Size,90 * Size, COLOUR, false, &mydc);
    DrwLine(10 * Size, 10 * Size, 200 * Size, 90 * Size, COLOUR, false, &mydc);
    DrwImage("windows10x.bmp", 5, 365, 400, &mydc);
    Sleep(1000);
    DrwWSOD(&mydc);
    ReleaseDC(myconsole, mydc);
    cin.ignore();
    return 0;
}
void DrwWSOD(HDC* console) {
    // White screen of death
    DrwImage("Win10XWSOD.bmp", 400, 0, 50, *&console);
}
void DrwLine(int LineHeight, int Vertical,int Border,int Horizontal, COLORREF COLOURV,bool Gradient, HDC *console) {
    int _border;
    COLORREF COLOUR;
    for (int h = 0; h < LineHeight; h++) {
        if (Gradient) {
            float sr = 10;
            float sg = 50;
            float sb = 150;

            float er = 100;
            float eg = 150;
            float eb = 200;

            int steps = 200;
            float n;
            unsigned char r, g, b;

                n = (float)h / (float)(steps - 1);
                r = (float)sr * (1.0f - n) + (float)er * n;
                g = (float)sg * (1.0f - n) + (float)eg * n;
                b = (float)sb * (1.0f - n) + (float)eb * n;
                COLOUR = RGB(r, g, b);
            
        }
        else if(!Gradient) {
            COLOUR = COLOURV;
        }
        SetPixel(*console, Vertical, Horizontal, COLOUR);

        for (_border = 0; _border < Border; _border++) {
            SetPixel(*console, Vertical + _border, Horizontal + h, COLOUR);

        }

    }
}
void DrwImage(std::string imagePath,int percent,int yC, int xC, HDC* console) {
    /*
    cv::Mat image;
    image = cv::imread(imagePath, cv::IMREAD_COLOR);
    //image.cols = width;
    //image.rows = height;
    

    */
    BMP image;
    image.ReadFromFile(imagePath.c_str());
    //int NewWidth = image.TellWidth() * percent / 100.0;
    //int NewHeight = image.TellHeight() * percent / 100.0;
    //image.SetSize(NewWidth, NewHeight);
    //image.SetBitDepth(24);
    image.ReadFromFile(imagePath.c_str());
    for (int x = 0; x < image.TellWidth(); x++)
    {
        for (int y = 0; y < image.TellHeight(); y++)
        {
            int RED = image.GetPixel(x, y).Red;
            int GREEN = image.GetPixel(x, y).Green;
            int BLUE = image.GetPixel(x, y).Blue;
            // Alpha values must 255 or 0 to be read
            int ALPHA = image.GetPixel(x, y).Alpha;
            // RGB: https://www.rrrgggbbb.com/

            COLORREF COLOUR = RGB(RED, GREEN, BLUE);
            //std::cout << Pixels[0] + ', ' + Pixels[1] + ', ' + Pixels[2] << std::endl;
            if (ALPHA == 0) {
                SetPixel(*console, xC + x,yC + y, COLOUR);
            }
        }
    }
}
