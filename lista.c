#include "lista.h"

// ============ Inicializar a tabela hash ============ //
void inicializa_fila(TLista *vetor){
	vetor->inicio = NULL;
	vetor->fim = NULL;
	vetor->total = 0;
}

void inicializa_vetor(TLista *vetor, int tamanho){
	int i;
	for(i = 0; i < tamanho; i++){
		//Inicializando todos os campos dos vetores
		inicializa_fila(&vetor[i]);
	}
}

// ============ Definindo o tamanho do arquivo ============ //
int file_size(){
	FILE *arq;
	char linha[100];
	int i, tamanho;
	
	arq = fopen("nomeArquivo.txt", "r");
	
	if (arq == NULL){
		printf("Problemas na CRIACAO do arquivo\n");
    	return 1;
	}
	
	//Percorre todo arquivo até o final, lendo todas as linhas
	while (fgets(linha, 100, arq)){
		i++;
	}

	tamanho = (i/2)*1.5;
	fclose(arq);
	
	return tamanho;
}

// ============ Retornar a posicao na tabela hash ============ //
int hash_function(long long int input, int tamanho){
	return input % tamanho;
}

// ============ Criacao do MENU ============ //
int menu(){
	int opcao;
	system("CLS"); 
    printf("\n\n\n\t=====| MENU |=====\n\n");
    printf("0 - SAIR (Encerrar Programa).\n\n");
    printf("1 - Inserir.\n");
    printf("2 - Exibir Lista Completa.\n");
    printf("3 - Excluir.\n");
    printf("4 - Buscar valor.\n");
    printf("5 - Salvar arquivo.\n");
    printf("\tInforme OPCAO desejada: ");
    
    scanf("%d",&opcao);
	
	if ((opcao > 5) || (opcao < 0)){
		printf("\n\n\n");
		printf("+-------------------------------+\n");
		printf("|ERRO  	------------------------|\n");
		printf("|Opção inválida	----------------|\n");
		printf("|Tente outra vez    ------------|\n");
		printf("+-------------------------------+\n\n\n");
		system("PAUSE");
	}
	return opcao;
}

// ============ Funcoes de INSERIR ============ //
void insere(TLista *lista, long long int matricula, char nome[]){
	TElemento *novo = (TElemento*)malloc(sizeof(TElemento));
	
	//Insere o valor sempre no início
	novo->valor = matricula;
	strcpy(novo->nome, nome);
	novo->prox = lista->inicio;
	
	lista->inicio = novo;
	lista->fim = novo;
	 
	lista->total++;
	
}

//Funcao para inserir no vetor através de arquivos.txt
void insere_vetor_arquivo(TLista *vetor, int tamanho, long long int matricula, char nome[]){
	int posicao_hash;
	//Retorna a posição do vetor onde o elemento será inserido
	posicao_hash = hash_function(matricula, tamanho);
	//Como o processo de inserir de um arquivo e parecido com o inserir manualmente, passei como parametro os 
	//elementos tirados do arquivo
	insere(&vetor[posicao_hash], matricula, nome);
}

// Funcao para inserir manualmente na tabela hash
void insere_vetor_input(TLista *vetor, int tamanho){
	int posicao_hash;
	long long int matricula;
	char nome[100];
	printf("Insira a matricula do usuario: ");
	scanf("%lld", &matricula);
	printf("Insira o nome do usuario: ");
	scanf(" %99[^\n]s" ,&nome);
	//Concatena o nome ao \n para não dar problema ao salvar o arquivo
	strcat(nome, "\n");
	posicao_hash = hash_function(matricula, tamanho);
	
	if (buscar_elemento(&vetor[posicao_hash], matricula) == 1){
		printf("\t\nElemento existente!! Tente novamente!\n\n\n");
		system("pause");
	}else {
		insere(&vetor[posicao_hash], matricula, nome);
	}
}

// ============ Exibir elementos da tabela Hash ============ //
void exibir_lista(TLista *lista){
	TElemento *atual = lista->inicio;
	int cont=0;
	while(atual != NULL){
		printf("(%d) - Valor: %lld\t %s\n" ,++cont, atual->valor, atual->nome);
		atual = atual->prox;
	}
	printf("\n\n");
}

void exibir_vetor(TLista *vetor, int tamanho){
	int i;
	for(i = 0; i < tamanho; i++){
		printf("Lista %d; Tamanho: %d\n" ,i, vetor[i].total);
		//É passado como parametro cada posição do vetor para ser listado no exibir_lista()
		exibir_lista(&vetor[i]);
	}
	system("pause");
}

