#include <iostream>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>

class Display
{
  private:

    ALLEGRO_DISPLAY *disp;
    ALLEGRO_BITMAP *buffer;

  public:

    void Disp_Init(int widthDisplay, int heightDisplay, int bufferWidth, int bufferHeight);
    void Disp_Deinit();
    void Disp_PreDraw();
    void Disp_PostDraw(int bufferWidth, int bufferHeightm, int widthDisplay, int heightDisplay);


};

void Display::Disp_Init(int widthDisplay, int heightDisplay, int bufferWidth, int bufferHeight)
{
  disp = al_create_display(widthDisplay, heightDisplay);

  buffer = al_create_bitmap(bufferWidth, bufferHeight);

 try
 {
   if (!disp)
   {
     throw 1;
   }

   if (!buffer)
   {
     throw 2;
   }
 }
   catch(int error)
   {
     std::cout << error << "\n";
   }
 }


void Display::Disp_Deinit()
{
  al_destroy_bitmap(buffer);
  al_destroy_display(disp);
}

void Display::Disp_PreDraw()
{
  al_set_target_bitmap(buffer);
}

void Display::Disp_PostDraw(int bufferWidth, int bufferHeight, int widthDisplay, int heightDisplay)
{
  al_set_target_backbuffer(disp);
  al_draw_scaled_bitmap(buffer, 0, 0, bufferWidth, bufferHeight, 0, 0, widthDisplay, heightDisplay, 0);

    al_flip_display();
}

