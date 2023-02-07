<<<<<<< Updated upstream
// Copyright 2021, Aline Normoyle, alinen

#include "image.h"
#include <iostream>
#include <cassert>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#include <fstream>
#define STBI_MSC_SECURE_CRT

namespace agl {


Image::Image() : Width(1), Height(1), Data(new unsigned char[3]), Channels_num(3) {
}

Image::Image(int width, int height) : Width(width), Height(height), Data(new unsigned char[width*height*3]), Channels_num(3) {
}

Image::Image(const Image& orig) : Width(orig.width()), Height(orig.height()), Data(orig.data()), Channels_num(orig.channels_num()) {
}

Image& Image::operator=(const Image& orig) {
  if (&orig == this) {
    return *this;
  }
  Width = orig.Width;
  Height = orig.Height;
  Data = orig.Data;
  Channels_num = orig.Channels_num;
  return *this;
}

Image::~Image() {
}

int Image::width() const { 
    return this->Width;
}

int Image::height() const {
   return this->Height;
}

unsigned char* Image::data() const {
   return this->Data;
}

int Image::channels_num() const {
    return this->Channels_num;
}

bool Image::load(const std::string& filename, bool flip) {
    Data = stbi_load(filename.c_str(), &Width, &Height, &Channels_num, 3);
    if (Data == NULL) {
        return false;
    }
    return true;
}

bool Image::save(const std::string& filename, bool flip) const {
    return stbi_write_png(filename.c_str(), width(), height(), channels_num(), data(), width() * channels_num());
}

Pixel Image::get(int row, int col) const {
    if (row * width() + col >= width() * height()) {
        std::cout << "Invalid dimensions" << std::endl;
        Pixel p;
        return p;
    }
    Pixel p;
    p.r = data()[(row * width() + col) * channels_num()];
    p.g = data()[(row * width() + col) * channels_num() + 1];
    p.b = data()[(row * width() + col) * channels_num() + 2];
    return p;
}

Pixel Image::get(int i) const
{
    if (i >= width() * height() * channels_num()) {
        std::cout << "Invalid dimensions" << std::endl;
        Pixel p;
        return p;
    }
    Pixel p;
    p.r = data()[i];
    p.g = data()[i + 1];
    p.b = data()[i + 2];
    return p;
}

void Image::set(int width, int height, unsigned char* data) {
    this->Width = width;
    this->Height = height;
    this->Data = data;
}

void Image::set(int row, int col, const Pixel& color) {
    if (row * width() + col >= width() * height()) {
        std::cout << "Invalid dimensions" << std::endl;
        return;
    }
    data()[(row * (width() - 1) + col) * channels_num()] = color.r;
    data()[(row * (width() - 1) + col) * channels_num() + 1] = color.g;
    data()[(row * (width() - 1) + col) * channels_num() + 2] = color.b;
}

Image Image::resize(int w, int h) const {
   Image result(w, h);
   for (int i = 0; i < h; ++i) {
       for (int j = 0; j < w; ++j) {
           result.data()[(i * w + j) * channels_num()] = data()[(i * height() / h * width() + (j * width() / w)) * channels_num()];
           result.data()[(i * w + j) * channels_num() + 1] = data()[(i * height() / h * width() + (j * width() / w)) * channels_num() + 1];
           result.data()[(i * w + j) * channels_num() + 2] = data()[(i * height() / h * width() + (j * width() / w)) * channels_num() + 2];
       }
   }
   return result;
}

Image Image::flipHorizontal() const {
   Image result(width(), height());
   for (int i = 0; i < height(); ++i) {
       for (int j = 0; j < width(); ++j) {
           result.data()[((i * width()) + width() - j) * channels_num()] = data()[(i * width() + j) * channels_num()];
           result.data()[((i * width()) + width() - j) * channels_num() + 1] = data()[(i * width() + j) * channels_num() + 1];
           result.data()[((i * width()) + width() - j) * channels_num() + 2] = data()[(i * width() + j) * channels_num() + 2];
       }
   }
   return result;
}

Image Image::flipVertical() const {
   Image result(Width, Height);
   /*for (int i = 0; i < Height; ++i) {
       for (int j = 0; j < Width; ++j) {
           result.Data[((Height - i - 1) * i + j) * channels_num] = Data[(i*(Width-1)+j) * channels_num];
           result.Data[((Height - i - 1) * i + j) * channels_num + 1] = Data[(i * (Width - 1) + j) * channels_num + 1];
           result.Data[((Height - i - 1) * i + j) * channels_num + 2] = Data[(i * (Width - 1) + j) * channels_num + 2];
       }
   }*/
   return result;
}

Image Image::rotate90() const {
    Image result(Width, Height);
    /*for (int i = 0; i < Height; ++i) {
        for (int j = 0; j < Width; ++j) {
            result.Data[(j*(Height-1) - i) * channels_num] = Data[(i * (Width-1) + j) * channels_num];
            result.Data[(j * (Height - 1) - i) * channels_num + 1] = Data[(i * (Width - 1) + j) * channels_num + 1];
            result.Data[(j * (Height - 1) - i) * channels_num + 2] = Data[(i * (Width - 1) + j) * channels_num + 2];
        }
    }*/
    return result;
}

Image Image::subimage(int startx, int starty, int w, int h) const {
    if (!(startx < width() && starty < height() && w <= width() && h <= height())) {
        std::cout << "illegal dimensions, subimage must be equal to or smaller than original image" << std::endl;
        return Image();
    }
    Image sub = Image(w, h);
    for (int i = 0; i < h; ++i) {
         for (int j = 0; j < w; ++j) {
             sub.data()[(i * w + j) * channels_num()] = data()[((starty + i) * width() + startx + j) * channels_num()];
             sub.data()[(i * w + j) * channels_num() + 1] = data()[((starty + i) * width() + startx + j) * channels_num() + 1];
             sub.data()[(i * w + j) * channels_num() + 2] = data()[((starty + i) * width() + startx + j) * channels_num() + 2];
        }
    }
    return sub;
}

void Image::replace(const Image& image, int startx, int starty) {
    Image result = Image(width(), height());
    result.Data = data();
    for (int i = 0; i < std::min(height(), image.height()); ++i) {
         for (int j = 0; j < std::min(width(), image.width()); ++j) {
            result.data()[((startx + i) * width() + j + starty) * channels_num()] = image.data()[(i * image.width() + j) * image.channels_num()];
            result.data()[((startx + i) * width() + j + starty)* channels_num() + 1] = image.data()[(i * image.width() + j) * image.channels_num() + 1];
            result.data()[((startx + i) * width() + j + starty)* channels_num() + 2] = image.data()[(i * image.width() + j) * image.channels_num() + 2];
         }
    }
}

Image Image::swirl() const {
   Image result(0, 0);
   return result;
}

Image Image::add(const Image& other) const {
   Image result(0, 0);
  
   return result;
}

Image Image::subtract(const Image& other) const {
   Image result(0, 0);
   
   return result;
}

Image Image::multiply(const Image& other) const {
   Image result(0, 0);
   
   return result;
}

Image Image::difference(const Image& other) const {
   Image result(0, 0);
  
   return result;
}

Image Image::lightest(const Image& other) const {
   Image result(0, 0);
  
   return result;
}

Image Image::darkest(const Image& other) const {
   Image result(0, 0);
  
   return result;
}

Image Image::gammaCorrect(float gamma) const {
    Image result(width(), height());
    for (int i = 0; i < width() * height() * channels_num(); ++i) {
        result.data()[i] = pow(data()[i] / 255.0f, (1.0f / gamma)) * 255.0f;
        result.data()[i + 1] = (data()[i + 1] / 255.0f, (1.0f / gamma)) * 255.0f;
        result.data()[i + 2] = (data()[i + 2] / 255.0f, (1 / gamma)) * 255.0f;
    }
    return result;
}

Image Image::alphaBlend(const Image& other, float alpha) const {
    if (width() != other.width() || height() != other.height()) {
        std::cout << "images must have the same dimensions to alpha blend" << std::endl;
        return Image();
    }
    Image result = Image(width(), height());
    for (int i = 0; i < width() * height() * channels_num(); ++i) {
        result.data()[i] = (data()[i] * (1 - alpha)) + (other.data()[i] * alpha);
    }
    return result;
}

Image Image::invert() const {
   Image image(0, 0);
   
   return image;
}

Image Image::grayscale() const {
    Image result(width(), height());
    for (int i = 0; i < height(); ++i) {
        for (int j = 0; j < width(); ++j) {
            unsigned char intensity = data()[(i * width() + j) * channels_num()] / 3.0 + 0.59 * data()[(i * width() + j) * channels_num() + 1] + 0.11 * data()[(i * width() + j) * channels_num() + 2];
            result.data()[(i * width() + j) * channels_num()] = intensity;
            result.data()[(i * width() + j) * channels_num() + 1] = intensity;
            result.data()[(i * width() + j) * channels_num() + 2] = intensity;
        }
    }
    return result;
}

Image Image::colorJitter(int size) const {
   Image image(0, 0);
  
   return image;
}

Image Image::bitmap(int size) const {
   Image image(0, 0);
   
   return image;
}

void Image::fill(const Pixel& c) {
  }

}  // namespace agl

