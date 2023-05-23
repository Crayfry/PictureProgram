//  Image.cpp
//
//  class for basic information
//  that represents a picture
//
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "Image.h"
#include <dirent.h>
#include <vector>
#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include "include/stb-master/stb_image.h"
#include "include/stb-master/stb_image_write.h"
#include "include/stb-master/stb_image_resize.h"

namespace fs = std::filesystem;
using namespace std;

Image::Image(char const* filename){
    if(read(filename)){
        size = w*h*channels;
        name = filename;
    } else{
        printf("Failed to read %s\n", filename);
        exit(0);
    }
}

Image::Image(char const* filename, string desiredname){
    if(read(filename)){
        size = w*h*channels;
        name = desiredname;
    } else{
        printf("Failed to read %s\n", filename);
        exit(0);
    }
}

Image::Image(int w, int h, int channels) : w(w), h(h), channels(channels){
    size = w*h*channels;
    data = new uint8_t[size];
}

Image::Image(Image const& other){
    this->avgr = other.avgr;
    this->avgg = other.avgg;
    this->avgb = other.avgb;
    this->name = other.name;
    this->w = other.w;
    this->h = other.h;
    this->channels = other.channels;
    this->size = other.size;
    for(int i = 0; i < other.size; i++){
        this->data[i] = other.data[i];
    }
}

Image& Image::operator=(const Image& other){
    if(this != &other) {
        this->avgr = other.avgr;
        this->avgg = other.avgg;
        this->avgb = other.avgb;
        this->name = other.name;
        this->w = other.w;
        this->h = other.h;
        this->channels = other.channels;
        this->size = other.size;
        for(int i = 0; i < other.size; i++){
            this->data[i] = other.data[i];
        }
    }
    return *this;
}

Image::~Image(){
    stbi_image_free(data);
}

bool Image::read(const char* filename){
    data = stbi_load(filename, &w, &h, &channels, 0);
    return data != NULL;
}

bool Image::readfromfile(FILE * file){
    data = stbi_load_from_file(file, &w, &h, &channels, 0);
    return data != NULL;
}

bool Image::write(const char* filename){
    ImageType type = getFileType(filename);
    int success;
    switch(type){
        case PNG:
            success = stbi_write_png(filename, w, h, channels, data, w*channels);
            break;
        case JPG:
            success = stbi_write_jpg(filename, w, h, channels, data, 100);
            break;
    }
    return success != 0;
}

ImageType Image::getFileType(const char* filename){
    const char* ext = strrchr(filename, '.');
    if(ext != nullptr){
        if(strcmp(ext, ".png") == 0){
            return PNG;
        } else if(strcmp(ext, ".jpg") == 0){
            return JPG;
        }
    }
    return PNG;
}

void Image::calculateAvgRGB(){
    avgr = 0;
    avgg = 0;
    avgb = 0;
    for(int col = 0; col < h; col++){
        for(int row = 0; row < w; row++){
            avgr += data[(row+(col*w))*channels+0];
            avgg += data[(row+(col*w))*channels+1];
            avgb += data[(row+(col*w))*channels+2];
        }
    }
    avgr = avgr/(w*h);
    avgg = avgg/(w*h);
    avgb = avgb/(w*h);
}

Image* Image::resize(int x, int y){
    Image *temp = new Image(x, y, channels);
    stbir_resize_uint8(data, w, h, 0, temp->data, x, y, 0, channels);
    temp->avgr = this->avgr;
    temp->avgg = this->avgg;
    temp->avgb = this->avgb;
    temp->name = this->name;
    temp->channels = this->channels;
    temp->w = x;
    temp->h = y;
    temp->size = x*y*channels;
    return temp;
}

void Image::convertToGray(){
    for(int i = 0; i < w*h*channels; i+=3){
        int average = (data[i]+data[i+1]+data[i+2])/3;
        data[i] = average;
        data[i+1] = average;
        data[i+2] = average;
    }
}

