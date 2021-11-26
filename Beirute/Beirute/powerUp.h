#pragma once
#include "enum.h"
#include <random>

class powerUp {
	private:
		int tipo;
		int x, y;
		ALLEGRO_BITMAP* img;
		int tamanho = 20;

	public:
		bool existe = false;

		//construto padroa
		powerUp(){
			x = -1;
			y = -1;
			tipo = -1;
			img = 0;
		}

		void setarTipo(char tipo) {
			//seta o tipo do powerUp
			switch (tipo){
				case 'V':
					//seta o tipo
					this->tipo = vida;
					//carrega a img equivalente
					img = al_load_bitmap("imgs/powerUp/medkit.png");
					break;
				case 'A':
					//seta o tipo
					this->tipo = defesa;
					//carrega a img equivalente
					img = al_load_bitmap("imgs/powerUp/armadura.png");
					break;
				case 'M':
					//seta o tipo
					this->tipo = movimento;
					//carega a img equivalente
					img = al_load_bitmap("imgs/powerUp/bota.png");
					break;
			}
		}

		//seta a nova posição, e assim q ele a possuir passa a exisitir
		void setPos(int x, int y) {
			this->x = x;
			this->y = y;
			existe = true;
		}

		void desenhar() {
			al_draw_bitmap(this->img, this->x, this->y, 0);
		}

		void efeito(objJogador* jogador) {
			//aplica o efeito de acordo com o tipo do powerUp
			printf("aplicando efeito \n");
			printf("tipo = %d \n", tipo);
			switch (tipo)
			{
				case vida:
					jogador->vida += 1;
					break;
				case defesa:
					jogador->armadura += 1;
					break;
				case movimento:
					jogador->velocidade += 0.5;
					break;
			}
			existe = false;
		}

		//colisao
		bool colisaoVar(int width, int length, float px, float py) {
			if (x + tamanho < px || x > px + width || y + tamanho < py || y > py + length) {
				//sem colisao de hitbox
				return false;
			}
			else {
				return true;
			}

		}
};