/* Copyright 2020 yushakobo
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

 /*
   How to Customize

   $ make helix/rev3_5rows:YOUR_KEYMAP:clean
   $ cp keyboards/helix/rev3_5rows/oled_display.c keyboards/helix/rev3_5rows/keymaps/YOUR_KEYMAP

   $ edit keyboards/helix/rev3_5rows/keymaps/YOUR_KEYMAP/oled_display.c
   $ make helix/rev3_5rows:YOUR_KEYMAP
   $ make helix/rev3_5rows:YOUR_KEYMAP:flash
 */

#include QMK_KEYBOARD_H
#include <math.h>
#include <stdlib.h>

// Defines names for use in layer keycodes and the keymap
enum layer_names {
  _BASE = 0,
  _WIN,
  _SUB,
  _FUNC,
  _ADJUST
};

#ifdef OLED_DRIVER_ENABLE

void render_status(void) {

  // Render to mode icon
//   static const char os_logo[][2][3] PROGMEM  ={{{0x95,0x96,0},{0xb5,0xb6,0}},{{0x97,0x98,0},{0xb7,0xb8,0}}};
//   if (is_mac_mode()) {
//     oled_write_P(os_logo[0][0], false);
//     oled_write_P(PSTR("\n"), false);
//     oled_write_P(os_logo[0][1], false);
//   }else{
//     oled_write_P(os_logo[1][0], false);
//     oled_write_P(PSTR("\n"), false);
//     oled_write_P(os_logo[1][1], false);
//   }

//   oled_write_P(PSTR(" "), false);
//   oled_write_P(PSTR("       "), false);

  // Host Keyboard Layer Status
//   oled_write_P(PSTR("Layer: "), false);

  switch (get_highest_layer(layer_state)) {
      case _BASE:
          oled_write_P(PSTR("Mac\n"), false);
          break;
      case _WIN:
          oled_write_P(PSTR("Win\n"), false);
          break;
      case _SUB:
          oled_write_P(PSTR("Sub\n"), false);
          break;
      case _FUNC:
          oled_write_P(PSTR("Func\n"), false);
          break;
      case _ADJUST:
          oled_write_P(PSTR("Adjust\n"), false);
          break;
      default:
          // Or use the write_ln shortcut over adding '\n' to the end of your string
          oled_write_ln_P(PSTR("Undefined"), false);
          break;
  }
  //   oled_write_P(PSTR("\n"), false);

  // Host Keyboard LED Status
//   led_t led_state = host_keyboard_led_state();
//   oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
//   oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
//   oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);
}


static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
    };

    oled_write_P(qmk_logo, false);
}

static void render_rgbled_status(bool full) {
#ifdef RGBLIGHT_ENABLE
  char buf[30];
  if (RGBLIGHT_MODES > 1 && rgblight_is_enabled()) {
      if (full) {
          snprintf(buf, sizeof(buf), "LED %2d: %d,%d,%d ",
                   rgblight_get_mode(),
                   rgblight_get_hue()/RGBLIGHT_HUE_STEP,
                   rgblight_get_sat()/RGBLIGHT_SAT_STEP,
                   rgblight_get_val()/RGBLIGHT_VAL_STEP);
      } else {
          snprintf(buf, sizeof(buf), "[%2d] ", rgblight_get_mode());
      }
      oled_write(buf, false);
  }
  oled_advance_page(false);
#endif
}

static void render_time_log(void) {
    char time_log_str[24];
    uint32_t uptime_millsec = timer_read32();
    uint32_t uptime_sec = uptime_millsec / 1000;
    int seconds = (int)(uptime_sec % 60);
    int minutes = (int)(uptime_sec / 60  % 60);
    int hour = (int)(uptime_sec / 60 / 60);
    snprintf(time_log_str, sizeof(time_log_str), "%02d:%02d:%02d", hour, minutes, seconds);
    oled_write(time_log_str, false);
    oled_advance_page(false);
}

 #define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

static void draw_circle(int width, int height, uint32_t time_milsec, bool *is_on)
{
    double atime = time_milsec / 300.0;
    int ry = height / 2;
    int rx = width / 2;
    // dprintf("start circle\n");
    for (int y = -ry; y < ry; y++) {
        for (int x = -rx; x < rx; x++) {
            double dist = sqrt(x * x + y * y);
            double radius_out = (0.5 + cos(atime) / 2) * width * 0.7;
            double radius_in  = max(0, radius_out - 3);
            int    yInPx      = y + ry;
            int xInPx = x + rx;
            if (dist < radius_out && dist > radius_in && xInPx % 2 == 0 && yInPx % 2 == 0)
                is_on[yInPx * width + xInPx] = true;
        }
    }
    // dprintf("end circle\n");
}

void draw_filled_wave(int width, int height, uint32_t time_milsec, bool *is_on)
{
    double atime  = time_milsec / 200.0;
    for (int x = 0; x < width; x += 2) {
        for (int y = 0; y < height; y++) {
            int    length_max    = (0.5 + cos(atime + x * 10.0 / width) * cos(atime + x * 0.02) * cos(atime + (x + 10) * 0.02) / 2) * height;
            double atime2        = atime - 0.01;
            int    length_min    = (0.5 + cos(atime2 + x * 10.0 / width) * cos(atime2 + x * 0.02) * cos(atime2 + (x + 10) * 0.02) / 2) * height * 0.7;
            is_on[y * width + x] = (length_min < y && y < length_max) || (y < length_min && y % 3 == 0);
        }
    }
}