void Image::reflectHorUpDown(){
    for(int row = 0; row < w; row++){
        for(int col = h/2; col < h; col++){
            data[(row+(col*w))*channels+0] = data[((row)+((((h/2)-col)+h/2)*w))*channels+0];
            data[(row+(col*w))*channels+1] = data[((row)+((((h/2)-col)+h/2)*w))*channels+1];
            data[(row+(col*w))*channels+2] = data[((row)+((((h/2)-col)+h/2)*w))*channels+2];
        }
    }
}

void Image::reflectHorDownUp(){
    for(int row = 0; row < w; row++){
        for(int col = h/2; col > 0; col--){
            int temp = col - h/2;
            temp = temp * -1;
            temp = h/2 + temp;

            data[(row+(col*w))*channels+0] = data[(row+(temp*w))*channels+0];
            data[(row+(col*w))*channels+1] = data[(row+(temp*w))*channels+1];
            data[(row+(col*w))*channels+2] = data[(row+(temp*w))*channels+2];
        }
    }
}

void Image::reflectVerRigLeft(){
    for(int row = 0; row < w/2; row++){
        for(int col = 0; col < h; col++){
            int temp = w - row;
            data[(row+(col*w))*channels+0] = data[(temp+(col*w))*channels+0];
            data[(row+(col*w))*channels+1] = data[(temp+(col*w))*channels+1];
            data[(row+(col*w))*channels+2] = data[(temp+(col*w))*channels+2];
        }
    }
}

void Image::reflectVerLeftRig(){
    for(int row = w/2; row < w; row++){
        for(int col = 0; col < h; col++){
            int temp = w - row;
            data[(row+(col*w))*channels+0] = data[(temp+(col*w))*channels+0];
            data[(row+(col*w))*channels+1] = data[(temp+(col*w))*channels+1];
            data[(row+(col*w))*channels+2] = data[(temp+(col*w))*channels+2];
        }
    }
}

//
//  colorMaker
//
//  Makes 64x64 images of all colors
//
void Image::colorMaker(){

    for(int r = 0; r < 255; r+=10){
        for(int g = 0; g < 255; g+=10){
            for(int b = 0; b < 255; b+=10){
                Image temp(64, 64, 3);

                for(int i = 0; i < temp.w*temp.h*temp.channels; i+=3){
                    temp.data[i+0] = r;
                    temp.data[i+1] = g;
                    temp.data[i+2] = b;
                }
                string temp2 = to_string(r) + to_string(g) + to_string(b) + ".jpg";
                int n = sizeof(temp2);
                char char_array[n];
                strcpy(char_array, temp2.c_str());
                temp.write(char_array);
            }
        }
    }
}

//
//  findingCellSize
//
//  returns a pair of ints, xsize and ysize of
//  a cell that is divisible by the image dimensions
//
pair<int,int> Image::findingCellSize(){
    int wCellSize = w;
    int hCellSize = h;
    for(int i = 96; i >= 15; i--){
        if(w%i == 0)
            wCellSize = i;
        if(h%i == 0)
            hCellSize = i;
    }
    return make_pair(wCellSize, hCellSize);
}

//
//  rgbCellCalculation
//
//  replaces each pixel in a cell with
//  the average color found in that cell
//
uint8_t* Image::rgbCellCalculation(int cellX, int cellY){
    uint8_t* newData = new uint8_t[w*h*channels];
    for(int cury = 0; cury < h; cury+=cellY){
        for(int curx = 0; curx < w; curx+=cellX){
            int rdata = 0;
            int gdata = 0;
            int bdata = 0;
            for(int row = 0; row < cellX; row++){
                for(int col = 0; col < cellY; col++){
                    rdata += data[((curx+row)+((cury+col)*w))*channels+0];
                    gdata += data[((curx+row)+((cury+col)*w))*channels+1];
                    bdata += data[((curx+row)+((cury+col)*w))*channels+2];
                }
            }
            rdata = rdata/(cellX*cellY);
            gdata = gdata/(cellX*cellY);
            bdata = bdata/(cellX*cellY);
            for(int row = 0; row < cellX; row++){
                for(int col = 0; col < cellY; col++){
                    newData[((curx+row)+((cury+col)*w))*channels+0] = rdata;
                    newData[((curx+row)+((cury+col)*w))*channels+1] = gdata;
                    newData[((curx+row)+((cury+col)*w))*channels+2] = bdata;
                }
            }
        }
    }
    return newData;
}

