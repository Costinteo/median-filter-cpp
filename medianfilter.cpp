#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

class Image {
private:
    int width, height, window, maxPixelValue;
    vector<vector<uint16_t>> pixelValues;
public:
    Image(int w, int h, int n, int maxP) {
        width = w;
        height = h;
        window = n;
        maxPixelValue = maxP;
        pixelValues.resize(height);
        for (int i = 0; i < height; i++)
            pixelValues[i].resize(width);
    }
    Image(const Image& obj) {
        width = obj.width;
        height = obj.height;
        window = obj.window;
        maxPixelValue = obj.maxPixelValue;
        pixelValues.resize(height);
        for (int i = 0; i < height; i++)
            pixelValues[i].resize(width);
    }
    int getWidth() const { return width; }
    int getHeight() const { return height; }
    uint16_t& operator[](const pair<int, int> coord) {
        return pixelValues[coord.first][coord.second];
    }
    Image& operator=(const Image& obj) {
        this->pixelValues = obj.pixelValues;
        return *this;
    }
    uint16_t valueOfPixel(int x, int y) const {
        if (x <= 0 and y <= 0) return pixelValues[0][0];
        else if (x <= 0 and y > 0) return pixelValues[min(y, this->getHeight() - 1)][0]; // if y out of bounds then take the max y possible
        else if (x > 0 and y <= 0) return pixelValues[0][min(x, this->getWidth() - 1)]; // if x oob then take the max x possible
        else if (x > 0 and y > 0) return pixelValues[min(y, this->getHeight() - 1)][min(x, this->getWidth() - 1)];
    }

    // we presume x and y in bounds for this function
    void modifyPixel(int x, int y, int value) {
        pixelValues[y][x] = value;
    }

    uint16_t calcMedianValueForPixel(int x, int y, const string& sortAlg) const {
        vector<uint16_t> medianArr;
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
                        swap(medianArr[i], medianArr[j]);
                }
            }
            return medianArr[medianArr.size() / 2];
        }
    }

};

void applyMedianFilter(Image& img, const string& sortAlg) {
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
    string sortAlg;
    int n;
    string inputFilename, outputFilename;
    cin >> sortAlg >> n >> inputFilename >> outputFilename;
    ifstream fin(inputFilename);
    ofstream fout(outputFilename);

    string fileType;
    fin >> fileType;
    cout << fileType << endl;
    fout << fileType << endl;

    fin.get();
    string line;
    while(true) {
        getline(fin, line);
        if (line.find('#') == string::npos) {
            break;
        }
    }
    int width, height;
    width = stoi(line.substr(0,line.find(' ')));
    height = stoi(line.substr(line.find(' ') + 1, line.length() - line.find(' ')));
    cout << width << " " << height << endl;
    fout << width << " " << height << endl;

    while(true) {
        getline(fin, line);
        if (line.find('#') == string::npos) {
            break;
        }
    }

    int maxPixelValue;
    maxPixelValue = stoi(line);
    cout << maxPixelValue << endl;
    fout << maxPixelValue << endl;

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
        fout << endl;
    }

    return 0;
}
