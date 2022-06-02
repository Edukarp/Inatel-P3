#include <iostream>
#include <iomanip>
using namespace std;

struct treenode
{
	int info;
	treenode *esq;
	treenode *dir;
};

typedef treenode* treenodeptr;

void tInsere(treenodeptr &p, int x)
{
	if (p == NULL) // insere na raiz
	{
		p = new treenode;
		p->info = x;
		p->esq = NULL;
		p->dir = NULL;
	}
	else if (x < p->info)
		tInsere(p->esq, x); // insere na subarvore esquerda
	else
		tInsere(p->dir, x);  // insere na subarvore direita
}

void contaPreOrdem (treenodeptr arvore, float &N)
{
	if (arvore != NULL)
	{
		contaPreOrdem(arvore->esq, N);
		contaPreOrdem(arvore->dir, N);
		N = N + arvore->info;
		
	}
}

//retorna a Media dos nos
float contaMedia(treenodeptr arvore)
{
	float N = 0;//contador da media

	contaPreOrdem(arvore, N);

	return N;
}

int main(int argc, char *argv[])
{
	treenodeptr arvore = NULL; //ponteiro para a arvore
	int x;
	float n;
	int quant = 0;//quantidade de nos

	cin >> x;
	while(x != -1)
	{
		quant++;
		tInsere(arvore, x);
		cin >> x;
	}

	n = contaMedia(arvore);

	cout << "Media: " << fixed << setprecision(2) << (float)n/quant << endl;

	return 0;
}