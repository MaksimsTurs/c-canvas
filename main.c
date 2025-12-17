#include "./include/ccanvas.h"

// clang -Wall -Wextra -O2 main.c ccanvas.c -o main

#define CANVAS_WIDTH  900
#define CANVAS_HEIGHT 900

static unsigned int pixels[CANVAS_WIDTH * CANVAS_HEIGHT] = {0};

static void save_to_ppm(t_canvas* canvas, const char* path)
{
  FILE* file = fopen(path, "wb+");

  fprintf_s(file, "P6\n%d %d\n%d\n", canvas->width, canvas->height, 255);

  for(int index = 0; index < canvas->width * canvas->height; index++)
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

  t_rect rect = { .x = CANVAS_WIDTH / 4, .y = CANVAS_HEIGHT / 4, .w = CANVAS_HEIGHT / 2, .h = CANVAS_HEIGHT / 2 };
  fill_rect(&canvas, &rect, (t_color){ 255, 0, 0 });

  t_rect arc = { .x = CANVAS_WIDTH / 4, .y = CANVAS_HEIGHT / 4, .w = CANVAS_HEIGHT / 2, .h = CANVAS_HEIGHT / 2 };
  fill_arc(&canvas, &arc, (t_color){ 0, 255, 0 }, 50);

  t_point _start = { 0, 0 };
  t_point _end = { CANVAS_WIDTH, CANVAS_HEIGHT };
  fill_line(&canvas, &_start, &_end, (t_color){ 0, 0, 255 }, 1);

  save_to_ppm(&canvas, "./test.ppm");

  return 0;
}
