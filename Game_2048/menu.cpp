#include "menu.h"

void init_menu(SDL_Window*& window, SDL_Renderer*& render)
{
	window = SDL_CreateWindow(u8"Игра <2048>", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, SDL_WINDOW_SHOWN);
	render = SDL_CreateRenderer(window, -1, 0);
}

void load_menu_music(Mix_Music* music, const char* file_name)
{
	music = Mix_LoadMUS(file_name);
	Mix_PlayMusic(music, -1);
}

void load_game_sound(Mix_Chunk* sound, const char* file_name)
{
	sound = Mix_LoadWAV(file_name);
	if (sound == nullptr) cout << Mix_GetError();
	Mix_PlayChannel(-1, sound, 0);
}

SDL_Texture* get_text_texture(SDL_Renderer*& render, char* text, TTF_Font* font)
{
	SDL_Surface* textSurface = NULL;
	SDL_Color fore_color = { 130, 140, 50 };
	SDL_Color back_color = { 255, 218, 185 };
	textSurface = TTF_RenderUTF8_Shaded(font, text, fore_color, back_color);
	SDL_SetColorKey(textSurface, SDL_TRUE, SDL_MapRGB(textSurface->format, 255, 218, 185));
	SDL_Texture* texture = SDL_CreateTextureFromSurface(render, textSurface);
	SDL_FreeSurface(textSurface);
	return texture;
}

SDL_Texture* get_start_texture(SDL_Renderer*& render, char* text, TTF_Font* font)
{
	SDL_Surface* textSurface = NULL;
	SDL_Color fore_color = { 188, 143, 143 };
	SDL_Color back_color = { 255, 218, 185 };
	textSurface = TTF_RenderUTF8_Shaded(font, text, fore_color, back_color);
	SDL_SetColorKey(textSurface, SDL_TRUE, SDL_MapRGB(textSurface->format, 255, 218, 185));
	SDL_Texture* texture = SDL_CreateTextureFromSurface(render, textSurface);
	SDL_FreeSurface(textSurface);
	return texture;
}

void draw_text(SDL_Renderer*& render, SDL_Texture* texture)
{
	int text_width = 0;
	int text_height = 0;
	SDL_QueryTexture(texture, NULL, NULL, &text_width, &text_height);

	SDL_Rect rect = { 300, 30, text_width, text_height };
	SDL_RenderCopy(render, texture, nullptr, &rect);
}

void draw_start(SDL_Renderer*& render, SDL_Texture* texture)
{
	int text_width = 0;
	int text_height = 0;
	SDL_QueryTexture(texture, NULL, NULL, &text_width, &text_height);
	SDL_Rect rect = { 255, 300, 500, 90 };

	SDL_RenderCopy(render, texture, nullptr, &rect);
}

void draw_game_mode(SDL_Renderer*& render, SDL_Texture* texture, SDL_Rect rect)
{
	int text_width = 0;
	int text_height = 0;
	SDL_QueryTexture(texture, NULL, NULL, &text_width, &text_height);

	SDL_RenderCopy(render, texture, nullptr, &rect);
}

void draw_exit(SDL_Renderer*& render, SDL_Texture* texture)
{
	int text_width = 0;
	int text_height = 0;
	SDL_QueryTexture(texture, NULL, NULL, &text_width, &text_height);
	SDL_Rect rect = { 960, 0, 64, 64 };

	SDL_RenderCopy(render, texture, nullptr, &rect);
}

void draw_music(SDL_Renderer*& render, SDL_Texture* texture, SDL_Rect rect)
{
	int text_width = 0;
	int text_height = 0;
	SDL_QueryTexture(texture, NULL, NULL, &text_width, &text_height);

	SDL_RenderCopy(render, texture, nullptr, &rect);
}

void draw_sound(SDL_Renderer*& render, SDL_Texture* texture, SDL_Rect rect)
{
	int text_width = 0;
	int text_height = 0;
	SDL_QueryTexture(texture, NULL, NULL, &text_width, &text_height);

	SDL_RenderCopy(render, texture, nullptr, &rect);
}

bool is_game_mode_hit(SDL_Rect rect, int x, int y)
{
	if (rect.w == 0 || rect.h == 0) return false;
	if ((x >= rect.x) && (x < rect.w + rect.x) && (y >= rect.y) && (y < rect.h + rect.y)) return true;
	return false;
}

bool is_exit_musuc_sound_hit(SDL_Rect rect, int x, int y)
{
	if (rect.w == 0 || rect.h == 0) return false;
	if ((x >= rect.x) && (x < rect.w + rect.x) && (y >= rect.y) && (y < rect.h + rect.y)) return true;
	return false;
}

SDL_Texture* LoadTextureFromFile(const char* filename, SDL_Renderer* render, SDL_Window* window)
{
	SDL_Surface* surface = SDL_LoadBMP(filename);
	if (surface == NULL)
	{
		cout << "Couldn't load image " << filename << "!" << " Error: " << SDL_GetError() << endl;
		
	}
	SDL_Texture* texture = SDL_CreateTextureFromSurface(render, surface);
	SDL_FreeSurface(surface);
	return texture;
}