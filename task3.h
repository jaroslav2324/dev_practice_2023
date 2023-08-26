#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <random>
#include <time.h>

#include <SDL.h>
#include <SDL_ttf.h>

using std::string;
using std::stack;
using std::cin;
using std::cout;
using std::endl;
using std::ifstream;

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

#define AMOUNT_STACKS 4 // do not change
#define T3_CONFIG_FILE_NAME "task3_config.txt"
#define FONT_FILE_NAME "Pixellettersfull-BnJ5.ttf"

#define STACK_ELM_WIDTH_ON_SCREEN 100
#define STACK_ELM_HEIGHT_ON_SCREEN 50
#define SPACE_BETWEEN_ELMS_ON_SCREEN 20

class SetOfStacks {
private:
	stack<int> stacksArr[AMOUNT_STACKS];
	unsigned int n;
	unsigned int maxn;
	unsigned int currentAmountElements = 0;
	unsigned int currentStack = 0;
	int topElmVal = 0; // to display on screen
	TTF_Font* font = nullptr;

	int renderLabelAndInt(SDL_Renderer* renderer, string label, int val, SDL_Rect* dst_rect,SDL_Color text_clr = { 0, 0, 0, 255 });
	int renderText(SDL_Renderer* renderer);
	int render(SDL_Renderer* renderer);

	void printState();

public:
	SetOfStacks();
	~SetOfStacks();
	int push(int val);
	int pop(int* ret_top_val);
	int loop();
};
