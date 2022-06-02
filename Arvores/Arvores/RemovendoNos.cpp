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

//Ordena em ordem crescente
void emOrdem (treenodeptr arvore)
{
	if (arvore != NULL)
	{
		emOrdem(arvore->esq);
		cout << arvore->info << " ";
		emOrdem(arvore->dir);
	}
}

treenodeptr tMenor(treenodeptr &raiz)
{
	treenodeptr t;
	t = raiz;
	if (t->esq == NULL) // encontrou o menor valor
	{
		raiz = raiz->dir;
		return t;
	}
	else // continua a busca na sub arvore esquerda
		return tMenor(raiz->esq);
}

//Remove e realoca um no especifico da arvore
int tRemove(treenodeptr &raiz, int x)
{
	treenodeptr p;
	if (raiz == NULL) // ´arvore vazia
		return 1;
	if (x == raiz->info)
	{
		p = raiz;
		if (raiz->esq == NULL) // a raiz n~ao tem filho esquerdo
			raiz = raiz->dir;
		else
		{
			if (raiz->dir == NULL) // a raiz n~ao tem filho direito
				raiz = raiz->esq;
			else // a raiz tem ambos os filhos
			{
				p = tMenor(raiz->dir);
				raiz->info = p->info;
			}
		}
		delete p;
		return 0;
	}
	else
	{
		if (x < raiz->info)
			return tRemove(raiz->esq, x);
		else
			return tRemove(raiz->dir, x);
	}
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
	int n;//no a ser removido
	int aux;

	cin >> x;
	while(x != 0)
	{
		tInsere(arvore, x);
		cin >> x;
	}

	cin >> n;
	
	//Enquanto houver no valor n na arvore deve remiver
	aux = tRemove(arvore, n);
	while(aux == 0)
		aux = tRemove(arvore, n);

	emOrdem(arvore); //organizando e mostrando
	
	tDestruir(arvore);//Delete Arvore

	return 0;
}
