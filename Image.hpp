#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#ifndef Image_hpp
#define Image_hpp

class Image {
private:
    int width, height, window, maxPixelValue;
    std::vector<std::vector<uint16_t>> pixelValues;
public:
    Image(int w, int h, int n, int maxP);
    Image(const Image& obj);
    int getWidth() const { return width; }
    int getHeight() const { return height; }
    uint16_t& operator[](const std::pair<int, int> coord);
    Image& operator=(const Image& obj);
    uint16_t valueOfPixel(int x, int y) const;
    void modifyPixel(int x, int y, int value);
    uint16_t calcMedianValueForPixel(int x, int y, const std::string& sortAlg) const;

};

#endif