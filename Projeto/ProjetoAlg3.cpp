#include <iostream> // Entrada e saida
#include <climits> // INT_MAX

using namespace std;

//Struct para identificação de cada item
struct item
{
	int address; //aonde o produto deve ser entregue
	int val; // valor do item
	int peso; // peso do item
	int pego; //verifica se o item foi pego ou nao (0-> nao pego, 1->pego nao entregue, 2-> pego entregue)
};

//Struct para identificação dos entregadores
struct entregadores
{
	int n_entregador;
	int valor_ida_supermercado;
	bool usado;
};

int main()
{
	///////////////Entregadores////////////////////////////

	int capacidade_entregadores;
	int numero_entregadores;
	int tempo_total[100];//Tempo final de cada entregador
	int na_mochila[100]; //quais itens estao na mochila

	cout << "Qual o numero de entregadores? " << endl;
	cin >> numero_entregadores;

	cout << "Entre com a capacidade dos Entregadores" << endl;
	cin >> capacidade_entregadores;

	entregadores teste[numero_entregadores];

	//Numerando os entregadores e atribuindo o tempo de ir ao supermercado
	for(int i = 1; i <= numero_entregadores ; i++)
	{
		teste[i].n_entregador = i;
		cout << "Qual o tamanho do percurso para o entregador " << i << " para ir ao supermercado?" << endl;
		cin >> teste[i].valor_ida_supermercado;
	}

	//Atribuindo nao "usado" a todos os entregadores
	for(int i = 1; i <= numero_entregadores; i++)
		teste[i].usado = false;

	int valor_entregador_mais_caro = INT_MIN; //definindo int_Min para encontar o mais longe
	int pos_entregador_mais_caro; //posicao do entregador mais longe

	//Encontrando o mais longe e validando
	for(int i = 1; i <= numero_entregadores ; i++)
	{
		if((teste[i].valor_ida_supermercado > valor_entregador_mais_caro) && (teste[i].usado == false))
		{
			valor_entregador_mais_caro = teste[i].valor_ida_supermercado;
			pos_entregador_mais_caro = teste[i].n_entregador;
		}
	}
	cout << "o entregador usado no momento será o " << pos_entregador_mais_caro  << endl;
	teste[pos_entregador_mais_caro].usado = true;

	////////////////////Entregas///////////////////////////

	int pd[100][100]; //Quanto tem e quanto pode usar(na mochila)
	item v[100];
	int entregas[100][100]; // custo[i][j] = custo de ir da entrega 'i' para a entrega 'j'
	int numero_entregas; //número de entregas
	int caminho[100][100]; 	// utilizado para recuperar quais itens foram escolhidos(0 -> nao pegar o item, 1 -> pegar o item)

	cout << "Entre com o numero de entregas" << endl;
	cin >> numero_entregas;

	//Atribuindo valor e peso do item a ser entregue
	for(int i = 1; i <= numero_entregas; i++)
	{
		cout << "Entre com o valor e peso da entrega " << i << endl;
		cin >> v[i].val >> v[i].peso;
		v[i].address = i;
	}
	//Atribuindo nao pego a todos os produtos
	for(int i = 1; i <= numero_entregas; i++)
		v[i].pego = 0;

	//Algoritimo da Mochila
	// CASO BASE:
	// olhando do ultimo item para frente, val. maximo = 0
	for(int j = 0; j <= capacidade_entregadores; j++)
		pd[numero_entregas][j] = 0;

	// olhando tendo uma mochila de capacidade 0, o val. maximo=0
	for(int i = 0; i <= numero_entregas; i++)
		pd[i][0] = 0;

	// CASO GERAL
	for(int i = numero_entregas - 1; i >= 0; i--)
	{
		for(int j = 1; j <= capacidade_entregadores; j++)
		{
			int pega, npega; // val. para caso eu pegar ou nao pegar o item 'i'
			if(v[i].pego == false)
			{
				npega = pd[i + 1][j]; // olhar o proximo item, mantendo a capacidade 'j'

				if(j >= v[i].peso) // se eu tiver capacidade disponivel p/ pegar o item 'i'
					pega = pd[i + 1][j - v[i].peso] + v[i].val;
				// olho o proximo item, subtraio o peso da capacidade
				// disponivel, e somo o valor do item 'i'
				else
					pega = 0; // se nao posso pegar, o valor eh 0

				if(pega > npega) // se valer a pena pegar
				{
					pd[i][j] = pega;
					caminho[i][j] = 1;
				}

				else // se valer a pena nao pegar
				{
					pd[i][j] = npega;
					caminho[i][j] = 0;
				}
			}
		}

	}

// Comeca na posicao final
	int x, y, z; //contadores auxiliares
	x = 0; // do item 0->final
	z = 1; //posicao inicial da mochila
	y = capacidade_entregadores; //para uma mochila de capacidade max

	while(x != numero_entregas)  //enquanto nao chegar no ultimo item
	{
		if(caminho[x][y] == 0) // se nesse momento a melhor opcao foi nao pegar eu nao pego
			x++; // avanca para o proxima posicao, mantendo a capacidade

		else // if(caminho[i][j] == 1) /// se nesse momento a melhor opcao for pegar, eu pego
		{
			cout << pos_entregador_mais_caro << " Entregou o produto: ";
			na_mochila[z] = x; //indicando qual item esta na mochila
			y -= v[x].peso; // diminuo a capacidade disponivel
			x++; // avanco para o proxima posicao
			v[x].pego = 1; //Foi entregue
			z++; //avanca a mochila
		}
	}

///////////////////////Percurso//////////////////////////////////

//Definindo Locais de entrega de cada item e seu custo
	for(int i = 1; i <= numero_entregas; i++)
	{
		for(int j = i + 1; j < numero_entregas; j++)
		{
			cout << "Entre com o custo de ir da entrega " << i << " para a entrega " << j << endl;
			cin >> entregas[i][j];
			entregas[j][i] = entregas[i][j]; // Custo de i->j = custo de j->i
		}
	}

	bool vis[100]; // marca se ja visitou ou nao uma cidade
	int numero_cidades = numero_entregas; // quantidade de cidades
	int menor_custo; // menor custo da viagem
	int custo_at; // menor custo atual
	int cidade_inicial = 0; //primeiro e último ponto do percurso(supermercado)
	int cidade_atual; // cidade atual
	int proxima_cidade; // proxima cidade


// inicializando vetor vis (nenhuma cidade foi visitada no inicio)
	for(int i = 0; i < numero_cidades; i++)
		vis[i] = false;

// guloso
	menor_custo = 0;
	cidade_atual = cidade_inicial; //Definindo a primeira cidade

	for(int i = 0; i < numero_cidades - 1; i++) // n-1 vezes = qnt de caminhos (exceto a volta para a cidade inicial)
	{
		//Definindo a validacao no comeco para "pualr" a cidade inicial
		vis[cidade_atual] = true; //Validando que a cidade atual ja foi visitada

		// encontrar qual a proxima cidade mais proxima
		custo_at = INT_MAX;
		for(int j = 0; j < numero_cidades; j++)
		{
			if(!vis[j] && custo_at > entregas[cidade_atual][j])
			{
				proxima_cidade = j;
				custo_at = entregas[cidade_atual][j];
			}
		}
		menor_custo += custo_at;
		cidade_atual = proxima_cidade;
	}
	menor_custo += entregas[cidade_atual][cidade_inicial];
	cout << "Menor custo = " << menor_custo << endl;

//////////////SAIDAS////////////////////////

//Mostrando quais itens o Entregador vai levar

	/*
	// Comeca na posicao final
	int aux1, aux2;
	aux1 = 0; // do item 0->final
	aux2 = capacidade_entregadores; // para uma mochila de capacidade max

	while(aux1 != numero_entregas)  // enquanto eu nao chegar no ultimo item
	{
		if(caminho[aux1][aux2] == 0) // se nesse momento a melhor opcao foi nao pegar eu nao pego
			aux1++; // avanca para o proxima posicao, mantendo a capacidade

		else // if(caminho[i][j] == 1) /// se nesse momento a melhor opcao for pegar, eu pego
		{
			cout << pos_entregador_mais_caro << " Entregou o produto: ";
			cout << aux1; //indicando qual item
			cout << " de Peso:" << v[aux1].peso;
			cout << " e Valor:" << v[aux1].val << endl;
			cout << "---------------------" << endl;
			aux2 -= v[aux1].peso; // diminuo a capacidade disponivel
			aux1++; // avanco para o proximo i
			v[aux1].pego = 1; //Foi entregue
		}
	}
	*/
	return 0;
}
