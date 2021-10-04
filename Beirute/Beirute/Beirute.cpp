#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include "objInimigo.h";

using namespace std;

void iniciar(bool teste, const char *descricao) {
	if (teste) return;

	printf("Nao foi pocivel iniciar %s\n", descricao);
}

struct bloco
{
	float x, y;

	void desenhar() {
		al_draw_filled_rectangle(x, y, x + 20, y + 20, al_map_rgb(0, 255, 0));
	}
};

int main()
{
	iniciar(al_init(), "Allegro");
	iniciar(al_init_primitives_addon(), "Addon Primitivas");

	ALLEGRO_DISPLAY* tela = al_create_display(800, 600);
	iniciar(tela, "Tela");

	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
	iniciar(queue, "Event Queue");

	ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
	iniciar(timer, "Timer");

	al_register_event_source(queue, al_get_display_event_source(tela));
	al_register_event_source(queue, al_get_timer_event_source(timer));

	ALLEGRO_EVENT event;

	bool done = false;

	objInimigo inimigo01(400.0, 300.0, esqDir, 3.0);
	objInimigo inimigo02(200.0, 300.0, cimaBaixo, 2.0);

	bloco b1;
	b1.x = 100;
	b1.y = 300;

	bloco b2;
	b2.x = 600;
	b2.y = 300;
		
	al_start_timer(timer);
	while (true) {
		al_wait_for_event(queue, &event);

		switch (event.type) {
			case ALLEGRO_EVENT_TIMER:
				inimigo01.colisao(b1.x, b1.y);
				inimigo01.colisao(b2.x, b2.y);
				inimigo01.colisao(inimigo02.x, inimigo02.y);
				inimigo01.mover(tela);
				inimigo02.colisao(inimigo01.x, inimigo01.y);
				inimigo02.mover(tela);
				break;
		
			case ALLEGRO_EVENT_DISPLAY_CLOSE:
				done = true;
				break;
		}

		if (done) break;

		al_clear_to_color(al_map_rgb(0, 0, 0));
		inimigo01.desenhar();
		inimigo02.desenhar();

		b1.desenhar();
		b2.desenhar();

		al_flip_display();
	}

	al_destroy_display(tela);
	al_destroy_event_queue(queue);

	return 0;
}
