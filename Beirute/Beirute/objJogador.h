#pragma once
#include "bloco.h";

class objJogador
{
	private:
		int timerDano;

	public:
		int vida;
		float x;
		float y;
		float velocidade;
		int dir;
		enum Direction { DOWN, LEFT, RIGHT, UP };
		bool dano = false;
		int tamanho[2];
		

		objJogador(float new_x, float new_y, float new_velocidade) {
			x = new_x;
			y = new_y;
			velocidade = new_velocidade;

			tamanho[0] = 38;
			tamanho[1] = 54;

			vida = 3;
			timerDano = 0;
		}

		void movimento(ALLEGRO_KEYBOARD_STATE &ks, ALLEGRO_DISPLAY* tela, bloco *paredes) {
			float new_x = x;
			float new_y = y;

			float last_x = x;
			float last_y = y;

			int size_bloc = 999;

			if (al_key_down(&ks, ALLEGRO_KEY_W)) {
				if (new_y > 0) new_y = y - velocidade;
				//y -= velocidade;
				dir = UP;
			}
			if (al_key_down(&ks, ALLEGRO_KEY_S)) {
				if (new_y + tamanho[1] < al_get_display_height(tela)) new_y = y + velocidade;
				//y += velocidade;
				dir = DOWN;
			}
			if (al_key_down(&ks, ALLEGRO_KEY_A)) {
				if (new_x > 0) new_x = x - velocidade;
				//x -= velocidade;
				dir = LEFT;
			}

			if (al_key_down(&ks, ALLEGRO_KEY_D)) {
				if (new_x + tamanho[0] < al_get_display_width(tela)) new_x = x + velocidade;
				//x += velocidade;
				dir = RIGHT;
			}

			//checa por colis�o com a parede, se n ouver aplica a nova posi��o
			for (int j = 0; j < size_bloc; j++) {
				if (!colisao(paredes[j].x, paredes[j].y, new_x, y)) {
					x = new_x;
				}else{
					j = size_bloc;
					x = last_x;
				}
			}
			for (int j = 0; j < size_bloc; j++) {
				if (!colisao(paredes[j].x, paredes[j].y, x, new_y)) {
					y = new_y;
				}
				else {
					j = size_bloc;
					y = last_y;
				}
			}

			//printf("Jogador atual[X: %.1f | Y: %.1f] mew[X: %.1f | Y: %.1f] \n", x, y, new_x, new_y);
			//colisao(x , y, 200, 200, 32, 32, dir, velocidade);
		}

		//colisão com tamanho padrão
		bool colisao(float ex, float ey, float new_x, float new_y) {
			if (new_x + tamanho[0] < ex || new_x > ex + 20 || new_y + tamanho[1] < ey || new_y > ey + 20) {
				//sem colisao de hitbox
				return false;
			}
			else {
				return true;
			}

		}
		//colisão com tamanho variado
		bool colisao(float ex, float ey, float eSize, float new_x, float new_y) {
			if (new_x + tamanho[0] < ex || new_x > ex + eSize || new_y + tamanho[1] < ey || new_y > ey + eSize) {
				//sem colisao de hitbox
				return false;
			}
			else {
				return true;
			}

		}

		void colisaoCirc(float x, float y, float ex, float ey, int praio, int eraio, int dir, float velocidade) {
			if (sqrt(pow(x - ex, 2) + pow(y - ey, 2)) < praio + eraio) {
				//sem colisao de hitbox
			}
			else {
				if (dir == 0)
					y -= velocidade;
				else if (dir == 1)
					x += velocidade;
				else if (dir == 2)
					x -= velocidade;
				else if (dir == 3)
					y += velocidade;
			}
		}		
		
		//recebe dano qnd colide com o obejto
		void recebeDano(float ex, float ey, float eSize) {
			bool aplicar = false;

			//checa se entro em colisão com o inimigo se n estiver em dano
			if (colisao(ex, ey, eSize, x, y) and dano == false) {
				dano = true;
				aplicar = true;
			}

			//aplica o dano
			if (dano) {
				//permite q leve dana em um intervalo de 30s
				timerDano++;
				if (timerDano >= 30) {
					dano = false;
					timerDano = 0;
				}
				//aplica o dano uma vez
				if (aplicar) {
					vida--;
					aplicar = false;
				}
				printf("Vida : %d | ", vida);
				printf("Time : %d \n", timerDano);
			}
		}
};

