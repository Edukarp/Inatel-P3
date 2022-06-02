#include <iostream> // Entrada e saida
#include <climits> // INT_MAX
#include <stdio.h>

using namespace std;

//Struct para identificação de cada item
struct item
{
	int address; //aonde o produto deve ser entregue
	int val; // valor do item
	int peso; // peso do item
	bool pego; //verifica se o item foi pego ou nao (0-> nao pego, 1->pego)
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
	int tempo_total;//Tempo final de cada entregador
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
	cout << "o entregador usado no momento sera o " << pos_entregador_mais_caro  << endl;
	teste[pos_entregador_mais_caro].usado = true;

	////////////////////Entregas///////////////////////////

	item v[100];
	int numero_entregas; //número de entregas
	int menor, pos_menor; //escolhendo as menores entregas
	int cont = 1; //contador da posicao na mochila
	int capacidade_ocupada = 0; //capacidade a ser usada na viagem

	cout << "Entre com o numero de entregas" << endl;
	cin >> numero_entregas;

	//Atribuindo peso e endereco do item a ser entregue
	for(int i = 1; i <= numero_entregas; i++)
	{
		cout << "Entre com peso da entrega " << i << endl;
		cin >> v[i].peso;
		v[i].address = i;
	}
	//Atribuindo nao pego a todos os produtos
	for(int i = 1; i <= numero_entregas; i++)
		v[i].pego = false;

	//Pegando as Entregas de Menor peso
	for(int j = 1; j <= numero_entregas; j++)
	{
		menor = INT_MIN;
		pos_menor = -1;
		for(int i = 1; i <= numero_entregas; i++)
		{
			if(v[i].pego == false && v[i].peso > menor && (capacidade_ocupada + v[i].peso) < capacidade_entregadores)
			{
				menor = v[i].peso;
				pos_menor = i;
			}
		}
		if(pos_menor != -1)
		{
			na_mochila[cont] = v[pos_menor].address;
			v[pos_menor].pego = true;
			capacidade_ocupada += v[pos_menor].peso;
			cont++;
		}
	}


///////////////////////Percurso//////////////////////////////////

	int entregas[100][100]; // custo[i][j] = custo de ir da entrega 'i' para a entrega 'j'

//Definindo Locais de entrega de cada item e seu custo
	for(int i = 1; i <= numero_entregas; i++)
	{
		for(int j = i + 1; j <= numero_entregas; j++)
		{
			cout << "Entre com o custo de ir da cidade " << i << " para a cidade " << j << endl;
			cin >> entregas[i][j];
			entregas[j][i] = entregas[i][j]; // Custo de i->j = custo de j->i
		}
	}

	bool vis[100]; // marca se ja visitou ou nao uma cidade
	int numero_cidades = numero_entregas; // quantidade de cidades
	int cidade_inicial = 0; //primeiro e último ponto do percurso(supermercado)
	int cidade_atual; // cidade atual
	int proxima_cidade; // proxima cidade
	int caminhos[100];
	int cont2 = 1; //contador dos caminhos realizados
	int tempo_aux[100]; //vetor aux para encontrar o caminho mais rapido
	int aux; //aux para encontrar o caminho mais rapido

	tempo_total = valor_entregador_mais_caro; //Estabelecendo tempo de chegar ao supermercado

// inicializando vetor vis (nenhuma cidade foi visitada no inicio)
	for(int i = 1; i <= numero_cidades; i++)
		vis[i] = false;

	cidade_atual = cidade_inicial; //Definindo a primeira cidade

	for(int i = 1; i <= numero_cidades - 1; i++)
	{
		if(cidade_atual != true)
		{
			//Definindo a validacao no comeco para "pular" a cidade inicial
			vis[cidade_atual] = true; //Validando que a cidade atual ja foi visitada
			for(int j = 1; j <= cont; j++)
			{
				tempo_aux[j] = 0;
				if(na_mochila[j] == v[i].address)
				{
					proxima_cidade = v[i].address;
					cidade_atual = proxima_cidade;
					tempo_aux[j] += entregas[i][j];
				}
			}
			for(int j = 1; j <= cont; j++)
			{
				if(tempo_aux[j] != 0  && tempo_aux[j] > tempo_aux[j + 1])
				{
					aux = tempo_aux[j + 1];
					tempo_aux[j + 1] = tempo_aux[j];
					tempo_aux[j] = aux;
				}
			}
			for(int j = 1; j <= cont; j++)
			{
				tempo_total += tempo_aux[j];
				caminhos[cont2] = v[i].address;
				cont2++;
			}
		}
	}
	/*

	// guloso
		menor_custo = 0;
		cidade_atual = cidade_inicial; //Definindo a primeira cidade

		for(int i = 0; i < numero_cidades - 1; i++) // n-1 vezes = qnt de caminhos (exceto a volta para a cidade inicial)
		{
			//Definindo a validacao no comeco para "pular" a cidade inicial
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

	*/
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
	cout << "O Entregador: [" << pos_entregador_mais_caro << "] realizou as entregas: ";
	for(int i = 1; i <= cont; i++)
		cout << na_mochila[i] << ", ";
	cout << "em " << tempo_total << " minutos, no trajeto: ";
	for(int i = 1; i <= cont2; i++)
		cout << caminhos[i] << " ";
	cout << endl;

	return 0;
}
