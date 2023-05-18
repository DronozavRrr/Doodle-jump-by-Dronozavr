#define _CRT_SECURE_NO_WARNINGS

#include "SDL.h"
#include "stdlib.h"
#include "SDL_ttf.h"
#include "SDL_image.h"
#include <malloc.h>
#include <time.h>
#include <stdio.h>
#include <iostream>
#include <cstring>
#include <malloc.h>
#include <string.h>
#include "SDL_mixer.h"

using namespace std;


const int kNumRecords = 5;

struct Record {
	int score;
	char name[20];
};

bool operator<(const Record& lhs, const Record& rhs) {
	return lhs.score > rhs.score;
}



SDL_Texture* get_text_texture_records(SDL_Renderer*& renderer, char* text, TTF_Font* font)
{
	SDL_Surface* textSurface = NULL;
	SDL_Color fore_color = { 0,0,0 };
	SDL_Color back_color = { 255,255,255 };
	textSurface = TTF_RenderText_Shaded(font, text, fore_color, back_color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_FreeSurface(textSurface);
	return texture;
}

SDL_Texture* get_text_texture(SDL_Renderer*& renderer, char* text, TTF_Font* font)
{
	SDL_Surface* textSurface = NULL;
	SDL_Color fore_color = { 0,0,0 };
	textSurface = TTF_RenderText_Blended(font, text, fore_color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_FreeSurface(textSurface);
	return texture;

}

void draw_text_sound(SDL_Renderer*& renderer, SDL_Texture* texture)
{
	SDL_Rect rect = { 130, 130, 150, 50 };
	SDL_RenderCopy(renderer, texture, NULL, &rect);
}
void draw_text_music(SDL_Renderer*& renderer, SDL_Texture* texture)
{
	SDL_Rect rect = { 530,130, 150, 50 };
	SDL_RenderCopy(renderer, texture, NULL, &rect);
}
void draw_text_for_nickname(SDL_Renderer*& renderer, SDL_Texture* texture)
{
	SDL_Rect rect = { 400,300, 150, 100 };
	SDL_RenderCopy(renderer, texture, NULL, &rect);
}

void draw_text(SDL_Renderer*& renderer, SDL_Texture* texture)
{
	SDL_Rect rect = { 10,10, 70, 50 };
	SDL_RenderCopy(renderer, texture, NULL, &rect);
}
void draw_text_records1(SDL_Renderer*& renderer, SDL_Texture* texture)
{
	SDL_Rect rect = { 300,0, 150, 50 };
	SDL_RenderCopy(renderer, texture, NULL, &rect);
}
void draw_text_records2(SDL_Renderer*& renderer, SDL_Texture* texture)
{
	SDL_Rect rect = { 300,50, 150, 50 };
	SDL_RenderCopy(renderer, texture, NULL, &rect);
}
void draw_text_records3(SDL_Renderer*& renderer, SDL_Texture* texture)
{
	SDL_Rect rect = { 300,100, 150, 50 };
	SDL_RenderCopy(renderer, texture, NULL, &rect);
}
void draw_text_records4(SDL_Renderer*& renderer, SDL_Texture* texture)
{
	SDL_Rect rect = { 300,150, 150, 50 };
	SDL_RenderCopy(renderer, texture, NULL, &rect);
}
void draw_text_records5(SDL_Renderer*& renderer, SDL_Texture* texture)
{
	SDL_Rect rect = { 300,200, 150, 50 };
	SDL_RenderCopy(renderer, texture, NULL, &rect);
}


void init_platforms(SDL_Rect platforms[], int count)
{
	srand(time(NULL));
	int c = 0;
	for (int i = 0; i < count; i++)
	{
		 int a = rand() % (800 - 90);
		int b = rand() % ((600 - 30) - c);

		platforms[i] = { a,b,90,15 };
		c -= 50;
	}
}


void draw_platforms(SDL_Renderer*& renderer, SDL_Rect platforms[], int count, SDL_Texture* texture[], SDL_Surface* GreenPlatform)
{
	for (int i = 0; i < count; i++)
	{
		if (platforms[i].w == 0) continue;
		texture[i] = SDL_CreateTextureFromSurface(renderer, GreenPlatform);
		SDL_RenderCopy(renderer, texture[i], NULL, &platforms[i]);
		SDL_DestroyTexture(texture[i]);
	}
}

bool is_intersection_platform(SDL_Rect rect1,SDL_Rect* platforms,int n)
{
	for (int i = 0; i < n; ++i)
	{
		if (rect1.x != platforms[i].x && rect1.y != platforms[i].y)
		{
			if (rect1.x < platforms[i].x + platforms[i].w &&
				rect1.x + rect1.w > platforms[i].x &&
				rect1.y < platforms[i].y + platforms[i].h &&
				rect1.y + rect1.h > platforms[i].y)
			{
				return true;
			}
		}
	}
	return false;
 }

bool is_colliding(SDL_Rect rect1, SDL_Rect rect2)
{
	if (rect1.x < rect2.x + rect2.w &&
		rect1.x + rect1.w > rect2.x &&
		rect1.y < rect2.y + rect2.h &&
		rect1.y + rect1.h > rect2.y)
	{
		return true;
	}
	return false;
}

void game(SDL_Renderer*& renderer, int& IsSound, int& IsMusic);
bool MainMenu(SDL_Renderer*& renderer, int& IsSound, int& IsMusic);
void RecordsMenu(SDL_Renderer*& renderer, int& IsSound, int& IsMusic);
void SettingMenu(SDL_Renderer*& renderer, int& IsSound, int& IsMusic);
 
 






int main(int argc, char** argv)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("Doodle Jump",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600,
		SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	int IsSound = 0;
	int IsMusic = 0;
	MainMenu(renderer,IsSound,IsMusic);



	return 0;
}



void RecordsMenu(SDL_Renderer*& renderer, int& IsSound, int& IsMusic) // Äîáàâèòü êíîïêó back
{
	TTF_Init();
	TTF_Font* my_font = TTF_OpenFont("Text.ttf", 100);
	FILE* records_file = fopen("records.txt", "r");



	const int kNumRecords = 5;
	const int kMaxRecordLength = 20;


	char charrecords1[kMaxRecordLength];
	char charrecords2[kMaxRecordLength];
	char charrecords3[kMaxRecordLength];
	char charrecords4[kMaxRecordLength];
	char charrecords5[kMaxRecordLength];
	SDL_Texture* texturerecord1;
	SDL_Texture* texturerecord2;
	SDL_Texture* texturerecord3;
	SDL_Texture* texturerecord4;
	SDL_Texture* texturerecord5;
	memset(charrecords1, 0, sizeof(charrecords1));
	memset(charrecords2, 0, sizeof(charrecords2));
	memset(charrecords3, 0, sizeof(charrecords3));
	memset(charrecords4, 0, sizeof(charrecords4));
	memset(charrecords5, 0, sizeof(charrecords5));
	char line[kMaxRecordLength];
	int i = 0;
	while (fgets(line, 100, records_file)) {
		if (i == 0) {
			strcpy(charrecords1, line);
		}
		else if (i == 1) {
			strcpy(charrecords2, line);
		}
		else if (i == 2) {
			strcpy(charrecords3, line);
		}
		else if (i == 3) {
			strcpy(charrecords4, line);
		}
		else if (i == 4) {
			strcpy(charrecords5, line);
		}
		i++;
		if (i >= kNumRecords) {
			break;
		}
	}
	fclose(records_file);
	int x1_for_line = 250;
	int x2_for_line = 200;
	int y_for_line = 500;

	bool quit = false;
	SDL_Event event;
	int nowx, nowy;
	SDL_Surface* ButtonBack = IMG_Load("ButtonBack.bmp");
	SDL_SetColorKey(ButtonBack, SDL_TRUE, SDL_MapRGB(ButtonBack->format, 255, 0, 0));
	SDL_Texture* TextureButtonBack = SDL_CreateTextureFromSurface(renderer, ButtonBack);
	SDL_FreeSurface(ButtonBack);

	SDL_Rect ForButtonBack = { 280,450,250,100 };
	while (!quit)
	{



		SDL_GetMouseState(&nowx, &nowy);
		SDL_Rect nowmouse = { nowx,nowy,2,2 };
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				quit = true;
			if (event.type == SDL_MOUSEBUTTONDOWN &&
				event.button.button == SDL_BUTTON_LEFT)
			{

				if (SDL_HasIntersection(&nowmouse, &ForButtonBack)) return;
			}
			if ((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_SPACE))
			{
				return;
			}
		}

		texturerecord1 = get_text_texture_records(renderer, charrecords1, my_font);
		texturerecord2 = get_text_texture_records(renderer, charrecords2, my_font);
		texturerecord3 = get_text_texture_records(renderer, charrecords3, my_font);
		texturerecord4 = get_text_texture_records(renderer, charrecords4, my_font);
		texturerecord5 = get_text_texture_records(renderer, charrecords5, my_font);
		draw_text_records1(renderer, texturerecord1);
		draw_text_records2(renderer, texturerecord2);
		draw_text_records3(renderer, texturerecord3);
		draw_text_records4(renderer, texturerecord4);
		draw_text_records5(renderer, texturerecord5);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderDrawLine(renderer, x1_for_line, y_for_line, x2_for_line, y_for_line);
		SDL_RenderDrawLine(renderer, x1_for_line, y_for_line, x1_for_line - 20, y_for_line - 20);
		SDL_RenderDrawLine(renderer, x1_for_line, y_for_line, x1_for_line - 20, y_for_line + 20);

		SDL_RenderCopy(renderer, TextureButtonBack, NULL, &ForButtonBack);


		SDL_RenderPresent(renderer);
		/* Èãðîâàÿ ëîãèêà */
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
		SDL_RenderClear(renderer);
		SDL_DestroyTexture(texturerecord1);
		SDL_DestroyTexture(texturerecord2);
		SDL_DestroyTexture(texturerecord3);
		SDL_DestroyTexture(texturerecord4);
		SDL_DestroyTexture(texturerecord5);

	}
}

void SettingsMenu(SDL_Renderer*& renderer, int& IsSound, int& IsMusic)
{
	TTF_Init();
	TTF_Font* my_font = TTF_OpenFont("Text.ttf", 100);
	FILE* records_file = fopen("records.txt", "r");





	bool quit = false;
	SDL_Event event;
	int nowx, nowy;
	SDL_Rect ForButtonBack = { 280,450,250,100 };
	SDL_Surface* ButtonBack = IMG_Load("ButtonBack.bmp");
	SDL_SetColorKey(ButtonBack, SDL_TRUE, SDL_MapRGB(ButtonBack->format, 255, 0, 0));
	SDL_Texture* TextureButtonBack = SDL_CreateTextureFromSurface(renderer, ButtonBack);
	SDL_FreeSurface(ButtonBack);

	SDL_Surface* ButtonOnOFF = IMG_Load("ButtonOnOff.bmp");
	SDL_SetColorKey(ButtonOnOFF, SDL_TRUE, SDL_MapRGB(ButtonOnOFF->format, 255, 0, 0));
	SDL_Texture* TextureButtonOnOff = SDL_CreateTextureFromSurface(renderer, ButtonOnOFF);
	SDL_FreeSurface(ButtonOnOFF);
	char strSound[50] = "SOUND";
	char strMusic[50] = "MUSIC";
	SDL_Texture* TextureForSound;
	SDL_Texture* TextureForMusic;

	SDL_Rect ForButtonSound = { 150,200,100,100 };
	SDL_Rect ForButtonMusic = { 550,200,100,100 };
	int x1_for_line = 250;
	int x2_for_line = 200;
	int y_for_line = 500;

	while (!quit)
	{




		SDL_GetMouseState(&nowx, &nowy);
		SDL_Rect nowmouse = { nowx,nowy,2,2 };
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				quit = true;
			if (event.type == SDL_MOUSEBUTTONDOWN &&
				event.button.button == SDL_BUTTON_LEFT)
			{

				if (SDL_HasIntersection(&nowmouse, &ForButtonBack)) return;
			}
			if ((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_SPACE))
			{
				return;
			}
			if (event.type == SDL_MOUSEBUTTONDOWN &&
				event.button.button == SDL_BUTTON_LEFT)
			{

				if (SDL_HasIntersection(&nowmouse, &ForButtonMusic))
				{

					IsMusic++;
					if (IsMusic % 2 == 0)
					{
						Mix_ResumeMusic();
					}
					else
					{
						Mix_PauseMusic();
					}
				}
			}
			if (event.type == SDL_MOUSEBUTTONDOWN &&
				event.button.button == SDL_BUTTON_LEFT)
			{

				if (SDL_HasIntersection(&nowmouse, &ForButtonSound))
				{

					IsSound++;
					if (IsMusic % 2 == 0)
					{
						Mix_ResumeMusic();
					}
					else
					{
						Mix_PauseMusic();
					}
				}
			}
		}
		TextureForSound = get_text_texture_records(renderer, strSound, my_font);
		TextureForMusic = get_text_texture_records(renderer, strMusic, my_font);
		draw_text_sound(renderer, TextureForSound);
		draw_text_music(renderer, TextureForMusic);

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderDrawLine(renderer, x1_for_line, y_for_line, x2_for_line, y_for_line);
		SDL_RenderDrawLine(renderer, x1_for_line, y_for_line, x1_for_line - 20, y_for_line - 20);
		SDL_RenderDrawLine(renderer, x1_for_line, y_for_line, x1_for_line - 20, y_for_line + 20);
		SDL_RenderCopy(renderer, TextureButtonBack, NULL, &ForButtonBack);
		SDL_RenderCopy(renderer, TextureButtonOnOff, NULL, &ForButtonSound);
		SDL_RenderCopy(renderer, TextureButtonOnOff, NULL, &ForButtonMusic);


		SDL_RenderPresent(renderer);
		/* Èãðîâàÿ ëîãèêà */
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
		SDL_RenderClear(renderer);
		SDL_DestroyTexture(TextureForSound);
		SDL_DestroyTexture(TextureForMusic);


	}
}

