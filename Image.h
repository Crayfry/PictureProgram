//  Image.cpp
//
//  header for image.cpp class
//  that represents a picture
//
#pragma once
#include <stdint.h>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

enum ImageType {
    PNG, JPG
};

struct Image{
    uint8_t* data = NULL;
    size_t size = 0;
    int w;
    int h;
    int channels;
    string name = "";
    double avgr = 0;
    double avgg = 0;
    double avgb = 0;

    Image(char const* filename);
    Image(char const* filename, string desiredname);
    Image(int w, int h, int channels);
    Image(Image const& img);
    Image& operator=(const Image& other);
    ~Image();

    bool read(const char* filename);
    bool readfromfile(FILE * file);
    bool write(const char* filename);
    void convertToGray();
    void reflectHorUpDown();
    void reflectHorDownUp();
    void reflectVerRigLeft();
    void reflectVerLeftRig();
    pair<int, int> findingCellSize();
    uint8_t* rgbCellCalculation(int x, int y);
    void createMosaic();
    void placeImages(vector<Image*> imageReservoir, int x, int y);
    void imageReplacements(int x, int y);
    Image* resize(int x, int y);
    void colorMaker();

    ImageType getFileType(const char* filename);
    void calculateAvgRGB();
    vector<Image> PicGetter(vector<Image> &pictures);
};