#include "sprites.h"
#include "sound.h"

typedef struct FX
{
  int x,y;
  int frame;
  bool spark;
  bool used;
}FX;

#define FX_N 128
FX fx[Fx_N];

class EffectsManager
{
  public:

    void fx_init();
    void fx_add(bool spark, int x, int y);
}

//Mark all fx as not used
void EffectsManager::fx_init()
{
  for (int i = 0; i < Fx_N; i++)
  {
    fx[i].used = false;
  }
}

//Spawning Effects
void EffectsManager::fx_add(bool spark, int x, int y)
  {
    AudioManager audio;
    if (!spark)
    {
    }

    for (int i = 0; i < FX_N; i++)
    {
      if(fx[i].used)
      {
        continue;
        
        fx[i].x = x;
        fx[i].y = y;
        fx[i].frame = 0;
        fx[i].spark = spark;
        fx[i].used = true;
        return;
      }
    }
  }

