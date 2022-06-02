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

void preOrdem (treenodeptr arvore)
{
	if (arvore != NULL)
	{
		cout << arvore->info << endl;
		preOrdem(arvore->esq);
		preOrdem(arvore->dir);
	}
}

void emOrdem (treenodeptr arvore)
{
	if (arvore != NULL)
	{
		emOrdem(arvore->esq);
		cout << arvore->info << endl;
		emOrdem(arvore->dir);
	}
}
void posOrdem (treenodeptr arvore)
{
	if (arvore != NULL)
	{
		posOrdem(arvore->esq);
		posOrdem(arvore->dir);
		cout << arvore->info << endl;
	}
}

int main(int argc, char *argv[])
{
	treenodeptr arvore = NULL; //ponteiro para a arvore
	int x;

	cin >> x;
	while(x != 0)
	{
		tInsere(arvore, x);
		cin >> x;
	}

	//Percurso pre-ordem
	cout << "Pre-ordem: " << endl;
	preOrdem(arvore);

	//Percurso em-ordem
	cout << "Em ordem: " << endl;
	emOrdem(arvore);

	//Percurso pos-ordem
	cout << "Pos-ordem: " << endl;
	posOrdem(arvore);
	return 0;
}
