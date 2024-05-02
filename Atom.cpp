#include "Atom.h"

Atom::Atom(State state, unsigned char r, unsigned char g, unsigned char b, unsigned char a) : state(state), color(r, g, b, a) {}

Atom::Atom(State state, unsigned char r, unsigned char g, unsigned char b) : Atom(state, r, g, b, 0xFF) {}