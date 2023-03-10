#include <string>
#include <cstring>
#include <memory>
#include <cstdlib>

#include "timer-test.hpp"

/*
TODO: This example is really dry, how can we make it awesome?
Without making it so complicated that it fails to elucidate its point.
*/

using namespace blit;

blit::Timer timer_count;
uint32_t count;

void timer_count_update(blit::Timer &t){
    count++;
    // Instead of using loops we're going to stop the timer in our callback
    // In this case it will count to ten and then stop.
    // But you could depend upon any condition to stop the timer.
    if(count == 10) {
        t.stop();
    }
}

void init() {
  blit::set_screen_mode(blit::ScreenMode::hires);

  // Timers must be initialized
  // In this case we want our timer to call the `timer_count_update` function
  // very 1000ms, or 1 second. We also want it to loop indefinitely.
  // We can pass -1 to loop indefinitely, or just nothing at all since -1
  // is the default.
  timer_count.init(timer_count_update, 1000, -1);

  // Next we probably want to start our timer!
  timer_count.start();
}

int tick_count = 0;
void render(uint32_t time_ms) {
  screen.pen = Pen(20, 30, 40);
  screen.clear();

  // Fancy title bar, nothing to see here.
  screen.pen = Pen(255, 255, 255);
  screen.rectangle(Rect(0, 0, 320, 14));
  screen.pen = Pen(0, 0, 0);
  screen.text("Timer Test", minimal_font, Point(5, 4));

  // Since our timer callback is updating our `count` variable
  // we can just display it on the screen and watch it tick up!
  screen.pen = Pen(255, 255, 255);
  screen.text("Count: " + std::to_string(count), minimal_font, Point(120, 100));

  // `is_running()` is a handy shorthand for checking the timer state
  if(timer_count.is_running()) {
    screen.text("Timer running...", minimal_font, Point(120, 110));
  } else {
    screen.text("Timer stopped!", minimal_font, Point(120, 110));
    screen.text("Press A to restart.", minimal_font, Point(120, 120));
  }
}

void update(uint32_t time_ms) {
  // `is_stopped()` works too!
  if (blit::buttons & blit::Button::A && timer_count.is_stopped()) {
      count = 0;
      timer_count.start();
  }
}
