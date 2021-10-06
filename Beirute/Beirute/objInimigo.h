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

	public:
		double x, y, velocida;
		int tipoCaminho;

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
						//se move até o alvo
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
						//se move até o alvo
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
						//se move até o alvo
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
					if (target_x == -1) target_x = x + mov_dist;
					//se move até o alvo
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
					//seta um novo alvo de movimento
					if (target_y == -1) target_y = y + mov_dist;
					//se move até o alvo
					if (y < target_y) {
						y += velocida;
					}
					//checa se chego no alvo
					if (y == target_y) {
						passo_atual += 1;
						target_y = -1;
					}
					break;

				case 3:
					//seta um novo alvo de movimento
					if (target_x == -1) target_x = x - mov_dist;
					//se move até o alvo
					if (x > target_x) {
						x -= velocida;
					}
					//checa se chego no alvo
					if (x == target_x) {
						passo_atual += 1;
						target_x = -1;
					}
					break;
				
				case 4:
					//seta um novo alvo de movimento
					if (target_y == -1) target_y = y - mov_dist;
					//se move até o alvo
					if (y > target_y) {
						y -= velocida;
					}
					//checa se chego no alvo
					if (y == target_y) {
						passo_atual = 0;
						target_y = -1;
					}
					break;

				}
				break;
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

		void desenhar(int r, int g, int b) {
			//se redesenha na tela com base na nova posição
			al_draw_filled_rectangle(x, y, x + TEMP_TAMANHO, y + TEMP_TAMANHO, al_map_rgb(r, g, b));
		}
};