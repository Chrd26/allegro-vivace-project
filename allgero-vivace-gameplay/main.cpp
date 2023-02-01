#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

int between(int lo, int hi);
bool collide(int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2);

int main(int argc, char **argv)
{
  long score, frames;

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
