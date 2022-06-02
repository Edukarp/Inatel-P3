#include <iostream>
using namespace std;

struct treenode //arvore
{
	int info;
	treenode *esq; //ponteiro para a folha esqueda
	treenode *dir; //ponteiro para a folha direita
};
typedef treenode* treenodeptr; //typedef -> cria um novo tipo de variavel

//funcao que insere na arvore
void tInsere(treenodeptr &p, int x)
{
	if (p == NULL) //insere na raiz
	{
		p = new treenode;
		p->info = x;
		p->esq = NULL;
		p->dir = NULL;
	}
	else if (x < p->info) //insere na subarvore esquerda
		tInsere(p->esq, x);
	else //insere na subarvore direita
		tInsere(p->dir, x);
}

//Ordena em ordem decrescente
void emOrdem (treenodeptr arvore, int &maiorPar)
{
	if (arvore != NULL)
	{
	    //verificando se o maior par esta no começo
		if(arvore->info > maiorPar && arvore->info % 2 == 0)
			maiorPar = arvore->info;
		
		emOrdem(arvore->dir, maiorPar);
		emOrdem(arvore->esq, maiorPar);
		
		//verificando se o maior par esta no final
		if(arvore->info > maiorPar && arvore->info % 2 == 0)
			maiorPar = arvore->info;
	}
}

//funcao para encontrar o maior par
int maiorPar(treenodeptr arvore)
{
	int maior = -999999;//maior par como INT_MIN

    //chamando a funcao emOrdem para percorrer toda a arvore
	emOrdem(arvore, maior);

	return maior;
}

//Destroi a arvore(delete)
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
	int x;//valor a ser inserido
	int M; //maior valor

	cin >> x;
	while(x != -1)
	{
		tInsere(arvore, x);
		cin >> x;
	}
    
	M = maiorPar(arvore);//Recebendo o maior valor par

	cout << M << endl; // Mostrando o maior valor par

	tDestruir(arvore);//Deletando memoria da arvore

	return 0;
}