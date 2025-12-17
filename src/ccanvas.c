#include "../include/ccanvas.h"

void fill_canvas(t_canvas* canvas, t_color color)
{
  const int length = canvas->width * canvas->height;

  for(int index = 0; index < length; index++)
  {
    canvas->pixels[index] = RGB(color.r, color.g, color.b);
  }
}

void fill_rect(t_canvas* canvas, t_rect* rect, t_color color)
{
  int xe = rect->x + rect->w;
  int ye = rect->y + rect->h;

  xe = xe > canvas->width ? canvas->width : xe;
  ye = ye > canvas->height ? canvas->height : ye;

  for(int x = rect->x; x < xe; x++)
  {
    for(int y = rect->y; y < ye; y++)
    {
      canvas->pixels[y * canvas->width + x] = RGB(color.r, color.g, color.b);
    }
  }
}

void fill_arc(t_canvas* canvas, t_rect* rect, t_color color, int radius)
{
  const int cx = rect->x + (rect->w / 2);
  const int cy = rect->y + (rect->h / 2);

  int xe = rect->x + rect->w;
  int ye = rect->y + rect->h;

  xe = xe > canvas->width ? canvas->width : xe;
  ye = ye > canvas->height ? canvas->height : ye;
  
  for(int x = rect->x; x < xe; x++)
  {
    for(int y = rect->y; y < ye; y++)
    {
      const int dx = (x - cx) * (x - cx);
      const int dy = (y - cy) * (y - cy);

      if((dx + dy) < radius)
      {
        canvas->pixels[y * canvas->width + x] = RGB(color.r, color.g, color.b);
      }
    }
  }
}

void fill_point(t_canvas* canvas, t_point* point, t_color color)
{
  if(point->y <= canvas->height && point->x <= canvas->height)
  {
    canvas->pixels[point->y * canvas->width + point->x] = RGB(color.r, color.g, color.b);
  }
}

// TODO: Do it better
void fill_line(t_canvas* canvas, t_point* start, t_point* end, t_color color, int thicness)
{
  (void)thicness;

  int dx = (end->x - start->x);
  int dy = (end->y - start->y);

  if(dx == 0)
  {
    const int ye = end->y > canvas->height ? canvas->width : end->y;

    if(dy < 0)
    {
      for(int y = start->y; y > ye; y--)
      {
        canvas->pixels[y * canvas->width + start->x] = RGB(color.r, color.g, color.b);   
      }
    }
    else
    {
      for(int y = start->y; y < ye; y++)
      {
        canvas->pixels[y * canvas->width + start->x] = RGB(color.r, color.g, color.b);   
      }
    }
  }
  else if(dy == 0)
  {
    const int xe = end->x > canvas->width ? canvas->width : end->x;

    if(dx < 0)
    {
      for(int x = start->x; x > xe; x--)
      {
        canvas->pixels[start->y * canvas->width + x] = RGB(color.r, color.g, color.b);   
      }
    }
    else
    {
      for(int x = start->x; x < xe; x++)
      {
        canvas->pixels[start->y * canvas->width + x] = RGB(color.r, color.g, color.b);   
      }
    }
  }
  else
  {
    int m = dy / dx;
    int e = (dy > dx ? dy : dx);
    int i = 0;
    int x = 0;
    int y = 0;

    while(i < e && i < canvas->height && i < canvas->width)
    {
      int _m = m || 1;

      // Fill all pixels on y - axis when m (step) is bigger then 1.
      while(_m--)
      {
        canvas->pixels[(y + _m) * canvas->width + x] = RGB(color.r, color.g, color.b);   
      }
      
      i++;
      x++;
      y += m;
    }
  }
}