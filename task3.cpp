#include "task3.h"

SetOfStacks::SetOfStacks()
	: font(TTF_OpenFont(FONT_FILE_NAME, 36))
{
	srand(time(0));

	ifstream fin(T3_CONFIG_FILE_NAME);
	fin >> n;
	fin >> maxn;
	fin.close();
	//font = TTF_OpenFont(FONT_FILE_NAME, 36);
}

SetOfStacks::~SetOfStacks()
{
	if (font != nullptr) {
		TTF_CloseFont(font);
		font = nullptr;
	}
}

int SetOfStacks::push(int val)
{
	if (currentStack * n + currentAmountElements == maxn) {
		// maxn blocks stacks growth
		return -1;
	}

	if (currentAmountElements == n) {
		if (currentStack == AMOUNT_STACKS - 1) {
			// no more place in stacks, all stacks are full
			return -1;
		}
		else {
			// add in new stack
			currentStack++;
			currentAmountElements = 1;
			stacksArr[currentStack].push(val);
			return 0;
		}
	}

	stacksArr[currentStack].push(val);
	currentAmountElements++;

	return 0;
}

int SetOfStacks::pop(int* ret_top_val)
{
	if (currentAmountElements == 0) {
		if (currentStack == 0) {
			// no elements in stacks
			return -1;
		}
		else {

			currentStack--;
			currentAmountElements = n - 1;
			int ret_val = stacksArr[currentStack].top();
			stacksArr[currentStack].pop();
			*ret_top_val = ret_val;
			return 0;
		}
	}
	currentAmountElements--;
	int ret_val = stacksArr[currentStack].top();
	stacksArr[currentStack].pop();
	*ret_top_val = ret_val;
	return 0;
}

int SetOfStacks::render(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_Rect window_rect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
	SDL_RenderFillRect(renderer, &window_rect);

	SDL_SetRenderDrawColor(renderer, 150, 150, 255, 255);
	int first_elm_y = (WINDOW_HEIGHT - 20) - STACK_ELM_HEIGHT_ON_SCREEN;
	int first_elm_x = 20;


	// draw filled stacks except last
	int x = first_elm_x;
	int y = first_elm_y;
	for (int i = 0; i < currentStack; i++) {
		for (int j = 0; j < n; j++) {
			SDL_Rect elm_rect = { x, y, STACK_ELM_WIDTH_ON_SCREEN, STACK_ELM_HEIGHT_ON_SCREEN };
			SDL_RenderFillRect(renderer, &elm_rect);
			y -= STACK_ELM_HEIGHT_ON_SCREEN + SPACE_BETWEEN_ELMS_ON_SCREEN;
		}
		x += STACK_ELM_WIDTH_ON_SCREEN + SPACE_BETWEEN_ELMS_ON_SCREEN;
		y = first_elm_y;
	}

	// draw last filled stack if it is filled
	if (currentAmountElements == n) {
		for (int i = 0; i < currentAmountElements; i++) {
			SDL_Rect elm_rect = { x, y, STACK_ELM_WIDTH_ON_SCREEN, STACK_ELM_HEIGHT_ON_SCREEN };
			SDL_RenderFillRect(renderer, &elm_rect);
			y -= STACK_ELM_HEIGHT_ON_SCREEN + SPACE_BETWEEN_ELMS_ON_SCREEN;
		}
	}
	else {
		// draw last unfilled stack
		for (int i = 0; i < currentAmountElements; i++) {
			SDL_Rect elm_rect = { x, y, STACK_ELM_WIDTH_ON_SCREEN, STACK_ELM_HEIGHT_ON_SCREEN };
			SDL_RenderDrawRect(renderer, &elm_rect);
			y -= STACK_ELM_HEIGHT_ON_SCREEN + SPACE_BETWEEN_ELMS_ON_SCREEN;
		}
	}

	renderText(renderer);

	SDL_RenderPresent(renderer);
	return 0;
}

int SetOfStacks::renderLabelAndInt(SDL_Renderer* renderer, string label, int val, SDL_Rect* dst_rect, SDL_Color text_clr)
{
	char val_str_buff[12]{};
	_itoa_s(val, val_str_buff, 10);
	string val_str = val_str_buff;
	string str = label + val_str;

	SDL_Surface* val_text_surf = TTF_RenderText_Blended(font, str.c_str(), text_clr);
	SDL_Texture* val_text_texture = SDL_CreateTextureFromSurface(renderer, val_text_surf);

	SDL_RenderCopy(renderer, val_text_texture, 0, dst_rect);

	SDL_FreeSurface(val_text_surf);
	SDL_DestroyTexture(val_text_texture);
	return 0;
}

int SetOfStacks::renderText(SDL_Renderer* renderer) {

	SDL_Color text_color = { 0, 0, 0, 255 };

	// render n
	SDL_Rect dst_rect = { 720, 10, 80, 50 };
	renderLabelAndInt(renderer, "n: ", n, &dst_rect);

	// render maxn
	dst_rect = { 650, 60, 150, 50 };
	renderLabelAndInt(renderer, "maxn: ", maxn, &dst_rect);

	// render number of current element
	dst_rect = { 400, 110, 400, 50 };
	renderLabelAndInt(renderer, "Number of current element: ", currentStack * n + currentAmountElements, &dst_rect);

	// render top element value
	dst_rect = { 500, 160, 300, 50 };
	renderLabelAndInt(renderer, "Last pushed/poped: ", topElmVal, &dst_rect);

	return 0;
}

void SetOfStacks::printState()
{
	cout << "n " << n << endl;
	cout << "maxn " << maxn << endl;
	cout << "curr stack " << currentStack << endl;
	cout << "curr amount elements " << currentAmountElements << endl;

	cout << endl;
}

int SetOfStacks::loop()
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
			if (ev.type == SDL_KEYDOWN) {
				if (ev.key.keysym.sym == SDLK_w) {
					int val = rand();
					if (push(val) != 0)
						continue;
					topElmVal = val;
					//printState();
					continue;
				}
				if (ev.key.keysym.sym == SDLK_s) {
					pop(&topElmVal);
					//printState();
					continue;
				}
			}
		}
		
		render(ren);
	}

	return 0;
}