=======
// Copyright 2021, Aline Normoyle, alinen

#include "image.h"

#include <cassert>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

namespace agl {


Image::Image() : Width(1), Height(1), Data(new unsigned char[3]), Channels_num(3){
}

Image::Image(int width, int height) : Width(width), Height(height), Data(new unsigned char[height*width*Channels_num]), Channels_num(3) {
}

Image::Image(const Image& orig) : Width(orig.Width), Height(orig.Height), Data(orig.Data), Channels_num(orig.Channels_num) {
}

Image& Image::operator=(const Image& orig) {
    if (&orig == this) {
        return *this;
    }
    this->Width = orig.width();
    this->Height = orig.height();
    this->Channels_num = orig.channels_num();
    this->Data = orig.Data;
    return *this;
}

Image::~Image() {
}

int Image::width() const { 
   return this->Width;
}

int Image::height() const {
   return this->Height;
}

unsigned char* Image::data() const {
   return this->Data;
}

int Image::channels_num() const {
    return this->Channels_num;
}

void Image::set(int width, int height, unsigned char* data) {
    this->Width = width;
    this->Height = height;
    this->Data = data;
}

bool Image::load(const std::string& filename, bool flip) {
    this->Data = stbi_load(filename.c_str(), &Width, &Height, &Channels_num, 3);
    return Data != NULL;
}


bool Image::save(const std::string& filename, bool flip) const {
    return stbi_write_png(filename.c_str(), width(), height(), channels_num(), data(), 100);
}

Pixel Image::get(int row, int col) const {
    Pixel p;
    p.r = data()[(row * width() + col) * channels_num()];
    p.g = data()[(row * width() + col)* channels_num() + 1];
    p.b = data()[(row * width() + col) * channels_num() + 2];
    return p;
}

void Image::set(int row, int col, const Pixel& color) {
    data()[(row * width() + col) * channels_num()] = color.r;
    data()[(row * width() + col) * channels_num() + 1] = color.g;
    data()[(row * width() + col) * channels_num() + 2] = color.b;
}


Pixel Image::get(int i) const
{
    Pixel p;
    p.r = data()[i * channels_num()];
    p.g = data()[i * channels_num()  + 1];
    p.b = data()[i * channels_num() + 2];
    return p;
}

void Image::set(int i, const Pixel& c)
{
    data()[i*channels_num()] = c.r;
    data()[i * channels_num() + 1] = c.g;
    data()[i *channels_num() + 2] = c.b;
}

Image Image::resize(int w, int h) const {
   Image result(w, h);
   for (int i = 0; i < this->Height; ++i) {
       for (int j = 0; j < width(); ++j) {
           result.data()[((i * height() / h * w) + (j * width() / w)) * channels_num()] = data()[(i * width() + j) * channels_num()];
           result.data()[((i * height() / h * w) + (j * width() / w)) * channels_num() + 1] = data()[(i * width() + j) * channels_num() + 1];
           result.data()[((i * height() / h * w) + (j * width() / w)) * channels_num() + 2] = data()[(i * width() + j) * channels_num() + 2];
       }
   }
   return result;
}

Image Image::flipHorizontal() const {
    Image result(width(), height());
    for (int i = 0; i < height(); ++i) {
        for (int j = 0; j < width(); ++j) {
            result.data()[(i*width() + width() - j) * channels_num()] = data()[(i*width()+j)*channels_num()];
            result.data()[(i * width() + width() - j) * channels_num() + 1] = data()[(i * width() + j) * channels_num() + 1];
            result.data()[(i * width() + width() - j) * channels_num() + 2] = data()[(i * width() + j) * channels_num() + 2];
        }
    }
    return result;

}

Image Image::flipVertical() const {
   Image result(0, 0);
   return result;
}

Image Image::rotate90() const {
   Image result(0, 0);
  
   return result;
}

Image Image::subimage(int startx, int starty, int w, int h) const {
    Image result(w, h);
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            result.data()[((i * w) + j) * channels_num()] = data()[((i + starty) * width() + j + startx)* channels_num()];
            result.data()[((i * w) + j) * channels_num() + 1] = data()[((i + starty) * width() + j + startx) * channels_num() + 1];
            result.data()[((i * w) + j)* channels_num() + 2] = data()[((i + starty) * width() + j + startx)* channels_num() + 2];
        }
    }
    return result;
}

