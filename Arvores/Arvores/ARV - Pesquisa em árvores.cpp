#include <iostream>
using namespace std;

struct treenode
{
	int info;
	treenode *esq; //ponteiro para a folha esqueda
	treenode *dir; //ponteiro para a folha direita
};
typedef treenode* treenodeptr; //typedef -> cria um novo tipo de variavel

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
treenodeptr tPesq(treenodeptr p, int x)
{
	if (p == NULL) //elemento nao encontrado
		return NULL;
	else if (x == p->info) //elemento encontrado na raiz
		return p;
	else if (x < p->info) //procura na sub arvore esquerda
		return tPesq(p->esq, x);
	else //procura na sub arvore direita
		return tPesq(p->dir, x);
}
int main(int argc, char *argv[])
{

	//treenode *arvore = NULL; //ponteiro para a raiz = NULL *IMPORTANTE APONTAR*
	treenodeptr arvore = NULL; //o treenodeptr já é uma variavel ponteiro de treenode entao substirui do de cima
	int x; //var aux para inseir os dados
	int y; //var aux para inseir o numero a ser encontrado
	int n; //numero de elementos na arvore

	treenodeptr aux;

	cin >> n;

	for(int i = 0; i < n; i++)
	{
		cin >> y;
		tInsere(arvore, y);
	}
	cin >> y;

	aux = tPesq(arvore, y);
	if(aux != NULL)
		cout << "Encontrado" << endl;
	else
		cout << "Nao encontrado" << endl;
	return 0;
}
