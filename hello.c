#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

#include "ssd1306.h"
#include "write.h"

#define BTN_L 3
#define BTN_U 4
#define BTN_R 5
#define BTN_D 6
#define BTN_B 24
#define BTN_A 27

// speaker pwm = gpio28
void beep(uint slice_num, int frequency, int duration) {
  pwm_config cfg = pwm_get_default_config();
  pwm_set_chan_level(slice_num,PWM_CHAN_A,0);
  pwm_set_enabled(slice_num, false);

  // This calculation copied verbatim from "Simple Sound with C"
  // https://forums.raspberrypi.com/viewtopic.php?t=310320
  uint count = 125000000 * 16 / frequency;
  uint div =  count / 60000;  // to be lower than 65535*15/16 (rounding error)
  if(div < 16)
      div=16;
  cfg.div = div;
  cfg.top = count / div;

  pwm_init(slice_num, &cfg, true);
  pwm_set_chan_level(slice_num,PWM_CHAN_A,cfg.top / 2);
  pwm_set_enabled(slice_num, true);
  sleep_ms(duration);
  pwm_set_enabled(slice_num, false);
}

int main() {
  stdio_init_all();

  // init buzzer PWM = gpio 28
  gpio_set_function(28, GPIO_FUNC_PWM);
  uint slice_num = pwm_gpio_to_slice_num(28);

  // Init button
  gpio_init(BTN_A);
  gpio_set_dir(BTN_A, GPIO_IN);
  gpio_pull_up(BTN_A);

  // Play a starting melody :)
  beep(slice_num, 440, 100);
  beep(slice_num, 660, 100);

  // Show something on screen
  char buffer[72*40 / 8];
  for (int i=0; i< 72*40 / 8; i++) buffer[i] = 0; //(i % 2) * 0xFF; // on / off byte pattern
  write_string("HoiHoi\x14", buffer, 0, 0);
  write_string("Dagdag\x15", buffer, 8, 8);
  //write_char('C', buffer, 0, 0);
  display_init();
  display_set_brightness(120);
  display_write_buffer(buffer, 72*40 / 8);
  
  while(true) {
    printf("Press 'y' or keypad up if you like a beep!\n");
    for (int i=0; i<10; i++) {
      if (!gpio_get(BTN_A) || getchar_timeout_us(100 * 1000) == 'y') {
        beep(slice_num, 440, 100);
        beep(slice_num, 660, 100);
      }
    }
  }
  return 0;
}
