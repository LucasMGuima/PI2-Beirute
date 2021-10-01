#include <iostream>
#include <allegro5/allegro.h>

using namespace std;

void iniciar(bool teste, const char *descricao) {
	if (teste) return;

	printf("Nao foi pocivel iniciar %s\n", descricao);
}

int main()
{
	iniciar(al_init(), "Allegro");

	ALLEGRO_DISPLAY* tela = al_create_display(800, 600);
	iniciar(tela, "Tela");

	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
	iniciar(queue, "Event Queue");

	al_register_event_source(queue, al_get_display_event_source(tela));

	ALLEGRO_EVENT event;

	bool done = false;

	while (true) {
		al_wait_for_event(queue, &event);

		switch (event.type) {
			case ALLEGRO_EVENT_DISPLAY_CLOSE:
				done = true;
				break;
		}

		if (done) break;

		al_flip_display();
	}

	al_destroy_display(tela);
	al_destroy_event_queue(queue);

	return 0;
}
