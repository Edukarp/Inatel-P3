#include <iostream>
#include <list>
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

void emNivel(treenodeptr t, int &soma)
{
	treenodeptr n;
	list<treenodeptr> q;
	if(t != NULL)
	{
		q.push_back(t);
		while(!q.empty())
		{
			n = *q.begin();
			q.pop_front();
			if(n->esq != NULL)
				q.push_back(n->esq);
			if(n->dir != NULL)
				q.push_back(n->dir);
			soma = soma + n->info;
		}
	}
}

int somaArvore(treenodeptr arvore){
	int soma = 0;
	
	emNivel(arvore, soma);
	
	return soma;
}

//Destroi a arvore(DELETE)
void tDestruir (treenodeptr &arvore)
{
	if (arvore != NULL)
	{
		tDestruir(arvore->esq);
		tDestruir(arvore->dir);
		delete arvore;
	}
	arvore = NULL;
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
	
	cout << somaArvore(arvore) << endl;
	tDestruir(arvore);//Delete Arvore

	return 0;
}