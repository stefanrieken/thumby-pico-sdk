#include <string.h>

#include "ascii1.xbm"
#include "ascii2.xbm"

#define SCREEN_WIDTH_BYTES 9

// As the screen is arranged in column bytes,
// the input xbms are rotated to match.
// The math does become a bit fiddly because of this.
void write_char(int ch, unsigned char * framebuffer, int x, int y) {
  unsigned char * src = ascii1_bits;
  if (ch >= 64) { src = ascii2_bits; ch -= 64; }
  
  for (int i=0; i<8;i++) {
    unsigned char data = src[((8-(ch % 8))*64 - (i+1)*8) + (ch / 8)];
    framebuffer[(y*SCREEN_WIDTH_BYTES) +x+i] = ~data;
  }
}

void write_string(char * string, unsigned char * framebuffer, int x, int y) {
  for (int i=0; i<strlen(string);i++) write_char(string[i], framebuffer, x+(i*8), y);
}
