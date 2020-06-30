#include "simulator.h"
#include <stdio.h>

static sim_t sim;

#define SIM_WIDTH 320
#define SIM_HEIGHT 240
#define SIM_TOUCH true
// #define SIM_FPS 30

void simulator_pset(UG_S16 x, UG_S16 y, UG_COLOR c);

sim_t* simulator_init(void)
{
    sim.m_width = SIM_WIDTH;
    sim.m_height = SIM_HEIGHT;

    if (SDL_Init(sim.m_flags) != 0)
    {
        return NULL;
    }

    if (SDL_CreateWindowAndRenderer(sim.m_width, sim.m_height, SDL_WINDOW_SHOWN, &(sim.m_window), &(sim.m_renderer)) != 0)
    {
        return NULL;
    }

    sim.m_surface = SDL_GetWindowSurface(sim.m_window);

    // clear the window with black
    SDL_FillRect(sim.m_surface, NULL, SDL_MapRGB(sim.m_surface->format, 0, 0, 0));

    // set up the UGUI
    UG_Init(&sim.m_gui, simulator_pset, SIM_WIDTH, SIM_HEIGHT);
    UG_SelectGUI(&sim.m_gui);

    return &sim;
}

bool simulator_deinit(void)
{
    SDL_FreeSurface(sim.m_surface);
    SDL_DestroyWindow(sim.m_window);
    SDL_DestroyRenderer(sim.m_renderer);
    SDL_Quit();

    return true;
}

void simulator_loop(void)
{
    bool quit = false;
    int x, y;
    SDL_Event event;

    while (!quit)
    {
        // process any events
        while (SDL_PollEvent(&event) != 0)
        {
            switch (event.type)
            {
            case SDL_QUIT:
                printf("EVENT: QUIT\n");
                quit = true;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_q:
                    printf("EVENT: KEYDOWN Q\n");
                    quit = true;
                    break;
                case SDLK_ESCAPE:
                    printf("EVENT: KEYDOWN ESCAPE\n");
                    quit = true;
                    break;
                }
                break;
                #if SIM_TOUCH
                case SDL_MOUSEBUTTONDOWN:
                    SDL_GetMouseState(&x, &y);
                    printf("EVENT: TOUCH PRESS (%d, %d)\n", x, y);
                    UG_TouchUpdate(x, y, TOUCH_STATE_PRESSED);
                    break;
                case SDL_MOUSEBUTTONUP:
                    printf("EVENT: TOUCH RELEASE\n");
                    UG_TouchUpdate(-1, -1, TOUCH_STATE_RELEASED);
                    break;
                #endif
            }
        }

        // update the ugui
        UG_Update();

        // render the window
        SDL_RenderPresent(sim.m_renderer);

        // wait for a little bit
        // SDL_Delay(1000 / SIM_FPS);
    }
}

UG_RESULT _HW_DrawLine( UG_S16 x1 , UG_S16 y1 , UG_S16 x2 , UG_S16 y2 , UG_COLOR c )
{
    int res;
    uint8_t r, g, b, a = 255;
    r = c >> 16;
    g = (c >> 8) & 0xff;
    b = c & 0xff;

    SDL_SetRenderDrawColor(sim.m_renderer, r, g, b, a);
    res = SDL_RenderDrawLine(sim.m_renderer, x1, y1, x2, y2);

    if (res == 0) {
        return UG_RESULT_OK;
    } else {
        return UG_RESULT_FAIL;
    }
}

UG_RESULT _HW_FillFrame( UG_S16 x1 , UG_S16 y1 , UG_S16 x2 , UG_S16 y2 , UG_COLOR c )
{
    int res;
    uint8_t r, g, b, a = 255;
    r = c >> 16;
    g = (c >> 8) & 0xff;
    b = c & 0xff;

    SDL_SetRenderDrawColor(sim.m_renderer, r, g, b, a);
    res = SDL_RenderDrawLine(sim.m_renderer, x1, y1, x2, y2);

    if (res == 0) {
        return UG_RESULT_OK;
    } else {
        return UG_RESULT_FAIL;
    }
}

void simulator_pset(UG_S16 x, UG_S16 y, UG_COLOR c)
{
    uint8_t r, g, b, a = 255;
    r = c >> 16;
    g = (c >> 8) & 0xff;
    b = c & 0xff;

    SDL_SetRenderDrawColor(sim.m_renderer, r, g, b, a);
    SDL_RenderDrawPoint(sim.m_renderer, x, y);
}

//void SDL::draw()
//{
//    // Clear the window with a black background
//    SDL_SetRenderDrawColor( m_renderer, 0, 0, 0, 255 );
//    SDL_RenderClear( m_renderer );
//
//    // Show the window
//    SDL_RenderPresent( m_renderer );
//
//    int rgb[] = { 203, 203, 203, // Gray
//                  254, 254,  31, // Yellow
//                    0, 255, 255, // Cyan
//                    0, 254,  30, // Green
//                  255,  16, 253, // Magenta
//                  253,   3,   2, // Red
//                   18,  14, 252, // Blue
//                    0,   0,   0  // Black
//                };
//
//    SDL_Rect colorBar;
//    colorBar.x = 0; colorBar.y = 0; colorBar.w = 90; colorBar.h = 480;
//
//    // Render a new color bar every 0.5 seconds
//    for ( int i = 0; i != sizeof rgb / sizeof *rgb; i += 3, colorBar.x += 90 )
//    {
//        SDL_SetRenderDrawColor( m_renderer, rgb[i], rgb[i + 1], rgb[i + 2], 255 );
//        SDL_RenderFillRect( m_renderer, &colorBar );
//        SDL_RenderPresent( m_renderer );
//        SDL_Delay( 500 );
//    }
//}
