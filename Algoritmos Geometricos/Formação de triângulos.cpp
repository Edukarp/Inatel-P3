#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

struct ponto
{
	int x;
	int y;
};
typedef ponto vetor; //Definindo "ponto" como "vetor"

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

//Area do Triangulo
float area_triangulo(ponto A, ponto B, ponto C)
{
	vetor AB;
	vetor AC;
	float area;

	AB = cria_vetor(A, B);
	AC = cria_vetor(A, C);
	area = fabs(vetorial(AB, AC)) / 2.0; //abs -> modulo, fbs -> modulo de float (cmath)

	return area;
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
	int n; //numero de casos
	ponto A, B, C;

	cin >> n;

	for(int i = 0; i < n; i++)
	{
		cin >> A.x >> A.y;
		cin >> B.x >> B.y;
		cin >> C.x >> C.y;

		if(sentido(A, B, C) != 0)
		{
			cout << fixed << setprecision(2) << area_triangulo(A, B, C) << endl;
		}
		else
			cout << "Nao formam triangulo" << endl;
	}

	return 0;
}
