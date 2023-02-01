#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include "display.h"
#include "sprites.h"


//Define 
#define BUFFER_W 320
#define BUFFER_H 240

#define DISP_SCALE 3
#define DISP_W (BUFFER_W * DISP_SCALE)
#define DISP_H (BUFFER_H * DISP_SCALE)

#define KEY_SEEN 1
#define KEY_RELEASED 2
unsigned char key[ALLEGRO_KEY_MAX];

//get min - max
int between(int lo, int hi);
//check collisions
bool collide(int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2);
//Initialize keyboard
void Keyboard_Init();
//Keyboard StateMachine
void Keyboard_Update(ALLEGRO_EVENT *event);

int main(int argc, char **argv)
{
  //Objects
  Display mainDisp;
  SpriteManager spriteManager;
  //Initialize
  al_init();
  
  //Variables
  long score, frames;
  //Create Display
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


void Keyboard_Init()
{
  switch(event->type)
  {
    case ALLEGRO_EVENT_TIMER:
      for (int i = 0; i < ALLEGRO_KEY_MAX; i++)
      {
        key[i] &= KEY_SEEN;
      }
      break;

  
      key[event->keyboard.keycode] = KEY_SEEN | KEY_RELEASED;
      break;

    case ALLEGRO_EVENT_KEY_UP:
      key[event->keyboard.keycode] &= KEY_RELEASED;
      break;
  }
}

