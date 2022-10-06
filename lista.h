#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>

typedef struct tipoElemento{
	long long int valor; //Matricula
	char nome[100];
	struct tipoElemento *prox;
}TElemento;

typedef struct TipoLista{
	TElemento *inicio;
	TElemento *fim;
	int total;
}TLista;

void inicializa_fila(TLista *vetor);
void inicializa_vetor(TLista *vetor, int tamanho);

int file_size();
int hash_function(long long int input, int tamanho);
int menu();

void insere(TLista *lista, long long int matricula, char nome[]);
void insere_vetor_arquivo(TLista *vetor, int tamanho, long long int matricula, char nome[]);
void insere_vetor_input(TLista *vetor, int tamanho);

void exibir_lista(TLista *lista);
void exibir_vetor(TLista *vetor, int tamanho);

void excluirElemento(TLista *lista, long long int input);
void excluir_vetor(TLista *vetor, int tamanho);

void buscar_valor(TLista *lista, long long int argumento, int posicao);
void buscar_vetor(TLista *vetor, int tamanho);

int buscar_elemento(TLista *lista, long long int matricula);
int salvar_arquivo(TLista *vetor, int tamanho);



