#include "Libraries.h"

void draw_rectangle(SDL_Renderer*& render, SDL_Rect shell);
void draw_rectangle1(SDL_Renderer*& render, SDL_Rect shell1);
int random_init_nominal();
void init_cell(SDL_Rect rect[][5], int count, int game_matrix[][5]);
void init_cell1(SDL_Rect rect[][5], int count, int game_matrix[][5]);
void rush_up(int game_matrix[][5], int count);
void move_up(int game_matrix[][5], int count, int& count_init_cell, int& score);
void rush_down(int game_matrix[][5], int count);
void move_down(int game_matrix[][5], int count, int& count_init_cell, int& score);
void rush_left(int game_matrix[][5], int count);
void move_left(int game_matrix[][5], int count, int& count_init_cell, int& score);
void rush_right(int game_matrix[][5], int count);
void move_right(int game_matrix[][5], int count, int& count_init_cell, int& score);
bool if_can_match_up(int game_matrix[][5], int count);
bool if_can_match_down(int game_matrix[][5], int count);
bool if_can_match_left(int game_matrix[][5], int count);
bool if_can_match_right(int game_matrix[][5], int count);
bool if_zero_on_field(int game_matrix[][5], int count);
bool if_end_game(int game_matrix[][5], int count);