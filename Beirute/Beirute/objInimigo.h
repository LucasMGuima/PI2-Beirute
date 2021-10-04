#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include "enum.h";

class objInimigo {
	private:
		bool direc = 1; //0 - direita | 1 - esquerda
		int TEMP_TAMANHO = 20;

	public:
		double x, y, velocida;
		int tipoCaminho;

		objInimigo(double new_x, double new_y, int new_tipoCaminho, double new_velo) {
			x = new_x;
			y = new_y;
			tipoCaminho = new_tipoCaminho;
			velocida = new_velo;
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
					x -= 4;
				}
				else {
					x += 4;
				}
				break;

			case cimaBaixo:
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

		void desenhar() {
			//se redesenha na tela com base na nova posição
			al_draw_filled_rectangle(x, y, x + TEMP_TAMANHO, y + TEMP_TAMANHO, al_map_rgb(255, 0, 0));
		}
};