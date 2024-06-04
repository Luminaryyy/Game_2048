#include "mode_4x4.h"

void draw_rectangle(SDL_Renderer*& render, SDL_Rect shell)
{
	SDL_RenderClear(render);
	SDL_SetRenderDrawColor(render, 0, 0, 0, 255);

	SDL_RenderDrawRect(render, &shell);
	SDL_RenderDrawLine(render, 363, 100, 363, 651);
	SDL_RenderDrawLine(render, 501, 100, 501, 651);
	SDL_RenderDrawLine(render, 639, 100, 639, 651);
	SDL_RenderDrawLine(render, 225, 238, 776, 238);
	SDL_RenderDrawLine(render, 225, 376, 776, 376);
	SDL_RenderDrawLine(render, 225, 514, 776, 514);
	SDL_SetRenderDrawColor(render, 255, 218, 185, 0);
}

void draw_rectangle1(SDL_Renderer*& render, SDL_Rect shell1)
{
	SDL_RenderClear(render);
	SDL_SetRenderDrawColor(render, 0, 0, 0, 255);

	SDL_RenderDrawRect(render, &shell1);

	for (int i = 1; i < 5; ++i)
	{
		int x = shell1.x + i * (shell1.w / 5);
		SDL_RenderDrawLine(render, x, shell1.y, x, shell1.y + shell1.h);
	}

	for (int j = 1; j < 5; ++j)
	{
		int y = shell1.y + j * (shell1.h / 5);
		SDL_RenderDrawLine(render, shell1.x, y, shell1.x + shell1.w, y);
	}

	SDL_SetRenderDrawColor(render, 255, 218, 185, 0);
}

int random_init_nominal()
{
	int nominal = -1, nominal_switch = -1;

	nominal_switch = 1 + rand() % 10;

	if ((nominal_switch >= 1) && (nominal_switch <= 9))
	{
		nominal = 2;
	}
	if (nominal_switch == 10)
	{
		nominal = 4;
	}
	return nominal;
}

void init_cell(SDL_Rect rect[][5], int count, int game_matrix[][5])
{
	bool cell_is_free = false;
	int x_switch = 0, x = 0, y = 0, y_switch = 0;
	
	for (int i = 0; i < count; ++i) 
	{
		for (int j = 0; j < count; ++j) 
		{
			if (game_matrix[i][j] == 0) 
			{
				cell_is_free = true;
				break;
			}
		}
		if (cell_is_free) 
		{
			break;
		}
	}

	if (!cell_is_free)
	{
		cout << "Конец!\n";
		return;
	}

	while (cell_is_free)
	{
		x_switch = rand() % 4;
		y_switch = rand() % 4;

		switch (x_switch)
		{

		case 0:
		{
			x = 225;
			break;
		}
		case 1:
		{
			x = 363;
			break;
		}
		case 2:
		{
			x = 501;
			break;
		}
		case 3:
		{
			x = 639;
			break;
		}

		}

		switch (y_switch)
		{

		case 0:
		{
			y = 100;
			break;
		}
		case 1:
		{
			y = 238;
			break;
		}
		case 2:
		{
			y = 376;
			break;
		}
		case 3:
		{
			y = 514;
			break;
		}

		}

		if (game_matrix[x_switch][y_switch] == 0)
		{
			cell_is_free = false;
			rect[x_switch][y_switch] = { x, y, 138, 138 };
			game_matrix[x_switch][y_switch] = random_init_nominal();
		}
	}
}

void init_cell1(SDL_Rect rect[][5], int count, int game_matrix[][5])
{
	bool cell_is_free = false;
	int x_switch = 0, x = 0, y = 0, y_switch = 0;

	for (int i = 0; i < count; ++i)
	{
		for (int j = 0; j < count; ++j)
		{
			if (game_matrix[i][j] == 0)
			{
				cell_is_free = true;
				break;
			}
		}
		if (cell_is_free)
		{
			break;
		}
	}

	if (!cell_is_free)
	{
		cout << "Конец!\n";
		return;
	}

	while (cell_is_free)
	{
		x_switch = rand() % 5;
		y_switch = rand() % 5;

		switch (x_switch)
		{

		case 0:
		{
			x = 262;
			break;
		}
		case 1:
		{
			x = 362;
			break;
		}
		case 2:
		{
			x = 462;
			break;
		}
		case 3:
		{
			x = 562;
			break;
		}
		case 4:
		{
			x = 662;
		}

		}

		switch (y_switch)
		{

		case 0:
		{
			y = 100;
			break;
		}
		case 1:
		{
			y = 200;
			break;
		}
		case 2:
		{
			y = 300;
			break;
		}
		case 3:
		{
			y = 400;
			break;
		}
		case 4:
		{
			y = 500;
		}

		}

		if (game_matrix[x_switch][y_switch] == 0)
		{
			cell_is_free = false;
			rect[x_switch][y_switch] = { x, y, 100, 100 };
			game_matrix[x_switch][y_switch] = random_init_nominal();
		}
	}
}

void rush_up(int game_matrix[][5], int count)
{
	for (int i = 0; i < count; i++)
	{
		for (int j = 1; j < count; j++)
		{
			if (game_matrix[i][j] != 0)
			{
				for (int k = j; k > 0; --k)
				{
					if (game_matrix[i][k - 1] == 0)
					{
						game_matrix[i][k - 1] = game_matrix[i][k];
						game_matrix[i][k] = 0;
					}
				}
			}
		}
	}
}