void Image::replace(const Image& image, int startx, int starty) {
    Image result(width(), height());
    result.Data = data();
    for (int i = 0; i < std::min(image.height(), height()); ++i) {
        for (int j = 0; j < std::min(image.width(), width()); ++j) {
            result.data()[((i + starty) * width() + j + starty) * channels_num()] = data()[(i * image.width() + j) * channels_num()];
            result.data()[((i + starty) * width() + j + starty) * channels_num() + 1] = data()[(i * image.width() + j) * channels_num() + 1];
            result.data()[((i + starty) * width() + j + starty) * channels_num() + 2] = data()[(i * image.width() + j) * channels_num() + 2];
        }
    }
    this->Data = result.data();
}

Image Image::swirl() const {
   Image result(0, 0);
   return result;
}

Image Image::add(const Image& other) const {
   Image result(0, 0);
  
   return result;
}

Image Image::subtract(const Image& other) const {
   Image result(0, 0);
   
   return result;
}

Image Image::multiply(const Image& other) const {
   Image result(0, 0);
   
   return result;
}

Image Image::difference(const Image& other) const {
   Image result(0, 0);
  
   return result;
}

Image Image::lightest(const Image& other) const {
   Image result(0, 0);
  
   return result;
}

Image Image::darkest(const Image& other) const {
   Image result(0, 0);
  
   return result;
}