bool MainMenu(SDL_Renderer*& renderer, int& IsSound, int& IsMusic)
{

	if (IsMusic % 2 == 0)
	{
		Mix_Init(0);
		Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024);
		Mix_Music* fon = Mix_LoadMUS("MainMusic.wav");
		Mix_PlayMusic(fon, -1);
	}
	

	SDL_Surface* ButtonStart = IMG_Load("play.bmp");
	SDL_SetColorKey(ButtonStart, SDL_TRUE, SDL_MapRGB(ButtonStart->format, 255, 0, 0));
	SDL_Texture* TextureButtonStart = SDL_CreateTextureFromSurface(renderer, ButtonStart);
	SDL_FreeSurface(ButtonStart);

	SDL_Surface* ButtonSettings = IMG_Load("settings.bmp");
	SDL_SetColorKey(ButtonSettings, SDL_TRUE, SDL_MapRGB(ButtonSettings->format, 255, 0, 0));
	SDL_Texture* TextureButtonSettings = SDL_CreateTextureFromSurface(renderer, ButtonSettings);
	SDL_FreeSurface(ButtonSettings);

	SDL_Surface* ButtonRecords = IMG_Load("records.bmp");
	SDL_SetColorKey(ButtonRecords, SDL_TRUE, SDL_MapRGB(ButtonRecords->format, 255, 0, 0));
	SDL_Texture* TextureButtonRecords = SDL_CreateTextureFromSurface(renderer, ButtonRecords);
	SDL_FreeSurface(ButtonRecords);

	SDL_Surface* ButtonExit = IMG_Load("exit.bmp");
	SDL_SetColorKey(ButtonExit, SDL_TRUE, SDL_MapRGB(ButtonExit->format, 255, 0, 0));
	SDL_Texture* TextureButtonExit = SDL_CreateTextureFromSurface(renderer, ButtonExit);
	SDL_FreeSurface(ButtonExit);


	SDL_Rect ForButtonStart = { 290,50,250,100 };
	SDL_Rect ForButtonSettings = { 290,170,250,100 };
	SDL_Rect ForButtonRecords = { 290,290,250,100 };
	SDL_Rect ForButtonExit = { 290,410,250,100 };
	bool quit = false;
	SDL_Event event;
	int x1_for_line = 250;
	int x2_for_line = 200;
	int y_for_line = 100;
	int nowx, nowy;
	
	while (!quit)
	{


		SDL_GetMouseState(&nowx, &nowy);
		SDL_Rect nowmouse = { nowx,nowy,2,2 };
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				quit = true;
			if (event.type == SDL_MOUSEBUTTONDOWN &&
				event.button.button == SDL_BUTTON_LEFT)
			{

				if (SDL_HasIntersection(&nowmouse, &ForButtonStart)) game(renderer, IsSound, IsMusic);
			}
			if (event.type == SDL_MOUSEBUTTONDOWN &&
				event.button.button == SDL_BUTTON_LEFT)
			{

				if (SDL_HasIntersection(&nowmouse, &ForButtonSettings))
				{
					SettingsMenu(renderer, IsSound, IsMusic);
					if (IsMusic % 2 == 0)
					{
						Mix_ResumeMusic();
					}
					else
					{
						Mix_PauseMusic();
					}
				};
			}
			if (event.type == SDL_MOUSEBUTTONDOWN &&
				event.button.button == SDL_BUTTON_LEFT)
			{

				if (SDL_HasIntersection(&nowmouse, &ForButtonRecords)) // ÑÎÇÄÀÒÜ ÍÎÂÓÞ ÔÓÍÊÖÈÞ
				{
					RecordsMenu(renderer, IsSound, IsMusic);

				};
			}
			if (event.type == SDL_MOUSEBUTTONDOWN &&
				event.button.button == SDL_BUTTON_LEFT)
			{

				if (SDL_HasIntersection(&nowmouse, &ForButtonExit)) return 0;
			}
			if ((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_w))
			{
				if (y_for_line != 100) y_for_line -= 120;
				else y_for_line = 460;

			}
			if ((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_s))
			{
				if (y_for_line != 460) y_for_line += 120;
				else y_for_line = 100;
			}
			if ((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_SPACE))
			{
				if (y_for_line == 100) game(renderer, IsSound, IsMusic);
				if (y_for_line == 220) SettingsMenu(renderer, IsSound, IsMusic);
				if (y_for_line == 340) RecordsMenu(renderer, IsSound, IsMusic);
				if (y_for_line == 460) return 0;
			}


		}
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderDrawLine(renderer, x1_for_line, y_for_line, x2_for_line, y_for_line);
		SDL_RenderDrawLine(renderer, x1_for_line, y_for_line, x1_for_line - 20, y_for_line - 20);
		SDL_RenderDrawLine(renderer, x1_for_line, y_for_line, x1_for_line - 20, y_for_line + 20);
		SDL_RenderCopy(renderer, TextureButtonStart, NULL, &ForButtonStart);
		SDL_RenderCopy(renderer, TextureButtonSettings, NULL, &ForButtonSettings);
		SDL_RenderCopy(renderer, TextureButtonRecords, NULL, &ForButtonRecords);
		SDL_RenderCopy(renderer, TextureButtonExit, NULL, &ForButtonExit);

		SDL_RenderPresent(renderer);
		/* Èãðîâàÿ ëîãèêà */
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
		SDL_RenderClear(renderer);
	}
	return false;
}


