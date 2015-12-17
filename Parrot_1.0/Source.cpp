/*		Adam Wejler
		nr albumu 150159

		Parrot 1.0
		Gra dzwiekowa oparta o mozliwosci biblioteki zewnetrznej - Allegro 5
*/

#include "Parrot_header.h"

using namespace std;
int main()
{

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
	al_install_audio();
	al_init_acodec_addon();
	
	//Wczytanie bitmap:
	mainMenu = al_load_bitmap("Obrazy/menuGlowne_0.jpg");
	instruction = al_load_bitmap("Obrazy/instrukcja.jpg");
	mainMenu_1 = al_load_bitmap("Obrazy/menuGlowne_1.jpg");
	mainMenu_2 = al_load_bitmap("Obrazy/menuGlowne_2.jpg");
	mainMenu_3 = al_load_bitmap("Obrazy/menuGlowne_3.jpg");
	mainMenu_4 = al_load_bitmap("Obrazy/menuGlowne_4.jpg");
	results = al_load_bitmap("Obrazy/wyniki.jpg");
	piano = al_load_bitmap("Obrazy/pianinoCzescGry_+.jpg");
	piano_started = al_load_bitmap("Obrazy/pianinoCzescGry_+_stop.jpg");
	piano_Q = al_load_bitmap("Obrazy/pianinoCzescGry_+Q.jpg");
	piano_W = al_load_bitmap("Obrazy/pianinoCzescGry_+W.jpg");
	piano_E = al_load_bitmap("Obrazy/pianinoCzescGry_+E.jpg");
	piano_R = al_load_bitmap("Obrazy/pianinoCzescGry_+R.jpg");
	piano_T = al_load_bitmap("Obrazy/pianinoCzescGry_+T.jpg");
	piano_Y = al_load_bitmap("Obrazy/pianinoCzescGry_+Y.jpg");
	piano_U = al_load_bitmap("Obrazy/pianinoCzescGry_+U.jpg");
	piano_I = al_load_bitmap("Obrazy/pianinoCzescGry_+I.jpg");
	piano_O = al_load_bitmap("Obrazy/pianinoCzescGry_+O.jpg");
	piano_P = al_load_bitmap("Obrazy/pianinoCzescGry_+P.jpg");
	melody_choice_window = al_load_bitmap("Obrazy/wybor_melodii.png");

	//Wczytywanie dzwiekow
	sound_on_Q = al_load_sample("Dzwieki/1.wav");
	sound_on_W = al_load_sample("Dzwieki/2.wav");
	sound_on_E = al_load_sample("Dzwieki/3.wav");
	sound_on_R = al_load_sample("Dzwieki/4.wav");
	sound_on_T = al_load_sample("Dzwieki/5.wav");
	sound_on_Y = al_load_sample("Dzwieki/6.wav");
	sound_on_U = al_load_sample("Dzwieki/7.wav");
	sound_on_I = al_load_sample("Dzwieki/8.wav");
	sound_on_O = al_load_sample("Dzwieki/9.wav");
	sound_on_P = al_load_sample("Dzwieki/10.wav");
	w_murowanej_piwnicy = al_load_sample("Dzwieki/W murowanej piwnicy.wav");
	panie_janie = al_load_sample("Dzwieki/Panie Janie.wav");

	//Rezerwacja ilosci plikow dzwiekowych
	al_reserve_samples(12);

	//Zdarzenia
	event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	
	//Akcje zaraz po wloczeniu programu
	al_draw_bitmap(mainMenu, 0, 0, NULL);
	al_flip_display();
	

	while(activeWindow == MENU_GLOWNE)
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
			al_draw_bitmap(mainMenu, 0, 0, NULL);
		}
		
		al_flip_display();
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
						break;
					}
				
					case ALLEGRO_KEY_Q:
					{
						al_stop_samples();										//Zatrzymanie dzia³ajacego dzwieku
						al_play_sample(sound_on_Q, 1.0, ALLEGRO_AUDIO_PAN_NONE, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
						break;	
					}
					case ALLEGRO_KEY_W:
					{
						al_stop_samples();
						al_play_sample(sound_on_W, 1.0, ALLEGRO_AUDIO_PAN_NONE, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
						break;	
					}
					case ALLEGRO_KEY_E:
					{
						al_stop_samples();
						al_play_sample(sound_on_E, 1.0, ALLEGRO_AUDIO_PAN_NONE, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
						break;	
					}
					case ALLEGRO_KEY_R:
					{
						al_stop_samples();
						al_play_sample(sound_on_R, 1.0, ALLEGRO_AUDIO_PAN_NONE, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
						break;	
					}
					case ALLEGRO_KEY_T:
					{
						al_stop_samples();
						al_play_sample(sound_on_T, 1.0, ALLEGRO_AUDIO_PAN_NONE, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
						break;	
					}
					case ALLEGRO_KEY_Y:
					{
						al_stop_samples();
						al_play_sample(sound_on_Y, 1.0, ALLEGRO_AUDIO_PAN_NONE, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
						break;	
					}
					case ALLEGRO_KEY_U:
					{
						al_stop_samples();
						al_play_sample(sound_on_U, 1.0, ALLEGRO_AUDIO_PAN_NONE, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
						break;	
					}
					case ALLEGRO_KEY_I:
					{
						al_stop_samples();
						al_play_sample(sound_on_I, 1.0, ALLEGRO_AUDIO_PAN_NONE, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
						break;	
					}
					case ALLEGRO_KEY_O:
					{
						al_stop_samples();
						al_play_sample(sound_on_O, 1.0, ALLEGRO_AUDIO_PAN_NONE, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
						break;	
					}
					case ALLEGRO_KEY_P:
					{
						al_stop_samples();
						al_play_sample(sound_on_P, 1.0, ALLEGRO_AUDIO_PAN_NONE, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
						break;	
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

	
	
		//=======================================================
		//AKCJE PO WYBORZE [ROZPOCZNIJ GRE]
		if(activeWindow == GRA)
		{
			al_draw_bitmap(piano, 0, 0, NULL);


			//----------WYBOR MELODII--------------------------



			al_draw_bitmap(melody_choice_window, 150, 50, NULL);
			al_flip_display();
		
			while(true)
			{
				ALLEGRO_EVENT events;
				al_wait_for_event(event_queue, &events);

				coursorCoordinate_X = events.mouse.x;
				coursorCoordinate_Y = events.mouse.y;

				if(coursorCoordinate_X>605 && coursorCoordinate_X<953 && coursorCoordinate_Y>184 && coursorCoordinate_Y<213 && (events.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) && (events.mouse.button & 1))
				{
					chosen_melody = W_MUROWANEJ_PIWNICY;
					al_play_sample(w_murowanej_piwnicy, 1.0, ALLEGRO_AUDIO_PAN_NONE, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
					break;
				}
				else if(coursorCoordinate_X>680 && coursorCoordinate_X<864 && coursorCoordinate_Y>252 && coursorCoordinate_Y<283 && (events.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) && (events.mouse.button & 1))
				{
					chosen_melody = PANIE_JANIE;
					al_play_sample(panie_janie, 1.0, ALLEGRO_AUDIO_PAN_NONE, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
					break;
				}
			}
		
			al_draw_bitmap(piano, 0, 0, NULL);
			al_flip_display();







			//-----------------------------------------------






			//Oczekiwanie na rozpoczecie pracy stopera poprzez wcisniecie przycisku START
			while(true)
			{
				ALLEGRO_EVENT events;
				al_wait_for_event(event_queue, &events);

				coursorCoordinate_X = events.mouse.x;
				coursorCoordinate_Y = events.mouse.y;

				if(coursorCoordinate_X>1367 && coursorCoordinate_X<1514 && coursorCoordinate_Y>10 && coursorCoordinate_Y<142 && (events.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) && (events.mouse.button & 1))
				{
					startClicked = true;
					stopper = 0;								//Wyzerowanie stopera
					_beginthread(start_stopper, 0, 0 );			//Rozpoczecie watku - funkcji pracy stopera
					break;
				}
			}

			while((activeWindow == GRA) && (startClicked == true))
			{
				al_draw_bitmap(piano_started, 0, 0, NULL);		//Zerowanie obrazu wciskanego klawisza
				al_flip_display();

				ALLEGRO_EVENT events;
				al_wait_for_event(event_queue, &events);			//Oczekiwanie na zdarzenia klawiatury i myszki

				coursorCoordinate_X = events.mouse.x;
				coursorCoordinate_Y = events.mouse.y;

				if(coursorCoordinate_X>1355 && coursorCoordinate_X<1537 && coursorCoordinate_Y>6 && coursorCoordinate_Y<146 && (events.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) && (events.mouse.button & 1))
				{
					startClicked = false;
					break;		//Zakonczenie dzialania klawiatury po wcisnieciu przycisku STOP	
				}
				else if(events.type == ALLEGRO_EVENT_KEY_DOWN)
				{
					switch(events.keyboard.keycode)
					{
						//Akcje dla wciskanych klawiszy
						case ALLEGRO_KEY_Q:
						{
							al_stop_samples();										//Zatrzymanie dzia³ajacego dzwieku
							al_draw_bitmap(piano_Q, 0, 0, NULL);
							al_play_sample(sound_on_Q, 1.0, ALLEGRO_AUDIO_PAN_NONE, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
						
							//Zapis granej nuty 
							user_sequence_of_melody[index_of_user_melody_array] = 1;
							index_of_user_melody_array++;
						
							break;	
						}
						case ALLEGRO_KEY_W:
						{
							al_stop_samples();
							al_draw_bitmap(piano_W, 0, 0, NULL);
							al_play_sample(sound_on_W, 1.0, ALLEGRO_AUDIO_PAN_NONE, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
						
							user_sequence_of_melody[index_of_user_melody_array] = 2;
							index_of_user_melody_array++;
						
							break;	
						}
						case ALLEGRO_KEY_E:
						{
							al_stop_samples();
							al_draw_bitmap(piano_E, 0, 0, NULL);
							al_play_sample(sound_on_E, 1.0, ALLEGRO_AUDIO_PAN_NONE, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
						
							user_sequence_of_melody[index_of_user_melody_array] = 3;
							index_of_user_melody_array++;
						
							break;	
						}
						case ALLEGRO_KEY_R:
						{
							al_stop_samples();
							al_draw_bitmap(piano_R, 0, 0, NULL);
							al_play_sample(sound_on_R, 1.0, ALLEGRO_AUDIO_PAN_NONE, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
						
							user_sequence_of_melody[index_of_user_melody_array] = 4;
							index_of_user_melody_array++;
						
							break;	
						}
						case ALLEGRO_KEY_T:
						{
							al_stop_samples();
							al_draw_bitmap(piano_T, 0, 0, NULL);
							al_play_sample(sound_on_T, 1.0, ALLEGRO_AUDIO_PAN_NONE, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
						
							user_sequence_of_melody[index_of_user_melody_array] = 5;
							index_of_user_melody_array++;
						
							break;	
						}
						case ALLEGRO_KEY_Y:
						{
							al_stop_samples();
							al_draw_bitmap(piano_Y, 0, 0, NULL);
							al_play_sample(sound_on_Y, 1.0, ALLEGRO_AUDIO_PAN_NONE, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
						
							user_sequence_of_melody[index_of_user_melody_array] = 6;
							index_of_user_melody_array++;
						
							break;	
						}
						case ALLEGRO_KEY_U:
						{
							al_stop_samples();
							al_draw_bitmap(piano_U, 0, 0, NULL);
							al_play_sample(sound_on_U, 1.0, ALLEGRO_AUDIO_PAN_NONE, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
						
							user_sequence_of_melody[index_of_user_melody_array] = 7;
							index_of_user_melody_array++;
						
							break;	
						}
						case ALLEGRO_KEY_I:
						{
							al_stop_samples();
							al_draw_bitmap(piano_I, 0, 0, NULL);
							al_play_sample(sound_on_I, 1.0, ALLEGRO_AUDIO_PAN_NONE, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
						
							user_sequence_of_melody[index_of_user_melody_array] = 8;
							index_of_user_melody_array++;
						
							break;	
						}
						case ALLEGRO_KEY_O:
						{
							al_stop_samples();
							al_draw_bitmap(piano_O, 0, 0, NULL);
							al_play_sample(sound_on_O, 1.0, ALLEGRO_AUDIO_PAN_NONE, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
						
							user_sequence_of_melody[index_of_user_melody_array] = 9;
							index_of_user_melody_array++;
						
							break;	
						}
						case ALLEGRO_KEY_P:
						{
							al_stop_samples();
							al_draw_bitmap(piano_P, 0, 0, NULL);
							al_play_sample(sound_on_P, 1.0, ALLEGRO_AUDIO_PAN_NONE, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
						
							user_sequence_of_melody[index_of_user_melody_array] = 10;
							index_of_user_melody_array++;
						
							break;	
						}
					}
					al_flip_display();
					al_rest(0.0225);							//Program zatrzymuje siê na moment aby mozna zauwazyc zmiane bitmapy
				}	
			}
			startClicked = false;
		}
		activeWindow = MENU_GLOWNE;								//Powrocenie do menu glownego
	}







	


	//Usuwanie elementow wskaznikowych bitmapowych
	al_destroy_bitmap(piano_Q);
	al_destroy_bitmap(piano_W);
	al_destroy_bitmap(piano_E);
	al_destroy_bitmap(piano_R);
	al_destroy_bitmap(piano_T);
	al_destroy_bitmap(piano_Y);
	al_destroy_bitmap(piano_U);
	al_destroy_bitmap(piano_I);
	al_destroy_bitmap(piano_O);
	al_destroy_bitmap(piano_P);
	al_destroy_display(display);
	al_destroy_bitmap(mainMenu);
	al_destroy_bitmap(mainMenu_1);
	al_destroy_bitmap(mainMenu_2);
	al_destroy_bitmap(mainMenu_3);
	al_destroy_bitmap(mainMenu_4);
	al_destroy_bitmap(piano);
	al_destroy_bitmap(piano_started);
	al_destroy_bitmap(melody_choice_window);

	//Usuwanie elementow wskaznikowych dzwiekowych
	al_destroy_sample(sound_on_Q);
	al_destroy_sample(sound_on_W);
	al_destroy_sample(sound_on_E);
	al_destroy_sample(sound_on_R);
	al_destroy_sample(sound_on_T);
	al_destroy_sample(sound_on_Y);
	al_destroy_sample(sound_on_U);
	al_destroy_sample(sound_on_I);
	al_destroy_sample(sound_on_O);
	al_destroy_sample(sound_on_P);
	al_destroy_sample(w_murowanej_piwnicy);
	al_destroy_sample(panie_janie);

	al_destroy_event_queue(event_queue);

	return 0;
}