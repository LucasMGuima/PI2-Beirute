#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include "enum.h";

struct bloco
{
	public:
		float x, y;

		bloco() { x = -1.0; y = -1.0; };

		bloco(int x, int y) {
			this->x = x;
			this->y = y;
		}

		void desenhar() {
			al_draw_filled_rectangle(x, y, x + 20, y + 20, al_map_rgb(0, 255, 0));
		}

};