//DANIEL FIENI PEREIRA
#include "lista.h"

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "Portuguese");
	
	FILE *arq;
	int i, tamanho;
	long long int matricula;
	char nome[100];
	char line[256];

	tamanho = file_size();
	
	arq = fopen("nomeArquivo.txt", "r");
	if (arq == NULL){
		printf("Problemas na CRIACAO do arquivo\n");
    	return 1;
	}
	
	TLista vetor[tamanho];
	
	//Inicilizar a tabela hash
	inicializa_vetor(&vetor, tamanho);
		
	while( fgets(nome, sizeof(line), arq)) {
		fscanf(arq, "%lld\n", &matricula);
		insere_vetor_arquivo(&vetor, tamanho, matricula, nome);
	}	
	
	fclose(arq);
	
	int op;
	do {
		op = menu();
		switch (op){
			case 1: insere_vetor_input(&vetor, tamanho); break;
			case 2: exibir_vetor(&vetor, tamanho); break;
			case 3: excluir_vetor(&vetor, tamanho); break;
			case 4: buscar_vetor(&vetor, tamanho); break;
			case 5: salvar_arquivo(&vetor, tamanho);
		}
	} while(op != 0);
		
	
	return 0;
}


