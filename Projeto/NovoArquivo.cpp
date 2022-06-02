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
		preOrdem(arvore->esq);
		preOrdem(arvore->dir);
	}
}

void emOrdem (treenodeptr arvore)
{
	if (arvore != NULL)
	{
		emOrdem(arvore->esq);
		emOrdem(arvore->dir);
	}
}

void posOrdem (treenodeptr arvore)
{
	if (arvore != NULL)
	{
		posOrdem(arvore->esq);
		posOrdem(arvore->dir);
	}
}


treenodeptr tPesq(treenodeptr p, int x, int &cont)
{
	if (p == NULL) //elemento nao encontrado
		return NULL;
	else if (x == p->info) //elemento encontrado na raiz
		return p;
	else if (x < p->info)  //procura na sub arvore esquerda
	{
		cont++;
		return tPesq(p->esq, x, cont);
	}
	else  //procura na sub arvore direita
	{
		cont++;
		return tPesq(p->dir, x, cont);
	}
}

int encontraPosicao(treenodeptr arvore, int v)
{
	int cont = 0;
	if(tPesq(arvore, v, cont) != NULL)
		return cont;
	else
		return -1;
}

int main(int argc, char *argv[])
{
	treenodeptr arvore = NULL; //ponteiro para a arvore
	int x;
	int v, aux, aux1, aux2;
	treenodeptr auxArvore;
	cin >> x;
	while(x != -1)
	{
		tInsere(arvore, x);
		cin >> x;
	}

	//Percurso pre-ordem
	auxArvore = preOrdem(arvore);
	aux = encontraPosicao(auxArvore, v);

	//Percurso em-ordem
	auxArvore = emOrdem(arvore);
	aux1 = encontraPosicao(auxArvore, v);

	//Percurso pos-ordem
	auxArvore = posOrdem(arvore);
	aux2 = encontraPosicao(auxArvore, v);

	if(aux <= aux1 && aux <= aux2)
		cout << "Pre" << endl;
	else if(aux1 <= aux && aux1 <= aux2)
		cout << "Em" << endl;
	else if(aux2 <= aux && aux2 <= aux1)
		cout << "Pos" << endl;
	return 0;
}
