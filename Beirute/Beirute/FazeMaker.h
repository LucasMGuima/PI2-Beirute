#pragma once

#include <fstream>
#include <iostream>
#include <sstream>

#include "bloco.h"

using namespace std;

class FazeMaker {
	/*
		Cada ploco tem 20px, logo o arquivo pode ter a meta da altura da tela em linhas e a metada da largura em colunas.
		0 -> espaço vazio
		1 -> muro
		2 -> inimigo esquerda direita
		3 -> inimigo cima baixo
	*/
	public:
		void criarParedes(int level, bloco paredes[]) {
			printf("criando paredes \n");
			string linha;

			ifstream arq;
			arq.open(acharNivel(level));

			if (arq.is_open()) {
				printf("Aqrquivo aberto \n");
				int count = 0;
				int lin = 1;
				while (!arq.eof()) {
					getline(arq, linha);
					
					int lSize = linha.size();

					for (int col = 0; col < lSize; col++) {
						if (linha[col] == '1') {
							bloco temp((col+1) * 20, lin * 20);
							//printf("X: %.f Y: %.f \n", temp.x, temp.y);
							paredes[count] = temp;
							count++;
						}
					}
					lin++;
				}
			}
			else {
				printf("Não foi pocivel abrir o arquivo");
			}

			arq.close();
		}

		void criarInimigos(int level, objInimigo inimigos[]) {
			printf("criando inimigos \n");
			string linha;

			ifstream arq;
			arq.open(acharNivel(level));

			if (arq.is_open()) {
				printf("Arquivo aberto \n");
				int count = 0;
				int lin = 1;
				while (!arq.eof()) {
					getline(arq, linha);

					int lSize = linha.size();

					for (int col = 0; col < lSize; col++) {
						if (linha[col] == '2') {
							objInimigo temp((col+1) * 20, lin*20, esqDir, 4, 0);
							printf("X: %.f Y: %.f \n", temp.x, temp.y);
							inimigos[count] = temp;
						}
						else if (linha[col] == '3') {
							objInimigo temp((col+1)*20, lin*20, cimaBaixo, 4, 0);
							printf("X: %.f Y: %.f \n", temp.x, temp.y);
							inimigos[count] = temp;
						}
						count++;
					}
					lin++;
				}
			}
		}

		//acha o arquivo do nivel
		string acharNivel(int level) {
			string levelStg;
			printf("Procurando o arquivo \n");
			switch (level) {
			case 1:
				levelStg = "levels/lv01.txt";
				printf("Achou o lv01 \n");
				break;

			case 2:
				levelStg = "levels/lv02.txt";
				printf("Achou o lv02 \n");
				break;
			}

			return levelStg;
		}
};
