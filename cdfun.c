typedef struct 
{
  size_t width;
  size_t height;
  size_t x_axis_posi;
  size_t y_axis_posi;
} canvas;

typedef uint32_t color;

int save_to_ppm(char *file_path, uint32_t* pixels, size_t width, size_t height)
{
  FILE *fp = fopen(file_path, "w");
  if (fp == NULL) {
    printf("Failed to open file.\n");
    return 1;
  }
  fprintf(fp, "P6\n%ld %ld\n255\n", width, height);
  // fwrite(data, sizeof(data[0]), HEIGHT*WIDTH, fp);
  for (size_t i = 0; i < width*height; ++i) {
      uint32_t pixel = pixels[i];
      uint8_t bytes[3] = {
          (pixel>>(8*0))&0xFF, // B
          (pixel>>(8*1))&0xFF, // G
          (pixel>>(8*2))&0xFF, // R
      };
      fwrite(bytes, sizeof(bytes), 1, fp);
  }
  fclose(fp);
  return 0;
}

int canvas_init(canvas ca, uint32_t* pixels, color init_color, color axis_color)
{
  for (int x = 0; x < ca.width; ++x) {
    for (int y = 0; y < ca.height; ++y) {
      if (x == ca.x_axis_posi || y == ca.y_axis_posi) {
        pixels[y*ca.width + x] = axis_color;
      } else {
        pixels[y*ca.width + x] = init_color;
      }
    }
  } 
  return 0;
}

int draw_func(canvas ca, uint32_t* pixels, int (*function)(int), color c)
{
  for (size_t x = 0; x < ca.width; ++x) {
    int x_fun = x - ca.x_axis_posi;
    int y_res = function(x_fun);
    for (size_t y = 0; y < ca.height; ++y) {
      int y_fun = -y + ca.y_axis_posi;
      if (y_fun == y_res) {
        pixels[y*ca.width + x] = c;
      }
    }  
  }
  return 0;
}
