# 32blit Examples

A collection of example projects demonstrating features of the 32blit SDK.

To get started writing your own game, you should use the 32blit boilerplate - https://github.com/32blit/32blit-boilerplate/

## Contents

### Audio Test

Demonstrates the configuration of multiple synth channels and playing a multi-channel melody.

### Audio Wave

Demonstrate playing a raw, headerless, 22,050Hz wave file using 32blit's `wave_buffer_callback`.

### DOOM Fire

A demo implementation of "Doom Fire", as documented by Fabien Sanglard: http://fabiensanglard.net/doom_fire_psx/

### Fizzlefade

A demo implementation of the fizzle-fade transition, as documented by Fabien Sanglard: https://fabiensanglard.net/fizzlefade/

Uses a linear-feedback shift-register to produce random-looking values for pixel locations, making the screen "fizzle" from one colour to another, pixel-by-pixel in an apparently random order.

### Flight

An example of a flight simulator using mode7 style graphics.

### Geometry

A playable game of asteroids.

### JPEG

Shows how to decode a JPEG image and display it on the screen.

### Logo

The 32blit logo being animated on-screen as swirling particles.

### Matrix Test

Wat?

### Metadata Test

Demonstrates the reading back of ".blit" metadata in an application.

### MP3

Demonstrates playing a 22,050Hz, mono .mp3 file loaded from the SD card.

### Multiplayer

A basic demonstration of the 32blit multiplayer functionality.

If you're using 32blit handhelds you will need a microUSB to microUSB OTG cable. For example: https://www.amazon.co.uk/gp/product/B00RX1H9ZS/

### Palette Cycle

The classic palette cycling technique, combining a static sprite with a rotating set of colours in the palette in order to give the appearance of animation.

### Palette Swap

Another classic technique, recoloring sprites on the fly by swapping their palette before they are drawn.

### Particle

A demonstration of various particle effects.

### Piano

A mini sequencer.

* DPad Left/Right: Move cursor
* DPad Up/Down: Change note (and play preview)
* A: Play/Pause
* B: Mute/Unmute note 
* Y: Return to start

### Platformer

A tile-based platformer demo.

* DPad Left/Right: Move player
* DPad Up/Down: Climb ladder or swim up/down
* A: Jump

### Profiler Test

A demonstration of the 32blit profiler showing the time taken to run various drawing functions.

* DPad Left/Right: Switch page
* DPad Up/Down: Increase/decrease profiler rows
* A: Enable/disable graph
* B: Enable/disable labels
* Y: Change time base
* Home: Log to CDC

### Raycaster (Ray Caster)

A playable raycasting-based bug-zapper game.

* DPad Left/Right: Turn player
* DPad Up/Down: Walk forwards/backwards
* A: Use bug spray

### Rotozoom

A basic example of the rotozoom effect.

### Saves

A basic demo of the save/load functionality.

### Scrolly Tile (Rainbow Ascent)

A playable jumping game. Outrun the rising water.

* DPad Left/Right: Move left/right, cling to walls
* DPad Up/Down: Climb up
* A: Jump

### Serial Debug

A basic demo of serial debug.

### SHMUP

Some messy Shoot 'em Up sprites and graphics that never became a working game.

### Sprite Test

A basic demo of loading and displaying sprites at different scales.

### Text

A basic demo of text rendering showing clipping, wrapping, and alignment.

### Tilemap Test

A series of scanline-rendering effects applied to a tilemap.

* DPad Up/Down: Switch effect.

### Tilt

A tilt-sensing sand demo. Requires hardware with a tilt sensor.

### Timer Test

A basic demo of timer functionality, illustrating a timer callback.

### Tunnel

A vertical scanline rendered zooming tunnel effect.

### Tween Demo

A visual demo of various animation easing functions.

* DPad Left/Right: Select previous/next function
* A: Start/pause animation

### Tween Test

A simple demo of multiple tweening functions used on an object.

### Voxel

A complete streaming Voxel rendering engine.

* DPad Up/Down: Move forwards/backwards
* Joystick: Move
* A: Switch map

### Waveform Demo

A basic demo of the built-in audio waveforms.