#include <iostream>
#include <allegro5/allegro.h>

using namespace std;


int main()
{
	al_init();
	ALLEGRO_DISPLAY* tela = al_create_display(800, 600);

	while (true)
		al_flip_display();
	
	std::cout << "Hello World!\n";

	return 0;

}
