/*		Adam Wejler
		nr albumu 150159

		Parrot 1.0
		Gra dzwiekowa oparta o mozliwosci biblioteki zewnetrznej - Allegro 5
*/

#include<allegro5\allegro.h>
#include<allegro5\allegro_native_dialog.h>
#include<allegro5\allegro_image.h>




int main(){

	if(!al_init())
		return -1;
	
	//Stworzenie okna programu
	ALLEGRO_DISPLAY *display = al_create_display(1580, 820);
	al_set_window_title(display, "Parrot 1.0");
	al_set_window_position(display, 0, 0);
	
	if(!display)
		return -1;

	//Instalacje i inicjalizacje
	al_install_mouse();
	al_init_image_addon();

	//Menu glowne gry
	ALLEGRO_BITMAP *mainMenu = al_load_bitmap("Menu(tymczasowe).png");
	al_draw_bitmap(mainMenu, 0, 0, NULL);
	al_flip_display();

	//Timer
	ALLEGRO_TIMER *timer = al_create_timer(1/60.0);

	//Zdarzenia
	ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	al_start_timer(timer);		//-----------------------------------------------------------------------------------------START TIMERA

	int coursorCoordinate_X;
	int coursorCoordinate_Y;

	while(true)
	{
		ALLEGRO_EVENT events;
		al_wait_for_event(event_queue, &events);

		coursorCoordinate_X = events.mouse.x;
		coursorCoordinate_Y = events.mouse.y;
		
		if((events.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) && (events.mouse.button & 1))
		{
			//Zdarzenia, po wcisnieciu przyciskow z menu glownego
			if(coursorCoordinate_X>617 && coursorCoordinate_X<847 && coursorCoordinate_Y>304 && coursorCoordinate_Y<347)
			{
				//Instrukcje dla ROZPOCZNIJ GRE
				break;
			}
			else if(coursorCoordinate_X>669 && coursorCoordinate_X<782 && coursorCoordinate_Y>394 && coursorCoordinate_Y<429)
			{
				//Instrukcje dla WYNIKI
				break;
			}
			else if(coursorCoordinate_X>540 && coursorCoordinate_X<959 && coursorCoordinate_Y>484 && coursorCoordinate_Y<518)
			{
				//Instrukcje dla WPROWADZENIE_I_INSTRUKCJA
				break;
			}
			else if(coursorCoordinate_X>638 && coursorCoordinate_X<824 && coursorCoordinate_Y>577 && coursorCoordinate_Y<612)
			{
				//Instrukcje dla WYJDZ_Z_GRY
				break;
			}
		}
	}	
	










	
	//Usuwanie elementow wskaznikowych
	al_destroy_display(display);
	al_destroy_bitmap(mainMenu);
	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);

	return 0;
}

