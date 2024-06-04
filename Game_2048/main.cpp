#include "file_work.h"
#include "menu.h"
#include "mode_4x4.h"

Mix_Chunk* sound = nullptr;
Mix_Music* music = nullptr;



int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Russian");
	srand(time(nullptr));
	cout << "\n\tДобро пожаловать в Игру: 2048\n";

	if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO) != 0)
	{
		cout << "Couldn't init SDL! Error: %s\n", SDL_GetError();
	}
	Mix_Init(0);
	IMG_Init(IMG_INIT_PNG);
	TTF_Init();

	SDL_Window* window = nullptr;
	SDL_Renderer* render = nullptr;

	init_menu(window, render);

	/// Init_Music \\\

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	Mix_VolumeMusic(MIX_MAX_VOLUME / 5);
	load_menu_music(music, "music/animebro.mp3");


	TTF_Font* my_font = TTF_OpenFont("fonts/text1.ttf", 100);

	/// Init_buttons \\\

	SDL_Texture* text_texture;
	char text_menu[10] = u8"Меню";
	text_menu[0] = toupper(static_cast<unsigned char>(text_menu[0]));
	text_texture = get_text_texture(render, text_menu, my_font);

	SDL_Texture* start4_texture;
	char start4[20] = u8"Поле 4x4";
	start4_texture = get_start_texture(render, start4, my_font);
	SDL_Rect start4_rect = { 255, 300, 500, 90 };

	SDL_Texture* start5_texture;
	char start5[20] = u8"Поле 5x5";
	start5_texture = get_start_texture(render, start5, my_font);
	SDL_Rect start5_rect = { 255, 400, 500, 90 };

	SDL_Texture* startfast_texture;
	char startfast[25] = u8"Быстрая игра";
	startfast_texture = get_start_texture(render, startfast, my_font);
	SDL_Rect startfast_rect = { 255, 500, 500, 90 };

	SDL_Texture* exit_texture = LoadTextureFromFile("images/exit_button.bmp", render, window);
	SDL_Rect exit_rect = { 960, 0, 64, 64 };

	SDL_Texture* music_texture = LoadTextureFromFile("images/music_on.bmp", render, window);
	SDL_Rect music_rect = { 0, 0, 64, 64 };

	SDL_Texture* sound_texture = LoadTextureFromFile("images/sound_on.bmp", render, window);
	SDL_Rect sound_rect = { 70, 0, 64, 64 };

	/// Init_cells \\\

	SDL_Rect shell = { 225, 100, 552, 552 };
	SDL_Rect shell1 = { 262, 100, 500, 500 };

	SDL_Rect cells[5][5];
	char nominals[200];
	
	int game_matrix[5][5];

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			game_matrix[i][j] = 0;
		}
	}

	SDL_Texture* cell_texture;

	SDL_SetRenderDrawColor(render, 255, 218, 185, 0);
	SDL_RenderClear(render);
	int game_mode = -1, menu_clear = -1, is_menu_clear = -1, count_init_cell = 0, current_init_cell_x = 0, current_init_cell_y = 0;
	
	int end_game = 1;
	int final_score = 0;
	char final_text1[50] = u8"Игра окончена!";
	char final_text2[50] = u8"Ваше количество очков: ";
	char final_score_text[10];
	SDL_Rect final_rect1 = { 290, 100, 500, 500 };
	SDL_Rect final_rect2 = { 300, 250, 500, 500 };
	SDL_Rect final_score_rect = { 335, 400, 500, 500};

	SDL_Texture* final_texture1, * final_texture2, * final_score_texture;

	final_texture1 = get_text_texture(render, final_text1, my_font);
	final_texture2 = get_text_texture(render, final_text2, my_font);

	int t_w, t_h;
	SDL_QueryTexture(final_texture1, nullptr, nullptr, &t_w, &t_h);
	final_rect1.h = t_h;
	final_rect2.h = t_h;

	SDL_Event e;
	
	Uint32 start_time, current_time;
	char time_char[100];
	SDL_Texture* time_texture;
	SDL_Rect time_rect = { 0, 70, 64, 64 };

	int time = 60;
	bool quit = false, music_volume = false, sound_volume = true;
	bool up_pressed = false, down_pressed = false, left_pressed = false, right_pressed = false;
	while (end_game != 0)
	{
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
			{
				if (is_exit_musuc_sound_hit(exit_rect, e.button.x, e.button.y))
				{
					cout << "Вы закрыли игру;\n";

					switch (game_mode)
					{
					case 1: file_4x4(final_score); break;
					case 2: file_5x5(final_score); break;
					case 3: file_fast(final_score); break;
					}

					exit(0);
				}

				if (is_exit_musuc_sound_hit(music_rect, e.button.x, e.button.y))
				{
					if (music_volume == true)
					{
						cout << "Вы включили музыку;\n";
						Mix_VolumeMusic(MIX_MAX_VOLUME / 5);
						music_volume = false;
						SDL_DestroyTexture(music_texture);
						music_texture = LoadTextureFromFile("images/music_on.bmp", render, window);
					}
					else if (music_volume == false)
					{
						cout << "Вы выключили музыку;\n";
						Mix_VolumeMusic(0);
						music_volume = true;
						SDL_DestroyTexture(music_texture);
						music_texture = LoadTextureFromFile("images/music_off.bmp", render, window);
					}
				}

				if (is_exit_musuc_sound_hit(sound_rect, e.button.x, e.button.y))
				{
					if (sound_volume == false)
					{
						cout << "Вы включили звук;\n";
						SDL_DestroyTexture(sound_texture);
						sound_volume = true;
						sound_texture = LoadTextureFromFile("images/sound_on.bmp", render, window);
					}
					else if (sound_volume == true)
					{
						cout << "Вы выключили звук;\n";
						SDL_DestroyTexture(sound_texture);
						sound_volume = false;
						sound_texture = LoadTextureFromFile("images/sound_off.bmp", render, window);
					}
				}
			}

			switch (game_mode)
			{
			case 1:
			{
				if (menu_clear < 0)
				{
					SDL_RenderClear(render);
					menu_clear = 1;

					SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
					SDL_RenderDrawRect(render, &shell);
					is_menu_clear = -1;
				}
				else
				{
					if (is_menu_clear < 0)
					{
						int X = rand() % 4;
						int Y = rand() % 4;
						game_matrix[X][Y] = 2;
						X = rand() % 4;
						Y = rand() % 4;
						game_matrix[X][Y] = 2;
						is_menu_clear = 1;
					}

					else
					{
						if (if_end_game(game_matrix, 4))
						{
							SDL_RenderClear(render);

							_itoa_s(final_score, final_score_text, 10);

							final_score_texture = get_text_texture(render, final_score_text, my_font);
							SDL_QueryTexture(final_score_texture, nullptr, nullptr, &t_w, &t_h);
							final_score_rect.w = t_w;
							final_score_rect.h = t_h;

							SDL_RenderCopy(render, final_texture1, nullptr, &final_rect1);

							SDL_RenderCopy(render, final_texture2, nullptr, &final_rect2);

							SDL_RenderCopy(render, final_score_texture, nullptr, &final_score_rect);

							if (is_exit_musuc_sound_hit(exit_rect, e.button.x, e.button.y))
							{
								cout << "Вы закрыли игру;\n";

								switch (game_mode)
								{
								case 1: file_4x4(final_score); break;
								case 2: file_5x5(final_score); break;
								case 3: file_fast(final_score); break;
								}

								exit(0);
							}
						}

						else if (e.type == SDL_KEYDOWN)
						{
							if (!e.key.repeat)
							{
								switch (e.key.keysym.sym)
								{

								case SDLK_UP:
								{
									if (if_can_match_up)
									{
										if (sound_volume)
										{
											load_game_sound(sound, "music/sound.wav");
										}
										move_up(game_matrix, 4, count_init_cell, final_score);

										init_cell(cells, 4, game_matrix);

										count_init_cell++;
									}

									up_pressed = true;
									break;
								}

								case SDLK_DOWN:
								{
									if (if_can_match_down)
									{
										if (sound_volume)
										{
											load_game_sound(sound, "music/sound.wav");
										}

										move_down(game_matrix, 4, count_init_cell, final_score);

										init_cell(cells, 4, game_matrix);

										count_init_cell++;
									}

									down_pressed = true;
									break;
								}

								case SDLK_LEFT:
								{
									if (if_can_match_left)
									{
										if (sound_volume)
										{
											load_game_sound(sound, "music/sound.wav");
										}

										move_left(game_matrix, 4, count_init_cell, final_score);

										init_cell(cells, 4, game_matrix);

										count_init_cell++;
									}

									left_pressed = true;
									break;
								}

								case SDLK_RIGHT:
								{
									if (if_can_match_right)
									{
										if (sound_volume)
										{
											load_game_sound(sound, "music/sound.wav");
										}

										move_right(game_matrix, 4, count_init_cell, final_score);

										init_cell(cells, 4, game_matrix);

										count_init_cell++;
									}

									right_pressed = true;
									break;
								}

								}

							}


						}

						if (e.type == SDL_KEYUP)
						{
							switch (e.key.keysym.sym)
							{
							case SDLK_UP:
							{
								up_pressed = false;
								break;
							}

							case SDLK_DOWN:
							{
								down_pressed = false;
								break;
							}

							case SDLK_LEFT:
							{
								left_pressed = false;
								break;
							}

							case SDLK_RIGHT:
							{
								right_pressed = false;
								break;
							}
							}
						}

						if (!if_end_game(game_matrix, 4))
						{
							SDL_RenderClear(render);
							draw_rectangle(render, shell);

							for (int i = 0; i < 4; i++)
							{
								for (int j = 0; j < 4; j++)
								{
									if (game_matrix[i][j] != 0)
									{
										switch (i)
										{
										case 0:
										{
											cells[i][j].x = 225;
											break;
										}
										case 1:
										{
											cells[i][j].x = 363;
											break;
										}
										case 2:
										{
											cells[i][j].x = 501;
											break;
										}
										case 3:
										{
											cells[i][j].x = 639;
											break;
										}
										}

										switch (j)
										{
										case 0:
										{
											cells[i][j].y = 100;
											break;
										}
										case 1:
										{
											cells[i][j].y = 238;
											break;
										}
										case 2:
										{
											cells[i][j].y = 376;
											break;
										}
										case 3:
										{
											cells[i][j].y = 514;
											break;
										}
										}

										cells[i][j].w = 138;
										cells[i][j].h = 138;

										_itoa_s(game_matrix[i][j], nominals, 10);

										cell_texture = get_text_texture(render, nominals, my_font);

										SDL_RenderCopy(render, cell_texture, nullptr, &cells[i][j]);
									}
								}
							}
						}

					}
				}
				break;
			}

			case 2:
			{
				if (menu_clear < 0)
				{
					SDL_RenderClear(render);
					menu_clear = 1;

					SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
					SDL_RenderDrawRect(render, &shell1);
					is_menu_clear = -1;
				}
				else
				{
					if (is_menu_clear < 0)
					{
						int X = rand() % 4;
						int Y = rand() % 4;
						game_matrix[X][Y] = 2;
						X = rand() % 4;
						Y = rand() % 4;
						game_matrix[X][Y] = 2;
						is_menu_clear = 1;
					}

					else
					{
						if (if_end_game(game_matrix, 5))
						{
							SDL_RenderClear(render);

							_itoa_s(final_score, final_score_text, 10);

							final_score_texture = get_text_texture(render, final_score_text, my_font);
							SDL_QueryTexture(final_score_texture, nullptr, nullptr, &t_w, &t_h);
							final_score_rect.w = t_w;
							final_score_rect.h = t_h;

							SDL_RenderCopy(render, final_texture1, nullptr, &final_rect1);

							SDL_RenderCopy(render, final_texture2, nullptr, &final_rect2);

							SDL_RenderCopy(render, final_score_texture, nullptr, &final_score_rect);

							if (is_exit_musuc_sound_hit(exit_rect, e.button.x, e.button.y))
							{
								cout << "Вы закрыли игру;\n";

								switch (game_mode)
								{
								case 1: file_4x4(final_score); break;
								case 2: file_5x5(final_score); break;
								case 3: file_fast(final_score); break;
								}

								exit(0);
							}
						}

						else if (e.type == SDL_KEYDOWN)
						{
							if (!e.key.repeat)
							{
								switch (e.key.keysym.sym)
								{

								case SDLK_UP:
								{
									if (if_can_match_up)
									{
										if (sound_volume)
										{
											load_game_sound(sound, "music/sound.wav");
										}
										move_up(game_matrix, 5, count_init_cell, final_score);

										init_cell1(cells, 5, game_matrix);

										count_init_cell++;
									}

									up_pressed = true;
									break;
								}

								case SDLK_DOWN:
								{
									if (if_can_match_down)
									{
										if (sound_volume)
										{
											load_game_sound(sound, "music/sound.wav");
										}

										move_down(game_matrix, 5, count_init_cell, final_score);

										init_cell1(cells, 5, game_matrix);

										count_init_cell++;
									}

									down_pressed = true;
									break;
								}

								case SDLK_LEFT:
								{
									if (if_can_match_left)
									{
										if (sound_volume)
										{
											load_game_sound(sound, "music/sound.wav");
										}

										move_left(game_matrix, 5, count_init_cell, final_score);

										init_cell1(cells, 5, game_matrix);

										count_init_cell++;
									}

									left_pressed = true;
									break;
								}

								case SDLK_RIGHT:
								{
									if (if_can_match_right)
									{
										if (sound_volume)
										{
											load_game_sound(sound, "music/sound.wav");
										}

										move_right(game_matrix, 5, count_init_cell, final_score);

										init_cell1(cells, 5, game_matrix);

										count_init_cell++;
									}

									right_pressed = true;
									break;
								}

								}

							}


						}

						if (e.type == SDL_KEYUP)
						{
							switch (e.key.keysym.sym)
							{
							case SDLK_UP:
							{
								up_pressed = false;
								break;
							}

							case SDLK_DOWN:
							{
								down_pressed = false;
								break;
							}

							case SDLK_LEFT:
							{
								left_pressed = false;
								break;
							}

							case SDLK_RIGHT:
							{
								right_pressed = false;
								break;
							}
							}
						}

						if (!if_end_game(game_matrix, 5))
						{
							SDL_RenderClear(render);
							draw_rectangle1(render, shell1);

							for (int i = 0; i < 5; i++)
							{
								for (int j = 0; j < 5; j++)
								{
									if (game_matrix[i][j] != 0)
									{
										switch (i)
										{
										case 0:
										{
											cells[i][j].x = 262;
											break;
										}
										case 1:
										{
											cells[i][j].x = 362;
											break;
										}
										case 2:
										{
											cells[i][j].x = 462;
											break;
										}
										case 3:
										{
											cells[i][j].x = 562;
											break;
										}
										case 4:
										{
											cells[i][j].x = 662;
										}
										}

										switch (j)
										{
										case 0:
										{
											cells[i][j].y = 100;
											break;
										}
										case 1:
										{
											cells[i][j].y = 200;
											break;
										}
										case 2:
										{
											cells[i][j].y = 300;
											break;
										}
										case 3:
										{
											cells[i][j].y = 400;
											break;
										}
										case 4:
										{
											cells[i][j].y = 500;
										}
										}

										cells[i][j].w = 100;
										cells[i][j].h = 100;

										_itoa_s(game_matrix[i][j], nominals, 10);

										cell_texture = get_text_texture(render, nominals, my_font);

										SDL_RenderCopy(render, cell_texture, nullptr, &cells[i][j]);
									}
								}
							}
						}

					}
				}
				break;
			}

			case 3:
			{
				if (menu_clear < 0)
				{
					SDL_RenderClear(render);
					menu_clear = 1;

					SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
					SDL_RenderDrawRect(render, &shell);
					is_menu_clear = -1;
				}
				else
				{
					if (is_menu_clear < 0)
					{
						int X = rand() % 4;
						int Y = rand() % 4;
						game_matrix[X][Y] = 2;
						X = rand() % 4;
						Y = rand() % 4;
						game_matrix[X][Y] = 2;
						is_menu_clear = 1;
					}

					else
					{
						current_time = SDL_GetTicks();

						if (if_end_game(game_matrix, 4) || (time * 1000 <= current_time - start_time))
						{
							SDL_RenderClear(render);

							_itoa_s(final_score, final_score_text, 10);

							final_score_texture = get_text_texture(render, final_score_text, my_font);
							SDL_QueryTexture(final_score_texture, nullptr, nullptr, &t_w, &t_h);
							final_score_rect.w = t_w;
							final_score_rect.h = t_h;

							SDL_RenderCopy(render, final_texture1, nullptr, &final_rect1);

							SDL_RenderCopy(render, final_texture2, nullptr, &final_rect2);

							SDL_RenderCopy(render, final_score_texture, nullptr, &final_score_rect);

							if (is_exit_musuc_sound_hit(exit_rect, e.button.x, e.button.y))
							{
								cout << "Вы закрыли игру;\n";

								switch (game_mode)
								{
								case 1: file_4x4(final_score); break;
								case 2: file_5x5(final_score); break;
								case 3: file_fast(final_score); break;
								}

								exit(0);
							}
						}

						else if (e.type == SDL_KEYDOWN)
						{
							if (!e.key.repeat)
							{
								switch (e.key.keysym.sym)
								{

								case SDLK_UP:
								{
									if (if_can_match_up)
									{
										if (sound_volume)
										{
											load_game_sound(sound, "music/sound.wav");
										}
										move_up(game_matrix, 4, count_init_cell, final_score);

										init_cell(cells, 4, game_matrix);

										count_init_cell++;
									}

									up_pressed = true;
									break;
								}

								case SDLK_DOWN:
								{
									if (if_can_match_down)
									{
										if (sound_volume)
										{
											load_game_sound(sound, "music/sound.wav");
										}

										move_down(game_matrix, 4, count_init_cell, final_score);

										init_cell(cells, 4, game_matrix);

										count_init_cell++;
									}

									down_pressed = true;
									break;
								}

								case SDLK_LEFT:
								{
									if (if_can_match_left)
									{
										if (sound_volume)
										{
											load_game_sound(sound, "music/sound.wav");
										}

										move_left(game_matrix, 4, count_init_cell, final_score);

										init_cell(cells, 4, game_matrix);

										count_init_cell++;
									}

									left_pressed = true;
									break;
								}

								case SDLK_RIGHT:
								{
									if (if_can_match_right)
									{
										if (sound_volume)
										{
											load_game_sound(sound, "music/sound.wav");
										}

										move_right(game_matrix, 4, count_init_cell, final_score);

										init_cell(cells, 4, game_matrix);

										count_init_cell++;
									}

									right_pressed = true;
									break;
								}

								}

							}


						}

						if (e.type == SDL_KEYUP)
						{
							switch (e.key.keysym.sym)
							{
							case SDLK_UP:
							{
								up_pressed = false;
								break;
							}

							case SDLK_DOWN:
							{
								down_pressed = false;
								break;
							}

							case SDLK_LEFT:
							{
								left_pressed = false;
								break;
							}

							case SDLK_RIGHT:
							{
								right_pressed = false;
								break;
							}
							}
						}

						if (!if_end_game(game_matrix, 4))
						{
							SDL_RenderClear(render);

							draw_rectangle(render, shell);

							_itoa_s((current_time - start_time) / 1000, time_char, 10);

							time_texture = get_text_texture(render, time_char, my_font);

							SDL_RenderCopy(render, time_texture, nullptr, &time_rect);

							for (int i = 0; i < 4; i++)
							{
								for (int j = 0; j < 4; j++)
								{
									if (game_matrix[i][j] != 0)
									{
										switch (i)
										{
										case 0:
										{
											cells[i][j].x = 225;
											break;
										}
										case 1:
										{
											cells[i][j].x = 363;
											break;
										}
										case 2:
										{
											cells[i][j].x = 501;
											break;
										}
										case 3:
										{
											cells[i][j].x = 639;
											break;
										}
										}

										switch (j)
										{
										case 0:
										{
											cells[i][j].y = 100;
											break;
										}
										case 1:
										{
											cells[i][j].y = 238;
											break;
										}
										case 2:
										{
											cells[i][j].y = 376;
											break;
										}
										case 3:
										{
											cells[i][j].y = 514;
											break;
										}
										}

										cells[i][j].w = 138;
										cells[i][j].h = 138;

										_itoa_s(game_matrix[i][j], nominals, 10);

										cell_texture = get_text_texture(render, nominals, my_font);

										SDL_RenderCopy(render, cell_texture, nullptr, &cells[i][j]);
									}
								}
							}
						}

					}
				}
				break;
			}

			default:
			{
				if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
				{
					if (is_game_mode_hit(start4_rect, e.button.x, e.button.y))
					{
						cout << "Вы выбрали: Игровое поле 4x4;\n";

						game_mode = 1;
					}

					if (is_game_mode_hit(start5_rect, e.button.x, e.button.y))
					{
						cout << "Вы выбрали: Игровое поле 5x5;\n";

						game_mode = 2;
					}

					if (is_game_mode_hit(startfast_rect, e.button.x, e.button.y))
					{
						cout << "Вы выбрали: Быстрый режим;\n";

						game_mode = 3;

						start_time = SDL_GetTicks();
					}

					if (is_exit_musuc_sound_hit(exit_rect, e.button.x, e.button.y))
					{
						cout << "Вы закрыли игру;\n";

						switch (game_mode)
						{
						case 1: file_4x4(final_score); break;
						case 2: file_5x5(final_score); break;
						case 3: file_fast(final_score); break;
						}

						exit(0);
					}
				}

				SDL_RenderClear(render);

				draw_text(render, text_texture);

				draw_game_mode(render, start4_texture, start4_rect);
				draw_game_mode(render, start5_texture, start5_rect);
				draw_game_mode(render, startfast_texture, startfast_rect);

				break;
			}
			}
		}
		SDL_SetRenderDrawColor(render, 255, 218, 185, 0);



		draw_exit(render, exit_texture);
		draw_music(render, music_texture, music_rect);
		draw_sound(render, sound_texture, sound_rect);

		SDL_RenderPresent(render);
	}
	
	/*for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			cout << game_matrix[j][i] << "\t";
		}
		cout << endl;
	}*/

	switch (game_mode)
	{
	case 1: file_4x4(final_score); break;
	case 2: file_5x5(final_score); break;
	case 3: file_fast(final_score); break;
	}

	Mix_FreeMusic(music);
	Mix_FreeChunk(sound);
	Mix_CloseAudio();
	SDL_DestroyTexture(text_texture);
	SDL_DestroyTexture(start4_texture);
	SDL_DestroyTexture(start5_texture);
	SDL_DestroyTexture(startfast_texture);
	SDL_DestroyTexture(final_texture1);
	SDL_DestroyTexture(final_texture2);
	SDL_DestroyTexture(exit_texture);
	SDL_DestroyTexture(music_texture);
	SDL_DestroyTexture(sound_texture);
	TTF_CloseFont(my_font);
	TTF_Quit();
	SDL_DestroyRenderer(render);
	SDL_DestroyWindow(window);
	SDL_Quit();

}