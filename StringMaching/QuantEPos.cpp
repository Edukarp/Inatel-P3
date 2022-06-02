#include <iostream>
#include <cmath>
#include <cstring>

using namespace std;

void rabin_karp(char T[], char P[], int tamT, int tamP, int d, int q) //!!! d = Cardinalidade
{

	int h; // valor utilizado para calculo de hash
	int p = 0; // padrao convertido para inteiro
	int t = 0; // texto convertido para inteiro
	int quant = 0; //quant de vezes que ocorreu
	int pos; //posicao da ultima ocorrencia

	for(int i = 0; i < tamP; i++)
	{
		p = (d * p + (P[i]-'0')) % q; // converte o padrao
		t = (d * t + (T[i]-'0')) % q; // converte o texto para o primeiro valor (t0)
	}
	
	h = (int)pow(d, tamP - 1) % q; // utilizado para calculo de hash
	
	for(int i = 0; i <= tamT - tamP; i++)
	{
		if(p == t) // Se encontrei um valor de hash valido
		{
			// Verifico se ha diferencas
			int j;
			for(j = 0; j < tamP; j++)
			{
				if(P[j] != T[i + j])
				{
					break;
				}
			}

			if(j == tamP){
				quant++;
				pos = i;
			}
		}

		if(i < tamT - tamP) // se ainda nao cheguei no final
		{
			t = (d * ( t - (T[i]-'0') * h ) + (T[i + tamP]-'0')) % q; // atualizo o ti para ti+1
			if(t < 0) t += q;
		}
	}
	
	if(quant == 0)
		cout << quant << " ocorrencia(s)" << endl;
	else{
		cout << "Ultima ocorrencia: posicao " << pos << endl;
		cout << quant << " ocorrencia(s)" << endl;
	}

}

int main()
{
	char T[100];
    char P[100]; 
	int tamT; 
	int tamP; 
	int d; 
	int q = 13;
	
	cin >> tamT >> tamP;
	cin.ignore();
	cin.getline(T, 100);
	cin.getline(P, 100);
	
	d = strlen(T);
	
	rabin_karp(T, P, tamT, tamP, d, q);
	
	return 0;
}