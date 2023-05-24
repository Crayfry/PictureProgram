//
//  PictureProgram
//  Author: Mohamed Mjawaz
//  Description: A basic picture program to take in a picture and copy, grayscale, reflect, resize a picture  
//
//  main.cpp
//
#include <iostream>
#include <stdint.h>
#include <cstdio>
#include <cstring>
#include "Image.h"
#include "include/stb-master/stb_image.h"
#include "include/stb-master/stb_image_write.h"

using namespace std;

Image* ResizeBy(Image* thePicture, int xFactor, int yFactor){
    Image* oldPicture = thePicture;
    thePicture = thePicture->resize(thePicture->w*xFactor, thePicture->h*yFactor);
    delete oldPicture;
    return thePicture;
}

Image* Resize(Image* thePicture){
    cout << "1. Resize by a factor" << endl
         << "2. Resize to a resolution" << endl;
    int userinput = 0;
    cin >> userinput;
    if(userinput == 1){
        cout << "To what resolution do you want to resize the picture?" << endl;
        int x, y;
        cout << "X: ";
        cin >> x;
        cout << "Y: ";
        cin >> y;
        Image* oldPicture = thePicture;
        thePicture = thePicture->resize(x, y);
        delete oldPicture;
        return thePicture;
    } else if (userinput == 2){
        int x, y;
        cout << "x factor: ";
        cin >> x;
        cout << "y factor: ";
        cin >> y;
        thePicture = ResizeBy(thePicture, x, y);
        return thePicture;
    } else {
        cout << "improper selection";
        exit(0);
    }
    return thePicture;
}

void HorizontalReflect(Image* thePicture){
    int userinput3;
    cout << "1. Reflect left onto right" << endl
        << "2. Reflect right onto left" << endl;
    cin >> userinput3;
    if(userinput3 == 1){
        thePicture->reflectVerLeftRig();
    } else if (userinput3 == 2){
        thePicture->reflectVerRigLeft();
    } else {
        cout << "improper selection";
        exit(0);
    }
}

void VerticalReflect(Image* thePicture){
    int userinput2;
    cout << "1. Reflection top onto bottom" << endl
         << "2. Reflection bottom onto top" << endl;
    cin >> userinput2;
    if(userinput2 == 1){
        thePicture->reflectHorUpDown();
    } else if(userinput2 == 2) {
        thePicture->reflectHorDownUp();
    } else {
        cout << "improper selection";
        exit(0);
    }
}

int main(){
    string filename;
    cout << "Insert the picture file name or directory" << endl;
    getline(cin, filename);
    int n = filename.size();
    char char_array[n];
    strcpy(char_array, filename.c_str());

    Image* thePicture = new Image(char_array);

    cout << "1. Make a pure Copy" << endl
         << "2. Make a grayscale copy" << endl
         << "3. Make a reflection over horizontal copy" << endl
         << "4. Make a reflection over verical copy" << endl
         << "5. Make a Mosaic" << endl
         << "6. Resize Image" << endl
         << "7. Make a lot of Images of colors" << endl;

    int userinput;
    cin >> userinput;

    switch(userinput){
        default:
            cout << "improper selection" << endl;
            system("pause");
            return 0;
        case 1:
            break;
        case 2:
            thePicture->convertToGray();
            break;
        case 3:
            VerticalReflect(thePicture);
            break;
        case 4:
            HorizontalReflect(thePicture);
            break;
        case 5:
            thePicture = ResizeBy(thePicture, 8, 8);
            thePicture->createMosaic();
            break;
        case 6:
            thePicture = Resize(thePicture);
            break;
        case 7:
            cout << "Creating blocks of colors" << endl;
            thePicture->colorMaker();
            break;
    }
    cout << "operation success" << endl;
    thePicture->write("result.jpg");

    printf("Result Successful in result.jpg\n");
    system("pause");
    return 0;
}