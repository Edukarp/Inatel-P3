#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm> // sort
#include <list> // para a pilha 
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

// funcao para comparar dois pontos durante a ordenacao
bool cmp(ponto a,ponto b)
{
	// atan2((a.y - 0),(a.x - 0)) -> arco tangente[(a.y - 0)/(a.x - 0)]
	float angA = atan2(a.y,a.x);  
	float angB = atan2(b.y,b.x);
	if(angA == angB) // se os angulos forem iguais, desempata pelo mais longe
	{
		float distA = sqrt(pow(a.x,2)+pow(a.y,2)); // raiz[(a.x - 0)^2 + (a.y - 0)^2]
		float distB = sqrt(pow(b.x,2)+pow(b.y,2)); // raiz[(b.x - 0)^2 + (b.y - 0)^2]
		return distA > distB; // primeiro o de maior distancia
	}
	else
		return angA < angB; // primeiro o de menor angulo
}

// funcao para ordenar os pontos de acordo com o angulo formado com a horizontal
void ordena_pelo_angulo(ponto p[],int n)
{
	ponto pivot; // será o ponto mais abaixo
	int pos_pivot;
	// encontro o ponto mais abaixo para ser o pivot
	pivot = p[0];
	pos_pivot = 0;
	for(int i = 1;i < n;i++)
	{
		if(p[i].y < pivot.y)
		{
			pivot = p[i];
			pos_pivot = i;
		}
		else if(p[i].y == pivot.y && p[i].x < pivot.x)
		{
			pivot = p[i];
			pos_pivot = i;
		}
	}
	
	// coloca o pivot na posicao 0 do vetor
	p[pos_pivot]= p[0];
	p[0] = pivot;
	
	// desloca o pivot para (0,0), e os demais pontos em relacao ao pivot
	for(int i = 0;i < n; i++)
	{
		p[i].x -= pivot.x;
		p[i].y -= pivot.y;
	}
	
	// ordenacao
	sort(p + 1, p + n,cmp); //chamando a funcao cmd
	
	// desloca os pontos de volta a posicao original
	for(int i = 0;i < n;i++)
	{
		p[i].x += pivot.x;
		p[i].y += pivot.y;
	}
}

// penultimo da pilha 
ponto next_to_top(list <ponto> pilha)
{
	pilha.pop_back();
	return pilha.back();
}

// Encontra o fecho convexo de um conjunto de pontos
// retorna uma lista com os pontos que compoem o fecho convexo
list <ponto> Graham_scan(ponto p[],int n)
{
	list <ponto> pilha;
	
	ordena_pelo_angulo(p,n);
	
	//Os 3 primeiros sempre participarao do poligono(triangulo menor poligono)
	pilha.push_back(p[0]);
	pilha.push_back(p[1]);
	pilha.push_back(p[2]);
	
	int i = 3;
	while(i < n)
	{
		// curva a esquerda, adiciona
		if(sentido(next_to_top(pilha),pilha.back(),p[i]) == 1)
		{
			pilha.push_back(p[i]);
			i++;
		}
		// curva a direita (ou mesma linha), remove
		else
			pilha.pop_back();
	}
	return pilha;
}

int main(int argc, char *argv[])
{
	int n;
	ponto *v;
	list <ponto> fecho_convexo;
	
	cin >> n;
	
	v = new ponto [n];
	
	for(int i = 0;i<n;i++)
		cin >> v[i].x >> v[i].y;
	
	fecho_convexo = Graham_scan(v,n);
	
	cout << fecho_convexo.size() << " lados" << endl;
	
	delete v;
	
	return 0;
}