#include <iostream>
#include <cmath>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <string>

#include "objJogador.h"
#include "objInimigo.h"
#include "bloco.h"
#include "powerUp.h"

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
	ALLEGRO_FONT* font18 = al_load_font("fonts/arial.ttf", 18, 0);
	ALLEGRO_FONT* font12 = al_load_font("fonts/arial.ttf", 12, 0);


	ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
	iniciar(timer, "Timer");

	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
	iniciar(queue, "Event Queue");

	al_register_event_source(queue, al_get_display_event_source(tela));
	al_register_event_source(queue, al_get_timer_event_source(timer));

	ALLEGRO_BITMAP* W, * A, * D, * IMG, * atak;
	IMG = al_load_bitmap("medico_frente.png");
	A = al_load_bitmap("medico_esq_andar_1.png");
	W = al_load_bitmap("medico_costas.png");
	D = al_load_bitmap("medico_dir_andar_1.png");
	objJogador jogador(4.0);

	bool done = false;
	bool AT = false;

	FazeMaker fazeMaker;

	powerUp powerUps[10];
	objInimigo inimigos[999];
	bloco blocos[999];
	bloco ataque(0, 0);

	//tamanho dos arrays
	int size = (sizeof inimigos) / (sizeof *inimigos);
	int size_bloc = (sizeof blocos) / (sizeof *blocos);
	int powerUp_size = (sizeof powerUps) / (sizeof *powerUps);

	//fase atual
	int fase = 1;
	int lastFase = 0;
	//ultima fase
	int endFase = 3;

	bool msngFase = true;
	bool inicio = true;

	ALLEGRO_EVENT event;
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
			//cria o(s) power ups
			fazeMaker.criarPowerUp(fase, powerUps);

			lastFase = fase;
		}
		
		al_wait_for_event(queue, &event);

		switch (event.type) {
			case ALLEGRO_EVENT_TIMER:
				al_get_keyboard_state(&ks);
				//checa se o jogador ainda esta vivo, conservar processamento
				if (jogador.vida >= 0 and !msngFase) {
					//movimento do jogador
					jogador.movimento(ks, tela, blocos);

					//corre pelo array de inimigos
					for (int i = 0; i < size; i++) {
						if (inimigos[i].vivo) {//checa por colis�o com solidos
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

					//corre pelo array dos powerUps
					for (int i = 0; i < powerUp_size; i++) {
						if (powerUps[i].existe) {
							//checa por colisao com o jogador
							if (powerUps[i].colisaoVar(jogador.tamanho[0], jogador.tamanho[1], jogador.x, jogador.y)) {
								powerUps[i].efeito(&jogador);
							}
						}
					}
				}
				else if (inicio) {
					if (al_key_down(&ks, ALLEGRO_KEY_ENTER)) {
						inicio = false;
					}
				}else if (al_key_down(&ks, ALLEGRO_KEY_ENTER)) {
					msngFase = false;
				}

					// criar hitbox ataque
					if (al_key_down(&ks, ALLEGRO_KEY_SPACE)) {
						if (al_key_down(&ks, ALLEGRO_KEY_W)) {
							ataque.x = jogador.x + 10;
							ataque.y = jogador.y - 45;
						}
						if (al_key_down(&ks, ALLEGRO_KEY_S)) {
							ataque.x = jogador.x + 9.5;
							ataque.y = jogador.y + 45;
						}
						if (al_key_down(&ks, ALLEGRO_KEY_A)) {
							ataque.x = jogador.x - 35;
							ataque.y = jogador.y + 25;
						}
						if (al_key_down(&ks, ALLEGRO_KEY_D)) {
							ataque.x = jogador.x + 25;
							ataque.y = jogador.y + 25;
						}

						
						AT = true;//determina o desaparecimento dosn inimigos
					}
					// checa colisao do inimigo com o hitbox
					if (AT) {
						for (int i = 0; i < size; i++) {
							if (inimigos[i].colisaoHitbox(ataque.x, ataque.y)) {
								inimigos[i].vivo = false;
								AT = false;
								i = size;
							}
						}
					}

				//TROCA A FASE MANUAL
				if (al_key_down(&ks, ALLEGRO_KEY_ALT)) {
					fase += 1;
				}

				//reseta a fase se morto
				if (al_key_down(&ks, ALLEGRO_KEY_R) and jogador.vida <= 0) {
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

		if (done) break;

		//checa se o jogador ainda esta vivo
		//se sim desenha a cena normalmente, se n apresenta a tela de morte
		if (jogador.vida >= 0) {
			//checa se a mensagem ja passou
			if (msngFase and !inicio) {
				switch (fase)
				{
					//mesagem para aparecer no começa da fase
					case 1:
						al_clear_to_color(al_map_rgb(0,0,0));
						al_draw_text(font24, al_map_rgb(255, 255, 255), 400, 100, ALLEGRO_ALIGN_CENTER, "Fase 1");
						al_draw_text(font12, al_map_rgb(255, 255, 255), 400, 200, ALLEGRO_ALIGN_CENTER, "Aperte ENTER para começar");
						al_draw_multiline_text(font18, al_map_rgb(255, 255, 255), 400, 300, 700, 20, ALLEGRO_ALIGN_CENTER, "Aproximadamente 4 pessoas por minuto são salvas devido à seus esforços, mantenha o ótimo trabalho o pesadelo que vivemos logo ira acabar.");
						break;
					case 2:
						al_clear_to_color(al_map_rgb(0, 0, 0));
						al_draw_text(font24, al_map_rgb(255, 255, 255), 400, 100, ALLEGRO_ALIGN_CENTER, "Fase 2");
						al_draw_text(font12, al_map_rgb(255, 255, 255), 400, 200, ALLEGRO_ALIGN_CENTER, "Aperte ENTER para começar");
						al_draw_multiline_text(font18, al_map_rgb(255, 255, 255), 400, 300, 700, 20, ALLEGRO_ALIGN_CENTER, "Até agora 96% dos mortos fazem parte dos grupos negacionista que seguem a ideologia dos moradores de cima com essas informações podemos convencer a todos a se juntarem a nós.");
						break;
					case 3:
						al_clear_to_color(al_map_rgb(0, 0, 0));
						al_draw_text(font24, al_map_rgb(255, 255, 255), 400, 100, ALLEGRO_ALIGN_CENTER, "Fase 3");
						al_draw_text(font12, al_map_rgb(255, 255, 255), 400, 200, ALLEGRO_ALIGN_CENTER, "Aperte ENTER para começar");
						al_draw_multiline_text(font18, al_map_rgb(255, 255, 255), 400, 300, 700, 20, ALLEGRO_ALIGN_CENTER, "Parabéns ótimo trabalho o virus está sendo exterminado graças ao poder da ciência e das vacinas os moradores de cima ainda vão acreditar em nós.");
						break;
				}
			}
			else if (inicio) {
				//messagem de inicio do jogo
				
				al_clear_to_color(al_map_rgb(0, 0, 0));
				al_draw_multiline_text(font18, al_map_rgb(255, 255, 255), 400, 200, 700, 20, ALLEGRO_ALIGN_CENTER, "No ano de 4097 surgiu um vírus que rapidamente contaminou 65% da população devido a sua alta capacidade de se adaptar e reproduzir além de ter a habilidade de se assimilar com outros  formando um super vírus, os 35% que não se infectaram são os mais ricos da humanidade que atualmente vivem fora da terra e são chamados de moradores de cima, para não entrarem em contato com os infectados, àqueles que continuaram desenvolveram uma tecnologia capaz de encolher objetos e seres vivos a nível celular podendo batalhar contra esses vírus enviando Medicos  para aplicar os remédios e vacinas diretamente nos vírus dentro das células, seu objetivo e mostrar a eficácia desse novo método e provar a todos a real importância da ciência e das vacinas provando com resultados aos moradores de cima que se recusaram a acreditar nos tratamentos e partiram para fora da terra.");
				al_draw_text(font12, al_map_rgb(255, 255, 255), 400, 500, ALLEGRO_ALIGN_CENTER, "Aperte ENTER para começar");
				
			}
			else {
				al_clear_to_color(al_map_rgb(100, 0, 0));
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
				if (AT) {
					ataque.desenharA();
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
						if (inimigos[i].vivo) {
							inimigos[i].desenhar();
						}
					}
				}

				//desenha os powerUps
				for (int i = 0; i < powerUp_size; i++) {
					if (powerUps[i].existe) {
						powerUps[i].desenhar();
					}
				}

				//desenha a "hud"
				//vida
				int incX = 0;
				for (int i = 0; i <= jogador.vida; i++) {
					bloco temp = bloco(20 + incX, 20);
					temp.desenharCor(255, 0, 0);
					incX += 30;
				}

				//armadura
				incX = 0;
				for (int i = 0; i < jogador.armadura; i++) {
					bloco temp = bloco(20 + incX, 50);
					temp.desenharCor(0, 0, 255);
					incX += 30;
				}
			}
		}else {
			al_clear_to_color(al_map_rgb(0, 0, 0));
			//mostra o texto
			al_draw_text(font24, al_map_rgb(255, 255, 255), 400, 200, ALLEGRO_ALIGN_CENTRE, "Você Morreu");
			al_draw_multiline_text(font18, al_map_rgb(255, 255, 255), 400, 300, 700, 20, ALLEGRO_ALIGN_CENTER, "Voce falhou em mostrar a todos o real poder da ciência tente novamente nós não podemos deixar o negacionismo vencer mais uma vez.");
			al_draw_text(font12, al_map_rgb(255, 255, 255), 800 / 2, 500, ALLEGRO_ALIGN_CENTRE, "Precione R para continuar");
		}


		bool vitoria = true;
		for (int i = 0; i < size; i++) {
			if (inimigos[i].vivo and inimigos[i].x != -1) {
				vitoria = false;
				i = size;
			}
		}

		if (vitoria) {
			al_clear_to_color(al_map_rgb(0, 0, 0));
			//mostra o texto
			al_draw_text(font24, al_map_rgb(255, 255, 255), 400, 200, ALLEGRO_ALIGN_CENTRE, "Você Venceu");
			//porcentangem dos virus
			int porcVir = fase * 20;
			al_draw_multiline_textf(font18, al_map_rgb(255, 255, 255), 400, 300, 700, 20, ALLEGRO_ALIGN_CENTER, "Parabéns ótimo trabalho %d por cento dos virus foram exterminados graças ao poder da ciência e das vacinas, os moradores de cima vão ter que aceitar a ciência graças a você.", porcVir);
			al_draw_text(font12, al_map_rgb(255, 255, 255), 800 / 2, 500, ALLEGRO_ALIGN_CENTRE, "Precione ENTER para continuar");

			//passa pra proxima fase
			al_get_keyboard_state(&ks);
			if (al_key_down(&ks, ALLEGRO_KEY_ENTER)) {
				if (fase < endFase) {
					fase += 1;
					msngFase = true;
				}
			}
		}
		AT = false;
		al_flip_display();
	}

	al_destroy_bitmap(IMG);
	al_destroy_display(tela);
	al_destroy_event_queue(queue);
	al_destroy_timer(timer);

	return 0;
}