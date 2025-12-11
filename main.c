#include "ccanvas.h"

// clang -Wall -Wextra -O2 main.c ./src/ccanvas.c -o main

#define CANVAS_WIDTH  100
#define CANVAS_HEIGHT 100

static unsigned int pixels[CANVAS_WIDTH * CANVAS_HEIGHT] = {0};

static void save_to_ppm(t_canvas* canvas, const char* path)
{
  FILE* file = fopen(path, "wb+");

  fprintf_s(file, "P6\n%d %d\n%d\n", canvas->width, canvas->height, 255);

  for(unsigned int index = 0; index < canvas->width * canvas->height; index++)
  {
    unsigned int pixel = canvas->pixels[index];

    const unsigned char bytes[3] = {
      (pixel >> 16) & 0xff,
      (pixel >> 8) & 0xff,
      (pixel >> 0) & 0xff,
    };

    fwrite(bytes, sizeof(bytes), 1, file);
  }

  fclose(file);
}

int main(void) 
{
  t_canvas canvas = {
    .width = CANVAS_WIDTH,
    .height = CANVAS_HEIGHT,
    .pixels = pixels
  };

  fill_canvas(&canvas, (t_color){ 255, 255, 255 });

  // t_rect round_rect = { .x = 0, .y = 0, .w = 40, .h = 40 };
  // fill_round_rect(&canvas, &round_rect, (t_color){ 255, 0, 0 }, 5);

  // t_rect rect = { .x = width / 4, .y = height / 4, .w = 50, .h = 50 };
  // fill_rect(&canvas, &rect, (t_color){ 255, 0, 0 });

  // t_rect arc = { .x = width / 4, .y = height / 4, .w = 50, .h = 50 };
  // fill_arc(&canvas, &arc, (t_color){ 0, 255, 0 }, 50);

  save_to_ppm(&canvas, "./test.ppm");

  return 0;
}
