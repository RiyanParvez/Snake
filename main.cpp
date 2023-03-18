#define SDL_MAIN_HANDLED
#include "SDL.h"
#include <Windows.h>
#include <iostream>
#include <cmath>
#undef main
#include <SDL_ttf.h>
#include <string>

bool Coliding(SDL_Rect* Rectangle, SDL_Rect* RectangleTwo) {
		if (Rectangle->x + Rectangle->w < RectangleTwo->x || Rectangle->x > RectangleTwo->x + RectangleTwo->w || Rectangle->y + Rectangle->h < RectangleTwo->y || Rectangle->y > RectangleTwo->y + RectangleTwo->h) {

			return false;
		}
		else {
			return true;
		}
}
int main(int argc, char* args[]) {
	TTF_Init();
	if (SDL_Init(SDL_INIT_VIDEO) > 0) {
		std::cout << "SDL Could'nt Be Initialized. " << std::endl << "Error: " << SDL_GetError() << std::endl;
	}
	else {
		//References
		int WindowX = NULL;
		int WindowY = NULL;
		bool IsRunning = true;
		int PreviousScore = NULL;
		bool DoneRendering = false;
		int CurrentScore = NULL;;
		int MovemntDelay = 150;
		bool HasDied = false;
		bool BotIsRunning = false;
		bool RenderApple = true;;
		int PreviousHighScore = NULL;
		int HighScore = NULL;
		int CurrentSpeed = 0;
		int RandomNumber = NULL;
		int RandomNumberTwo = NULL;
		int MouseX = NULL;
		int MouseY = NULL;
		int x = NULL;
		int y = NULL;
		int h = NULL;
		int FontSize = 23;
		int w = NULL;
		int ww = NULL;
		int wh = NULL;
		bool restartedGame = false;
		int FontSizeTwo = (FontSize / 2) + 2;
		int SW = 0;
		int SH = 0;
		int ScreenWidth = 800;
		int ScreenHeight = 600;
		bool BoredMode = false;
		SDL_Window* GameWindow = SDL_CreateWindow("A Simple Game.", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, ScreenWidth, ScreenHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_RENDERER_PRESENTVSYNC | SDL_WINDOW_BORDERLESS);
		SDL_Renderer* Renderer = SDL_CreateRenderer(GameWindow, -1, 0);
		SDL_Surface* WindowSurface = SDL_GetWindowSurface(GameWindow);
		TTF_Init();
		//Rects
		SDL_Rect RectangleTwo;
		SDL_Rect TextureRectangle;
		SDL_Rect TextureRectangleTwo;
		SDL_Rect MouseRect{ 5, 5, 5, 5 };
		SDL_Rect XposRect;
		SDL_Rect YposRect;
		SDL_Rect Intersection;
		SDL_Rect IntersectionThree;
		SDL_Rect IntersectionFour;
		SDL_Rect IntersectionFive;
		SDL_Rect SnakeBodySegments[1000];
		SDL_Rect FullScreenRect;
		SDL_Rect FullScreenRectTwo;
		SDL_Rect maximizeSquare;
		SDL_Rect TitleBarMinimize;
		SDL_Rect TitleBarClose;
		//Colors
		SDL_Color White = { 200, 200, 200 };
		SDL_Color NewColor = { 68, 68, 68 };
		SDL_Color NewColorTwo = { 255, 0, 0 };
		//Fonts
		TTF_Font* font = TTF_OpenFont("Courier Std Bold.otf", FontSize);
		TTF_Font* fontTwo = TTF_OpenFont("Courier Std Bold.otf", 40);
		//Positions And Proportions

		SnakeBodySegments[0].x = (ScreenWidth / 2);
		SnakeBodySegments[0].y = (ScreenHeight / 2);
		SnakeBodySegments[0].w = 25;
		SnakeBodySegments[0].h = 25;
		SDL_FillRect(WindowSurface, NULL, SDL_MapRGB(WindowSurface->format, 0, 0, 0));
		RectangleTwo.x = RectangleTwo.y = 120;
		RectangleTwo.w = 23;
		RectangleTwo.h = 23;
		SDL_FillRect(WindowSurface, NULL, SDL_MapRGB(WindowSurface->format, 0, 0, 0));
		//Enums
		enum class Direction {
			None,
			Up,
			Down,
			Left,
			Right,
			Nll
		};
		enum class MovingDir {
			L,
			R,
			U,
			D,
			Nll
		};
		enum Theme {
			Dark,
			Light
		};
		Theme theme = Theme::Light;
		MovingDir MovingDirection = MovingDir::Nll;
		Direction MovementDirection = Direction::Nll;
		//
		SDL_Event Event;
		//
		SDL_Surface* GameOverSurface = TTF_RenderText_Blended(fontTwo, "You Died.", NewColor);
		SDL_Surface* Retry = TTF_RenderText_Blended(fontTwo, "Press 'R' to Retry.", NewColorTwo);
		SDL_Texture* GameOverTexture = SDL_CreateTextureFromSurface(Renderer, GameOverSurface);
		SDL_Texture* RetryTexture = SDL_CreateTextureFromSurface(Renderer, Retry);
		TTF_Font* fontForDebugging = TTF_OpenFont("Courier Std Bold.otf", FontSizeTwo);
		SDL_Texture* XposTexture;
		SDL_Texture* YposTexture;
		SDL_Surface* XposSurface;
		SDL_Surface* YposSurface;
		SDL_Surface* TextSurface;
		SDL_Texture* TextTexture;
		SDL_Surface* TextSurfaceTwo;
		SDL_Texture* TextTextureTwo;
		//Strings
		std::string Xpos;
		std::string Ypos;
		std::string Score;
		std::string HighScoreText;
		//
		
		MovementDirection = Direction::Up;
		MovingDirection = MovingDir::U;
		TitleBarMinimize.w = 15;
		TitleBarMinimize.h = 15;
		TitleBarMinimize.y = 10;
		TitleBarClose.w = 15;
		TitleBarClose.h = 15;
		TitleBarClose.y = 10;
		FullScreenRect.w = GameOverSurface->w;
		FullScreenRect.h = GameOverSurface->h;
		FullScreenRect.x = ScreenWidth / 2 - 100;
		FullScreenRect.y = (ScreenHeight / 2) - 75;
		FullScreenRectTwo.w = Retry->w;
		FullScreenRectTwo.h = Retry->h;
		FullScreenRectTwo.x = (ScreenWidth / 2) - 220;
		FullScreenRectTwo.y = ((ScreenHeight + 100) / 2) - 75;
		//
		SDL_GetWindowPosition(GameWindow, &WindowX, &WindowY);
		//GameLoop 
		while (IsRunning) {
			TitleBarMinimize.x = ((1078 * SW) / 1200) + 35;
			TitleBarClose.x = ((1078 * SW) / 1200) + 55;
			if (theme == Theme::Dark) {
				SDL_SetRenderDrawColor(Renderer, 4, 10, 15, 255);
			}
			else if (theme == Theme::Light) {
				SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
			}
			SDL_RenderClear(Renderer);
			if (PreviousScore > CurrentScore) {
				HighScore = PreviousScore;
			}
			else if (CurrentScore > PreviousScore) {
				HighScore = CurrentScore;
			}
			if (PreviousHighScore > HighScore) {
				HighScore = PreviousHighScore;
			}
			//Random Number
			srand(time(0));
			RandomNumber = (rand() * rand()) % ScreenHeight;
			RandomNumberTwo = (rand() * rand()) % ScreenWidth;
			//Set Snake Segment Size
			if (Coliding(&SnakeBodySegments[0], &RectangleTwo)) {
				if (CurrentScore > 1 && MovemntDelay > 18) {
					MovemntDelay -= 1;
				}
				for (int i = CurrentScore + 1; i > 0; i--) {
					SnakeBodySegments[i].h = 25;
					SnakeBodySegments[i].w = 25;
					SnakeBodySegments[i].x = SnakeBodySegments[i - 1].x;
					SnakeBodySegments[i].y = SnakeBodySegments[i - 1].y;
				}
				RectangleTwo.y = RandomNumber;
				RectangleTwo.x = RandomNumberTwo;

				if (!restartedGame) PreviousScore = CurrentScore++; //Somehow works , if ++ is after the integer then the previous code gets executed first so, first Previous Score Becomes equal to Current Score Then Current Score Increases
				else CurrentScore++;
			}
			if (RectangleTwo.x <= 24) {
				srand(time(0));
				RectangleTwo.x = rand() % ScreenWidth;
			}
			if (RectangleTwo.x == SnakeBodySegments[0].x || SnakeBodySegments[0].x + 1 == RectangleTwo.x || SnakeBodySegments[0].x + 2 == RectangleTwo.x || SnakeBodySegments[0].x + 12 == RectangleTwo.x  ||  SnakeBodySegments[0].x + 3 == RectangleTwo.x || SnakeBodySegments[0].x + 4 == RectangleTwo.x || SnakeBodySegments[0].x + 5 == RectangleTwo.x || SnakeBodySegments[0].x + 6 == RectangleTwo.x || SnakeBodySegments[0].x + 7 == RectangleTwo.x || SnakeBodySegments[0].x + 8 == RectangleTwo.x || SnakeBodySegments[0].x + 9 == RectangleTwo.x || SnakeBodySegments[0].x + 10 == RectangleTwo.x || SnakeBodySegments[0].x + 11 == RectangleTwo.x || SnakeBodySegments[0].x + 13 == RectangleTwo.x || SnakeBodySegments[0].x + 14 == RectangleTwo.x || SnakeBodySegments[0].x + 15 == RectangleTwo.x) {
				if (RectangleTwo.y == SnakeBodySegments[0].y || SnakeBodySegments[0].y + 1 == RectangleTwo.y || SnakeBodySegments[0].y + 2 == RectangleTwo.y || SnakeBodySegments[0].y + 3 == RectangleTwo.y || SnakeBodySegments[0].y + 4 == RectangleTwo.y || SnakeBodySegments[0].y + 5 == RectangleTwo.y || SnakeBodySegments[0].y + 6 == RectangleTwo.y || SnakeBodySegments[0].y + 7 == RectangleTwo.y || SnakeBodySegments[0].y + 8 == RectangleTwo.y || SnakeBodySegments[0].y + 9 == RectangleTwo.y || SnakeBodySegments[0].y + 10 == RectangleTwo.y || SnakeBodySegments[0].y + 11 == RectangleTwo.y || SnakeBodySegments[0].y + 12 == RectangleTwo.y || SnakeBodySegments[0].y + 13 == RectangleTwo.y || SnakeBodySegments[0].y + 14 == RectangleTwo.y || SnakeBodySegments[0].y + 15 == RectangleTwo.y) {
					srand(time(0));
					RectangleTwo.x = rand() % ScreenWidth;
					RectangleTwo.y = rand() % ScreenHeight;
				}
			}
			//Text 
			SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");
			if (CurrentScore == 0) CurrentScore = 1;
			Score = "Score:" + std::to_string(CurrentScore - 1);
			if (HighScore == 0) HighScore = 1;
			HighScoreText = "HighScore:" + std::to_string(HighScore - 1);
			//Surface
			TextSurface = TTF_RenderText_Blended(font, Score.c_str(), White);
			TextSurfaceTwo = TTF_RenderText_Blended(font, HighScoreText.c_str(), White);
			//Converting Surface To Texture
			TextTexture = SDL_CreateTextureFromSurface(Renderer, TextSurface);
			TextTextureTwo = SDL_CreateTextureFromSurface(Renderer, TextSurfaceTwo);
			//Dimentions
			TextureRectangle.w = TextSurface->w;
			TextureRectangle.h = TextSurface->h;
			TextureRectangleTwo.h = TextSurfaceTwo->h;
			TextureRectangleTwo.w = TextSurfaceTwo->w;
			//Positions
			TextureRectangle.x = 10;
			TextureRectangleTwo.x = TextSurface->w + 20;
			TextureRectangleTwo.y = 10;
			TextureRectangle.y = 10;
			//For Debugging And Bug Fixing
			Xpos = "X:" + std::to_string(SnakeBodySegments[0].x);
			Ypos = "Y:" + std::to_string(SnakeBodySegments[0].y);
			//Surface
			XposSurface = TTF_RenderText_Blended(fontForDebugging, Xpos.c_str(), White);
			YposSurface = TTF_RenderText_Blended(fontForDebugging, Ypos.c_str(), White);
			//Converting Surface To Texture
			XposTexture = SDL_CreateTextureFromSurface(Renderer, XposSurface);
			YposTexture = SDL_CreateTextureFromSurface(Renderer, YposSurface);
			//Dimentions
			XposRect.w = XposSurface->w;
			XposRect.h = XposSurface->h;
			YposRect.h = YposSurface->h;
			YposRect.w = YposSurface->w;
			//Window Size For Text Position
			SDL_GetWindowSize(GameWindow, &SW, &SH);
			//Positions
			XposRect.x = ((1078 * SW) / 1200)+25;
			YposRect.x = ((1078 * SW) / 1200)+25;
			YposRect.y = ((10 * SH) / 720) + 20;
			XposRect.y = ((32 * SH) / 720) + 20;
			//Window Size
			//BoredMode
			if (BoredMode) {
				SDL_SetWindowOpacity(GameWindow, 0.65f);
			}
			//ComeBack
			if (SnakeBodySegments[0].y > ScreenHeight) {
				SnakeBodySegments[0].y = 30;
			}
			if (SnakeBodySegments[0].y < 30) {
				SnakeBodySegments[0].y = ScreenHeight;
			}
			if (SnakeBodySegments[0].x > ScreenWidth) {
				SnakeBodySegments[0].x = 0;
			}
			if (SnakeBodySegments[0].x < 0) {
				SnakeBodySegments[0].x = ScreenWidth - SnakeBodySegments[0].w;
			}
			if (RectangleTwo.y > ScreenHeight - 20) {
				RectangleTwo.y = ScreenHeight - 20;
			}
			if (RectangleTwo.y < 30) {
				RectangleTwo.y = 30;
			}
			SDL_GetMouseState(&MouseX, &MouseY);
			MouseRect.x = MouseX;
			MouseRect.y = MouseY;
			while (SDL_PollEvent(&Event)) {
				if (Event.type == SDL_QUIT) {
					IsRunning = false;
				}
				if (Event.type == SDL_KEYDOWN) {
					if (Event.key.keysym.sym == SDLK_r) {
						if (HasDied) {
							PreviousHighScore = HighScore;
							MovemntDelay = 150;
							CurrentScore = 0;
							RectangleTwo.x = RectangleTwo.y = 120;
							SnakeBodySegments[0].x = (ScreenWidth / 2);
							SnakeBodySegments[0].y = (ScreenHeight / 2);
							HasDied = false;
						}
					}


					if (Event.key.keysym.sym == SDLK_s && MovingDirection != MovingDir::U) {
						MovementDirection = Direction::Down;
					}
					if (Event.key.keysym.sym == SDLK_w && MovingDirection != MovingDir::D) {
						MovementDirection = Direction::Up;
					}
					if (Event.key.keysym.sym == SDLK_a && MovingDirection != MovingDir::R) {
						MovementDirection = Direction::Left;
					}
					if (Event.key.keysym.sym == SDLK_d && MovingDirection != MovingDir::L) {
						MovementDirection = Direction::Right;
					}


					if (Event.key.keysym.sym == SDLK_q) {
						BoredMode = true;
					}
					if (Event.key.keysym.sym == SDLK_UP) {
						WindowY -= 10;
							SDL_SetWindowPosition(GameWindow, WindowX, WindowY);
					}
					if (Event.key.keysym.sym == SDLK_LEFT) {
						WindowX -= 10;
							SDL_SetWindowPosition(GameWindow, WindowX, WindowY);
					}
					if (Event.key.keysym.sym == SDLK_DOWN) {

						WindowY += 10;
							SDL_SetWindowPosition(GameWindow, WindowX, WindowY);
					}
					if (Event.key.keysym.sym == SDLK_RIGHT) {
						WindowX += 10;
							SDL_SetWindowPosition(GameWindow, WindowX, WindowY);
					}
					if (Event.key.keysym.sym == SDLK_1) {
						theme = Theme::Dark;
					}
					if (Event.key.keysym.sym == SDLK_2) {
						theme = Theme::Light;
					}
					
				}
				if (Event.type == SDL_MOUSEBUTTONDOWN) {
					if (Event.button.button == SDL_BUTTON_LEFT) {
						if (SDL_IntersectRect(&MouseRect, &TitleBarClose, &IntersectionThree)) {
							IsRunning = false;
						}
						if (SDL_IntersectRect(&MouseRect, &TitleBarMinimize, &IntersectionFour)) {
							SDL_MinimizeWindow(GameWindow);
						}
					}
				}
			}
			if (theme == Theme::Light) {
				SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 255);
				SDL_RenderFillRect(Renderer, &RectangleTwo);
				SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 255);
				SDL_RenderFillRect(Renderer, &SnakeBodySegments[0]);
				SDL_SetRenderDrawColor(Renderer, 45, 45, 45, 255);
				for (int i = 1; i < CurrentScore; i++) {
					SDL_RenderFillRect(Renderer, &SnakeBodySegments[i]);
				}
				SDL_SetRenderDrawColor(Renderer, 76, 76, 76, 255);
				for (int i = 1; i < CurrentScore; i++) {
					SDL_RenderDrawRect(Renderer, &SnakeBodySegments[i]);
				}
				SDL_SetRenderDrawColor(Renderer, 76, 76, 76, 255);
				SDL_RenderDrawRect(Renderer, &SnakeBodySegments[0]);
			}
			
			SDL_RenderPresent(Renderer);
			if (theme == Theme::Dark) {
				SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
				if (RenderApple) {
					SDL_RenderFillRect(Renderer, &RectangleTwo);
				}
				SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
				SDL_RenderFillRect(Renderer, &SnakeBodySegments[0]);
				SDL_SetRenderDrawColor(Renderer, 210, 210, 210, 255);
				for (int i = 1; i < CurrentScore; i++) {
					SDL_RenderFillRect(Renderer, &SnakeBodySegments[i]);
				}
				SDL_SetRenderDrawColor(Renderer, 179, 179, 179, 255);
				for (int i = 1; i < CurrentScore; i++) {
					SDL_RenderDrawRect(Renderer, &SnakeBodySegments[i]);
				}
				SDL_SetRenderDrawColor(Renderer, 179, 179, 179, 255);
				SDL_RenderDrawRect(Renderer, &SnakeBodySegments[0]);
			}
			
			SDL_RenderPresent(Renderer);
			//TitleBar
			SDL_SetRenderDrawColor(Renderer, 30, 30, 35, 125);
			SDL_RenderFillRect(Renderer, &TitleBarClose);
			SDL_RenderFillRect(Renderer, &TitleBarMinimize);
			SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
			SDL_RenderDrawRect(Renderer, &maximizeSquare);
			SDL_RenderDrawLine(Renderer, TitleBarMinimize.x + 5, TitleBarMinimize.y + 13, TitleBarMinimize.x + 13, TitleBarMinimize.y + 13);
			SDL_RenderDrawLine(Renderer, TitleBarClose.x + 2, TitleBarClose.y + 2, TitleBarClose.x + 11, TitleBarClose.y + 11);
			SDL_RenderDrawLine(Renderer, TitleBarClose.x + 2, TitleBarClose.y + 11, TitleBarClose.x + 11, TitleBarClose.y + 2);
			SDL_SetRenderDrawColor(Renderer, 25, 4, 6, 255);
			SDL_RenderDrawRect(Renderer, &RectangleTwo);
			//Done
			if (HasDied) {
				SDL_RenderCopy(Renderer, GameOverTexture, NULL, &FullScreenRect);
				SDL_RenderCopy(Renderer, RetryTexture, NULL, &FullScreenRectTwo);
			} 
			SDL_RenderCopy(Renderer, TextTexture, NULL, &TextureRectangle);
			SDL_RenderCopy(Renderer, TextTextureTwo, NULL, &TextureRectangleTwo);
			//Freeing Memory
			SDL_FreeSurface(TextSurface);
			TextSurface = NULL;
			SDL_FreeSurface(TextSurfaceTwo);
			TextSurfaceTwo = NULL;
			SDL_DestroyTexture(TextTexture);
			TextTexture = NULL;
			SDL_DestroyTexture(TextTextureTwo);
			TextTextureTwo = NULL;
			//Debugging and Bud Fixing
			SDL_RenderCopy(Renderer, XposTexture, NULL, &XposRect);
			SDL_RenderCopy(Renderer, YposTexture, NULL, &YposRect);
			SDL_DestroyTexture(XposTexture);
			XposTexture = NULL;
			SDL_DestroyTexture(YposTexture);
			YposTexture = NULL;
			SDL_FreeSurface(XposSurface);
			XposSurface = NULL;
			SDL_FreeSurface(YposSurface);
			YposSurface = NULL;
			//LineRenderer
			if (theme == Theme::Light) {
				SDL_SetRenderDrawColor(Renderer, 46, 46, 46, 255);
				SDL_RenderDrawLine(Renderer, TextureRectangle.w + 13, TextureRectangle.y, TextureRectangle.w + 13, TextureRectangle.y + 23);
			}
			else if (theme == Theme::Dark) {
				SDL_SetRenderDrawColor(Renderer, 209, 209, 209, 255);
				SDL_RenderDrawLine(Renderer, TextureRectangle.w + 13, TextureRectangle.y, TextureRectangle.w + 13, TextureRectangle.y + 23);
			}
			SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 255);
			SDL_RenderPresent(Renderer);
			SDL_RenderClear(Renderer);
			//Speed
			if (CurrentScore < 185) CurrentSpeed = SnakeBodySegments[0].h;
			else CurrentSpeed = (185 / 6);
			if (CurrentSpeed == 0) {
				CurrentSpeed = 1;
			}
			for (int i = CurrentScore; i > 0; i--) {
				if (Coliding(&SnakeBodySegments[i], &RectangleTwo) && i > 0) {
					RenderApple = false;
					RectangleTwo.x = rand() % ScreenWidth;
					RectangleTwo.y = rand() % ScreenHeight;
					RenderApple = true;
				}
				if (MovingDirection == MovingDir::U) {
					SnakeBodySegments[i].x = SnakeBodySegments[i - 1].x;
					SnakeBodySegments[i].y = SnakeBodySegments[i - 1].y;

				}
				if (MovingDirection == MovingDir::D) {
					SnakeBodySegments[i].x = SnakeBodySegments[i - 1].x;
					SnakeBodySegments[i].y = SnakeBodySegments[i - 1].y;
				}
				if (MovingDirection == MovingDir::R) {
					SnakeBodySegments[i].y = SnakeBodySegments[i - 1].y;
					SnakeBodySegments[i].x = SnakeBodySegments[i - 1].x;

				}
				if (MovingDirection == MovingDir::L) {
					SnakeBodySegments[i].y = SnakeBodySegments[i - 1].y;
					SnakeBodySegments[i].x = SnakeBodySegments[i - 1].x;
				}
				if (SDL_IntersectRect(&SnakeBodySegments[0], &SnakeBodySegments[i - 1], &Intersection)) {
					for (int i = 4; i < CurrentScore; i++) {
						if (SDL_IntersectRect(&SnakeBodySegments[0], &SnakeBodySegments[i - 1], &Intersection)) {
							HasDied = true;
							break;
						}
					}
				}
			}
			if (!HasDied) {
				if (MovementDirection == Direction::Up && MovingDirection != MovingDir::D) {
					MovingDirection = MovingDir::U;
					SDL_Delay(MovemntDelay);
					SnakeBodySegments[0].y -= CurrentSpeed;
				}
				if (MovementDirection == Direction::Down && MovingDirection != MovingDir::U) {
					MovingDirection = MovingDir::D;
					SDL_Delay(MovemntDelay);
					SnakeBodySegments[0].y += CurrentSpeed;
				}
				if (MovementDirection == Direction::Left && MovingDirection != MovingDir::R) {
					MovingDirection = MovingDir::L;
					SDL_Delay(MovemntDelay);
					SnakeBodySegments[0].x -= CurrentSpeed;
				}
				if (MovementDirection == Direction::Right && MovingDirection != MovingDir::L) {
					MovingDirection = MovingDir::R;

					SDL_Delay(MovemntDelay);
					SnakeBodySegments[0].x += CurrentSpeed;
				}
				
			}
		}
		//Freeing Memory
		SDL_DestroyWindow(GameWindow);
		GameWindow = NULL;
		SDL_DestroyRenderer(Renderer);
		Renderer = NULL;
		SDL_DestroyTexture(GameOverTexture);
		GameOverTexture = NULL;
		SDL_FreeSurface(GameOverSurface);
		GameOverSurface = NULL;
		SDL_DestroyTexture(RetryTexture);
		RetryTexture = NULL;
		SDL_FreeSurface(Retry);
		Retry = NULL;
		TTF_Quit();
		SDL_Quit();
	}
	return 0;
}











