#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include "enum.h";

struct bloco
{
public:
	float x, y;
	int s = 0;
	bloco() { x = -1.0; y = -1.0; };

	bloco(int x, int y) {
		this->x = x;
		this->y = y;
	}

	void desenhar() {
		al_draw_filled_rectangle(x, y, x + 20, y + 20, al_map_rgb(55, 55,55));
	}
	void desenharCor(int r, int g, int b) {
		al_draw_filled_rectangle(x, y, x + 20, y + 20, al_map_rgb(r, g, b));
	}

	void desenharA() {
		ALLEGRO_KEYBOARD_STATE ks;
		al_get_keyboard_state(&ks);

		ALLEGRO_BITMAP* W, * A, * D, * S;
		S = al_load_bitmap("seringa_baixo.png");
		A = al_load_bitmap("seringa_esq.png");
		W = al_load_bitmap("seringa_cima.png");
		D = al_load_bitmap("seringa_dir.png");

		
		 if (al_key_down(&ks, ALLEGRO_KEY_W) && !al_key_down(&ks, ALLEGRO_KEY_D) && !al_key_down(&ks, ALLEGRO_KEY_A) && !al_key_down(&ks, ALLEGRO_KEY_S)) {
			al_draw_bitmap(W, x, y, 0);

		}
		if (al_key_down(&ks, ALLEGRO_KEY_D) && !al_key_down(&ks, ALLEGRO_KEY_W) && !al_key_down(&ks, ALLEGRO_KEY_A) && !al_key_down(&ks, ALLEGRO_KEY_S)) {
			al_draw_bitmap(D, x, y, 0);
		}
		if (al_key_down(&ks, ALLEGRO_KEY_A) && !al_key_down(&ks, ALLEGRO_KEY_D) && !al_key_down(&ks, ALLEGRO_KEY_W) && !al_key_down(&ks, ALLEGRO_KEY_S)) {
			al_draw_bitmap(A, x, y, 0);
		}
		if (al_key_down(&ks, ALLEGRO_KEY_S) && !al_key_down(&ks, ALLEGRO_KEY_D) && !al_key_down(&ks, ALLEGRO_KEY_A) && !al_key_down(&ks, ALLEGRO_KEY_W)) {
			al_draw_bitmap(S, x, y, 0);
		}

	}



};