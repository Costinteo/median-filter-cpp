#include "Image.hpp"


Image::Image(int w, int h, int n, int maxP) {
        width = w;
        height = h;
        window = n;
        maxPixelValue = maxP;
        pixelValues.resize(height);
        for (int i = 0; i < height; i++)
            pixelValues[i].resize(width);
}

Image::Image(const Image& obj) {
        width = obj.width;
        height = obj.height;
        window = obj.window;
        maxPixelValue = obj.maxPixelValue;
        pixelValues.resize(height);
        for (int i = 0; i < height; i++)
            pixelValues[i].resize(width);
}

uint16_t& Image::operator[](const std::pair<int, int> coord) {
        return pixelValues[coord.first][coord.second];
}

Image& Image::operator=(const Image& obj){
        this->pixelValues = obj.pixelValues;
        return *this;
}

uint16_t Image::valueOfPixel(int x, int y) const {
        if (x <= 0 and y <= 0) return pixelValues[0][0];
        else if (x <= 0 and y > 0) return pixelValues[std::min(y, this->getHeight() - 1)][0]; // if y out of bounds then take the max y possible
        else if (x > 0 and y <= 0) return pixelValues[0][std::min(x, this->getWidth() - 1)]; // if x oob then take the max x possible
        else if (x > 0 and y > 0) return pixelValues[std::min(y, this->getHeight() - 1)][std::min(x, this->getWidth() - 1)];
        else return -1;  // won't ever reach this case
}

// we presume x and y in bounds for this function
void Image::modifyPixel(int x, int y, int value) {
        pixelValues[y][x] = value;
}

uint16_t Image::calcMedianValueForPixel(int x, int y, const std::string& sortAlg) const{
        std::vector<uint16_t> medianArr;
        for (int i = -window / 2; i <= window / 2; i++) {
            for (int j = -window / 2; j <= window / 2; j++) {
                medianArr.push_back(valueOfPixel(x + i, y + j));
            }
        }
        if (sortAlg == "merge") {
            stable_sort(medianArr.begin(), medianArr.end());
            return medianArr[medianArr.size() / 2];
        } else if (sortAlg == "bubble") {
            for (int i = 0; i < medianArr.size(); i++) {
                for (int j = i + 1; j < medianArr.size(); j++) {
                    if (medianArr[i] > medianArr[j])
                        std::swap(medianArr[i], medianArr[j]);
                }
            }
            return medianArr[medianArr.size() / 2];
        }
        return -1; // won't ever reach this return if input is correct
    }