#include <SDL3/SDL.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_main.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <fcntl.h>

#define WIDTH 800
#define HEIGHT 600
#define NUM_ELEMENTS 100 // 6767
#define DELAY_MS 10

typedef struct {
    int *array;
    int size;
} ArrayData;

ArrayData* loadArr(const char* filename)
{
    FILE* f = fopen(filename, "r");
    if (!f) {
        fprintf(stderr, "error opening file: %s\n", filename);
        exit(1);
    }

    int len = 0;
    int temp;

    while (fscanf(f, "%d", &temp) == 1) {
        len++;
    }

    ArrayData* arr = malloc(sizeof(ArrayData));
    if (!arr) {
        perror("malloc fail struct");
        fclose(f);
        return NULL;
    }

    arr->array = malloc(len * sizeof(int));
    if (!arr->array) {
        perror("malloc fail array");
        free(arr);
        fclose(f);
        return NULL;
    }

    arr->size = len;
    rewind(f);
    for (int i = 0; i < len - 1; i++) {
        if (fscanf(f, "%d", &arr->array[i]) != 1) {
            fprintf(stderr, "last element from file %s is %d\n", filename, i);
            arr->size = i;
            break;
        }
    }
    fclose(f);
    return arr;
}

void draw_bars(SDL_Renderer *renderer, ArrayData *data, int highlight1, int highlight2, int max_value) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    float bar_width = (float)WIDTH / data->size;
    for (int i = 0; i < data->size; i++) {
        if (i == highlight1 || i == highlight2) {
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Highlight in red
        } else {
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Green for normal
        }
        float scaled = (float)data->array[i] / max_value * HEIGHT;
        SDL_FRect rect = {i * bar_width, HEIGHT - scaled, bar_width, scaled};
        SDL_RenderFillRect(renderer, &rect);
    }

    SDL_RenderPresent(renderer);
}

typedef struct {
    int i, j;
    int sorted;
} BubState;

void initBub(BubState* state)
{
    state->i = 0;
    state->j = 0;
    state->sorted = 0;
}

int bubble_sort(SDL_Renderer *renderer, ArrayData *data, BubState* state, int max_value) {
    if (state->sorted) return 1; // Done

    if (state->j < data->size - state->i - 1) {
        if (data->array[state->j] > data->array[state->j + 1]) {
            // Swap
            int temp = data->array[state->j];
            data->array[state->j] = data->array[state->j + 1];
            data->array[state->j + 1] = temp;
        }
        draw_bars(renderer, data, state->j, state->j + 1, max_value);
        SDL_Delay(1);
        state->j++;
    } else {
        state->j = 0;
        state->i++;
        if (state->i >= data->size - 1) {
            state->sorted = 1;
        }
    }
    return 0;
}


int main(int argc, char *argv[]) {
    srand(time(NULL));

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Sorting Algorithm Visualizer", WIDTH, HEIGHT, 0);
    if (!window) {
        SDL_Log("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer) {
        SDL_Log("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    ArrayData* data = loadArr("num.txt");
    if (!data) return 1;

    int max_value = 0;
    for (int i = 0; i < data->size; i++) {
        if (data->array[i] > max_value) max_value = data->array[i];
    }
    if (max_value == 0) max_value = 1;

    draw_bars(renderer, data, -1, -1, max_value);

    BubState bs;
    initBub(&bs);

    // insertion_sort(renderer, data);

    // Wait for user to close
    SDL_Event e;
    int quit = 0;
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = 1;
            }
        }
        bubble_sort(renderer, data, &bs, max_value);
        SDL_Delay(1);
    }

    free(data->array);
    free(data);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
