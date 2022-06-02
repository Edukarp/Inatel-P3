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

//Verifica se o ponto P esta dentro do triangulo ABC
int dentro_triangulo(ponto A, ponto B, ponto C, ponto P)
{
	int s1,s2,s3;
	s1 = sentido(A,B,P);
	s2 = sentido(B,C,P);
	s3 = sentido(C,A,P);
	if(s1 == s2 && s2 == s3)
		return 1; 
	else if(s1*s3 == -1 || s1*s2 == -1 || s2*s3 == -1)
		return -1;
	else
		return 0;
}

float area_triangulo(ponto A,ponto B,ponto C)
{
	vetor AB;
	vetor AC;
	float area;
	AB = cria_vetor(A,B);
	AC = cria_vetor(A,C);
	area = fabs(vetorial(AB,AC)) / 2;
	return area;
}

// Os pontos devem estar ordenados pelo angulo
// O poligono deve ser convexo
// Retorna a area do poligono
float area_poligono(ponto v[],int n)
{
	float area = 0;
	for(int i = 0;i < n-2;i++)
	{
		area = area + area_triangulo(v[0],v[i+1],v[i+2]);
	}
	return area;
}

int main(int argc, char *argv[])
{
    int n = 6;
	ponto *v;
	
	v = new ponto [n];
	
	for(int i = 0;i<n;i++)
		cin >> v[i].x >> v[i].y;

	cout << " Area do escudo: " << fixed << setprecision(2) << area_poligono(v, n);

	return 0;
}