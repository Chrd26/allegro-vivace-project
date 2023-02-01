#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

int main(int argc, char **argv)
{
  al_init(); //Initialize Allegro Essentials
  al_install_keyboard(); //Enable keyboard buttons for the game

  ALLEGRO_TIMER *timer = al_create_timer(1.0/30.0); //Create a timer to handle the game's speed. This sets a 30 frame max
  ALLEGRO_DISPLAY *disp = al_create_display(640, 480);
  ALLEGRO_FONT *font = al_create_builtin_font();
  ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();

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
      std::cout << "Fauled to initialize quque!\n";
      throw 5;
    }
  }
  catch (int errorNumber) {
    std::cout << "Error: " << errorNumber << "!\n";
    return errorNumber;
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
    //display the result to the display and set the redraw boolean to false!
    if (redraw && al_is_event_queue_empty(queue))
    {
      al_clear_to_color(al_map_rgb(0, 0, 0));
      al_draw_text(font, al_map_rgb(255, 255, 255), 0, 0, 0, "Hello World!");
      al_flip_display();
      redraw = false;
    }

  }

  //Destory objects when the app is closed
  al_destroy_font(font);
  al_destroy_display(disp);
  al_destroy_timer(timer);
  al_destroy_event_queue(queue);

  return 0;
  
}

