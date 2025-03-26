#include "bmp.h"

using namespace std;



BMPImage::BMPImage(string fileName) {
        this->fileName = fileName;
        ReadFile();
    }


    void BMPImage::ReadFile() {
        ifstream file(fileName, ios::binary);

        if (!file.is_open()) {
            cout << "Bad open file!";
            return;
        }

        file.read(reinterpret_cast<char*>(&fileHeader), sizeof(fileHeader));
        file.read(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));

        if (fileHeader.bfType != 0x4D42) {
            cout << "NO format .bmp";
            return;
        }

        if (infoHeader.biBitCount != 24 && infoHeader.biBitCount != 32) {
            cout << "Only 24 or 32 bit bmp";
            return;
        }

        width = infoHeader.biWidth;
        height = abs(infoHeader.biHeight);
        bytesCount = infoHeader.biBitCount / 8;
        padding = (4 - (width * bytesCount) % 4) % 4;


        for (int i = 0; i < height; i++) {
            vector<bool> row;
            for (int j = 0; j < width; j++) {
               
                vector<char> pixel(bytesCount);

                file.read(&pixel[0], bytesCount);

                row.push_back((pixel[0] == 0));

            }
            imageData.push_back(row);
            file.ignore(padding);

        }
        file.close();
    }




    void  BMPImage::DrawBMP() {

        double k = static_cast<double>(width - 1) / (height - 1);

        for (int i = 0; i < height - 1; i++) {

            int j = round(k * i);
            int jNext = round(k * (i + 1));

            imageData[i][j] = !imageData[i][j];
            imageData[i][width - 1 - j] = !imageData[i][width - 1 - j];

            for (int m = j + 1; m <= jNext; m++) {
                imageData[i][m] = !imageData[i][m];
                imageData[i][width - 1 - m] = !imageData[i][width - 1 - m];
            }
        }

        imageData[height - 1][width - 1] = !imageData[height - 1][width - 1];
        imageData[height - 1][0] = !imageData[height - 1][0];

    }

    void BMPImage::PrintBMP() {

        for (int i = height - 1; i >= 0; i--) {
            for (int j = 0; j < width; j++) {
                cout << imageData[i][j];
            }
            cout << endl;
        }
    }

    void BMPImage::SaveBMP() {

        string newFilename;
        cout << "Enter save  BMP file name:"; // Ввод имени файла в формате *****.bmp
        cin >> newFilename;
        
        ofstream newFile(newFilename, ios::binary);
        if (!newFile.is_open()) {
            cerr << "Bad open file!" << endl;
            return;
        }

        newFile.write(reinterpret_cast<char*>(&fileHeader), sizeof(fileHeader));
        newFile.write(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
               
                vector<char> pixel(bytesCount);

                if (imageData[i][j]) {
                    pixel[0] = 0; pixel[1] = 0; pixel[2] = 0;
                }
                else {
                    pixel[0] = 255; pixel[1] = 255; pixel[2] = 255;
                }

                newFile.write(&pixel[0], bytesCount);
            }
            vector<char> pad(padding, 0);
            newFile.write(pad.data(), padding);
        }
        newFile.close();

    }


