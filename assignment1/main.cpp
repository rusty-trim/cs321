/***********************************
 * Name: Rusty Trim               *
 * Class: CSCI 321, Fall 2026     *
 * Assignment: Squares            *
 * Due Date: September 04, 2026   *
 * Last Modified: August 24, 2026 *
 ***********************************/
#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <cstdio>
#include <vector>

// Constants for window creation.
#define WINDOW_TITLE "Assignment 1"
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

// Print most recent SDL error to the error stream.
void print_err()
{
    fprintf(stderr, "SDL failed to initialize: %s\n", SDL_GetError());
}

int main(int argc, char **argv) 
{
    // Define variables
    // is_running: Whether the application should continue to run or quit.
    // window: Instance of the window.
    // renderer: Instance of the renderer.
    // event: Reusable variable to consume and process polled events.
    // rectangles: An array of rectangles that has no fixed limit.
    bool is_running = true;
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Event event;
    std::vector<SDL_Rect> rectangles;

    // If initializing video fails, then an error will be printed and the process will quit.
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        print_err();
        return 1;
    }

    // Create the window.
    window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);

    // If the window fails to be created, then an error will be printed and SDL will cleanup the window.
    if (window == NULL)
    {
        print_err();
        SDL_Quit();
        return 1;
    }

    // Create the renderer that acts sort of like our brush.
    renderer = SDL_CreateRenderer(window, -1, 0);

    // If the renderer is not created, then an error will be printed and SDL will cleanup the window and the renderer.
    if (renderer == NULL)
    {
        print_err();
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Game loop logic.
    while (is_running)
    {
        // Continuously poll events.
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT: {
                    // Break out of game loop when SDL says that the application should quit.
                    is_running = false;
                    break;
                }
                case SDL_MOUSEBUTTONDOWN: {
                    // Most frequent case, handle areas besides x < 50 and y < 50
                    if (event.button.x >= 50 && event.button.y >= 50)
                    {
                        // Create a rectangle and push it onto the end of the array
                        SDL_Rect rect = {event.button.x - (50 / 2), event.button.y - (50/2), 50, 50};
                        rectangles.push_back(rect);
                    }
                    else if (event.button.x < 50 && event.button.y < 50)
                    {
                        // Break out of the game loop
                        is_running = false;
                    }
                    break;
                }
            }
        }

        // Set the draw color of the renderer to white.
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        // Clear the whole window content with color that we are drawing with.
        SDL_RenderClear(renderer);

        // Set the draw color of the renderer to red.
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

        // Draw each red rectangle in the array.
        for (SDL_Rect rect : rectangles)
        {
            SDL_RenderFillRect(renderer, &rect);
        }

        // Render all fillings and outlines that the renderer drew.
        SDL_RenderPresent(renderer);
    }
    
    // Cleanup the renderer when the game loop finishes.
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
