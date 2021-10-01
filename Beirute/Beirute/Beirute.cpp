#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

using namespace std;

struct inimigo {
	private:
		bool direc = 1; //0 - direita | 1 - esquerda
		int TEMP_TAMANHO = 20;
	public:
		float x, y;
		int tipo_caminho; //1 - esq direita | 2 - sima baixo | 3 - quadrado

	void mover(ALLEGRO_DISPLAY* tela) {
		int dp_height = al_get_display_height(tela);
		int dp_width = al_get_display_width(tela);

		switch (tipo_caminho) {
			case 1:
				//tipo 1 de mov - esquerda direita
				if (x + TEMP_TAMANHO >= dp_width) {
					//muda p esquerda
					direc = 1;
				}
				if (x <= 0) {
					//muda p direita
					direc = 0;
				}

				if (direc == 1) {
					x -= 4;
				}
				else {
					x += 4;
				}
				break;

			case 2:
				//tipo 2 de mov - sima baixo
				if (y + TEMP_TAMANHO >= dp_height) {
					//muda p esquerda
					direc = 1;
				}
				if (y <= 0) {
					//muda p direita
					direc = 0;
				}

				if (direc == 1) {
					y -= 4;
				}
				else {
					y += 4;
				}
				break;

			case 3:
				//tipo 3 de mov
				break;
		}
	}

	void desenhar() {
		//se redesenha na tela com base na nova posição
		al_draw_filled_rectangle(x, y, x + TEMP_TAMANHO, y + TEMP_TAMANHO, al_map_rgb(255, 0, 0));
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

	inimigo inimigo02;
	inimigo02.x = 200;
	inimigo02.y = 300;
	inimigo02.tipo_caminho = 2;

	inimigo inimigo03;
	inimigo03.x = 500;
	inimigo03.y = 300;
	inimigo03.tipo_caminho = 3;

	al_start_timer(timer);
	while (true) {
		al_wait_for_event(queue, &event);

		switch (event.type) {
			case ALLEGRO_EVENT_TIMER:
				inimigo01.mover(tela);
				inimigo02.mover(tela);
				inimigo03.mover(tela);
				break;
		
			case ALLEGRO_EVENT_DISPLAY_CLOSE:
				done = true;
				break;
		}

		if (done) break;

		al_clear_to_color(al_map_rgb(0, 0, 0));
		inimigo01.desenhar();
		inimigo02.desenhar();
		inimigo03.desenhar();
		al_flip_display();
	}

	al_destroy_display(tela);
	al_destroy_event_queue(queue);

	return 0;
}
