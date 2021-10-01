#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include "objJogador.h"

using namespace std;


void iniciar(bool teste, const char* descricao) {
	if (teste) return;

	printf("Nao foi possivel iniciar %s\n", descricao);
}

int main()
{
	iniciar(al_init(), "allegro");
	iniciar(al_install_keyboard(), "teclado");
	iniciar(al_init_primitives_addon(), "addon primitivas");
	iniciar(al_init_image_addon(), "iniciar imagems");


	ALLEGRO_BITMAP* W, * A, * D, * IMG;
	IMG = al_load_bitmap("img.png");
	A = al_load_bitmap("img2.png");
	W = al_load_bitmap("img3.png");
	D = al_load_bitmap("img1.png");



	ALLEGRO_DISPLAY* tela = al_create_display(800, 600);
	iniciar(tela, "tela");

	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
	iniciar(queue, "queue");

	ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60);
	iniciar(timer, "timer");

	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_timer_event_source(timer));


	objJogador jogador(400.0, 300.0, 4.0);

	ALLEGRO_EVENT evento;
	ALLEGRO_KEYBOARD_STATE ks;

	al_start_timer(timer);
	while (true) {
		al_wait_for_event(queue, &evento);

		switch (evento.type) {
		case ALLEGRO_EVENT_TIMER:
			al_get_keyboard_state(&ks);
			jogador.movimento(ks, tela);

			break;
		}


		al_clear_to_color(al_map_rgb(0, 55, 0));




		al_flip_display();
	}

	al_destroy_bitmap(IMG);
	al_destroy_display(tela);
	al_destroy_event_queue(queue);
	al_destroy_timer(timer);

	return 0;
}
