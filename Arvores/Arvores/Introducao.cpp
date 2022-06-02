#include <iostream>
using namespace std;

struct treenode
{
	int info;
	treenode *esq; //ponteiro para a folha esqueda
	treenode *dir; //ponteiro para a folha direita
};

typedef treenode* treenodeptr; //typedef -> cria um novo tipo de variavel

int main(int argc, char *argv[])
{
	//treenode *arvore = NULL; //ponteiro para a raiz = NULL *IMPORTANTE APONTAR*
	treenodeptr arvore = NULL; //o treenodeptr já é uma variavel ponteiro de treenode entao substirui do de cima
	int x; //var aux para inseir dados

	x = 14;// raiz
	arvore = new treenode; //alocando memoria
	arvore->info = x; //preenchendo o campo info
	arvore->esq = NULL;
	arvore->dir = NULL;

	x = 4; //filho esquerdo
	arvore->esq = new treenode; //criando um novo no a esq da arvore
	(arvore->esq)->info = x;
	(arvore->esq)->esq = NULL;
	(arvore->esq)->dir = NULL;

	x = 18; //filho direito
	arvore->dir = new treenode; //criando um novo no a esq da arvore
	(arvore->dir)->info = x;
	(arvore->dir)->esq = NULL;
	(arvore->dir)->dir = NULL;

	//Mostrando a arvore
	cout << "raiz: " << arvore->info << endl;
	cout << "flho esquerdo: " << (arvore->esq)->info << endl;
	cout << "filho direito: " << (arvore->dir)->info << endl;
	
	return 0;
}
