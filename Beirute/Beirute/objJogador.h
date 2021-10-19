#pragma once
class objJogador
{
	private:
		int TEMP_TAMANHO = 20;

	public:
		float x;
		float y;
		float velocidade;
		int dir;
		enum Direction { DOWN, LEFT, RIGHT, UP };
		

		objJogador(float new_x, float new_y, float new_velocidade) {
			x = new_x;
			y = new_y;
			velocidade = new_velocidade;
		}

		void movimento(ALLEGRO_KEYBOARD_STATE &ks, ALLEGRO_DISPLAY* tela) {
			if (al_key_down(&ks, ALLEGRO_KEY_W)) {
				float new_y = y - velocidade;
				if (new_y > 0) y = new_y;
				//y -= velocidade;
				dir = UP;
			}
			if (al_key_down(&ks, ALLEGRO_KEY_S)) {
				float new_y = y + velocidade;
				if (new_y + TEMP_TAMANHO < al_get_display_height(tela)) y = new_y;
				//y += velocidade;
				dir = DOWN;
			}
			if (al_key_down(&ks, ALLEGRO_KEY_A)) {
				float new_x = x - velocidade;
				if (new_x > 0) x = new_x;
				//x -= velocidade;
				dir = LEFT;
			}

			if (al_key_down(&ks, ALLEGRO_KEY_D)) {
				float new_x = x + velocidade;
				if (new_x + TEMP_TAMANHO < al_get_display_width(tela)) x = new_x;
				//x += velocidade;
				dir = RIGHT;
			}
			colisao(x , y, 200, 200, 32, 32, dir, velocidade);
		}

		void colisao(float x, float y, float ex, float ey, int width, int height, int dir, float velocidade) {
			if (x + width < ex || x > ex + width || y + height < ey || y > ey + height) {
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

		
};