//
//  getPicturesFromReservoir
//
vector<Image*> getPicturesFromReservoir(string reservoirPath){
    vector<Image*> imageReservoir;
    for(const auto & entry : fs::directory_iterator(reservoirPath)){
        string picPath = fs::absolute( entry.path() ).string();
        char pathdir[picPath.size()];
        strcpy(pathdir, picPath.c_str());
        string desiredname = picPath;
        int i = picPath.size();
        while(desiredname[i] != '\\'){
            i--;
        }
        desiredname = desiredname.substr(i+1);
        Image* curImg = new Image(pathdir, desiredname);
        imageReservoir.push_back(curImg);
    }
    return imageReservoir;
}

//
//  getDist
//
int getDist(int avgr, int avgg, int avgb, Image* compPic){
    int distR = (compPic->avgr)-avgr;
    int distG = (compPic->avgg)-avgg;
    int distB = (compPic->avgb)-avgb;
    return sqrt((distR*distR)+(distG*distG)+(distB*distB));
}

//
//  placeImages
//
void Image::placeImages(vector<Image*> imageReservoir, int cellX, int cellY){
    for(int cury = 0; cury < h; cury+=cellY){
        for(int curx = 0; curx < w; curx+=cellX){
            int closestPic = 0;
            int closestDist = 999;
            int index = 0;
            int avgr = data[(curx+(cury*w))*channels+0];
            int avgg = data[(curx+(cury*w))*channels+1];
            int avgb = data[(curx+(cury*w))*channels+2];
            for(auto picture : imageReservoir){
                int currDist = getDist(avgr, avgg, avgb, picture);
                if(currDist < closestDist){
                    closestDist = currDist;
                    closestPic = index;
                }
                index++;
            }
            Image* imageToPlace = imageReservoir[closestPic];
            // imageToPlace = imageToPlace->resize(cellX, cellY);
            for(int col = 0; col < cellY; col++){
                for(int row = 0; row < cellX; row++){
                    this->data[((curx+row)+((cury+col)*w))*channels+0] = imageToPlace->data[((row)+((col)*cellY))*channels+0];
                    this->data[((curx+row)+((cury+col)*w))*channels+1] = imageToPlace->data[((row)+((col)*cellY))*channels+1];
                    this->data[((curx+row)+((cury+col)*w))*channels+2] = imageToPlace->data[((row)+((col)*cellY))*channels+2];
                }
            }
        }
    }
}

//
//  imageReplacements
//
//  replaces the pixels in a cell with
//  an image found in the image reservoir
//
void Image::imageReplacements(int cellX, int cellY){
    string reservoirPath = "picture_reservoir";
    vector<Image*> imageReservoir = getPicturesFromReservoir(reservoirPath);
    for(int i = 0; i < imageReservoir.size(); i++){
        imageReservoir[i]->calculateAvgRGB();
        imageReservoir[i] = imageReservoir[i]->resize(cellX, cellY);
    }
    placeImages(imageReservoir, cellX, cellY);
}


//
//  createMosaic
//
//  first the picture is blurred to get the average colors of pixels around a given pixel
//  then get all pictures given in a folder
//  then replace the blurs with the given pictures
//

void Image::createMosaic(){
    pair<int, int> cellSize = this->findingCellSize();
    uint8_t* newData = this->rgbCellCalculation(cellSize.first, cellSize.second);
    uint8_t* oldData = this->data;
    this->data = newData;
    delete oldData;
    this->imageReplacements(cellSize.first, cellSize.second);

}