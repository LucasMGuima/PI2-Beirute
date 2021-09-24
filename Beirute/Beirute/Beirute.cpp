#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>

using namespace std;

void iniciar(bool teste, const char *descricao) {
	if (teste) return;

	printf("Nao foi pocivel iniciar %s\n", descricao);
}

struct jogador {
	float x;
	float y;
	float velocidade;

	void movimento(ALLEGRO_KEYBOARD_STATE &ks, jogador &jogador) {
		if (al_key_down(&ks, ALLEGRO_KEY_W)) {
			jogador.y -= jogador.velocidade;
		}
		if (al_key_down(&ks, ALLEGRO_KEY_S)) {
			jogador.y += jogador.velocidade;
		}
		if (al_key_down(&ks, ALLEGRO_KEY_A)) {
			jogador.x -= jogador.velocidade;
		}
		if (al_key_down(&ks, ALLEGRO_KEY_D)) {
			jogador.x += jogador.velocidade;
		}
	};
};


int main()
{
	iniciar(al_init(), "allegro");
	iniciar(al_install_keyboard(), "teclado");
	iniciar(al_init_primitives_addon(), "addon primitivas");

	ALLEGRO_DISPLAY* tela = al_create_display(800, 600);
	iniciar(tela, "tela");

	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
	iniciar(queue, "queue");

	ALLEGRO_TIMER* timer = al_create_timer(1.0/30.0);
	iniciar(timer, "timer");

	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_timer_event_source(timer));

	jogador jogador;
	jogador.x = 400.0;
	jogador.y = 300.0;
	jogador.velocidade = 4.0;

	ALLEGRO_EVENT evento;
	ALLEGRO_KEYBOARD_STATE ks;

	al_start_timer(timer);
	while (true) {
		al_wait_for_event(queue, &evento);

		switch (evento.type) {
			case ALLEGRO_EVENT_TIMER:
				al_get_keyboard_state(&ks);
				jogador.movimento(ks, jogador);
				break;
		}

		al_clear_to_color(al_map_rgb(0, 0, 0));
		al_draw_filled_rectangle(jogador.x, jogador.y, jogador.x + 20, jogador.y + 20, al_map_rgb(255, 0, 0));
		al_flip_display();
	}

	al_destroy_display(tela);
	al_destroy_event_queue(queue);
	al_destroy_timer(timer);

	return 0;
}
