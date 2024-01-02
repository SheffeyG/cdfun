#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include "cdfun.c"

#define WIDTH 800
#define HEIGHT 400

#define INIT_COLOR 0x00000000
#define AXIS_COLOR 0x00989898

#define PPM_FILE "test.ppm"

uint32_t canvas_data[HEIGHT*WIDTH];

int target_func(int x)
{
  double y = 100*sin(((double)x/50));
  return (int)y;
}

int main() 
{
  canvas ca = { WIDTH, HEIGHT, WIDTH/2, HEIGHT/2 };
  canvas_init(ca, canvas_data, INIT_COLOR, AXIS_COLOR);
  draw_func(ca, canvas_data, target_func, 0x000000FF);
  save_to_ppm(PPM_FILE, canvas_data, WIDTH, HEIGHT);
  return 0;
}
