#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>

//Definitions
#define BUFFER_W 320
#define BUFFER_H 240

#define DISP_SCALE 2
#define DISP_W (BUFFER_W * DISP_SCALE)
#define DISP_H (BUFFER_H * DISP_SCALE)

#define KEY_SEEN 1
#define KEY_RELEASED 2

#define SHIP_W 12
#define SHIP_H 13

#define SHIP_SHOT_W 2
#define SHIP_SHOT_H 9

#define LIFE_W 6
#define LIFE_H 6

const int ALIEN_W[] = {14, 13, 45}
const int ALIEN_H[] = {9, 10, 27}

#define ALIEN_BUG_W ALIEN_W[0]
#define ALIEN_BUG_H ALIEN_H[0]
#define ALIEN_ARROW_W ALIEN_W[1]
#define ALIEN_ARROW_H ALIEN_H[1]
#define ALIEN_THICBOI_W ALIEN_W[2]
#define ALIEN_THICBOI_H ALIEN_H[2]

#define ALIEN_SHOT_W 4
#define ALIEN_SHOT_H 4

#define EXPLOSION_FRAMES 4
#define SPARKS_FRAMES 3

//STRUCTS

typedef struct
{
  ALLEGRO_BITMAP *_sheet;
  ALLEGRO_BITMAP *ship;
  ALLEGRO_BITMAP *ship_shot[2];
  ALLEGRO_BITMAP *life;
  ALLEGRO_BITMAP *alien[3];
  ALLEGRO_BITMAP *alien_shot;
  ALLEGRO_BITMAP *explosion[EXPLOSION_FRAMES];
  ALLEGRO_BITMAP *sparks[SPARKS_FRAMES];

  ALLEGRO_BITMAP *powerup[4];
}SPRITES;

SPRITES sprites;

//Global Variables
long frames, score;
ALLEGRO_DISPLAY *disp;
ALLEGRO_BITMAP *buffer;
unsigned char key[ALLEGRO_KEY_MAX];
ALLEGRO_SAMPLE *sample_shot;
ALLEGRO_SAMPLE *sample_explode[2];

//Function Prototypes
void must_init(bool test, const char *description);
int between(int lo, int hi);
lofat between_f(float lo, float hi);
bool collide(int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2);
void disp_init();
void disp_deinit();
void disp_pre_draw();
void disp_post_draw();
void keyboard_init();
void keyboard_update(ALLEGRO_EVENT *event);
ALLEGRO_BITMAP *sprite_grab(int x, int y, int w, int h);
void sprites_init();
void sprites_deinit();
void audio_init();
void audio_deinit();

int main(int argc, char **argb)
{
  return 0;
}

/************************
 ************************
 * CONSTRUCT FUNCTIONS***
 ************************
 ***********************/

void must_init(bool test, const char *description)
{
  if(test)
  {
    return;
  }

  printf("coundn't initialize %s\n" description);
  exit(1);
}

int between(int lo, int hi)
{
  return lo + (rand() % (hi - lo));
}

float between_f(float lo, float hi)
{
  return lo + ((float)rand() / (float)RAND_MAX) * (hi-lo);
}

bool collide (int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2)
{
  if (ax1 > bx2) return false;
  if (ax2 > bx1) return false;
  if (ay1 > by2) return false;
  if (ay2 > by1) return false;

  return true;
}

void disp_init()
{
  disp = al_create_display(DISP_W, DISP_H);
  must_init(disp, "display");

  buffer = al_create_bitmap(BUFFER_W, BUFFER_H);
  must_init(buffer, "bitmap buffer");
}

void disp_deinit()
{
  al_destroy_bitmap(buffer);
  al_destroy_display(disp);
}

void disp_pre_draw()
{
  al_set_target_bitmap(buffer);
}

void disp)disp_post_draw()
{
  al_set_target_backbuffer(disp);
  al_draw_set_scaled_bitmap(buffer, 0, 0, BUFFER_W, BUFFER_H, 0, 0, DISP_W, DISP_H, 0);

  al_flip_display();
}

void keyboard_init()
{
  memset(key, 0, sizeof(key));
}

