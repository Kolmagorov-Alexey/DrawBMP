#pragma once
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <string>
#include <windows.h>


    using namespace std;

    class BMPImage {

    public:
       
        BMPImage(string fileName);

        void ReadFile();// чтение содержимого файла

        void SaveBMP(); // запись модернизированного файла

        void DrawBMP(); //рисование диагонального креста

        void PrintBMP(); //вывод в консоль картинки

    private:

        string fileName;
        vector<vector<bool>> imageData;

        BITMAPFILEHEADER fileHeader;
        BITMAPINFOHEADER infoHeader;

        int width;
        int height;
        int padding;
        int bytesCount;

    };

