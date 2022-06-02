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
treenodeptr pMenor(treenodeptr arvore)
{
	if (arvore->esq != NULL)
		pMenor(arvore->esq);
	else
		return arvore;
}
treenodeptr pMaior(treenodeptr arvore)
{
	if (arvore->dir != NULL)
		pMaior(arvore->dir);
	else
		return arvore;

}

int main(int argc, char *argv[])
{
	treenodeptr arvore = NULL; //ponteiro para a arvore
	int x;
	treenodeptr m, M; //menor e maior

	cin >> x;
	while(x != -1)
	{
		tInsere(arvore, x);
		cin >> x;
	}

	m = pMenor(arvore);
	M = pMaior(arvore);

	cout << m->info << " e " << M->info << endl;

	return 0;
}
