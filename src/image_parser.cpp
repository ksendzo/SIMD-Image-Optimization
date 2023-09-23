
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_image_write.h"
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

void load_image(char* filename, int *width, int* height, int* channels, vector<float>& picture) {
    unsigned char* data = stbi_load(filename, width, height, channels, 0);
    
    picture.resize((*width) * (*height) * (*channels));
    
    for (size_t i = 0; i < picture.size(); i += *channels) {
        picture[i] = ((float)data[i]);
        picture[i + 1] = ((float)data[i + 1]);
        picture[i + 2] = ((float)data[i + 2]);
    }

    free(data);
}

void store_image(char* filename, vector<float> picture, int width, int height) {
    int size = picture.size();
    unsigned char *pixels = new unsigned char[size];
    for (size_t i = 0; i < size; ++i) {
        pixels[i] = (unsigned char) (max(min(picture[i], 255.0f), 0.0f));
    }
    string sf = filename;
    if (sf[sf.length() - 1] == 'g')
        stbi_write_jpg(filename, width, height, 3, pixels, 100);
    else
        stbi_write_bmp(filename, width, height, 3, pixels);
    delete[] pixels;
}