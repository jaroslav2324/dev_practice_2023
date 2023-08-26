#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <ctime>
#include <cmath>

#include <SDL.h>
#include <SDL_ttf.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

#define T2_DATA_FILE "task2_config.txt"
#define FONT_FILE_NAME "Pixellettersfull-BnJ5.ttf"

using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;

using std::string;
using std::vector;
using std::pair;

class FenceBuilder {
private:
	vector<pair<int, int>> vecCoordsTrees;
	pair<int, int> cornerPoints[4];
	int borderLength;
	int readCoords();
	int render(SDL_Renderer* renderer);
	int findCornerPoints();
	TTF_Font* font = nullptr;
public:
	FenceBuilder();
	~FenceBuilder();
	int loop();
};

int generateCoordsTrees();