// ============ Excluir elementos da tabela Hash ============ //
void excluirElemento(TLista *lista, long long int input){
	TElemento *atual=NULL, *anterior=NULL;
	int excluido = 0;
	
	if(lista->inicio == NULL){
		//Se a lista está vazia
		printf("\n\nNenhum elemento na lista\n\n\n");	
	}else {
		atual = lista->inicio;
		while(atual != NULL){
			//Vai percorrer até achar o elemento que pretende ser excluído
			if(atual->valor == input){
				excluido = 1;
				if(anterior == NULL){
					//Se o elemento for o primeiro da lista ele vai excluir, e o proximo valor será o primeiro
					lista->inicio = atual->prox;
				} else {
					anterior->prox = atual->prox;
					if(atual == lista->fim){
						//Se o elemento for o último da lista, ele irá excluí-lo e o fim será null
						lista->fim = NULL;
					}
				}
				//Liberando espaço na memória
				free(atual);
				lista->total--;
				break;
			}
			//O anterior recebe o atual porque quando um elemento do meio da lista for excluido, ele fará a ligação com o próximo elemento
			anterior = atual;
			atual = atual->prox;
		}
		if(!excluido){
			printf("\t\n\nElemento %lld não encontrado!!", input);
			printf("\t\n\nTente novamente\n\n\n");
		}
	}
	system("pause");
}

void excluir_vetor(TLista *vetor, int tamanho){
	int posicao_hash;
	long long int input;
	printf("\n\nInsira o valor que será removido: ");
	scanf("%lld" ,&input);
	posicao_hash = hash_function(input, tamanho);
	//Encontra a posição do vetor que o elemento está para ser excluído
	excluirElemento(&vetor[posicao_hash], input);
}

// ============ Funcoes de Buscar ============ //
void buscar_valor(TLista *lista, long long int argumento, int posicao){
	TElemento *atual = lista->inicio;
	int encontrado=0;
	
	if(lista->inicio == NULL){
		printf("\t\n\nFILA VAZIA!!\n\n\n");
	}
	else {
		while(atual != NULL){
			if(atual->valor == argumento){
				encontrado = 1;
				printf("\t\n\nElemento %lld encontrado!\n", argumento);
				printf("Nome: %s\n", atual->nome);
				printf("Lista: %d; tamanho: %d\n\n\n" ,posicao, lista->total);
			}
			atual = atual->prox;
		}
		
		if(!encontrado){
			printf("\t\n\nElemento %lld não encontrado!!", argumento);
			printf("\t\n\nTente novamente\n\n\n");
		}
	}
	system("pause");	
}

void buscar_vetor(TLista *vetor, int tamanho){
	int posicao_hash;
	long long int input;
	printf("\n\nInsira o valor que será pesquisado: ");
	scanf("%lld" ,&input);
	posicao_hash = hash_function(input, tamanho);
	buscar_valor(&vetor[posicao_hash], input, posicao_hash);
}

//Funcao para verificar se o elemento existe; Se o retorno for 1, esse elemento existe
int buscar_elemento(TLista *lista, long long int matricula){
	TElemento *atual = lista->inicio;
	while(atual != NULL){
		if (atual->valor == matricula){
			return 1;
		}
		atual = atual->prox;
	}
	return -1;
}

// ============ Funcao para salvar no arquivo ============ //
int salvar_arquivo(TLista *vetor, int tamanho){
	TElemento *elemento;
	int i, j, cont=0;
	FILE *arq;
		
	arq = fopen("nomeArquivo.txt", "wt");
	//Percorre todas as posições do vetor
	for(i = 0; i < tamanho; i++){
		//Em cada posição, o elemento sempre vai receber o primeiro da fila
		elemento = vetor[i].inicio;
		while (elemento != NULL){
			//Percorre a fila e insere no arquivo
			//Como utilizei o fgets para pegar o nome do arquivo não precisei utilizar o \n para quebrar linha
			//Por isso utilizei o strcat quando inseri manualmente, para não precisar fazer uma condição adicional
			fprintf(arq, "%s", elemento->nome);
			fprintf(arq, "%lld\n", elemento->valor);
			elemento = elemento->prox;
		}
	}

	fclose(arq);
	system("pause");
	
}
