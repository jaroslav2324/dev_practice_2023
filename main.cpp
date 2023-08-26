#include <iostream>
#include <fstream>

#include "SDL.h"
#include "SDL_ttf.h"

#include "task1.h"
#include "task2.h"
#include "task3.h"

int main(int argc, char* argv[]) {

	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();

	// task 1
	//std::ios_base::sync_with_stdio(0);
	//std::cin.tie(0);
	//std::cout.tie(0);
	//executeTask();

	// task2
	//generateCoordsTrees();
	//FenceBuilder fenceBuilder;
	//fenceBuilder.loop();
	//fenceBuilder.~FenceBuilder();

	// task 3
	SetOfStacks set;
	set.loop();
	set.~SetOfStacks();

	TTF_Quit();
	SDL_Quit();
	return 0;
}