#include "Libraries.h"

void init_menu(SDL_Window*& window, SDL_Renderer*& render);
void load_menu_music(Mix_Music* music, const char* file_name);
void load_game_sound(Mix_Chunk* sound, const char* file_name);
SDL_Texture* get_text_texture(SDL_Renderer*& render, char* text, TTF_Font* font);
SDL_Texture* get_start_texture(SDL_Renderer*& render, char* text, TTF_Font* font);
void draw_text(SDL_Renderer*& render, SDL_Texture* texture);
void draw_start(SDL_Renderer*& render, SDL_Texture* texture);
void draw_game_mode(SDL_Renderer*& render, SDL_Texture* texture, SDL_Rect rect);
void draw_exit(SDL_Renderer*& render, SDL_Texture* texture);
void draw_music(SDL_Renderer*& render, SDL_Texture* texture, SDL_Rect rect);
void draw_sound(SDL_Renderer*& render, SDL_Texture* texture, SDL_Rect rect);
bool is_game_mode_hit(SDL_Rect rect, int x, int y);
bool is_exit_musuc_sound_hit(SDL_Rect rect, int x, int y);
SDL_Texture* LoadTextureFromFile(const char* filename, SDL_Renderer* render, SDL_Window* window);