void game(SDL_Renderer*& renderer, int& IsSound, int& IsMusic)
{


	TTF_Init();
	TTF_Font* my_font = TTF_OpenFont("Text.ttf", 100);
	SDL_Texture* Score;

	int k = 0;
	char text[10];
	_itoa_s(k, text, 10);

	SDL_Surface* Fon = IMG_Load("Fon.bmp");
	SDL_Texture* TextureForFon = SDL_CreateTextureFromSurface(renderer, Fon);
	SDL_Rect FullScreen = { 0,0,800,600 };

	SDL_Surface* Sky = IMG_Load("Sky.bmp");
	SDL_SetColorKey(Sky, SDL_TRUE, SDL_MapRGB(Sky->format, 255, 255, 255));
	SDL_SetSurfaceAlphaMod(Sky, 150);
	SDL_Texture* TextureSky = SDL_CreateTextureFromSurface(renderer, Sky);
	SDL_FreeSurface(Sky);
	SDL_Rect RectForSky = { 0,0,800,80 };

	SDL_Surface* ButtonPause = IMG_Load("ButtonPause.bmp");
	SDL_SetColorKey(ButtonPause, SDL_TRUE, SDL_MapRGB(ButtonPause->format, 255, 255, 255));
	SDL_SetSurfaceAlphaMod(ButtonPause, 150);
	SDL_Texture* TextureButtonPause = SDL_CreateTextureFromSurface(renderer, ButtonPause);
	SDL_FreeSurface(ButtonPause);
	SDL_Rect RectForButtonPause = { 730,15,40,40 };

	SDL_Surface* DoodleLeft = IMG_Load("DoodleLookLeft.bmp");
	SDL_SetColorKey(DoodleLeft, SDL_TRUE, SDL_MapRGB(DoodleLeft->format, 255, 255, 255));
	SDL_Texture* TextureDoodleLeft = SDL_CreateTextureFromSurface(renderer, DoodleLeft);
	SDL_FreeSurface(DoodleLeft);

	SDL_Surface* DoodleRight = IMG_Load("DoodleLookRight.bmp");
	SDL_SetColorKey(DoodleRight, SDL_TRUE, SDL_MapRGB(DoodleRight->format, 255, 255, 255));
	SDL_Texture* TextureDoodleRight = SDL_CreateTextureFromSurface(renderer, DoodleRight);
	SDL_FreeSurface(DoodleRight);

	SDL_Surface* DoodleLeftInJump = IMG_Load("DoodleLookLeftAndJump.bmp");
	SDL_SetColorKey(DoodleLeftInJump, SDL_TRUE, SDL_MapRGB(DoodleLeftInJump->format, 255, 255, 255));
	SDL_Texture* TextureDoodleLeftInJump = SDL_CreateTextureFromSurface(renderer, DoodleLeftInJump);
	SDL_FreeSurface(DoodleLeftInJump);

	SDL_Surface* DoodleRightInJump = IMG_Load("DoodleLookRightAndJump.bmp");
	SDL_SetColorKey(DoodleRightInJump, SDL_TRUE, SDL_MapRGB(DoodleRightInJump->format, 255, 255, 255));
	SDL_Texture* TextureDoodleRightInJump = SDL_CreateTextureFromSurface(renderer, DoodleRightInJump);
	SDL_FreeSurface(DoodleRightInJump);

	SDL_Surface* DoodleAttack = IMG_Load("DoodleAttack.bmp");
	SDL_SetColorKey(DoodleAttack, SDL_TRUE, SDL_MapRGB(DoodleAttack->format, 255, 255, 255));
	SDL_Texture* TextureDoodleAttack = SDL_CreateTextureFromSurface(renderer, DoodleAttack);
	SDL_FreeSurface(DoodleAttack);


	SDL_Surface* Monster1 = IMG_Load("Monster1.bmp");
	SDL_SetColorKey(Monster1, SDL_TRUE, SDL_MapRGB(Monster1->format, 255, 255, 255));
	SDL_Texture* TextureMonster1 = SDL_CreateTextureFromSurface(renderer, Monster1);
	SDL_FreeSurface(Monster1);

	SDL_Surface* BallForAttack = IMG_Load("BallForAttack.bmp");
	SDL_SetColorKey(BallForAttack, SDL_TRUE, SDL_MapRGB(BallForAttack->format, 255, 255, 255));
	SDL_Texture* TextureBallForAttack = SDL_CreateTextureFromSurface(renderer, BallForAttack);
	SDL_FreeSurface(BallForAttack);

	SDL_Surface* BrokenPlatform = IMG_Load("BrokenPlatform.bmp");
	SDL_SetColorKey(BrokenPlatform, SDL_TRUE, SDL_MapRGB(BrokenPlatform->format, 255, 255, 255));
	SDL_Texture* TextureBrokenPlatform = SDL_CreateTextureFromSurface(renderer, BrokenPlatform);
	SDL_FreeSurface(BrokenPlatform);

	SDL_Surface* GreenPlatform = IMG_Load("GreenPlatform.bmp");
	SDL_SetColorKey(GreenPlatform, SDL_TRUE, SDL_MapRGB(GreenPlatform->format, 255, 255, 255));
	int n = 10;
	SDL_Texture** TextureGreenPlatform = (SDL_Texture**)malloc(sizeof(SDL_Texture*) * n);
	SDL_Rect* platforms = (SDL_Rect*)malloc(sizeof(SDL_Rect) * n);
	init_platforms(platforms, 10);

	SDL_Rect PointDoodle;
	SDL_Rect RectBallAttack;

	SDL_Rect* startPlat;


	SDL_Surface* SurfaceForNickname = SDL_CreateRGBSurface(0, 200, 50, 32, 0, 0, 0, 0);
	SDL_Texture* TextureNickname = SDL_CreateTextureFromSurface(renderer, SurfaceForNickname);
	SDL_StartTextInput();
	char* inputText = (char*)malloc(sizeof(char));
	char Rules[50] = "NickName: ";
	SDL_Texture* rulesfornicname;

	strcpy(inputText, " ");
	bool quit = false;
	SDL_Event event;
	SDL_Color textColor = { 255, 255, 255 };
	SDL_Rect textRect;

	while (!quit) {
		while (SDL_PollEvent(&event)) {
			switch (event.type)
			{
			case SDL_QUIT:
				quit = 1;
				break;
			case SDL_TEXTINPUT:
				inputText = strcat(inputText, event.text.text);
				break;
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_BACKSPACE && strlen(inputText) > 0)
				{
					if (strlen(inputText) != 1) inputText[strlen(inputText) - 1] = '\0';
				}
				if (event.key.keysym.sym == SDLK_RETURN)
				{
					quit = true; break;
				}
			}
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		SurfaceForNickname = TTF_RenderText_Solid(my_font, inputText, textColor);
		TextureNickname = SDL_CreateTextureFromSurface(renderer, SurfaceForNickname);

		textRect.x = (800 - SurfaceForNickname->w) / 2;
		textRect.y = (600 - SurfaceForNickname->h) / 2;
		textRect.w = SurfaceForNickname->w;
		textRect.h = SurfaceForNickname->h;
		if (textRect.x <= 210)
		{
			quit = true; break;
		}
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
		rulesfornicname = get_text_texture_records(renderer, Rules, my_font);
		SDL_Rect forRules = { 0,textRect.y,200,textRect.h };
		SDL_RenderCopy(renderer, rulesfornicname, NULL, &forRules);

		SDL_RenderCopy(renderer, TextureNickname, NULL, &textRect);
		SDL_RenderPresent(renderer);


		SDL_FreeSurface(SurfaceForNickname);
		SDL_DestroyTexture(TextureNickname);
		SDL_DestroyTexture(rulesfornicname);
	}
	SDL_StopTextInput();

	quit = false;
	float jump_speed = -19.0;
	int x = 400; int y = 50; int h = 100;
	float dy = 0, dx = 0;
	bool side = false;
	srand(time(NULL));
	
	int Ruletka = 10;
	int Monster = 10;
	int m = 0;
	int temp = 0;
	int b = NULL;
	int nowx, nowy;
	while (!quit)
	{

		Monster = rand() % 100;
		bool isjump = false;
		bool isattack = false;
		SDL_GetMouseState(&nowx, &nowy);
		SDL_Rect nowmouse = { nowx,nowy,2,2 };
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				quit = true;
			if ((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_d))
			{
				x += 20;
				side = true;

			}
			if ((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_a))
			{
				x -= 20;
				side = false;
			}
			if ((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_SPACE))
			{
				isattack = true;
			}
			if (event.type == SDL_MOUSEBUTTONDOWN &&
				event.button.button == SDL_BUTTON_LEFT)
			{

				if (SDL_HasIntersection(&nowmouse, &RectForButtonPause)) MainMenu(renderer, IsSound, IsMusic);
			}
			if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) MainMenu(renderer, IsSound, IsMusic);
		}
		PointDoodle = { x,y,70,70 };
		dy += 0.7;
		y += dy;
		if (m == 0)
		{
			PointDoodle = { platforms[1].x, platforms[1].y, 80, 80 }; m++;
		}
		if (y > 580)
		{
			if (IsSound % 2 == 0)
			{
				Mix_Chunk* fireMusic = Mix_LoadWAV("MusicForDie.wav");
				Mix_PlayChannel(-1, fireMusic, 0);
			}
			break;
		}

		if (y < h)
		{
			for (int i = 0; i < 10; ++i)
			{
				y = h;
				platforms[i].y = platforms[i].y - dy;

				if (platforms[i].y > 533)
				{
					do
					{
						platforms[i].y = rand() % (50);
						platforms[i].x = rand() % 800 - 90;
					} while (is_intersection_platform(platforms[i], platforms, n));
				}
			}
		}

		if ( Monster % 5 == 0)
		{

		}
		

		for (int i = 0; i < 10; i++)
		{
			if (is_colliding(PointDoodle, platforms[i]) && dy > 0)
			{
				if (temp != platforms[i].y && b != i)
				{

					isjump = true;
					b = i;
					temp = platforms[i].y;
					k++;
				}
				
				dy = jump_speed;
				SDL_Delay(3);
				
				if (IsSound % 2 == 0) 
				{
					Mix_Chunk* fireMusic = Mix_LoadWAV("MusicForJump.wav");
					Mix_PlayChannel(-1, fireMusic, 0);
				}
				break;
			}
		}


		if (PointDoodle.x < 0) x = 795;
		if (PointDoodle.x > 800) x = 5;

		SDL_RenderCopy(renderer, TextureForFon, NULL, &FullScreen);
		SDL_RenderCopy(renderer, TextureSky, NULL, &RectForSky);
		SDL_RenderCopy(renderer, TextureButtonPause, NULL, &RectForButtonPause);
		draw_platforms(renderer, platforms, 10, TextureGreenPlatform, GreenPlatform);
		if (side)
		{
			if (isattack)
			{
				SDL_RenderCopy(renderer, TextureDoodleAttack, NULL, &PointDoodle);


				RectBallAttack = PointDoodle;

				if (IsSound % 2 == 0)
				{
					Mix_Chunk* fireMusic = Mix_LoadWAV("MusicForAttack.wav");
					Mix_PlayChannel(-1, fireMusic, 0);
				}
				while (RectBallAttack.y >= 10)
				{

					SDL_RenderClear(renderer);
					RectBallAttack.y -= 5;
					SDL_RenderCopy(renderer, TextureForFon, NULL, &FullScreen);
					SDL_RenderCopy(renderer, TextureDoodleAttack, NULL, &PointDoodle);
					RectBallAttack.w = 20;
					RectBallAttack.h = 20;
					RectBallAttack.x = PointDoodle.x + 20;
					SDL_RenderCopy(renderer, TextureBallForAttack, NULL, &RectBallAttack);
					draw_platforms(renderer, platforms, 10, TextureGreenPlatform, GreenPlatform);
					Score = get_text_texture(renderer, text, my_font);
					draw_text(renderer, Score);
					SDL_DestroyTexture(Score);
					SDL_RenderPresent(renderer);
					
				}



			}
			else
			{
				if (isjump)
				{
					SDL_RenderCopy(renderer, TextureDoodleRightInJump, NULL, &PointDoodle);
					SDL_RenderPresent(renderer);
				}
				else {


					SDL_RenderCopy(renderer, TextureDoodleRight, NULL, &PointDoodle);
				}
			}
		}

		else
		{
			if (isattack)
			{
				SDL_RenderCopy(renderer, TextureDoodleAttack, NULL, &PointDoodle);


				RectBallAttack = PointDoodle;

				if (IsSound % 2 == 0)
				{
					Mix_Chunk* fireMusic = Mix_LoadWAV("MusicForAttack.wav");
					Mix_PlayChannel(-1, fireMusic, 0);
				}
				while (RectBallAttack.y >= 10)
				{
					SDL_RenderClear(renderer);
					RectBallAttack.y -= 5;
					SDL_RenderCopy(renderer, TextureForFon, NULL, &FullScreen);
					SDL_RenderCopy(renderer, TextureDoodleAttack, NULL, &PointDoodle);
					RectBallAttack.w = 20;
					RectBallAttack.h = 20;
					RectBallAttack.x = PointDoodle.x + 20;
					SDL_RenderCopy(renderer, TextureBallForAttack, NULL, &RectBallAttack);
					draw_platforms(renderer, platforms, 10, TextureGreenPlatform, GreenPlatform);
					Score = get_text_texture(renderer, text, my_font);
					draw_text(renderer, Score);
					SDL_DestroyTexture(Score);
					SDL_RenderPresent(renderer);
					

				}


			}
			else
			{
				if (isjump)
				{
					SDL_RenderCopy(renderer, TextureDoodleLeftInJump, NULL, &PointDoodle);
					SDL_RenderPresent(renderer);
				}
				else {

					SDL_RenderCopy(renderer, TextureDoodleLeft, NULL, &PointDoodle);

				}
			}


		}

		_itoa_s(k, text, 10);
		Score = get_text_texture(renderer, text, my_font);
		draw_text(renderer, Score);
		SDL_DestroyTexture(Score);
		SDL_RenderPresent(renderer);
		SDL_Delay(5);
		SDL_RenderClear(renderer);
	}
	FILE* records_read_file = fopen("records.txt", "r");
	if (records_read_file != NULL) {
		Record records[kNumRecords];
		memset(records, 0, sizeof(records));
		char line[100];
		char score[20];
		int i = 0;
		while (fgets(line, 100, records_read_file)) {
			i = 0;
			memset(score, 0, sizeof(score));
			while (line[i] != ' ') {
				score[i] += line[i];
				i++;
			}
			int intscore = atoi(score);
			if (intscore > records[kNumRecords].score) {
				// This is one of the best records.
				Record new_record;
				new_record.score = intscore;
				sscanf(line + i + 2, "%s", new_record.name);
				for (int i = 0; i < kNumRecords; i++) {
					if (new_record.score > records[i].score) {
						// Insert the new record.
						for (int j = kNumRecords - 1; j > i; j--) {
							records[j] = records[j - 1];
						}
						records[i] = new_record;
						break;
					}
				}
			}
		}

		fclose(records_read_file);

		// Add the new record to the array, if it's a new high score.
		int intscore = k;
		if (intscore > records[kNumRecords].score) {
			Record new_record;
			new_record.score = intscore;
			strcpy(new_record.name, inputText);
			for (int i = 0; i < kNumRecords; i++) {
				if (new_record.score > records[i].score) {
					for (int j = kNumRecords - 1; j > i; j--) {
						records[j] = records[j - 1];
					}
					records[i] = new_record;
					break;
				}
			}
		}

		// Write the sorted records back to the file.
		FILE* records_write_file = fopen("records.txt", "w");
		if (records_write_file != NULL) {
			for (int i = 0; i < kNumRecords; i++) {
				char* name = records[i].name;
				name[strcspn(name, "\n")] = '\0';
				fprintf(records_write_file, "%d - %s\n", records[i].score, name);
			}
			fclose(records_write_file);
		}
		else {
			printf("Failed to open the file for writing.\n");
		}
	}
	else {
		printf("Failed to open the file for reading.\n");
	}


}