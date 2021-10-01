#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

using namespace std;

struct inimigo {
	float x, y;
	int tipo_caminho;

	void mover() {
		//logica do movimento aqui;
	}

	void desenhar() {
		al_draw_filled_rectangle(x, y, x + 20, y + 20, al_map_rgb(255, 0, 0));
		//se redesenha na tela com base na nova posição
	}
};

void iniciar(bool teste, const char *descricao) {
	if (teste) return;

	printf("Nao foi pocivel iniciar %s\n", descricao);
}

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

	inimigo inimigo01;
	inimigo01.x = 400;
	inimigo01.y = 300;
	inimigo01.tipo_caminho = 1;

	al_start_timer(timer);
	while (true) {
		al_wait_for_event(queue, &event);

		switch (event.type) {
			case ALLEGRO_EVENT_TIMER:
				inimigo01.mover();
				break;
		
			case ALLEGRO_EVENT_DISPLAY_CLOSE:
				done = true;
				break;
		}

		if (done) break;

		al_clear_to_color(al_map_rgb(0, 0, 0));
		inimigo01.desenhar();
		al_flip_display();
	}

	al_destroy_display(tela);
	al_destroy_event_queue(queue);

	return 0;
}
