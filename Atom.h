#ifndef PULVERPLAY_ATOM_H
#define PULVERPLAY_ATOM_H
#include <SDL2/SDL.h>

enum State
{
    POWDER, LIQUID, WALL
};

class Atom
{
public:
    State state;
    SDL_Color color;

    Atom(State state, unsigned char r, unsigned char g, unsigned char b, unsigned char a);

    Atom(State state, unsigned char r, unsigned char g, unsigned char b);
};
#endif//PULVERPLAY_ATOM_H
