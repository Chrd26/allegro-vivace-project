#include <allegro5/allegro_image.h>

#define SHIP_W 12
#define SHIP_H 13

#define SHIP_SHOT_W 2
#define SHIP_SHOT_H 9

#define LIFE_W 6
#define LIFE_H 6

const int ALIEN_W[] = {14, 13, 45};
const int ALIEN_H[] = {9, 10, 27};

#define ALIEN_BUG_W      ALIEN_W[0]
#define ALIEN_BUG_H      ALIEN_H[0]
#define ALIEN_ARROW_W    ALIEN_W[1]
#define ALIEN_ARROW_H    ALIEN_H[1]
#define ALIEN_THICCBOI_W ALIEN_W[2]
#define ALIEN_THICCBOI_H ALIEN_H[2]

#define ALIEN_SHOT_W 4
#define ALIEN_SHOT_H 4

#define EXPLOSION_FRAMES 4
#define SPARKS_FRAMES    3

typedef struct SPRITES
{
  ALLEGRO_BITMAP* _sheet;

  ALLEGRO_BITMAP* ship;
  ALLEGRO_BITMAP* ship_shot[2];
  ALLEGRO_BITMAP* life;

  ALLEGRO_BITMAP* alien[3];
  ALLEGRO_BITMAP* alien_shot;

  ALLEGRO_BITMAP* explosion[EXPLOSION_FRAMES];
  ALLEGRO_BITMAP* sparks[SPARKS_FRAMES];

  ALLEGRO_BITMAP* powerup[4];

}SPRITES;

SPRITES sprites;

//Sprite Class
class SpriteManager 
{
  public:

    ALLEGRO_BITMAP *Sprite_Grab(int x, int y, int w,int h)
    {
      ALLEGRO_BITMAP *sprite = al_create_sub_bitmap(sprites._sheet, x, y, w, h);

      return sprite;
    }
    void Sprites_Init();
    void Sprites_Deinit();

};

//Initialize Sprites
void SpriteManager::Sprites_Init()
{
  sprites._sheet = al_load_bitmap("/graphics/spritesheet.png");

  sprites.ship = Sprite_Grab(0, 0, SHIP_W, SHIP_H);

  sprites.life = Sprite_Grab(0, 14, LIFE_W, LIFE_H);

  sprites.ship_shot[0] = Sprite_Grab(13, 0, SHIP_SHOT_W, SHIP_SHOT_H);
  sprites.ship_shot[1] = Sprite_Grab(16, 0, SHIP_SHOT_W, SHIP_SHOT_H);

  sprites.alien[0] = Sprite_Grab(19, 0, ALIEN_BUG_W, ALIEN_BUG_H);
  sprites.alien[1] = Sprite_Grab(19, 10, ALIEN_ARROW_W, ALIEN_ARROW_H);
  sprites.alien[2] = Sprite_Grab(0, 21, ALIEN_THICCBOI_W, ALIEN_THICCBOI_H);

  sprites.alien_shot = Sprite_Grab(13, 10, ALIEN_SHOT_W, ALIEN_SHOT_H);

  sprites.explosion[0] = Sprite_Grab(33, 10, 9, 9);
  sprites.explosion[1] = Sprite_Grab(43, 9, 11, 11);
  sprites.explosion[2] = Sprite_Grab(46, 21, 17, 18);
  sprites.explosion[3] = Sprite_Grab(46, 40, 17, 17);

  sprites.sparks[0] = Sprite_Grab(34, 0, 10, 8);
  sprites.sparks[1] = Sprite_Grab(45, 0, 7, 8);
  sprites.sparks[2] = Sprite_Grab(54, 0, 9, 8);

  sprites.powerup[0] = Sprite_Grab(0, 49, 9, 12);
  sprites.powerup[1] = Sprite_Grab(10, 49, 9, 12);
  sprites.powerup[2] = Sprite_Grab(20, 49, 9, 12);
  sprites.powerup[3] = Sprite_Grab(30, 49, 9, 12);
}


//Destroy sprites
void SpriteManager::Sprites_Deinit()
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