Image Image::gammaCorrect(float gamma) const {
    Image result(width(), height());
    for (int i = 0; i < width()*height()*channels_num(); ++i) {
        result.data()[i] = pow(data()[i] / 255.0f, 1 / gamma) * 255.0f;
    }
    return result;
}

Image Image::alphaBlend(const Image& other, float alpha) const {
    Image result(width(), height());
    for (int i = 0; i < height(); ++i) {
        for (int j = 0; j < width(); ++j) {
            result.data()[(i * width() + j) * channels_num()] = data()[(i * width() + j) * channels_num()] * (1 - alpha) + other.data()[(i * width() + j) * channels_num()] * alpha;
            result.data()[(i * width() + j) * channels_num() + 1] = data()[(i * width() + j) * channels_num() + 1] * (1 - alpha) + other.data()[(i * width() + j) * channels_num() + 1] * alpha;
            result.data()[(i * width() + j) * channels_num() + 2] = data()[(i * width() + j) * channels_num() + 2] * (1 - alpha) + other.data()[(i * width() + j) * channels_num() + 2] * alpha;
        }
    }
    return result;
}

Image Image::invert() const {
   Image image(0, 0);
   
   return image;
}

Image Image::grayscale() const {
    Image result(width(), height());
    for (int i = 0; i < height(); ++i) {
        for (int j = 0; j < width(); ++j) {
            unsigned char intensity = data()[(i * width() + j) * channels_num()] / 3.0f + data()[(i * width() + j)* channels_num() + 1] * 0.59f + data()[(i * width() + j)* channels_num() + 2] * 0.11f;
            result.data()[(i * width() + j) * channels_num()] = intensity;
            result.data()[(i * width() + j) * channels_num() + 1] = intensity;
            result.data()[(i * width() + j) * channels_num() + 2] = intensity;
        }
    }
    return result;
}

Image Image::colorJitter(int size) const {
   Image image(0, 0);
  
   return image;
}

Image Image::bitmap(int size) const {
   Image image(0, 0);
   
   return image;
}

void Image::fill(const Pixel& c) {
  }

}  // namespace agl

>>>>>>> Stashed changes
