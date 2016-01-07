//Biblioteki
	#include<allegro5\allegro.h>
	#include<allegro5\allegro_native_dialog.h>
	#include<allegro5\allegro_image.h>
	#include<iostream>
	#include<process.h>							//Do obslugi watkow
	#include<time.h>							//Do obslugi czasu
	#include<stdlib.h>
	#include<allegro5\allegro_audio.h>
	#include<allegro5\allegro_acodec.h>

	


	using namespace std;

//Deklaracja zmiennych bitmapowych

	ALLEGRO_DISPLAY *display;			//Okno programu
	ALLEGRO_BITMAP *mainMenu;			//Zdjecie dla menu glownego
	ALLEGRO_BITMAP *mainMenu_1;
	ALLEGRO_BITMAP *mainMenu_2;
	ALLEGRO_BITMAP *mainMenu_3;
	ALLEGRO_BITMAP *mainMenu_4;
	ALLEGRO_BITMAP *instruction;		//Zdjecie dla Wprowadzenie i Instrukcja
	ALLEGRO_BITMAP *results;			//Zdjecie dla Wyniki
	ALLEGRO_BITMAP *piano;				//Zdjecie na glowny tryb gry
	ALLEGRO_BITMAP *piano_started;		//Zdjecie po uruchomieniu stopera
	ALLEGRO_BITMAP *piano_Q;
	ALLEGRO_BITMAP *piano_W;
	ALLEGRO_BITMAP *piano_E;
	ALLEGRO_BITMAP *piano_R;
	ALLEGRO_BITMAP *piano_T;
	ALLEGRO_BITMAP *piano_Y;
	ALLEGRO_BITMAP *piano_U;
	ALLEGRO_BITMAP *piano_I;
	ALLEGRO_BITMAP *piano_O;
	ALLEGRO_BITMAP *piano_P;
	ALLEGRO_BITMAP *melody_choice_window;

//Deklaracja zmiennych dzwiekowych

	ALLEGRO_SAMPLE *sound_on_Q;
	ALLEGRO_SAMPLE *sound_on_W;
	ALLEGRO_SAMPLE *sound_on_E;
	ALLEGRO_SAMPLE *sound_on_R;
	ALLEGRO_SAMPLE *sound_on_T;
	ALLEGRO_SAMPLE *sound_on_Y;
	ALLEGRO_SAMPLE *sound_on_U;
	ALLEGRO_SAMPLE *sound_on_I;
	ALLEGRO_SAMPLE *sound_on_O;
	ALLEGRO_SAMPLE *sound_on_P;
	ALLEGRO_SAMPLE *w_murowanej_piwnicy;
	ALLEGRO_SAMPLE *panie_janie;

	ALLEGRO_EVENT_QUEUE *event_queue;				//Zdarzenie

	enum mainMenuChoices {ROZPOCZNIJ_GRE, WYNIKI, WPROWADZENIE_I_INSTRUKCJA, WYJDZ_Z_GRY};
	enum activeWindows {MENU_GLOWNE, GRA, INFORMACJA_O_WYNIKU};
	enum melodies {W_MUROWANEJ_PIWNICY, PANIE_JANIE};

	int coursorCoordinate_X;
	int coursorCoordinate_Y;
	int mainMenuChoice = NULL;					//Wybor z menu glownego
	int activeWindow = MENU_GLOWNE;				//Aktualne okno
	int mainMenuButtonCoursored = NULL;			//Przycisk nakierowany kursorem
	int stopper = 0;							//Aktualny stan stopera
	int chosen_melody;							//Wybrana melodia
	int amount_of_correct_nuts = 0;
	int index_of_user_melody_array = 0;
	int number_of_threads = 0;

	int sequence_of_W_MUROWANEJ_PIWNICY[5] = {1, 2, 3, 4, 5};
	int sequence_of_PANIE_JANIE[5] = {1, 2, 3, 4, 5};
	int user_sequence_of_melody[1000];
	
double punctation = 0;                          //Punktacja gracza
	double punctation_bonus = 1.0;

	bool leftMouseButtonClicked = false;
	bool startClicked = false;


//Funkcje watkowe
	void start_stopper(void* dummy)
	{
		number_of_threads++;

		if(number_of_threads > 1)
		{
			number_of_threads = 1;
			_endthread();
		}

		while(true)
		{
			Sleep(1000);		//Czeka 1 sekunde = 1000 milisekund
			stopper++;
			cout<<stopper<<endl;
		}
		_endthread();		//Zakoñczenie w¹tku
	}
