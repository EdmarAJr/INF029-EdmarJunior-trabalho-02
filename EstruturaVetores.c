/* para compilar
gcc mainTeste.c EstruturaVetores.c -o teste
gcc main.c EstruturaVetores.c -o teste
*/
#include <stdio.h>
#include <stdlib.h>
#include "EstruturaVetores.h"
#define TAM 10

typedef struct celula {
	int *posicao;
	int contador;
	int tamanho;
} Celula;

Celula vetorPrincipal[TAM];

int verificarEstrutura(int posicao){
	if(vetorPrincipal[posicao-1].posicao != NULL) return 1;
	return 0;
}

int ehPosicaoValida(int posicao){
	if(posicao < 1 || posicao > 10)	return 0;
	return 1;
}

int verificarEspaco(int posicao){
	int diferenca = vetorPrincipal[posicao-1].tamanho - vetorPrincipal[posicao-1].contador;
	
	if(diferenca > 0) return diferenca;
	return 0;
}

int verficarValor(int posicao, int valor) {
	for (int i = 0; i < vetorPrincipal[posicao-1].tamanho; i++)
		if(vetorPrincipal[posicao-1].posicao[i] == valor) return i;	
	return -1;
}

int criarEstruturaAuxiliar(int posicao, int tamanho){
	if(!ehPosicaoValida(posicao)) return POSICAO_INVALIDA;
	if(tamanho < 1) return TAMANHO_INVALIDO;
	if(verificarEstrutura(posicao)) return JA_TEM_ESTRUTURA_AUXILIAR;  
		
	vetorPrincipal[posicao-1].posicao =  malloc(tamanho*sizeof(int));
	vetorPrincipal[posicao-1].contador = 0;
	vetorPrincipal[posicao-1].tamanho = tamanho;

	if(vetorPrincipal[posicao-1].posicao != NULL)	return SUCESSO;
	 
	return SEM_ESPACO_DE_MEMORIA;
}

int inserirNumeroEmEstrutura(int posicao, int valor){
	if (!ehPosicaoValida(posicao)) return POSICAO_INVALIDA;
	if (!verificarEstrutura(posicao)) return SEM_ESTRUTURA_AUXILIAR;
	if (!verificarEspaco(posicao))return SEM_ESPACO;
	int cont = vetorPrincipal[posicao-1].contador;
	
	vetorPrincipal[posicao-1].posicao[cont] = valor;
	vetorPrincipal[posicao-1].contador++;
	return SUCESSO;
}

int excluirNumeroDoFinaldaEstrutura(int posicao) {
	if(!ehPosicaoValida(posicao)) return POSICAO_INVALIDA;
	if(!verificarEstrutura(posicao)) return SEM_ESTRUTURA_AUXILIAR;
	if(vetorPrincipal[posicao-1].contador == 0) return ESTRUTURA_AUXILIAR_VAZIA;
	
	vetorPrincipal[posicao-1].contador--;
	return SUCESSO;
}

int excluirNumeroEspecificoDeEstrutura(int posicao, int valor){
	int existeValor = verficarValor(posicao, valor);
	if(!ehPosicaoValida(posicao)) return POSICAO_INVALIDA;
	if(!verificarEstrutura(posicao)) return SEM_ESTRUTURA_AUXILIAR;
	if(vetorPrincipal[posicao-1].contador == 0) return ESTRUTURA_AUXILIAR_VAZIA;
	if(existeValor < 0) return NUMERO_INEXISTENTE;	

	for(int i = 0; i < vetorPrincipal[posicao-1].contador; i++) { 
		if(vetorPrincipal[posicao-1].posicao[i] == valor){
			for(int j = i; j < vetorPrincipal[posicao-1].contador-1; j++){
				vetorPrincipal[posicao-1].posicao[j] = vetorPrincipal[posicao-1].posicao[j+1];
			}
			i--;
			vetorPrincipal[posicao-1].contador--;
		}
	}
	return SUCESSO;
}

int getDadosEstruturaAuxiliar(int posicao, int vetorAux[]){		
	if(!ehPosicaoValida(posicao)) return POSICAO_INVALIDA;
	if(!verificarEstrutura(posicao)) return SEM_ESTRUTURA_AUXILIAR;

	int j = 0;
	for(int i = 0; i < vetorPrincipal[posicao-1].contador; i++){
		vetorAux[j] = vetorPrincipal[posicao-1].posicao[i];
		j++;
	}	
	return SUCESSO;
}

