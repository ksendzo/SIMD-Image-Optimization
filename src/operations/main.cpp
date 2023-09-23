// AOR2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "Cache.h"
#include <vector>
#include "Timer.h"

using namespace std;

void parse_arguments(int argc, char* argv[]);
void load_image(char* filename, int* width, int* height, int* channels, vector<float> &photo);
void store_image(char* filename, vector<float> picture, int width, int height);

void optimized_execution(vector<float>& picture, int height, int width);
void unoptimized_execution(vector<float>& picture, int height, int width);

int main(int argc, char* argv[])
{
    if (argc <= 1)
        return 0;
    char* inputFile = argv[1], * outputFile = argv[2];
    parse_arguments(argc, argv);
    Cache::cache_info();

    cout << "Cache line: " << Cache::cacheLine << endl;
    cout << "Cache size: " << Cache::cacheSize << endl;
    cout << "Cache assoc: " << Cache::cacheAssociativity << endl;

    int width, height, channels;
    vector<float> picture;
    load_image(inputFile, &width, &height,  &channels, picture);
    vector<float> unopPicture(picture);
    Timer optimizedTimer, unoptimizedTimer;

    optimizedTimer.StartTimer();
    optimized_execution(picture, height, width);
    optimizedTimer.EndTimer();

    unoptimizedTimer.StartTimer();
    unoptimized_execution(unopPicture, height, width);
    unoptimizedTimer.EndTimer();

    double acc = (long double)unoptimizedTimer.Duration() / (long double)optimizedTimer.Duration();
    cout << "Ubrzanje je: " << acc << endl;

    store_image(outputFile, picture, width, height);
    store_image( (char*)"check.jpg", unopPicture, width, height);

    
    return 0;
}
