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

//Ordena em ordem decrescente
void emOrdemInversa (treenodeptr arvore)
{
	if (arvore != NULL)
	{
		emOrdemInversa(arvore->dir);
		cout << arvore->info << " ";
		emOrdemInversa(arvore->esq);
	}
}

int main(int argc, char *argv[])
{
	treenodeptr arvore = NULL; //ponteiro para a arvore
	int x;

	cin >> x;
	while(x != -1)
	{
		tInsere(arvore, x);
		cin >> x;
	}
	
	emOrdemInversa(arvore);
	
	return 0;
}
