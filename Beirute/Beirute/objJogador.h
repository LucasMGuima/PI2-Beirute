#pragma once
class objJogador
{
	private:
		int TEMP_TAMANHO = 20;

	public:
		float x;
		float y;
		float velocidade;
		
		objJogador(float new_x, float new_y, float new_velocidade) {
			x = new_x;
			y = new_y;
			velocidade = new_velocidade;
		}

		void movimento(ALLEGRO_KEYBOARD_STATE &ks, ALLEGRO_DISPLAY* tela) {
			if (al_key_down(&ks, ALLEGRO_KEY_W)) {
				float new_y = y - velocidade;
				if (new_y > 0) y = new_y;
			}
			if (al_key_down(&ks, ALLEGRO_KEY_S)) {
				float new_y = y + velocidade;
				if (new_y + TEMP_TAMANHO < al_get_display_height(tela)) y = new_y;
			}
			if (al_key_down(&ks, ALLEGRO_KEY_A)) {
				float new_x = x - velocidade;
				if (new_x > 0) x = new_x;
			}
			if (al_key_down(&ks, ALLEGRO_KEY_D)) {
				float new_x = x + velocidade;
				if (new_x + TEMP_TAMANHO < al_get_display_width(tela)) x = new_x;
			}
		}
};

