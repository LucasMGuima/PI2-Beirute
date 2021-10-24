#include <iostream>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>

#include "objJogador.h"
#include "objInimigo.h"
#include "bloco.h"

#include "FazeMaker.h"

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

	ALLEGRO_DISPLAY* tela = al_create_display(800, 600);
	iniciar(tela, "Tela");

	ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
	iniciar(timer, "Timer");

	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
	iniciar(queue, "Event Queue");

	al_register_event_source(queue, al_get_display_event_source(tela));
	al_register_event_source(queue, al_get_timer_event_source(timer));

	ALLEGRO_BITMAP* W, * A, * D, * IMG;
	IMG = al_load_bitmap("img.png");
	A = al_load_bitmap("img2.png");
	W = al_load_bitmap("img3.png");
	D = al_load_bitmap("img1.png");

	objJogador jogador(400.0, 300.0, 4.0);

	ALLEGRO_EVENT event;

	bool done = false;

	FazeMaker fazeMaker;

	/*
	objInimigo inimigo01(400.0, 300.0, esqDir, 3.0, 0);
	objInimigo inimigo02(200.0, 300.0, cimaBaixo, 2.0, 0);
	objInimigo inimigo03(200.0, 100.0, cimaBaixo, 2.0, 0);
	objInimigo inimigo04(300.0, 500.0, triangulo, 2.5, 200);
	objInimigo inimigo05(300.0, 100.0, quadrado, 2.5, 200);
	*/

	objInimigo inimigos[999];
	bloco blocos[999];

	//tamanho dos arrays
	int size = (sizeof inimigos) / (sizeof *inimigos);
	int size_bloc = (sizeof blocos) / (sizeof *blocos);

	//fase atual
	int fase = 1;
	int lastFase = 0;

	ALLEGRO_EVENT evento;
	ALLEGRO_KEYBOARD_STATE ks;

	al_start_timer(timer);
	while (true) {
		//atualiza o nivel
		if (lastFase != fase) {
			//cria as paredes
			fazeMaker.criarParedes(fase, blocos);
			//spawna os inimgos
			fazeMaker.criarInimigos(fase, inimigos);
			lastFase = fase;
		}
		al_wait_for_event(queue, &evento);

		switch (evento.type) {
			case ALLEGRO_EVENT_TIMER:
				//movimento do jogador
				al_get_keyboard_state(&ks);
				jogador.movimento(ks, tela);

				//movimento dos inimigos
				for (int i = 0; i < size; i++) {
					//checa por colis�o com solidos
					for (int j = 0; j < size_bloc; j++) {
						inimigos[i].colisao(blocos[j].x, blocos[j].y);
					}
					//checa por colis�o com outros inimigos
					for (int j = 0; j < size; j++) {
						if (j != i) {
							inimigos[i].colisao(inimigos[j].x, inimigos[j].y);
						}
					}
					inimigos[i].mover(tela);
				}

				//TROCA A FASE MANUAL
				if (al_key_down(&ks, ALLEGRO_KEY_ALT)) {
					fase += 1;
				}

				break;
		
			case ALLEGRO_EVENT_DISPLAY_CLOSE:
				done = true;
				break;
		}

		//fecha o jogo se o X for cliclado
		if (done) break;

		al_clear_to_color(al_map_rgb(0, 55, 0));
		if (al_key_down(&ks, ALLEGRO_KEY_W)){
			al_draw_bitmap(W, jogador.x, jogador.y, 0);
		}else if (al_key_down(&ks, ALLEGRO_KEY_D)){
			al_draw_bitmap(D, jogador.x, jogador.y, 0);
		}
		else if (al_key_down(&ks, ALLEGRO_KEY_A)){
			al_draw_bitmap(A, jogador.x, jogador.y, 0);
		}else{
			al_draw_bitmap(IMG, jogador.x, jogador.y, 0);
		}

		//desenha os blocos
		for (int i = 0; i < size_bloc; i++) {
			if (!(blocos[i].x == -1 and blocos[i].y == -1)) {
				blocos[i].desenhar();
			}
		}

		//desenha todos os inimigos na tela
		for (int i = 0; i < size; i++) {
			if (!(inimigos[i].x == -1 and inimigos[i].y == -1)) {
				int r = rand() % 255;
				int g = rand() % 255;
				int b = rand() % 255;
				inimigos[i].desenhar(r, g, b);
			}
		}

		al_flip_display();
	}

	al_destroy_bitmap(IMG);
	al_destroy_display(tela);
	al_destroy_event_queue(queue);
	al_destroy_timer(timer);

	return 0;
}