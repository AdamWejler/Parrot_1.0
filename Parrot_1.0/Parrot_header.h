//Biblioteki
	#include<allegro5\allegro.h>
	#include<allegro5\allegro_native_dialog.h>
	#include<allegro5\allegro_image.h>
	#include<string>

//Deklaracja zmiennych

	ALLEGRO_DISPLAY *display;			//Okno programu
	ALLEGRO_BITMAP *mainMenu;			//Zdjecie dla menu glownego
	ALLEGRO_BITMAP *mainMenu_1;
	ALLEGRO_BITMAP *mainMenu_2;
	ALLEGRO_BITMAP *mainMenu_3;
	ALLEGRO_BITMAP *mainMenu_4;
	ALLEGRO_BITMAP *instruction;		//Zdjecie dla Wprowadzenie i Instrukcja
	ALLEGRO_BITMAP *results;			//Zdjecie dla Wyniki
	ALLEGRO_BITMAP *piano;				//Zdjecie na glowny tryb gry
	ALLEGRO_TIMER *timer;				//Timer
	ALLEGRO_EVENT_QUEUE *event_queue;	//Zdarzenie

	enum mainMenuChoices {ROZPOCZNIJ_GRE, WYNIKI, WPROWADZENIE_I_INSTRUKCJA, WYJDZ_Z_GRY};
	enum activeVindows {MENU_GLOWNE, GRA, INFORMACJA_O_WYNIKU};

	int coursorCoordinate_X;
	int coursorCoordinate_Y;
	int mainMenuChoice = NULL;					//Wybor z menu glownego
	int activeWindow = MENU_GLOWNE;				//Aktualne okno
	int mainMenuButtonCoursored = NULL;			//Przycisk nakierowany kursorem
	
	bool leftMouseButtonClicked = false;

