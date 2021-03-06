#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include "enum.h";

class objInimigo {
	private:
		bool direc = 1;
		int TEMP_TAMANHO = 20;

		double target_x = -1, target_y = -1;
		int mov_passo[4] = {0, 0, 0, 0};
		int passo_atual = 0;
		int mov_dist = 0;

		ALLEGRO_BITMAP* img;

		int last_pos[2] = {-1, -1};
	public:
		double x, y, velocida;
		int tipoCaminho;
		bool vivo = true;

		objInimigo() { x = -1; y = -1; tipoCaminho = 0; velocida = 0; mov_dist = 0; };

		objInimigo(double new_x, double new_y, int new_tipoCaminho, double new_velo, int new_movDist) {
			x = new_x;
			y = new_y;
			tipoCaminho = new_tipoCaminho;
			velocida = new_velo;
			mov_dist = new_movDist;

			switch (tipoCaminho){
				case triangulo:
					mov_passo[0] = 1;
					mov_passo[1] = 2;
					mov_passo[2] = 3;
					break;
				case quadrado:
					mov_passo[0] = 1;
					mov_passo[1] = 2;
					mov_passo[2] = 3;
					mov_passo[3] = 4;
					break;
			}

			//img do inimigo
			switch (new_tipoCaminho)
			{
				case esqDir:
					img = al_load_bitmap("imgs/inimigos/Green_Virus.png");
					break;
				case cimaBaixo:
					img = al_load_bitmap("imgs/inimigos/Blue_Virus.png");
					break;
			}
		}