void draw_wave_form(int width, int height, uint32_t time_milsec, bool *is_on)
{
    double atime = time_milsec / 200.0;
    int ry = height / 2;
    int rx = width / 2;
    // dprintf("start wave\n");
    for (int y = -ry; y < ry; y += 3) {
        for (int x = -rx; x < rx; x += 2) {
            double dist = sqrt(x * x + y * y);
            double z    = cos(dist / 5 + atime) * 9;
            int yInPx  = y + ry;
            int xInPx = (int)-z + x + rx;
            // if (y + width / 2 == 30 && x + height / 2 == 30) dprintf("[%d, %d]: %d\n", x, y, yInPx);
            if (xInPx >= 0 && xInPx < width) is_on[yInPx * width + xInPx] = true;
        }
    }
    // dprintf("end wave\n");
}

int get_rand(int range) { return (int)(rand() / 32767.0 * range); }

enum snake_direction { S_RIGHT = 0, S_LEFT, S_UP, S_DOWN };
bool snake_initialized = false;
int  snake_dir         = S_RIGHT;
#    define SNAKE_LENGTH 20
int  snake_x[SNAKE_LENGTH];
int  snake_y[SNAKE_LENGTH];

void update_snake_dir(void) { snake_dir = get_rand(4); }

void init_snake(void) {
    if (snake_initialized) return;
    for (int i = 0; i < SNAKE_LENGTH; i++) {
        snake_x[i] = 15;
        snake_y[i] = 15;
    }
    update_snake_dir();
    snake_initialized = true;
}

bool check_x_line(int width)
{
    bool changed = false;
    if (snake_dir == S_RIGHT && snake_x[0] == width - 1) {
        do{
            update_snake_dir();
        } while (snake_dir == S_RIGHT);
        changed = true;
    } else if (snake_dir == S_LEFT && snake_x[0] == 0) {
        do{
            update_snake_dir();
        } while (snake_dir == S_LEFT);
        changed = true;
    }
    return changed;
}

bool check_y_line(int height)
{
    bool changed = false;
    if (snake_dir == S_UP && snake_y[0] == 0) {
        do{
            update_snake_dir();
        } while (snake_dir == S_UP);
        changed = true;
    } else if (snake_dir == S_DOWN && snake_y[0] == height - 1) {
        do{
            update_snake_dir();
        } while (snake_dir == S_DOWN);
        changed = true;
    }
    return changed;
}

void draw_snake(int width, int height, uint32_t time_milsec, bool *is_on) {
    init_snake();

    // update dir
    if (get_rand(100) < 10) update_snake_dir();
    while (true) {
        if (!check_x_line(width) && !check_y_line(height)) break;
    }

    // update pos
    int prev_x = snake_x[0];
    int prev_y = snake_y[0];
    switch (snake_dir) {
        case S_RIGHT:
            snake_x[0]++;
            break;
        case S_LEFT:
            snake_x[0]--;
            break;
        case S_UP:
            snake_y[0]--;
            break;
        case S_DOWN:
            snake_y[0]++;
            break;
    }
    for (int i = SNAKE_LENGTH - 1; i > 1; i--) {
        snake_x[i] = snake_x[i - 1];
        snake_y[i] = snake_y[i - 1];
    }
    snake_x[1] = prev_x;
    snake_y[1] = prev_y;

    // update pixels
    for (int i = 0; i < SNAKE_LENGTH; i++) {
        is_on[snake_y[i] * width + snake_x[i]] = true;
    }

    // debug dir out
    // char str[20];
    // snprintf(str, sizeof(str), "        %d", snake_dir);
    // oled_write(str, false);
}

uint32_t prev_time = 0;

static void render_animation(void) {
    int width = 32;
    int height = 32;
    bool is_on[width * height];

    uint32_t time_milsec = timer_read32();
    int default_FPS = 10;
    int FPS         = 8;
    int interval    = 1000 / FPS;

    if (time_milsec - prev_time < interval) return;
    prev_time = time_milsec;

    // reset pixels
    for (int i = 0; i < width * height; i++) {
        is_on[i] = false;
    }

    // core animations

    uint32_t animation_sec = (uint32_t)(time_milsec * ((double)default_FPS / FPS));
    switch (get_highest_layer(layer_state)) {
        case _BASE:
            draw_wave_form(width, height, animation_sec, is_on);
            break;
        case _SUB:
            draw_filled_wave(width, height, animation_sec, is_on);
            break;
        case _ADJUST:
            draw_circle(width, height, animation_sec, is_on);
            break;
        case _FUNC:
            draw_snake(width, height, animation_sec, is_on);
            break;
    }

    // update pixels
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            oled_write_pixel(x, y, is_on[y * width + x]);
        }
    }
}

void oled_task_user(void) {
    if (!is_oled_on()) return;
    if (is_keyboard_master()) {
        if(false)render_logo();
        int head_of_line = 8;
        oled_set_cursor(head_of_line, 0);
        render_status();
        oled_set_cursor(head_of_line, 1);
        render_time_log();
        render_animation();
    } else {
        render_rgbled_status(true);
        oled_write_ln_P(PSTR("shutosg.net"), false);
    }
}
#endif
