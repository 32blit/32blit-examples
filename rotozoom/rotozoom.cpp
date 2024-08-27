#include <string>
#include <cstring>
#include <memory>
#include <cstdlib>

#include "rotozoom.hpp"

using namespace blit;

uint8_t logo[16][16] = {
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 2, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 2, 0, 0, 0},
  {0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 2, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 1, 0, 0, 0, 0, 1, 0, 2, 0, 1, 0, 0, 0, 0},
  {0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0},
  {0, 0, 2, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0},
  {0, 0, 2, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0},
  {0, 0, 2, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

/* setup */
void init() {
  set_screen_mode(hires);
}

void rotozoom(uint32_t time_ms) {
  static float angle = 0.0f;

  static Pen palette[] = { Pen(0, 0, 0), Pen(255, 255, 255), Pen(0, 255, 0) };

  int32_t c = cosf(angle * pi / 180.0f) * 1024;
  int32_t s = sinf(angle * pi / 180.0f) * 1024;

  angle += 0.25f;
  angle = angle >= 360.0f ? 0.0f : angle;

  Point p;

  int16_t w = screen.bounds.w;
  int16_t h = screen.bounds.h;

  int16_t hw = w / 2;
  int16_t hh = h / 2;

  uint32_t o = 0;
  for (p.y = 0; p.y < h; p.y++) {
    for (p.x = 0; p.x < w; p.x++) {
      uint8_t u = ((((p.x - hw) * c - (p.y - hh) * s) * s) >> 20) & 0b1111;
      uint8_t v = ((((p.x - hw) * s + (p.y - hh) * c) * s) >> 20) & 0b1111;

      uint8_t pi = logo[15 - u][v];

      // slower to call the pixel routine due to extra overhead of the function
      // call and clipping
      // - screen.pen(palette[pi]);
      // - screen.pixel(p);

      // however we know our coordinates are within bounds so we can call the
      // pen blend function (pbf) directly for a big speed up!
      screen.pbf(&palette[pi], &screen, o, 1);

      o++;
    }
  }
}

int tick_count = 0;
void render(uint32_t time_ms) {
  screen.alpha = 255;
  screen.pen = Pen(0, 0, 0, 255);
  screen.clear();

  uint32_t ms_start = now();

  rotozoom(time_ms);

  uint32_t ms_end = now();

  // draw FPS meter
  screen.pen = Pen(0, 0, 0, 200);
  screen.rectangle(Rect(5, 5, 20, 16));
  screen.pen = Pen(255, 0, 0);
  std::string fms = std::to_string(ms_end - ms_start);
  screen.text(fms, minimal_font, Rect(10, 10, 10, 16));

  int block_size = 4;
  for (uint32_t i = 0; i < (ms_end - ms_start); i++) {
    screen.pen = Pen(i * 5, 255 - (i * 5), 0);
    screen.rectangle(Rect(i * (block_size + 1) + 1, screen.bounds.h - block_size - 1, block_size, block_size));
  }

}

void update(uint32_t time) {
  if ((buttons.released & DPAD_UP)) {
    set_screen_mode(lores);
  }
  else if(buttons.released & DPAD_DOWN) {
    set_screen_mode(hires);
  }
}