void move_up(int game_matrix[][5], int count, int& count_init_cell, int& score)
{
	rush_up(game_matrix, count);

	for (int i = 0; i < count; i++)
	{
		for (int j = 1; j < count; j++)
		{
			if (game_matrix[i][j] != 0)
			{
				if (game_matrix[i][j] == game_matrix[i][j - 1])
				{
					game_matrix[i][j - 1] *= 2;
					score += game_matrix[i][j - 1];
					game_matrix[i][j] = 0;
					count_init_cell -= 1;
				}
			}
		}
	}

	rush_up(game_matrix, count);
}

void rush_down(int game_matrix[][5], int count)
{
	for (int i = 0; i < count; i++) {
		for (int j = count - 2; j >= 0; j--) {
			if (game_matrix[i][j] != 0) {
				for (int k = j; k < count - 1; ++k) {
					if (game_matrix[i][k + 1] == 0) {
						game_matrix[i][k + 1] = game_matrix[i][k];
						game_matrix[i][k] = 0;
					}
				}
			}
		}
	}
}

void move_down(int game_matrix[][5], int count, int& count_init_cell, int& score)
{
	rush_down(game_matrix, count);

	for (int i = 0; i < count; i++) {
		for (int j = count - 2; j >= 0; j--) {
			if (game_matrix[i][j] != 0) {
				if (game_matrix[i][j] == game_matrix[i][j + 1]) {
					game_matrix[i][j + 1] += game_matrix[i][j];
					score += game_matrix[i][j + 1];
					game_matrix[i][j] = 0;
					count_init_cell -= 1;
				}
			}
		}
	}

	rush_down(game_matrix, count);
}

void rush_left(int game_matrix[][5], int count)
{
	for (int j = 0; j < count; j++)
	{
		for (int i = 1; i < count; i++)
		{
			if (game_matrix[i][j] != 0)
			{
				for (int k = i; k > 0; --k)
				{
					if (game_matrix[k - 1][j] == 0)
					{
						game_matrix[k - 1][j] = game_matrix[k][j];
						game_matrix[k][j] = 0;
					}
				}
			}
		}
	}
}

void move_left(int game_matrix[][5], int count, int& count_init_cell, int& score)
{
	rush_left(game_matrix, count);

	for (int j = 0; j < count; j++)
	{
		for (int i = 1; i < count; i++)
		{
			if (game_matrix[i][j] != 0 && game_matrix[i - 1][j] == game_matrix[i][j])
			{
				game_matrix[i - 1][j] *= 2;
				score += game_matrix[i - 1][j];
				game_matrix[i][j] = 0;
				count_init_cell -= 1;
			}
		}
	}

	rush_left(game_matrix, count);
}

void rush_right(int game_matrix[][5], int count)
{
	for (int i = 0; i < count; i++) {
		for (int j = count - 2; j >= 0; j--) {
			if (game_matrix[j][i] != 0) {
				for (int k = j; k < count - 1; ++k) {
					if (game_matrix[k + 1][i] == 0) {
						game_matrix[k + 1][i] = game_matrix[k][i];
						game_matrix[k][i] = 0;
					}
				}
			}
		}
	}
}

void move_right(int game_matrix[][5], int count, int& count_init_cell, int& score)
{
	rush_right(game_matrix, count);

	for (int i = 0; i < count; i++) {
		for (int j = count - 2; j >= 0; j--) {
			if (game_matrix[j][i] != 0) {
				if (game_matrix[j][i] == game_matrix[j + 1][i]) {
					game_matrix[j + 1][i] += game_matrix[j][i];
					score += game_matrix[j + 1][i];
					game_matrix[j][i] = 0;
					count_init_cell -= 1;
				}
			}
		}
	}

	rush_right(game_matrix, count);
}

bool if_can_match_up(int game_matrix[][5], int count)
{
	bool flag = false;
	for (int i = 0; i < count; i++) {
		for (int j = 1; j < count; j++) {
			if (game_matrix[i][j - 1] == game_matrix[i][j])
				flag = true;
		}
	}
	return flag;
}

bool if_can_match_down(int game_matrix[][5], int count)
{
	bool flag = false;
    for (int i = count - 2; i >= 0; i--) {
        for (int j = 0; j < count; j++) {
            if (game_matrix[i + 1][j] == game_matrix[i][j])
                flag = true;
        }
    }
    return flag;
}

bool if_can_match_left(int game_matrix[][5], int count)
{
	bool flag = false;
	for (int i = 1; i < count; i++)
	{
		for (int j = 0; j < count; j++)
		{
			if (game_matrix[i - 1][j] == game_matrix[i][j])
				flag = true;
		}
	}
	return flag;
}

bool if_can_match_right(int game_matrix[][5], int count)
{
	bool flag = false;
	for (int i = 0; i < count; i++) {
		for (int j = count - 2; j >= 0; j--) {
			if (game_matrix[i][j + 1] == game_matrix[i][j])
				flag = true;
		}
	}
	return flag;
}

bool if_zero_on_field(int game_matrix[][5], int count)
{
	bool put = 0;

	for (int i = 0; i < count; i++) {
		for (int j = 0; j < count; j++) {
			if (game_matrix[i][j] == 0) put = 1;
		}
	}

	return put;
}

bool if_end_game(int game_matrix[][5], int count)
{
	bool lose = 1;

	for (int i = 0; i < count; i++) {
		for (int j = 0; j < count - 1; j++) {
			if (game_matrix[i][j] == game_matrix[i][j + 1]) lose = 0;
		}
	}
	for (int i = 0; i < count - 1; i++) {
		for (int j = 0; j < count; j++) {
			if (game_matrix[i][j] == game_matrix[i + 1][j]) lose = 0;
		}
	}

	if (if_zero_on_field(game_matrix, count)) lose = 0;

	return lose;
}