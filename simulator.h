#ifndef SIMULATOR_H_
#define SIMULATOR_H_

#include <SDL.h>
#include <stdint.h>
#include <stdbool.h>
#include "ugui.h"

typedef struct {
    uint32_t m_width;
    uint32_t m_height;
    uint32_t m_flags;
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    SDL_Surface* m_surface;
    UG_GUI m_gui;
} sim_t;

sim_t* simulator_init(void);
bool simulator_deinit(void);
void simulator_loop(void);

#endif // SIMULATOR_H_
