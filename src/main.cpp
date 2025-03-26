#include "bmp.h"

using namespace std;


int main() {
   
    string fileName;
    cout << " Enter input BMP file name: ";// Ввод имени файла в формате *****.bmp
    cin >> fileName;
    
    BMPImage image(fileName);
    
    image.PrintBMP(); // вывод в консоль содержимое bmp
    image.DrawBMP(); // добавление диагонального креста в файл bmp
    image.PrintBMP(); // вывод в консоль модернизированного файла с крестом
    image.SaveBMP(); // запись модернизированного файла с новым именем
}
