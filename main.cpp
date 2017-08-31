#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "GameSystem.h"
#include "Sprite.h"
#include "GameScene.h"


int main(int argc, char* argv[])
{
	int windows_width = GameSystem::GetInstance()->GetWindowWidth();
	int windows_height = GameSystem::GetInstance()->GetWindowHeight();

	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO);
	
	SDL_Window* sdlWindow = SDL_CreateWindow("SDL Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windows_width, windows_height, SDL_WINDOW_OPENGL);
	SDL_Renderer* sdlRenderer = SDL_CreateRenderer(sdlWindow, 0,0);
	GameSystem::GetInstance()->SetRenderer(sdlRenderer);
	SDL_SetRenderDrawColor(sdlRenderer, 255, 255, 255, 255);
	
	int BPM = 120;
	int tempo = BPM / 60;
	float gametime = 50.0f;
	int trackheight = GameSystem::GetInstance()->GetWindowHeight() * gametime * tempo;
	trackheight /= 2;

	GameSystem::GetInstance()->SetGameTime(gametime); // GameTime Setting
	GameSystem::GetInstance()->SetTrackHeight(trackheight); // Track size
	GameScene* gameScene = new GameScene;
	gameScene->Init();

	int frame = 0;
	int oldFrame = 0;
	int currentTick = SDL_GetTicks();
	int oldTick = currentTick;

	SDL_Event sdlEvent;

	while (true)
	{
		currentTick = SDL_GetTicks();
		frame = (SDL_GetTicks() % 1000) * 60;
		frame /= 1000;

		if (oldFrame != frame)
		{
			int deltaTime = currentTick - oldTick;
			oldTick = currentTick;
			oldFrame = frame;
			if (SDL_PollEvent(&sdlEvent))
			{
				if (SDL_QUIT == sdlEvent.type)
					break;

				if (SDL_KEYUP == sdlEvent.type)
				{
					if (sdlEvent.key.keysym.sym == SDLK_ESCAPE)
					{
						SDL_Event quitEvent;
						quitEvent.type = SDL_QUIT;
						SDL_PushEvent(&quitEvent);
					}
					
					if (sdlEvent.key.keysym.sym == SDLK_SPACE)
					{
						gameScene->KeyUp(SDLK_SPACE);
					}

					if (sdlEvent.key.keysym.sym == SDLK_s)
					{
						gameScene->KeyUp(SDLK_s);
					}

					if (sdlEvent.key.keysym.sym == SDLK_k)
					{
						gameScene->KeyUp(SDLK_k);
					}

				}

				if (SDL_KEYDOWN == sdlEvent.type)
				{
					if (sdlEvent.key.keysym.sym == SDLK_SPACE)
					{
						gameScene->KeyDown(SDLK_SPACE);
					}

					if (sdlEvent.key.keysym.sym == SDLK_s)
					{
						gameScene->KeyDown(SDLK_s);
					}

					if (sdlEvent.key.keysym.sym == SDLK_k)
					{
						gameScene->KeyDown(SDLK_k);
					}
				}


				
			}
			
			{
				gameScene->Update(deltaTime);
			}
			
			SDL_RenderClear(sdlRenderer);
			{
				gameScene->Render();
			}
			
			SDL_RenderPresent(sdlRenderer);
		}	
	}
	
	gameScene->Deinit();

	return 0;
}