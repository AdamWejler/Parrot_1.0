/*		Adam Wejler
		nr albumu 150159

		Parrot 1.0
		Gra dzwiekowa oparta o mozliwosci biblioteki zewnetrznej - Allegro 5
*/

#include "Parrot_header.h"

using namespace std;
int main(){

	if(!al_init())
		return -1;
	
	//Ustawienia okna programu
	display = al_create_display(1580, 820);
	al_set_window_title(display, "Parrot 1.0");
	al_set_window_position(display, 0, 0);
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_flip_display();
	
	if(!display)
	return -1;

	//Instalacje i inicjalizacje
	al_install_mouse();
	al_init_image_addon();
	al_install_keyboard();
	
	//ZMIENNE DYNAMICZNE:
	timer = al_create_timer(1/60.0);
	mainMenu = al_load_bitmap("Obrazy/menuGlowne_0.jpg");
	instruction = al_load_bitmap("Obrazy/instrukcja.jpg");
	mainMenu_1 = al_load_bitmap("Obrazy/menuGlowne_1.jpg");
	mainMenu_2 = al_load_bitmap("Obrazy/menuGlowne_2.jpg");
	mainMenu_3 = al_load_bitmap("Obrazy/menuGlowne_3.jpg");
	mainMenu_4 = al_load_bitmap("Obrazy/menuGlowne_4.jpg");
	results = al_load_bitmap("Obrazy/wyniki.jpg");
	piano = al_load_bitmap("Obrazy/pianinoCzescGry.jpg");

	//Zdarzenia
	event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());


	al_start_timer(timer);		//----------------------------------------------------------------START TIMERA
	
	//Akcje zaraz po wloczeniu programu
	while(activeWindow == MENU_GLOWNE)
	{
			al_draw_bitmap(mainMenu, 0, 0, NULL);
			al_flip_display();

			while(true)
			{
				ALLEGRO_EVENT events;
				al_wait_for_event(event_queue, &events);

				coursorCoordinate_X = events.mouse.x;
				coursorCoordinate_Y = events.mouse.y;
		

				if((events.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) && (events.mouse.button & 1))
					leftMouseButtonClicked = true;

				if(coursorCoordinate_X>235 && coursorCoordinate_X<612 && coursorCoordinate_Y>153 && coursorCoordinate_Y<208)
				{
					//Instrukcje dla nakierowania kursora na ROZPOCZNIJ GRE
					al_draw_bitmap(mainMenu_1, 0, 0, NULL);
					//Instrukcje dla klikniecia na ROZPOCZNIJ GRE
					if(leftMouseButtonClicked)
					{
						mainMenuChoice = ROZPOCZNIJ_GRE;
						activeWindow = GRA;
						break;
					}
				}
				else if(coursorCoordinate_X>313 && coursorCoordinate_X<503 && coursorCoordinate_Y>244 && coursorCoordinate_Y<298)
				{
					//Instrukcje dla nakierowania kursora na WYNIKI
					al_draw_bitmap(mainMenu_2, 0, 0, NULL);
					//Instrukcje dla klikniecia na WYNIKI
					if(leftMouseButtonClicked)
					{
						mainMenuChoice =  WYNIKI;
						break;
					}
				}
				else if(coursorCoordinate_X>93 && coursorCoordinate_X<764 && coursorCoordinate_Y>339 && coursorCoordinate_Y<397)
				{
					//Instrukcje dla nakierowania kursora na WPROWADZENIE I INSTRUKCJA
					al_draw_bitmap(mainMenu_3, 0, 0, NULL);
					//Instrukcje dla klikniecia na WPROWADZENIE I INSTRUKCJA
					if(leftMouseButtonClicked)
					{
						mainMenuChoice =  WPROWADZENIE_I_INSTRUKCJA;
						break;
					}
				}
				else if(coursorCoordinate_X>267 && coursorCoordinate_X<568 && coursorCoordinate_Y>431 && coursorCoordinate_Y<491)
				{
					//Instrukcje dla nakierowania kursora na WYJDZ Z GRY
					al_draw_bitmap(mainMenu_4, 0, 0, NULL);
					//Instrukcje dla klikniecia na WYJDZ Z GRY
					if(leftMouseButtonClicked)
					{
						activeWindow = -1;
						mainMenuChoice = WYJDZ_Z_GRY;
						break;
					}
				}
				else
				{
					leftMouseButtonClicked = false;					
				}
				
				al_flip_display();
				
							
			}

		//===============================================
	
		while(mainMenuChoice == WPROWADZENIE_I_INSTRUKCJA)
		{
			//Akcja po wybraniu WPROWADZENIE I INSTRUKCJA

			al_draw_bitmap(instruction, 0, 0, NULL);
			al_flip_display();
			ALLEGRO_EVENT events;
			al_wait_for_event(event_queue, &events);

			if(events.type == ALLEGRO_EVENT_KEY_DOWN)
			{
				switch(events.keyboard.keycode)
				{
					case ALLEGRO_KEY_ESCAPE:
					{
						//Akcja po wcisnieciu ESCAPE
						mainMenuChoice = -1;
						activeWindow = MENU_GLOWNE;
					}
				}
			}
		}

		//==============================================
		while(mainMenuChoice ==  WYNIKI)
		{
			//Akcja po wybraniu WYNIKI
			al_draw_bitmap(results, 0, 0, NULL);
			al_flip_display();
			ALLEGRO_EVENT events;
			al_wait_for_event(event_queue, &events);

			if(events.type == ALLEGRO_EVENT_KEY_DOWN)
			{
				switch(events.keyboard.keycode)
				{
					case ALLEGRO_KEY_ESCAPE:
					{
						//Akcja po wcisnieciu ESCAPE
						mainMenuChoice = -1;
						activeWindow = MENU_GLOWNE;
					}
				}
			}
		}

	}
	
	//Akcje po wyborze ROZPOCZNIJ GRE
	if(activeWindow == GRA)
	{
		al_draw_bitmap(piano, 0, 0, NULL);
		al_flip_display();
	}








	


	//Usuwanie elementow wskaznikowych
	al_destroy_display(display);
	al_destroy_bitmap(mainMenu);
	al_destroy_bitmap(mainMenu_1);
	al_destroy_bitmap(mainMenu_2);
	al_destroy_bitmap(mainMenu_3);
	al_destroy_bitmap(mainMenu_4);
	al_destroy_bitmap(piano);
	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);

	return 0;
}

