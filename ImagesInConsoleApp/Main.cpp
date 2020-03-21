#include <windows.h>
#include <iostream>
#include "EasyBMP.h"

void DrwImage(std::string imagePath, HDC* console);
int main()
{
    //Get current console handle
    HWND console = GetConsoleWindow();
    //Get a handle to console
    HDC dc = GetDC(console);
    // Call DrwImage
    DrwImage("mybitmap.bmp", &dc);
    return 0;
}
void DrwImage(std::string imagePath, HDC* console) {

    BMP image;
    image.ReadFromFile(imagePath.c_str());
    //image.SetBitDepth(32);
    for (int x = 0; x < image.TellWidth(); x++)
    {
        for (int y = 0; y < image.TellHeight(); y++)
        {
            int RED = image.GetPixel(x, y).Red;
            int GREEN = image.GetPixel(x, y).Green;
            int BLUE = image.GetPixel(x, y).Blue;

            int ALPHA = image.GetPixel(x, y).Alpha;

            COLORREF COLOUR = RGB(RED, GREEN, BLUE);
            if (ALPHA == 0) {
                SetPixel(*console, x, y, COLOUR);
            }
        }
    }
}