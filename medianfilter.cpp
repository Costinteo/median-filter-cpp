#include <iostream>
#include <fstream>
#include "Image.hpp"

void applyMedianFilter(Image& img, const std::string& sortAlg) {
    Image copyImg(img);
    for (int i = 0; i < img.getHeight(); i++) {
        for (int j = 0; j < img.getWidth(); j++) {
            uint16_t medianValue = img.calcMedianValueForPixel(j, i, sortAlg);
            copyImg.modifyPixel(j, i, medianValue);
        }
    }
    img = copyImg;
}

int main() {
    std::string sortAlg;
    int n;
    std::string inputFilename, outputFilename;
    std::cin >> sortAlg >> n >> inputFilename >> outputFilename;
    std::ifstream fin(inputFilename);
    std::ofstream fout(outputFilename);

    std::string fileType;
    fin >> fileType;
    fout << fileType << std::endl;

    fin.get();
    std::string line;
    while(true) {
        std::getline(fin, line);
        if (line.find('#') == std::string::npos) {
            break;
        }
    }
    int width, height;
    width = stoi(line.substr(0,line.find(' ')));
    height = stoi(line.substr(line.find(' ') + 1, line.length() - line.find(' ')));
    fout << width << " " << height << std::endl;

    while(true) {
        getline(fin, line);
        if (line.find('#') == std::string::npos) {
            break;
        }
    }

    int maxPixelValue;
    maxPixelValue = stoi(line);
    fout << maxPixelValue << std::endl;

    Image img(width, height, n, maxPixelValue);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            fin >> img[{i, j}];
        }
    }

    applyMedianFilter(img, sortAlg);

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            fout << img[{i, j}] << " ";
        }
        fout << std::endl;
    }

    return 0;
}
