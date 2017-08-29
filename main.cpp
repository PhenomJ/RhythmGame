#include "SDL.h"
#include "SDL_image.h"
#include "GameSystem.h"
#include "Sprite.h"
#include "GameScene.h"

int main(int argc, char* argv[])
{
	int windows_width = GameSystem::GetInstance()->GetWindowWidth(1024);
	int windows_height = GameSystem::GetInstance()->GetWindowHeight(800);

	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
	
	SDL_Window* sdlWindow = SDL_CreateWindow("SDL Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windows_width, windows_height, SDL_WINDOW_OPENGL);
	SDL_Renderer* sdlRenderer = SDL_CreateRenderer(sdlWindow, 0,0);
	GameSystem::GetInstance()->SetRenderer(sdlRenderer);
	SDL_SetRenderDrawColor(sdlRenderer, 255, 255, 255, 255);
	
	int BPM = 120;
	int tempo = BPM / 60;
	float gametime = 50.0f;
	int trackheight = GameSystem::GetInstance()->GetWindowHeight(800) * gametime * tempo;
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