int getDadosOrdenadosEstruturaAuxiliar(int posicao, int vetorAux[]){
	if(!ehPosicaoValida(posicao)) return POSICAO_INVALIDA;
	if(!verificarEstrutura(posicao)) return SEM_ESTRUTURA_AUXILIAR;
	
	int temp, cont = 0;
	int j = 0; 
	for(int i = 0; i < vetorPrincipal[posicao-1].contador; i++){
		vetorAux[j] = vetorPrincipal[posicao-1].posicao[i];
		j++;
		cont++;
	}
			
	for(int i = 0; i < cont-1; i++) { 
		for(int j = 0; j < cont-1; j++){
			if(vetorAux[j] > vetorAux[j+1]){
				temp = vetorAux[j]; 
				vetorAux[j] = vetorAux[j+1]; 
				vetorAux[j+1] = temp;
			}
		}
	}
	return SUCESSO;		
}

int getDadosDeTodasEstruturasAuxiliares(int vetorAux[]) {
	int k = 0;
	int todasEstuturasVazias = 1; 

	for (int i = 0; i < TAM; i++) {
		if (vetorPrincipal[i].posicao != NULL && vetorPrincipal[i].contador > 0) {
			todasEstuturasVazias = 0; 
			for (int j = 0; j < vetorPrincipal[i].contador; j++) {
				vetorAux[k] = vetorPrincipal[i].posicao[j];
				k++;
			}
		}
	}
	if (todasEstuturasVazias) {
		return TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;
	} else {
		return SUCESSO;
	}
}

int getDadosOrdenadosDeTodasEstruturasAuxiliares(int vetorAux[]){
	int i, j, k = 0, temp;
	int todasEstuturasVazias = 1;

	for(int i = 0; i < TAM; i++) {
		if(vetorPrincipal[i].posicao != NULL && vetorPrincipal[i].contador > 0) {
			todasEstuturasVazias = 0;
			for(int j = 0; j < vetorPrincipal[i].contador; j++) {
				vetorAux[k] = vetorPrincipal[i].posicao[j];
				k++;
			}
		}
	}

	if (todasEstuturasVazias) return TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;
	
	for(i = 0; i < k-1; i++) {
		for(j = 0; j < k-1; j++){
			if(vetorAux[j+1]<vetorAux[j]){
				temp = vetorAux[j];
				vetorAux[j] = vetorAux[j+1];
				vetorAux[j+1] = temp;
			}
		}
	}
	return SUCESSO;
}

int modificarTamanhoEstruturaAuxiliar(int posicao, int novoTamanho){
	if (!ehPosicaoValida(posicao)) return POSICAO_INVALIDA;
	if (!verificarEstrutura(posicao)) return SEM_ESTRUTURA_AUXILIAR;
	
	int tamanhoAtual = vetorPrincipal[posicao-1].tamanho;
	int tamanhoAlterado = tamanhoAtual + novoTamanho;
	

	if (tamanhoAlterado <= 0) return NOVO_TAMANHO_INVALIDO;

	int *novoVetor = realloc(vetorPrincipal[posicao-1].posicao, tamanhoAlterado * sizeof(int)); 
	if (novoVetor == NULL) return SEM_ESPACO_DE_MEMORIA;

	vetorPrincipal[posicao-1].posicao = novoVetor;
	vetorPrincipal[posicao-1].tamanho = tamanhoAlterado;

	if (tamanhoAlterado < vetorPrincipal[posicao-1].contador) {
		vetorPrincipal[posicao-1].contador = tamanhoAlterado;
	}

	return SUCESSO;
}

int getQuantidadeElementosEstruturaAuxiliar(int posicao){
		if(!ehPosicaoValida(posicao)) return POSICAO_INVALIDA;
		if(!verificarEstrutura(posicao)) return SEM_ESTRUTURA_AUXILIAR;

		return vetorPrincipal[posicao-1].contador;
}

No *montarListaEncadeadaComCabecote(){
	int tam = 0;
	for(int i = 0; i < TAM; i++) {
		tam += vetorPrincipal[i].contador;
	}
	int vetorAux2[tam];
	getDadosDeTodasEstruturasAuxiliares(vetorAux2);

	No *inicio = (No *) malloc(sizeof(No));
	
	inicio->prox = NULL;
	No *atual = inicio;
	
	for(int i = 0; i < TAM; i++) {
		No *novo = (No *)malloc(sizeof(No));
		novo->conteudo = vetorAux2[i];
		novo->prox = NULL;
		atual->prox = novo;
		atual = novo;
	}

	return inicio;
}

void getDadosListaEncadeadaComCabecote(No *inicio, int vetorAux[]){
	No *atual = inicio->prox;
	int i = 0;
	while (atual != NULL) {
	 	vetorAux[i] = atual->conteudo;
	 	atual = atual->prox;
	 	i++;
	}
}

void destruirListaEncadeadaComCabecote(No **inicio){
	No *atual = *inicio;
	while (atual != NULL) {
		No *proximo = atual->prox;
		free(atual);
		atual = proximo;
	}
	*inicio = NULL;
}

void inicializar(){ 
	for(int i = 0; i < TAM; i++) 
		vetorPrincipal[i].posicao = NULL;
}

void finalizar(){
	free(vetorPrincipal -> posicao);
}
