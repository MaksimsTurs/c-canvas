#include "../include/ccanvas.h"

void fill_canvas(t_canvas* canvas, t_color color)
{
  const unsigned int length = canvas->width * canvas->height;

  for(unsigned int index = 0; index < length; index++)
  {
    canvas->pixels[index] = RGB(color.r, color.g, color.b);
  }
}

void fill_rect(t_canvas* canvas, t_rect* rect, t_color color)
{
  const unsigned int xend = rect->x + rect->w;
  const unsigned int yend = rect->y + rect->h;

  for(unsigned int x = rect->x; x < xend; x++)
  {
    for(unsigned int y = rect->y; y < yend; y++)
    {
      canvas->pixels[y * canvas->width + x] = RGB(color.r, color.g, color.b);
    }
  }
}

void fill_arc(t_canvas* canvas, t_rect* rect, t_color color, unsigned int radius)
{
  const unsigned int cx = rect->x + (rect->w / 2);
  const unsigned int cy = rect->y + (rect->h / 2);

  const unsigned int xend = rect->x + rect->w;
  const unsigned int yend = rect->y + rect->h;
  
  for(unsigned int x = rect->x; x < xend; x++)
  {
    for(unsigned int y = rect->y; y < yend; y++)
    {
      const unsigned int dx = (x - cx) * (x - cx);
      const unsigned int dy = (y - cy) * (y - cy);

      if((dx + dy) < radius)
      {
        canvas->pixels[y * canvas->width + x] = RGB(color.r, color.g, color.b);
      }
    }
  }
}

void fill_point(t_canvas* canvas, t_point* point, t_color color)
{
  if(point->y <= canvas->height || point->x <= canvas->height)
  {
    canvas->pixels[point->y * canvas->width + point->x] = RGB(color.r, color.g, color.b);
  }
}
