#include <iostream>
#include <cmath>
using namespace std;

struct ponto
{
	int x;
	int y;
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

//Produto Escalar
int escalar(vetor A, vetor B)
{
	int e;
	e = A.x * B.x + A.y * B.y;

	return e;
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

//Verificar se um ponto pertence ou nao a um triangulo
int dentro_triangulo(ponto A, ponto B, ponto C, ponto P)  //1->dentro, -1->fora, 0->na linha
{
	int s1, s2, s3;
	s1 = sentido(A, B, P);
	s2 = sentido(A, C, P);
	s3 = sentido(C, A, P);

	if(s1 == s2 && s2 == s3)
		return 1; //dentro do triangulo ABC
	else if(s1*s3 == -1 || s1*s2 == -1 || s2*s3 == -1)
		return -1; //fora do triangulo ABC
	else
		return 0; //em alguma linha do triangulo ABC
}

//Area de Poligono
float area_poligono(ponto v[], int n)  //deve ser convexo e os pontos ordenados radialmente(ABCD... na ordem)
{
	float area = 0;
	for(int i = 0; i < n - 2; i++)
		area = area + area_triangulo(v[0], v[i + 1], v[i + 2]);

	return area;
}

//Verificar se um ponto pertence a um segmento
bool ponto_segmento(segmento S, ponto P)
{
	if(sentido(S.A,S.B,P) != 0)
		return false;
	else if(P.x > S.A.x && P.x < S.B.x)
		return true;
	else if(P.x < S.A.x && P.x > S.B.x)
		return true;
	else if(P.y < S.A.y && P.y > S.B.y)
		return true;
	else if(P.y > S.A.y && P.y < S.B.y)
		return true;
	else
		return false;
}

int main(int argc, char *argv[])
{


	return 0;
}
