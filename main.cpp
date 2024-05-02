#include "Atom.h"
#include <SDL2/SDL.h>
#include <iostream>
#include <memory>
#include <random>
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
    std::vector<unsigned char> canvas(WIDTH * HEIGHT, 0);
    unsigned int a, b = 0, delta;
    int mouseX, mouseY;
    std::unique_ptr<Atom> atoms[256];
    atoms[1] = std::make_unique<Atom>(POWDER, 0xFF, 0xFF, 0x00);
    atoms[2] = std::make_unique<Atom>(LIQUID, 0x00, 0x00, 0xFF);
    atoms[3] = std::make_unique<Atom>(WALL, 0x00, 0xFF, 0x00);
    unsigned char drawing = 2, temp;
    std::mt19937 mt = std::mt19937(std::random_device()());
    std::uniform_int_distribution<int> dist(0, 1);
    while (!quit) {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
            else if (e.type == SDL_MOUSEWHEEL)
            {
                drawing = (drawing + 1) % 4;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderClear(renderer);
        if (SDL_GetMouseState(&mouseX, &mouseY) & SDL_BUTTON_LEFT && mouseX >= 0 && mouseX < WIDTH && mouseY >= 0 && mouseY < HEIGHT)
        {
            canvas[mouseY * WIDTH + mouseX] = drawing;
        }

        for (int y = HEIGHT - 2; y >= 0; y--)
        {
            for (int x = 0; x < WIDTH; x++)
            {
                temp = canvas[y * WIDTH + x];
                if (temp != 0)
                {
                    if (atoms[temp]->state == POWDER)
                    {
                        if (canvas[(y + 1) * WIDTH + x] == 0)
                        {
                            canvas[(y + 1) * WIDTH + x] = temp;
                            canvas[y * WIDTH + x] = 0;
                        }
                        else if (canvas[(y + 1) * WIDTH + x - 1] == 0)
                        {
                            canvas[(y + 1) * WIDTH + x - 1] = temp;
                            canvas[y * WIDTH + x] = 0;
                        }
                        else if (canvas[(y + 1) * WIDTH + x + 1] == 0)
                        {
                            canvas[(y + 1) * WIDTH + x + 1] = temp;
                            canvas[y * WIDTH + x] = 0;
                        }
                    }
                    else if (atoms[temp]->state == LIQUID)
                    {
                        if (canvas[(y + 1) * WIDTH + x] == 0)
                        {
                            canvas[(y + 1) * WIDTH + x] = temp;
                            canvas[y * WIDTH + x] = 0;
                        }
                        else if (canvas[(y + 1) * WIDTH + x - 1] == 0)
                        {
                            canvas[(y + 1) * WIDTH + x - 1] = temp;
                            canvas[y * WIDTH + x] = 0;
                        }
                        else if (canvas[(y + 1) * WIDTH + x + 1] == 0)
                        {
                            canvas[(y + 1) * WIDTH + x + 1] = temp;
                            canvas[y * WIDTH + x] = 0;
                        }
                        else if (canvas[y * WIDTH + x - 1] == 0 && dist(mt) == 0)
                        {
                            canvas[y * WIDTH + x - 1] = temp;
                            canvas[y * WIDTH + x] = 0;
                        }
                        else if (canvas[y * WIDTH + x + 1] == 0 && dist(mt) == 1)
                        {
                            canvas[y * WIDTH + x + 1] = temp;
                            canvas[y * WIDTH + x] = 0;
                        }
                    }

                    SDL_SetRenderDrawColor(renderer, atoms[temp]->color.r, atoms[temp]->color.g, atoms[temp]->color.b, atoms[temp]->color.a);
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