#include <allegro5/allegro5.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

class AudioManager
{

  //Declare variables and create 1 audio initialization and 1 audio deinitializaiton
  // & functions
  public:
    ALLEGRO_SAMPLE *sample_shot;
    ALLEGRO_SAMPLE *sample_explode[2];
    void Audio_Init();
    void Audio_Deinit();

};

void AudioManager::Audio_Init()
{

  al_install_audio();
  al_init_acodec_addon();
  al_reserve_samples(128);

  sample_shot = al_load_sample("/sound-effects/shot.flac");

  sample_explode[0] = al_load_sample("/sound-effects/explode1.flac");

  sample_explode[1] = al_load_sample("/sound-effects/explode2.flac");

}

void AudioManager::Audio_Deinit()
{
  al_destroy_sample(sample_shot);
  al_destroy_sample(sample_explode[0]);
  al_destroy_sample(sample_explode[1]);
}
