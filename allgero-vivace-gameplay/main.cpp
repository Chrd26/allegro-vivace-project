#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include "display.h"

#define BUFFER_W 320
#define BUFFER_H 240

#define DISP_SCALE 3
#define DISP_W (BUFFER_W * DISP_SCALE)
#define DISP_H (BUFFER_H * DISP_SCALE)

int between(int lo, int hi);
bool collide(int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2);

int main(int argc, char **argv)
{
  long score, frames;

  Display mainDisp;

  al_init();
  mainDisp.Disp_Init(DISP_W, DISP_H, BUFFER_W, BUFFER_H);

  while(1)
  {
  }

  mainDisp.Disp_Deinit();
  return 0;
}

int between(int lo, int hi)
{
  return lo + (rand() % (hi - lo));
}

bool collide(int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2)
{
  if (ax1 > bx2) return false;
  if (ax2 > bx1) return false;
  if (ay1 > by2) return false;
  if (ay2 < by1) return false;

  return true;
}
