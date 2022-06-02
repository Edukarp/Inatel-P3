#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

struct ponto
{
	float x;
	float y;
};
typedef ponto vetor; //Definindo "ponto" como "vetor"

//Reta (infinito) e Segmento de reta (finito)
struct reta
{
	ponto A;
	ponto B;
};
typedef reta segmento;

//Criando um Vetor
vetor cria_vetor(ponto A, ponto B)
{

	vetor AB;
	AB.x = B.x - A.x;
	AB.y = B.y - A.y;

	return AB;
}

//Produto Vetorial
int vetorial(vetor A, vetor B)  //Considerando que z = 0, pois está em 2D
{
	int v;
	v = A.x * B.y - A.y * B.x;

	return v;
}

//Verificar a posicao de um ponto em relacao a um vetor
int sentido(ponto A, ponto B, ponto C)  //1->esquerda, -1 ->direita, 0 ->colinear
{
	vetor AB;
	vetor AC;
	int vet;

	AB = cria_vetor(A, B);
	AC = cria_vetor(A, C);
	vet = vetorial(AB, AC);

	if(vet > 0)
		return 1; //esquerda
	else if(vet < 0)
		return -1; //direita
	else
		return 0; //colinear
}

int main(int argc, char *argv[])
{
	ponto A, B, P;
	
	cin >> A.x >> A.y;
	cin >> B.x >> B.y;
	cin >> P.x >> P.y;

	if(sentido(A, B, P) == 1)
	{
		cout << "GOL!" << endl;
	}
	else
		cout << "NAO GOL!" << endl;

	return 0;
}