		void mover(ALLEGRO_DISPLAY* tela) {
			int dp_height = al_get_display_height(tela);
			int dp_width = al_get_display_width(tela);

			switch (tipoCaminho) {
			case esqDir:
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
					x -= velocida;
				}
				else {
					x += velocida;
				}
				break;

			case cimaBaixo:
				//tipo 2 de mov - cima baixo
				if (y + TEMP_TAMANHO >= dp_height) {
					//muda p cima
					direc = 1;
				}
				if (y <= 0) {
					//muda p baixo
					direc = 0;
				}

				if (direc == 1) {
					y -= velocida;
				}
				else {
					y += velocida;
				}
				break;

			case triangulo:
				switch (mov_passo[passo_atual])
				{
					case 1:
						//seta um novo alvo de movimento
						if (target_x == -1) target_x = x + mov_dist;
						//se move at? o alvo
						if (x < target_x) {
							x += velocida;
						}
						//checa se chego no alvo
						if (x == target_x) {
							passo_atual += 1;
							target_x = -1;
						}
						break;

					case 2:
						//seta um novo alvo
						if (target_x == -1 and target_y == -1) {
							target_x = x - mov_dist/2;
							target_y = y - mov_dist/2;
						}
						//se move at? o alvo
						if (x > target_x) {
							x -= velocida;
						}
						if (y > target_y) {
							y -= velocida;
						}
						//checa se chegou ao alvo
						if (x == target_x and y == target_y) {
							passo_atual += 1;
							target_x = -1;
							target_y = -1;
						}
						break;

					case 3:
						//seta um novo alvo
						if (target_x == -1 and target_y == -1) {
							target_x = x - mov_dist/2;
							target_y = y + mov_dist/2;
						}
						//se move at? o alvo
						if (x > target_x) {
							x -= velocida;
						}
						if (y < target_y) {
							y += velocida;
						}
						//checa se chegou ao alvo
						if (x == target_x and y == target_y) {
							passo_atual = 0;
							target_x = -1;
							target_y = -1;
						}
						break;

				}
				break;
			
			case quadrado:
				switch (mov_passo[passo_atual])
				{
					case 1:
						//seta um novo alvo de movimento
						if (target_x == -1) {
							if (direc == 1) {
								target_x = x + mov_dist;
							}
							else if (direc == 0) {
								target_x = x - mov_dist;
							}
						}
						//se move at? o alvo
						if (x < target_x && direc == 1) {
							x += velocida;
						}
						if (x > last_pos[0] && direc == 0) {
							x -= velocida;
						}
						//checa se chego no alvo
						if (x == target_x || x == last_pos[0]) {
							if (x == target_x) passo_atual += 1;
							else if (x == last_pos[0]) passo_atual ;
							last_pos[0] = -1;
							last_pos[1] = y;
							target_x = -1;
						}
						break;

					case 2:
						//seta um novo alvo de movimento
						if (target_y == -1) {
							if(direc == 1) target_y = y + mov_dist;
							else if (direc == 0) target_y = y - mov_dist;
						}
						//se move at? o alvo
						if (y < target_y && direc == 1) {
							y += velocida;
						}
						if (y > last_pos[1] && direc == 0) {
							y -= velocida;
						}
						//checa se chego no alvo
						if (y == target_y || y == last_pos[1]) {
							if (y == target_y) passo_atual += 1;
							else if (y == last_pos[1]) passo_atual -= 1;
							last_pos[0] = x;
							last_pos[1] = -1;
							target_y = -1;
						}
						break;

					case 3:
						//seta um novo alvo de movimento
						if (target_x == -1) {
							if(direc == 1) target_x = x - mov_dist;
							else if (direc == 0) target_x = x + mov_dist;
						}
						//se move at? o alvo
						if (x > target_x && direc == 1) {
							x -= velocida;
						}
						if (x < last_pos[0] && direc == 0) {
							x += velocida;
						}
						//checa se chego no alvo
						if (x == target_x || x == last_pos[0]) {
							if(x == target_x) passo_atual += 1;
							else if (x == last_pos[0]) passo_atual -= 1;
							last_pos[0] = -1;
							last_pos[1] = y;
							target_x = -1;
						}
						break;

					case 4:
						//seta um novo alvo de movimento
						if (target_y == -1) {
							if(direc == 1) target_y = y - mov_dist;
							else if (direc == 0) target_y = y + mov_dist;
						}
						//se move at? o alvo
						if (y > target_y && direc == 1) {
							y -= velocida;
						}
						if (y < last_pos[1] && direc == 0) {
							y += velocida;
						}
						//checa se chego no alvo
						if (y == target_y || y == last_pos[1]) {
							if (y == target_y) passo_atual = 0;
							else if (y == last_pos[1]) passo_atual -= 1;
							last_pos[0] = x;
							last_pos[1] = -1;
							target_y = -1;
						}
						break;
				}
				printf("last_pos[%d, %d] | direc[%d] | passo_atual[%d] \n", last_pos[0], last_pos[1], direc, passo_atual);
			}

		}

		void colisao(float ex, float ey) {
			if (x + TEMP_TAMANHO < ex || x > ex + TEMP_TAMANHO || y + TEMP_TAMANHO < ey || y > ey + TEMP_TAMANHO) {
				//sem colisao de hitbox
			}
			else {
				if (direc == 0) {
					direc = 1;
				}
				else if (direc == 1) {
					direc = 0;
				}
			}
		}
		bool colisaoHitbox(float ex, float ey) {
			if (x + TEMP_TAMANHO < ex || x > ex + TEMP_TAMANHO || y + TEMP_TAMANHO < ey || y > ey + TEMP_TAMANHO) {
				return false;
			}
			else {
				return true;
			}
		}

		//colis?o com tamanho variado
		void colisaoVar(int width, int length, float px, float py) {
			if (x + TEMP_TAMANHO < px || x > px + width || y + TEMP_TAMANHO < py || y > py + length) {
				//sem colisao de hitbox
			}
			else {
				if (direc == 0) {
					direc = 1;
				}
				else if (direc == 1) {
					direc = 0;
				}
			}

		}

		void desenhar() {
			//se redesenha na tela com base na nova posi??o
			al_draw_bitmap(this->img, this->x, this->y, 0);
		}
};