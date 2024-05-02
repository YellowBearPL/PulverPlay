#include <SDL2/SDL.h>
#include <iostream>
#include <vector>

const int WIDTH = 640;
const int HEIGHT = 480;

int main()
{
    SDL_Window *window;
    SDL_Renderer* renderer;
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        exit(1);
    }

    window = SDL_CreateWindow("PulverPlay", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr)
    {
        std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        exit(2);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr)
    {
        std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
    }

    SDL_Event e;
    bool quit = false;
    std::vector<unsigned char> atoms(WIDTH * HEIGHT, 0);
    unsigned int a, b = 0, delta;
    int mouseX, mouseY;
    while (!quit) {
        if (SDL_PollEvent(&e) && e.type == SDL_QUIT)
        {
            quit = true;
        }

        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0x00, 0xFF);
        if (SDL_GetMouseState(&mouseX, &mouseY) & SDL_BUTTON_LEFT && mouseX >= 0 && mouseX < WIDTH && mouseY >= 0 && mouseY < HEIGHT)
        {
            atoms[mouseY * WIDTH + mouseX] = 1;
        }

        for (int y = HEIGHT - 2; y >= 0; y--)
        {
            for (int x = 0; x < WIDTH; x++)
            {
                if (atoms[y * WIDTH + x] == 1)
                {
                    if (atoms[(y + 1) * WIDTH + x] == 0)
                    {
                        atoms[(y + 1) * WIDTH + x] = 1;
                        atoms[y * WIDTH + x] = 0;
                    }
                    else if (atoms[(y + 1) * WIDTH + x - 1] == 0)
                    {
                        atoms[(y + 1) * WIDTH + x - 1] = 1;
                        atoms[y * WIDTH + x] = 0;
                    }
                    else if (atoms[(y + 1) * WIDTH + x + 1] == 0)
                    {
                        atoms[(y + 1) * WIDTH + x + 1] = 1;
                        atoms[y * WIDTH + x] = 0;
                    }

                    SDL_RenderDrawPoint(renderer, x, y);
                }
            }
        }

        SDL_RenderPresent(renderer);
        a = SDL_GetTicks();
        delta = a - b;
        std::cout << 1000 / delta << "~ fps" << std::endl;
        b = a;
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}