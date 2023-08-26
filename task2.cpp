#include "task2.h"

FenceBuilder::FenceBuilder()
	: font(TTF_OpenFont(FONT_FILE_NAME, 12))
{
	readCoords();
	findCornerPoints();

}

FenceBuilder::~FenceBuilder()
{
}

int FenceBuilder::readCoords()
{
	ifstream fin(T2_DATA_FILE);

	int amount_trees;
	fin >> amount_trees;
	
	int x, y;
	for (int i = 0; i < amount_trees; i++) {
		fin >> x;
		fin >> y;
		vecCoordsTrees.push_back(pair<int, int>(x, y));
	}

	fin.close();
	return 0;
}

int FenceBuilder::render(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);

	// draw fence
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderDrawLine(renderer, cornerPoints[0].first, cornerPoints[0].second, cornerPoints[1].first, cornerPoints[1].second);
	SDL_RenderDrawLine(renderer, cornerPoints[1].first, cornerPoints[1].second, cornerPoints[2].first, cornerPoints[2].second);
	SDL_RenderDrawLine(renderer, cornerPoints[2].first, cornerPoints[2].second, cornerPoints[3].first, cornerPoints[3].second);
	SDL_RenderDrawLine(renderer, cornerPoints[3].first, cornerPoints[3].second, cornerPoints[0].first, cornerPoints[0].second);

	// draw trees

	SDL_Color textClr = { 0, 0, 0, 255 };
	for (auto point : vecCoordsTrees) {

		char val_str_buff[12]{};
		_itoa_s(point.first, val_str_buff, 10);
		string x_str = val_str_buff;
		_itoa_s(point.second, val_str_buff, 10);
		string y_str = val_str_buff;
		string str = "(" + x_str + ", " + y_str + ")";

		SDL_Surface* coordsSurf = TTF_RenderText_Blended(font, str.c_str(), textClr);
		SDL_Texture* coordsTexture = SDL_CreateTextureFromSurface(renderer, coordsSurf);

		SDL_Rect dstRect = { point.first - 20, point.second - 20, 40, 20};
		SDL_RenderCopy(renderer, coordsTexture, 0, &dstRect);

		SDL_FreeSurface(coordsSurf);
		SDL_DestroyTexture(coordsTexture);

		SDL_SetRenderDrawColor(renderer, 0, 200, 0, 255);
		SDL_Rect treeRect = { point.first - 2, point.second - 2, 5, 5 };
		SDL_RenderFillRect(renderer, &treeRect);
	}

	char val_str_buff[12]{};
	_itoa_s(borderLength, val_str_buff, 10);
	string border_length_val_str = val_str_buff;
	string border_length_str = "Border length : " + border_length_val_str;

	SDL_Surface* borderStrSurface = TTF_RenderText_Blended(font, border_length_str.c_str(), textClr);
	SDL_Texture* borderStrTexture = SDL_CreateTextureFromSurface(renderer, borderStrSurface);

	SDL_Rect dstRect = { WINDOW_WIDTH - 150,  0, 130, 20 };
	SDL_RenderCopy(renderer, borderStrTexture, 0, &dstRect);

	SDL_FreeSurface(borderStrSurface);
	SDL_DestroyTexture(borderStrTexture);

	SDL_RenderPresent(renderer);
	return 0;
}

int FenceBuilder::findCornerPoints()
{
	int minX, minY, maxX, maxY;
	auto firstPair = vecCoordsTrees.front();
	minX = maxX = firstPair.first;
	minY = maxY = firstPair.second;
	for (auto point : vecCoordsTrees) {
		minX = fmin(minX, point.first);
		maxX = fmax(maxX, point.first);
		minY = fmin(minY, point.second);
		maxY = fmax(maxY, point.second);
	}
	cornerPoints[0] = pair<int, int>(minX, minY);
	cornerPoints[1] = pair<int, int>(maxX, minY);
	cornerPoints[2] = pair<int, int>(maxX, maxY);
	cornerPoints[3] = pair<int, int>(minX, maxY);

	borderLength = (maxX - minX) * 2 + (maxY - minY) * 2;

	return 0;
}


int FenceBuilder::loop()
{
	bool exit_task = false;

	SDL_Window* win = SDL_CreateWindow("pr", 50, 50, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
	SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);

	while (!exit_task) {

		SDL_Event ev;
		while (SDL_PollEvent(&ev) != 0) {
			if (ev.type == SDL_QUIT) {
				exit_task = true;
				break;
			}
		}
		render(ren);
	}

	return 0;
}

int generateCoordsTrees()
{
	const int MIN_X_COORD = 20;
	const int MAX_X_COORD = WINDOW_WIDTH - 20;
	const int MIN_Y_COORD = 20;
	const int MAX_Y_COORD = WINDOW_HEIGHT - 20;
	const int MIN_AMOUNT_TREES = 3;
	const int MAX_AMOUNT_TREES = 20;

	ofstream fout(T2_DATA_FILE);
	srand(time(0));
	int amountTrees = rand() % (MAX_AMOUNT_TREES - MIN_AMOUNT_TREES) + MIN_AMOUNT_TREES;
	fout << amountTrees << endl;

	for (int i = 0; i < amountTrees; i++) {
		int x = rand() % WINDOW_WIDTH;
		int y = rand() % WINDOW_HEIGHT;
		x = fmin(x, MAX_X_COORD);
		x = fmax(x, MIN_X_COORD);
		y = fmin(y, MAX_Y_COORD);
		y = fmax(y, MIN_Y_COORD);
		fout << x << " " << y << endl;
	}
	fout.close();
	return 0;
}
