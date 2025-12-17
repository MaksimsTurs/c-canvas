#ifndef H_CCANVAS
#define H_CCANVAS

#include <stdio.h>

typedef struct s_rect {
  int x;
  int y;
  int w;
  int h;
} t_rect;

typedef struct s_point {
  int x;
  int y;
} t_point;

typedef struct s_color {
  unsigned char r;
  unsigned char g;
  unsigned char b;
} t_color;

typedef struct s_canvas {
  unsigned int* pixels;
  int  width;
  int  height;
} t_canvas;

#define RGB(r, g, b) ((unsigned int)((r << 16) | (g << 8) | (b << 0)))

void fill_canvas(t_canvas* canvas, t_color color);
void fill_rect(t_canvas* canvas, t_rect* rect, t_color color);
void fill_arc(t_canvas* canvas, t_rect* rect, t_color color, int radius);
void fill_point(t_canvas* canvas, t_point* point, t_color color);
void fill_line(t_canvas* canvas, t_point* start, t_point* end, t_color color, int thicness);

#endif // H_CCANVAS
