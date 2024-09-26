#include <string>
#include <cstring>
#include <memory>
#include <cstdlib>

#include "tilemap-types.hpp"
#include "assets.hpp"

using namespace blit;

static TiledMap *map;
static TiledMap *trans_map;

static Point scroll_position(0, 0);
static bool spin = false;
static bool draw_transformed = false;

static void draw_fps_meter(uint32_t elapsed_ms) {
  screen.pen = Pen(0, 0, 0);
  screen.rectangle(Rect(1, 120 - 10, 12, 9));

  screen.pen = Pen(255, 255, 255, 200);
  std::string fms = std::to_string(elapsed_ms);
  screen.text(fms, minimal_font, Rect(3, 120 - 9, 10, 16));

  int block_size = 4;
  for (unsigned i = 0; i < elapsed_ms; i++) {
    screen.pen = Pen(i * 5, 255 - (i * 5), 0);
    screen.rectangle(Rect(i * (block_size + 1) + 1 + 13, screen.bounds.h - block_size - 1, block_size, block_size));
  }
}

void init() {
  set_screen_mode(ScreenMode::lores);

  auto sprites = Surface::load(asset_platformer);

  //map = new TiledMap(asset_tilemap, sprites);
  map = new TiledMap("tilemap.bin", sprites);

  // load a transformable map, this requires the bounds to be a power of two
  // (copying tiles/transforms is the default)
  trans_map = new TiledMap(asset_tilemap_pot, sprites, /*COPY_TILES | COPY_TRANSFORMS |*/ LAYER_TRANSFORMS);

  map->get_layer("background")->repeat_mode = TileLayer::REPEAT;
}

void render(uint32_t time_ms) {
  // background
  screen.pen = Pen(39, 39, 54);
  screen.clear();

  uint32_t ms_start = now();

  auto draw_map = draw_transformed ? trans_map : map;

  if(spin) {
    // then main advantage of the transformed map is... being able to transform the map, so make it spin
    // apply an offset to the scroll position so we rotate around the centre of the screen
    draw_map->set_transform(  Mat3::translation(Vec2(scroll_position) + Vec2(screen.bounds.w / 2, screen.bounds.h / 2))
                       * Mat3::rotation(float(time_ms) / 1000)
                       * Mat3::translation(-Vec2(screen.bounds.w / 2, screen.bounds.h / 2)));
  } else {
    draw_map->set_scroll_position(scroll_position);
  }
  
  draw_map->draw();


  uint32_t ms_end = now();

  // draw FPS meter
  draw_fps_meter(ms_end - ms_start);

  // help text
  screen.pen = {255, 255, 255};
  screen.text(std::string("X: ") + (draw_transformed ? "simple" : "transformed"), minimal_font, {3, screen.bounds.h - 28});
  screen.text(std::string("Y: ") + (spin ? "stop" : "spin"), minimal_font, {3, screen.bounds.h - 18});

  // draw header
  screen.pen = {255, 255, 255};
  screen.rectangle(Rect(0, 0, 320, 14));

  screen.pen = {0, 0, 0};
  screen.text("Tilemap demo", minimal_font, Point(5, 4));
  screen.watermark();
}

void update(uint32_t time) {

  // scroll with dpad
  auto map_bounds_px = map->get_bounds() * 8;

  if((buttons & Button::DPAD_UP) && scroll_position.y > 0)
    scroll_position.y--;
  if((buttons & Button::DPAD_DOWN) && scroll_position.y < map_bounds_px.h - screen.bounds.h)
    scroll_position.y++;

  if((buttons & Button::DPAD_LEFT))// && scroll_position.x > 0)
    scroll_position.x--;
  if((buttons & Button::DPAD_RIGHT) && scroll_position.x < map_bounds_px.w - screen.bounds.w)
    scroll_position.x++;

  // toggle transformed map
  if(buttons.released & Button::X)
    draw_transformed = !draw_transformed;

  // toggle spin mode
  if(buttons.released & Button::Y)
    spin = !spin;
}
