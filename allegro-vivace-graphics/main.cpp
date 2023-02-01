#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

int main(int argc, char **argv)
{
  al_init(); //Initialize Allegro Essentials
  al_install_keyboard(); //Enable keyboard buttons for the game
  al_init_image_addon(); //Initialize image addon
  al_init_primitives_addon(); //Initialize primitives addon

  ALLEGRO_TIMER *timer = al_create_timer(1.0/30.0); //Create a timer to handle the game's speed. This sets a 30 frame max
  ALLEGRO_DISPLAY *disp = al_create_display(640, 480);
  ALLEGRO_FONT *font = al_create_builtin_font();
  ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
  ALLEGRO_BITMAP *mysha = al_load_bitmap("/Users/chrisd/Desktop/intro-to-allegro/allegro-vivace-graphics/mysha.png");

  ALLEGRO_VERTEX v[] = 
  {
    { .x = 210, .y = 320, .z = 0, .color = al_map_rgb_f(1, 0, 0) },
    { .x = 330, .y = 320, .z = 0, .color = al_map_rgb_f(0, 1, 0) },
    { .x = 210, .y = 420, .z = 0, .color = al_map_rgb_f(0, 0, 1) },
    { .x = 330, .y = 420, .z = 0, .color = al_map_rgb_f(1, 1, 0) },
  };
  
  //Enumerate bouncer types
  enum BOUNCER_TYPE
  {
    BT_HELLO = 0,
    BT_MYSHA,
    BT_TRIANGLE,
    BT_RECTANGLE_1,
    BT_RECTANGLE_2,
    BT_CIRCLE,
    BT_LINE1,
    BT_LINE2,
    BT_N
  };

  //Create a bounce struct
  typedef struct BOUNCER
  {
    float x, y;
    float dx, dy;
    int type;
  }BOUNCER;

  //This is not needed but it is a good practice to make sure the declarations work properly!
  //If an error is spotted, the application should quit!
  try {
    if (!al_init())
    {
      std::cout << "Failed to initialize Allegro!\n";
      throw 1;
    }
    else if(!al_install_keyboard())
    {
      std::cout << "Failed to initialize keyboard!\n"; 
      throw 2;
    }
    else if (!timer)
    {
      std::cout << "Failed to initialize timer!\n";
      throw 3;
    }
    else if (!disp)
    {
      std::cout << "Failed to initialize display!\n";
      throw 4;
    }
    else if(!queue)
    {
      std::cout << "Failed to initialize queue!\n";
      throw 5;
    }
    if (!mysha)
    {
      std::cout << "Failed to find mysha's picture!\n";
      throw 6;
    }
  }
  catch (int errorNumber) {
    std::cout << "Error: " << errorNumber << "!\n";
    return errorNumber;
  }

  //Create as many structs as the enumerator has and Enumerate through thm and apply the attributes of the struct
  //The first attributes that are applied are completely random.
  BOUNCER obj[BT_N];
  for(int i = 0; i < BT_N; i++)
  {
    BOUNCER* b = &obj[i];
    b->x = rand() % 640;
    b->y = rand() % 480;
    b->dx = ((((float)rand()) / RAND_MAX) - 0.5) * 2 * 4;
    b->dy = ((((float)rand()) / RAND_MAX) - 0.5) * 2 * 4;
    b->type = i;
  }

  //REGISTER EVENTS TO THE EVENT QUEUE TO ENABLE KEYBOARD INPUT DETECTION, DISPLAY CREATION AND TIMER COUNTER
  al_register_event_source(queue, al_get_keyboard_event_source());
  al_register_event_source(queue, al_get_display_event_source(disp));
  al_register_event_source(queue, al_get_timer_event_source(timer));

  bool done = false, redraw = true; //These booleans are used to check if it is the time to redraw the screen or to quit the app
  ALLEGRO_EVENT event; //Return the events that are happening
  al_start_timer(timer);

  //Main game loop! The loop runs as long as the game is running
  while(1)
  {
    al_wait_for_event(queue, &event);

    //Check the type of the event and run a code block accordingly to case
    //every 1/30th of a second (once per frame) sets the redraw boolean to true which lets 
    //the program move to the next frame
    //When the player presses a button, it sets the done boolean to true.
    switch (event.type)
    {
      case ALLEGRO_EVENT_TIMER:
        //Iterate through the total amount of objects
        //and each time change the x and y value by the value of the velocity
        for(int i = 0; i < BT_N; i++)
        {
          BOUNCER* b = &obj[i];
           b->x += b->dx;
           b->y += b->dy;

           if(b->x < 0)
           {
             b->x  *= -1;
             b->dx *= -1;
           }
           if(b->x > 640)
           {
             b->x -= (b->x - 640);
             b->dx *= -1;
           }
           if(b->y < 0)
           {
             b->y  *= -1;
             b->dy *= -1;
           }
           if(b->y > 480)
           {
             b->x -= (b->y - 480);
             b->dy *= -1;
           }
        }

        redraw = true;
        break;

      case ALLEGRO_EVENT_KEY_DOWN:
        done = true;
        break;
      case ALLEGRO_EVENT_DISPLAY_CLOSE:
        done = true;
        break;
    }
    
    //If the player presses a button, then the switch case sets the done boolean to true which
    // makes use of the code in the following conditional statement. The code breaks the game loop
    // and closes the app.

    if (done)
    {
      break;
    }

    //If the redraw is set to true and the event queue is empty, 
    //clear the display to the black color, draw the text "Hello World!"
    //draw the image to the screen
    //display the result to the display and set the redraw boolean to false!
    //apply display and bitmaps options and flags
    if (redraw && al_is_event_queue_empty(queue))
    {
      ALLEGRO_VERTEX v[4];
      al_clear_to_color(al_map_rgb(0, 0, 0));
      
      //Itereate through the struct
      //Since the type i refers to the index of the enumerater that is in the same place as the type's number
      //Then, 
      for(int i = 0; i < BT_N; i++)
      {
        BOUNCER* b = &obj[i];
        switch(b->type)
        {
          case BT_HELLO:
            al_draw_text(font, al_map_rgb(255, 255, 255), b->x, b->y, 0, "Hello world!");
            break;

          case BT_MYSHA:
            al_draw_bitmap(mysha, b->x, b->y, 0);
            break;

          case BT_TRIANGLE:
            al_draw_filled_triangle(b->x, b->y, b->x + 50, b->y + 25, b->x, b->y + 50, al_map_rgb_f(0, 1, 0));
            break;

          case BT_RECTANGLE_1:
             al_draw_filled_rectangle(b->x, b->y, b->x + 100, b->y + 80, al_map_rgba_f(0, 0, 0.5, 0.5));
             break;

          case BT_RECTANGLE_2:
             v[0].x = b->x;       v[0].y = b->y;       v[0].z = 0; v[0].color = al_map_rgb_f(1, 0, 0);
             v[1].x = b->x + 120; v[1].y = b->y;       v[1].z = 0; v[1].color = al_map_rgb_f(0, 1, 0);
             v[2].x = b->x;       v[2].y = b->y + 100; v[2].z = 0; v[2].color = al_map_rgb_f(0, 0, 1);
             v[3].x = b->x + 120; v[3].y = b->y + 100; v[3].z = 0; v[3].color = al_map_rgb_f(1, 1, 0);
             al_draw_prim(v, NULL, NULL, 0, 4, ALLEGRO_PRIM_TRIANGLE_STRIP);
              break;

          case BT_CIRCLE:
              al_draw_circle(b->x, b->y, 30, al_map_rgb_f(1, 0, 1), 2);
              break;

          case BT_LINE1:
            al_draw_line(b->x, b->y, b->x + 20, b->y + 100, al_map_rgb_f(1, 0, 0), 1);
            break;

          case BT_LINE2:
            al_draw_line(b->x, b->y, b->x + 70, b->y - 20, al_map_rgb_f(1, 1, 0), 1);
            break;
        }
      }
      al_flip_display();
      redraw = false;
    }

  }

  //Destroy objects when the app is closed
  al_destroy_bitmap(mysha);
  al_destroy_font(font);
  al_destroy_display(disp);
  al_destroy_timer(timer);
  al_destroy_event_queue(queue);

  return 0;
  
}