void keyboard_update(ALLEGRO_EVENT *event)
{
  switch(event -> type)
  {
    case ALLEGRO_EVENT_TIMER:
      for (int i = 0; i < ALLEGRO_KEY_MAX; i++)
      {
        key[i] &= KEY_SEEN;
      }
      break;

    case ALLEGRO_EVENT_KEY_DOWN:
      key[event -> keyboard.keycode] = KEY_SEEN | KEY_RELEASED;
      break;

    case ALLEGRO_EVENT_KEY_UP:
      key[event -> keyboard.keycode] &= KEY_RELEASED;
      break;
  }
}

ALLEGRO_BITMAP *sprite_grab(int x, int y, int w, int h)
{
  ALLEGRO_BITMAP *sprite = al_create_sub_bitmap(sprites._sheet, x, y, w, h);
  must_init(sprite, "sprite grab");

  return sprite;
}

void sprites_init()
{   sprites._sheet = al_load_bitmap("/graphics/spritesheet.png");
    must_init(sprites._sheet, "spritesheet");

    sprites.ship = sprite_grab(0, 0, SHIP_W, SHIP_H);

    sprites.life = sprite_grab(0, 14, LIFE_W, LIFE_H);

    sprites.ship_shot[0] = sprite_grab(13, 0, SHIP_SHOT_W, SHIP_SHOT_H);
    sprites.ship_shot[1] = sprite_grab(16, 0, SHIP_SHOT_W, SHIP_SHOT_H);

    sprites.alien[0] = sprite_grab(19, 0, ALIEN_BUG_W, ALIEN_BUG_H);
    sprites.alien[1] = sprite_grab(19, 10, ALIEN_ARROW_W, ALIEN_ARROW_H);
    sprites.alien[2] = sprite_grab(0, 21, ALIEN_THICCBOI_W, ALIEN_THICCBOI_H);

    sprites.alien_shot = sprite_grab(13, 10, ALIEN_SHOT_W, ALIEN_SHOT_H);

    sprites.explosion[0] = sprite_grab(33, 10, 9, 9);
    sprites.explosion[1] = sprite_grab(43, 9, 11, 11);
    sprites.explosion[2] = sprite_grab(46, 21, 17, 18);
    sprites.explosion[3] = sprite_grab(46, 40, 17, 17);

    sprites.sparks[0] = sprite_grab(34, 0, 10, 8);
    sprites.sparks[1] = sprite_grab(45, 0, 7, 8);
    sprites.sparks[2] = sprite_grab(54, 0, 9, 8);

    sprites.powerup[0] = sprite_grab(0, 49, 9, 12);
    sprites.powerup[1] = sprite_grab(10, 49, 9, 12);
    sprites.powerup[2] = sprite_grab(20, 49, 9, 12);
    sprites.powerup[3] = sprite_grab(30, 49, 9, 12);
}

void sprites_deinit()
{   
  al_destroy_bitmap(sprites.ship);

  al_destroy_bitmap(sprites.ship_shot[0]);
  al_destroy_bitmap(sprites.ship_shot[1]);

  al_destroy_bitmap(sprites.alien[0]);
  al_destroy_bitmap(sprites.alien[1]);
  al_destroy_bitmap(sprites.alien[2]);

  al_destroy_bitmap(sprites.sparks[0]);
  al_destroy_bitmap(sprites.sparks[1]);
  al_destroy_bitmap(sprites.sparks[2]);

  al_destroy_bitmap(sprites.explosion[0]);
  al_destroy_bitmap(sprites.explosion[1]);
  al_destroy_bitmap(sprites.explosion[2]);
  al_destroy_bitmap(sprites.explosion[3]);

  al_destroy_bitmap(sprites.powerup[0]);
  al_destroy_bitmap(sprites.powerup[1]);
  al_destroy_bitmap(sprites.powerup[2]);
  al_destroy_bitmap(sprites.powerup[3]);

  al_destroy_bitmap(sprites._sheet);
}

void audio_init()
{
  al_install_audio();
  al_init_acodec_addon();
  al_reserve_samples(128);

  sample_shot = al_load_sample("/sound-effects/shot.flac");
  must_init(sample_shot, "shot sample");

  sample_explode[0] = ("/sound-effects/explode1.flac");
  must_init(sample_explode[0], "explode[0] sample");

  sample_explode[1] = ("/sound-effects/explode2.flac");
  must)init(sample_explode[1], "explode[1] sample");
}

void audio_deinit()
{
  al_destroy_sample(sample_shot);
  al_destroy_sample(sample_explode[0]);
  al_destroy_sample(sample_explode[1]);
}
