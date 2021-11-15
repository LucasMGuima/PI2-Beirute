#pragma once
#include "enum.h"

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

		void setarTipo() {
			int num = rand() % 6; //pega um valor aleatório entre 0 - 5

			//seta o tipo do powerUp
			switch (num){
				case 0:
				case 1:
					//seta o tipo
					tipo = vida;
					//carrega a img equivalente
					img = al_load_bitmap("imgs/powerUp/medkit.png");
					break;
				case 2:
				case 3:
					//seta o tipo
					tipo = defesa;
					//carrega a img equivalente
					img = al_load_bitmap("imgs/powerUp/armadura.png");
					break;
				case 4:
				case 5:
					//seta o tipo
					tipo = movimento;
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