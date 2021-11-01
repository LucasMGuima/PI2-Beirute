#include <iostream>
#include <cmath>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

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
	iniciar(al_init_ttf_addon(), "leitor de .ttf");
	iniciar(al_init_font_addon(), "fontes");

	ALLEGRO_DISPLAY* tela = al_create_display(800, 600);
	iniciar(tela, "Tela");

	//fontes
	ALLEGRO_FONT* font24 = al_load_font("fonts/arial.ttf", 24, 0);
	ALLEGRO_FONT* font12 = al_load_font("fonts/arial.ttf", 12, 0);


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

	objJogador jogador(4.0);

	ALLEGRO_EVENT event;

	bool done = false;

	FazeMaker fazeMaker;

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
			//posiciona o jogador
			fazeMaker.posicionarJogador(fase, &jogador);

			lastFase = fase;
		}
		al_wait_for_event(queue, &evento);

		switch (evento.type) {
			case ALLEGRO_EVENT_TIMER:
				al_get_keyboard_state(&ks);
				//checa se o jogador ainda esta vivo, conservar processamento
				if (jogador.vida >= 0) {
					//movimento do jogador
					jogador.movimento(ks, tela, blocos);

					//corre pelo array de inimigos
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
						//checa se colidiu com o jogador e aplica o dano se sim
						inimigos[i].colisaoVar(jogador.tamanho[0], jogador.tamanho[1], jogador.x, jogador.y);
						jogador.recebeDano(inimigos[i].x, inimigos[i].y, 20);

						inimigos[i].mover(tela);
					}
				}

				//TROCA A FASE MANUAL
				if (al_key_down(&ks, ALLEGRO_KEY_ALT)) {
					fase += 1;
				}

				//reseta a fase se morto
				if (jogador.vida < 0 and al_key_down(&ks, ALLEGRO_KEY_ENTER)) {
					jogador.vida = 3;
					//recaga a faze
					lastFase = 0;
				}

				//fecha a janela no ESC
				if (al_key_down(&ks, ALLEGRO_KEY_ESCAPE)) {
					done = true;
				}

				break;
		
			case ALLEGRO_EVENT_DISPLAY_CLOSE:
				done = true;
				break;
		}

		//fecha o jogo se o X for cliclado
		if (done) break;

		//checa se o jogador ainda esta vivo
		//se sim desenha a cena normalmente, se n apresenta a tela de morte
		if (jogador.vida >= 0) {
			al_clear_to_color(al_map_rgb(0, 55, 0));
			if (al_key_down(&ks, ALLEGRO_KEY_W)) {
				al_draw_bitmap(W, jogador.x, jogador.y, 0);
			}
			else if (al_key_down(&ks, ALLEGRO_KEY_D)) {
				al_draw_bitmap(D, jogador.x, jogador.y, 0);
			}
			else if (al_key_down(&ks, ALLEGRO_KEY_A)) {
				al_draw_bitmap(A, jogador.x, jogador.y, 0);
			}
			else {
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
		}
		else {
			//jogador morto
			al_clear_to_color(al_map_rgb(0, 0, 0));

			//mostra o texto
			al_draw_text(font24, al_map_rgb(255,255,255), 800/2, 600/2, ALLEGRO_ALIGN_CENTRE,"Você Morreu");
			al_draw_text(font12, al_map_rgb(255, 255, 255), 800/2, 600/2 + 24, ALLEGRO_ALIGN_CENTRE, "Precione ENTER para continuar");
		}

		al_flip_display();
	}

	al_destroy_bitmap(IMG);
	al_destroy_display(tela);
	al_destroy_event_queue(queue);
	al_destroy_timer(timer);

	return 0;
}