#include <iostream>
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

void contaPreOrdem (treenodeptr arvore, int &N)
{
	if (arvore != NULL)
	{
		N++;
		contaPreOrdem(arvore->esq, N);
		contaPreOrdem(arvore->dir, N);
	}
}

//retorna o numero de nos da arvore
int contaNos(treenodeptr arvore){
	int N = 0;//contador de numero de nos da arvore
		
	contaPreOrdem(arvore, N);
	
	return N;
}

int main(int argc, char *argv[])
{
	treenodeptr arvore = NULL; //ponteiro para a arvore
	int x;
	int n;

	cin >> x;
	while(x != 0)
	{
		tInsere(arvore, x);
		cin >> x;
	}
	
	n = contaNos(arvore);
	
	cout << n << " nos" << endl;

	return 0;
}