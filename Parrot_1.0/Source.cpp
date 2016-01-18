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
	al_init_font_addon();								
	al_init_ttf_addon();
	
	//Wczytanie fontow
	font = al_load_font("Fonty/BuxtonSketch.ttf", 60, NULL);

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
	window_of_point_information = al_load_bitmap("Obrazy/okienko_komunikatu_punktacyjnego.jpg");
	write_down_your_name = al_load_bitmap("Obrazy/podaj_imie.jpg");

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
		is_score_high_enought = false;


		best_scores_list.open("najlepsze_wyniki.txt", ios::in|ios::out);			//Plik zewnetrzny do odczytu i zapisu
		best_players_list.open("najlepsi_gracze.txt", ios::in|ios::out);
		for(int i=0; i<=4; i++)														//Wczytanie wynikow z bazy wynikow
		{
			getline(best_scores_list, table_of_scores[i]);
			DIGITAL_table_of_scores[i] = atof(table_of_scores[i].c_str());			//Zamiana typu string na double
			getline(best_players_list, table_of_players[i]);
		}
		best_scores_list.close();
		best_players_list.close();


	


		punctation = 0;					//Wyzerowanie punktacji

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
			

			//Pomocnicza tablica wynikow
			char score[5][5];
			for(int i=0; i<=4; i++)
			{
				for(int j=0; j<=4; j++)
				{
					score[i][j] = NULL;
				}
			}

			int id_score = 0;
			for(int i = 0; i<=4; i++)
			{
				id_score = 0;
				while(table_of_scores[i][id_score] != NULL)
				{
					if(id_score == 4)
					{
						break;
					}
					score[i][id_score] = table_of_scores[i][id_score];
					id_score++;
				}
			}
			 
	
			//Pomocnicza tablica nazw graczy
			char names[5][20];
			for(int i=0; i<=4; i++)
			{
				for(int j=0; j<=19; j++)
				{
					names[i][j] = NULL;
				}
			}
			
			int id_name = 0;
			for(int i = 0; i<=4; i++)
			{
				id_name = 0;
				while(table_of_players[i][id_name] != NULL)
				{
					names[i][id_name] = table_of_players[i][id_name];
					id_name++;
				}
			}

			//WYPIS
			al_draw_bitmap(results, 0, 0, NULL);

			al_draw_text(font, al_map_rgb(255, 0, 0), 570, 50, ALLEGRO_ALIGN_LEFT, "NAJLEPSZE WYNIKI");
			al_draw_text(font, al_map_rgb(255, 0, 0), 520, 150, ALLEGRO_ALIGN_LEFT, "1.           |");
			al_draw_text(font, al_map_rgb(255, 0, 0), 520, 230, ALLEGRO_ALIGN_LEFT, "2.          |");
			al_draw_text(font, al_map_rgb(255, 0, 0), 520, 310, ALLEGRO_ALIGN_LEFT, "3.          |");
			al_draw_text(font, al_map_rgb(255, 0, 0), 520, 390, ALLEGRO_ALIGN_LEFT, "4.          |");
			al_draw_text(font, al_map_rgb(255, 0, 0), 520, 470, ALLEGRO_ALIGN_LEFT, "5.          |");
			
			//Wypis wynikow
			al_draw_text(font, al_map_rgb(170, 68, 63), 600, 150, ALLEGRO_ALIGN_LEFT, score[0]);
			al_draw_text(font, al_map_rgb(170, 68, 63), 600, 230, ALLEGRO_ALIGN_LEFT, score[1]);
			al_draw_text(font, al_map_rgb(170, 68, 63), 600, 310, ALLEGRO_ALIGN_LEFT, score[2]);
			al_draw_text(font, al_map_rgb(170, 68, 63), 600, 390, ALLEGRO_ALIGN_LEFT, score[3]);
			al_draw_text(font, al_map_rgb(170, 68, 63), 600, 470, ALLEGRO_ALIGN_LEFT, score[4]);

			//Wypis nazw graczy
			al_draw_text(font, al_map_rgb(170, 68, 63), 800, 150, ALLEGRO_ALIGN_LEFT, names[0]);
			al_draw_text(font, al_map_rgb(170, 68, 63), 800, 230, ALLEGRO_ALIGN_LEFT, names[1]);
			al_draw_text(font, al_map_rgb(170, 68, 63), 800, 310, ALLEGRO_ALIGN_LEFT, names[2]);
			al_draw_text(font, al_map_rgb(170, 68, 63), 800, 390, ALLEGRO_ALIGN_LEFT, names[3]);
			al_draw_text(font, al_map_rgb(170, 68, 63), 800, 470, ALLEGRO_ALIGN_LEFT, names[4]);




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
			al_stop_samples();

			//Zliczenie punktacji
			if(chosen_melody == PANIE_JANIE)
			{
				for(int n = 0; n<=31; n++)
				{
					if(sequence_of_PANIE_JANIE[n]==user_sequence_of_melody[n])
						punctation++;
					
					user_sequence_of_melody[n] = 0;					//Czyszczenie tablicy
				}
			}
			else if(chosen_melody == W_MUROWANEJ_PIWNICY)
			{
				for(int n = 0; n<=27; n++)
				{
					if(sequence_of_W_MUROWANEJ_PIWNICY[n]==user_sequence_of_melody[n])
						punctation++;

					user_sequence_of_melody[n] = 0;
				}
			}

			if(stopper <= 15)
			{
				punctation_bonus = (16-stopper)/4.0;
				if(punctation_bonus<1)
					punctation_bonus = 1;
			}

			punctation  = punctation * punctation_bonus;
			std::cout<<"Punkty: "<<punctation<<endl;

			index_of_user_melody_array = 0;

			punctation_bonus = 1;
			

			//Wyœwietlanie punktacji

			gcvt(punctation, 7, string_version_points);						//Zamiana typu double na string (7-liczbowy)
			al_draw_bitmap(window_of_point_information, 650, 250, NULL);
			al_draw_text(font, al_map_rgb(255, 0, 0), 750, 300, ALLEGRO_ALIGN_LEFT, string_version_points);
			al_flip_display();
			al_rest(2);



			//ZMIANY W TABLICY WYNIKOW
			//Wpisywanie wyniku do tablicy najlepszych punktow
			if(punctation >= DIGITAL_table_of_scores[0])
			{
				DIGITAL_table_of_scores[4] = DIGITAL_table_of_scores[3];
				DIGITAL_table_of_scores[3] = DIGITAL_table_of_scores[2];
				DIGITAL_table_of_scores[2] = DIGITAL_table_of_scores[1];
				DIGITAL_table_of_scores[1] = DIGITAL_table_of_scores[0];
				DIGITAL_table_of_scores[0] = punctation;
				is_score_high_enought = true;
			}
			else if(punctation >= DIGITAL_table_of_scores[1])
			{
				DIGITAL_table_of_scores[4] = DIGITAL_table_of_scores[3];
				DIGITAL_table_of_scores[3] = DIGITAL_table_of_scores[2];
				DIGITAL_table_of_scores[2] = DIGITAL_table_of_scores[1];
				DIGITAL_table_of_scores[1] = punctation;
				is_score_high_enought = true;
			}
			else if(punctation >= DIGITAL_table_of_scores[2])
			{
				DIGITAL_table_of_scores[4] = DIGITAL_table_of_scores[3];
				DIGITAL_table_of_scores[3] = DIGITAL_table_of_scores[2];
				DIGITAL_table_of_scores[2] = punctation;
				is_score_high_enought = true;
			}
			else if(punctation >= DIGITAL_table_of_scores[3])
			{
				DIGITAL_table_of_scores[4] = DIGITAL_table_of_scores[3];
				DIGITAL_table_of_scores[3] = punctation;
				is_score_high_enought = true;
			}
			else if(punctation >= DIGITAL_table_of_scores[4])
			{
				DIGITAL_table_of_scores[4] = punctation;
				is_score_high_enought = true;
			}
			else
			{
				is_score_high_enought = false;
			}



			//Zamiana punktacji w typie double na typ string
			table_of_scores[4] = std::to_string(DIGITAL_table_of_scores[4]);
			table_of_scores[3] = std::to_string(DIGITAL_table_of_scores[3]);
			table_of_scores[2] = std::to_string(DIGITAL_table_of_scores[2]);
			table_of_scores[1] = std::to_string(DIGITAL_table_of_scores[1]);
			table_of_scores[0] = std::to_string(DIGITAL_table_of_scores[0]);

			//Zapis danych do pliku
			best_scores_list.open("najlepsze_wyniki.txt", ios::in|ios::out);
			for(int i = 0; i<=4; i++)
			{
				cout<<"Wynik "<<i<<"-ty = "<<table_of_scores[i]<<endl;
				best_scores_list<<table_of_scores[i]<<endl;
			}
			best_scores_list.close();


			//WPISYWANIE NAZWY GRACZA DO BAZY WYNIKOW
			letter_situation = 550;
			int userName_ind = 0;
			if(is_score_high_enought == true)
			{
				al_draw_bitmap(write_down_your_name, 400, 200, NULL);
				al_flip_display();
				userName_ind = 0;
				for(int i=0; i<=19; i++)
				{
					userName[i] = NULL;
				}
				
				while(true)
				{
					ALLEGRO_EVENT events;
					al_wait_for_event(event_queue, &events);

					coursorCoordinate_X = events.mouse.x;
					coursorCoordinate_Y = events.mouse.y;
				

					//Wpisanie nazwy
					if(userName_ind == 12)
						{break;}

					if(events.type == ALLEGRO_EVENT_KEY_DOWN)
					{
							switch(events.keyboard.keycode)
							{
								case ALLEGRO_KEY_Q:
								{
									userName[userName_ind] = 'Q';
									al_draw_text(font, al_map_rgb(255, 0, 0), letter_situation, 350, ALLEGRO_ALIGN_LEFT, "Q");
									letter_situation += letter_width;
									userName_ind++;
									break;
								}
								case ALLEGRO_KEY_W:
								{
									userName[userName_ind] = 'W';
									al_draw_text(font, al_map_rgb(255, 0, 0), letter_situation, 350, ALLEGRO_ALIGN_LEFT, "W");
									letter_situation += letter_width;
									userName_ind++;
									break;
								}
								case ALLEGRO_KEY_E:
								{
									userName[userName_ind] = 'E';
									al_draw_text(font, al_map_rgb(255, 0, 0), letter_situation, 350, ALLEGRO_ALIGN_LEFT, "E");
									letter_situation += letter_width;
									userName_ind++;
									break;
								}
								case ALLEGRO_KEY_R:
								{
									userName[userName_ind] = 'R';
									al_draw_text(font, al_map_rgb(255, 0, 0), letter_situation, 350, ALLEGRO_ALIGN_LEFT, "R");
									letter_situation += letter_width;
									userName_ind++;
									break;
								}
								case ALLEGRO_KEY_T:
								{
									userName[userName_ind] = 'T';
									al_draw_text(font, al_map_rgb(255, 0, 0), letter_situation, 350, ALLEGRO_ALIGN_LEFT, "T");
									letter_situation += letter_width;
									userName_ind++;
									break;
								}
								case ALLEGRO_KEY_Y:
								{
									userName[userName_ind] = 'Y';
									al_draw_text(font, al_map_rgb(255, 0, 0), letter_situation, 350, ALLEGRO_ALIGN_LEFT, "Y");
									letter_situation += letter_width;
									userName_ind++;
									break;
								}
								case ALLEGRO_KEY_U:
								{
									userName[userName_ind] = 'U';
									al_draw_text(font, al_map_rgb(255, 0, 0), letter_situation, 350, ALLEGRO_ALIGN_LEFT, "U");
									letter_situation += letter_width;
									userName_ind++;
									break;
								}
								case ALLEGRO_KEY_I:
								{
									userName[userName_ind] = 'I';
									al_draw_text(font, al_map_rgb(255, 0, 0), letter_situation+10, 350, ALLEGRO_ALIGN_LEFT, "I");
									letter_situation += letter_width;
									userName_ind++;
									break;
								}
								case ALLEGRO_KEY_O:
								{
									userName[userName_ind] = 'O';
									al_draw_text(font, al_map_rgb(255, 0, 0), letter_situation, 350, ALLEGRO_ALIGN_LEFT, "O");
									letter_situation += letter_width;
									userName_ind++;
									break;
								}
								case ALLEGRO_KEY_P:
								{
									userName[userName_ind] = 'P';
									al_draw_text(font, al_map_rgb(255, 0, 0), letter_situation, 350, ALLEGRO_ALIGN_LEFT, "P");
									letter_situation += letter_width;
									userName_ind++;
									break;
								}
								case ALLEGRO_KEY_A:
								{
									userName[userName_ind] = 'A';
									al_draw_text(font, al_map_rgb(255, 0, 0), letter_situation, 350, ALLEGRO_ALIGN_LEFT, "A");
									letter_situation += letter_width;
									userName_ind++;
									break;
								}
								case ALLEGRO_KEY_S:
								{
									userName[userName_ind] = 'S';
									al_draw_text(font, al_map_rgb(255, 0, 0), letter_situation, 350, ALLEGRO_ALIGN_LEFT, "S");
									letter_situation += letter_width;
									userName_ind++;
									break;
								}
								case ALLEGRO_KEY_D:
								{
									userName[userName_ind] = 'D';
									al_draw_text(font, al_map_rgb(255, 0, 0), letter_situation, 350, ALLEGRO_ALIGN_LEFT, "D");
									letter_situation += letter_width;
									userName_ind++;
									break;
								}
								case ALLEGRO_KEY_F:
								{
									userName[userName_ind] = 'F';
									al_draw_text(font, al_map_rgb(255, 0, 0), letter_situation, 350, ALLEGRO_ALIGN_LEFT, "F");
									letter_situation += letter_width;
									userName_ind++;
									break;
								}
								case ALLEGRO_KEY_G:
								{
									userName[userName_ind] = 'G';
									al_draw_text(font, al_map_rgb(255, 0, 0), letter_situation, 350, ALLEGRO_ALIGN_LEFT, "G");
									letter_situation += letter_width;
									userName_ind++;
									break;
								}
								case ALLEGRO_KEY_H:
								{
									userName[userName_ind] = 'H';
									al_draw_text(font, al_map_rgb(255, 0, 0), letter_situation, 350, ALLEGRO_ALIGN_LEFT, "H");
									letter_situation += letter_width;
									userName_ind++;
									break;
								}
								case ALLEGRO_KEY_J:
								{
									userName[userName_ind] = 'J';
									al_draw_text(font, al_map_rgb(255, 0, 0), letter_situation, 350, ALLEGRO_ALIGN_LEFT, "J");
									letter_situation += letter_width;
									userName_ind++;
									break;
								}
								case ALLEGRO_KEY_K:
								{
									userName[userName_ind] = 'K';
									al_draw_text(font, al_map_rgb(255, 0, 0), letter_situation, 350, ALLEGRO_ALIGN_LEFT, "K");
									letter_situation += letter_width;
									userName_ind++;
									break;
								}
								case ALLEGRO_KEY_L:
								{
									userName[userName_ind] = 'L';
									al_draw_text(font, al_map_rgb(255, 0, 0), letter_situation, 350, ALLEGRO_ALIGN_LEFT, "L");
									letter_situation += letter_width;
									userName_ind++;
									break;
								}
								case ALLEGRO_KEY_Z:
								{
									userName[userName_ind] = 'Z';
									al_draw_text(font, al_map_rgb(255, 0, 0), letter_situation, 350, ALLEGRO_ALIGN_LEFT, "Z");
									letter_situation += letter_width;
									userName_ind++;
									break;
								}
								case ALLEGRO_KEY_X:
								{
									userName[userName_ind] = 'X';
									al_draw_text(font, al_map_rgb(255, 0, 0), letter_situation, 350, ALLEGRO_ALIGN_LEFT, "X");
									letter_situation += letter_width;
									userName_ind++;
									break;
								}
								case ALLEGRO_KEY_C:
								{
									userName[userName_ind] = 'C';
									al_draw_text(font, al_map_rgb(255, 0, 0), letter_situation, 350, ALLEGRO_ALIGN_LEFT, "C");
									letter_situation += letter_width;
									userName_ind++;
									break;
								}
								case ALLEGRO_KEY_V:
								{
									userName[userName_ind] = 'V';
									al_draw_text(font, al_map_rgb(255, 0, 0), letter_situation, 350, ALLEGRO_ALIGN_LEFT, "V");
									letter_situation += letter_width;
									userName_ind++;
									break;
								}
								case ALLEGRO_KEY_B:
								{
									userName[userName_ind] = 'B';
									al_draw_text(font, al_map_rgb(255, 0, 0), letter_situation, 350, ALLEGRO_ALIGN_LEFT, "B");
									letter_situation += letter_width;
									userName_ind++;
									break;
								}
								case ALLEGRO_KEY_N:
								{
									userName[userName_ind] = 'N';
									al_draw_text(font, al_map_rgb(255, 0, 0), letter_situation, 350, ALLEGRO_ALIGN_LEFT, "N");
									letter_situation += letter_width;
									userName_ind++;
									break;
								}
								case ALLEGRO_KEY_M:
								{
									userName[userName_ind] = 'M';
									al_draw_text(font, al_map_rgb(255, 0, 0), letter_situation, 350, ALLEGRO_ALIGN_LEFT, "M");
									letter_situation += letter_width;
									userName_ind++;
									break;
								}
								case ALLEGRO_KEY_SPACE:
								{
									userName[userName_ind] = ' ';
									al_draw_text(font, al_map_rgb(255, 0, 0), letter_situation, 350, ALLEGRO_ALIGN_LEFT, " ");
									letter_situation += letter_width;
									userName_ind++;
									break;
								}
								case ALLEGRO_KEY_BACKSPACE:
								{
									userName_ind = 0;
									for(int i=0; i<=19; i++)
									{
										userName[i] = NULL;
									}
									letter_situation = 550;
									al_draw_bitmap(write_down_your_name, 400, 200, NULL);
									break;
								}
							
							}
						al_flip_display();
					}
					


					if(coursorCoordinate_X<880 && coursorCoordinate_X>645 && coursorCoordinate_Y<512 &&coursorCoordinate_Y>466)
					{
						if((events.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) && (events.mouse.button & 1))
						{
							break;
						}
					}
				}

				//Wpisanie imienia gracza do tablicy najlepszych wynikow
				if(punctation >= DIGITAL_table_of_scores[0])
				{
					table_of_players[4] = table_of_players[3];
					table_of_players[3] = table_of_players[2];
					table_of_players[2] = table_of_players[1];
					table_of_players[1] = table_of_players[0];
					table_of_players[0] = userName;
				}
				else if(punctation >= DIGITAL_table_of_scores[1])
				{
					table_of_players[4] = table_of_players[3];
					table_of_players[3] = table_of_players[2];
					table_of_players[2] = table_of_players[1];
					table_of_players[1] = userName;
				}
				else if(punctation >= DIGITAL_table_of_scores[2])
				{
					table_of_players[4] = table_of_players[3];
					table_of_players[3] = table_of_players[2];
					table_of_players[2] = userName;
				}
				else if(punctation >= DIGITAL_table_of_scores[3])
				{
					table_of_players[4] = table_of_players[3];
					table_of_players[3] = userName;
				}
				else if(punctation >= DIGITAL_table_of_scores[4])
				{
					table_of_players[4] =  userName;
				}





				//Zapis imienia do pliku
				best_players_list.open("najlepsi_gracze.txt", ios::in|ios::out);
				for(int i = 0; i<=4; i++)
				{
					cout<<"Gracz "<<i<<"-ty = "<<table_of_players[i]<<endl;
					best_players_list<<table_of_players[i]<<endl;
				}
				best_players_list.close();



			}












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
	al_destroy_bitmap(window_of_point_information);
	al_destroy_bitmap(write_down_your_name);

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

	//Usuwanie fontow
	al_destroy_font(font);

	al_destroy_event_queue(event_queue);

	return 0;
}