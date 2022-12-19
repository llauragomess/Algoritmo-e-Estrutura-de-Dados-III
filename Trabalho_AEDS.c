#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#define QUANTIDADE_PALAVRAS 63070
#define TAMANHO_HEAP 5882
#define VAZIO 0

typedef struct no{
    char info[30];
    struct no *esq;
    struct no *dir;
    int altura;
    int qt;
}No;//struct arvore

typedef struct texto{
    char palavras[30];
    int prio;
}Texto;//struct informacoes do arquivo

typedef struct heap{
    Texto *palavras;
    int quantidade;
}Heap;

//funcoes avl
No *criarArvore();
No *inserir_avl(No *raiz, char *palavra);
int altura_no(No *raiz);
int altura_arvore(No *raiz);
int maior(int a, int b);
int fator_balanceamento(No *raiz);
No *rotEsquerda (No *raiz);
No *rotDireita (No *raiz);
No *rotEsqDir (No *raiz);
No *rotDirEsq(No *raiz);
No *balancear (No *raiz);
No *busca (No *raiz, char *chave);
void imprimir (No *raiz, int n);
int qt_nos(No *raiz);
int tamanho_avl(No *raiz);

//funcoes heap
Heap *criarHeap();
int inserir_heap(Heap *heap, Texto palavra);
void balancear_inserir(Heap *heap, int quantidade);
int remover_heap(Heap *heap, Texto *removida);
void balancear_remover(Heap *heap, int quantidade);
int acessar_heap(Heap *heap, Texto *acessada);
int tamanho_heap(Heap *heap);
int heap_cheia(Heap *heap);
int heap_vazia(Heap *heap);
int liberar_heap(Heap *heap);
No *remover_inserir(No *raiz, Heap *heap);
void imprimir_heap(Heap *heap);

int main(){
    No *raiz = criarArvore(); // criando a AVL
    No *buscar;

    //variáveis que serão utilizadas ao decorrer do programa
    char b[50];
    int op, i, a, cont=0;
    Texto acessada;
    Texto removida;

    /////////////////////////////////tratando o arquivo//////////////////////////////////////////
    FILE *novo;
    FILE *velho;

    velho = fopen("arquivo_trabalho2.txt", "r");
    if(velho == NULL){
        printf("\nErro ao abrir o arquivo!\n");
    }else{
        printf("\nArquivo aberto!\n");
    }

    while((a = fgetc(velho)) != EOF){//contando caracteres do arquivo
        cont++;
    }

    fclose(velho);

    velho = fopen("arquivo_trabalho2.txt", "r");
    novo = fopen("arquivo_modificado.txt", "w");//criando arquivo novo

    if(novo == NULL){
        printf("\nErro ao criar o arquivo!\n");
    }else{
        printf("\nArquivo criado!\n");
    }

    for(i=0; i<cont; i++){//tratando arquivo
        char caractere = getc(velho);
        if (caractere == '.' || caractere == ',' || caractere == '!' || caractere == '?' || caractere == ';' || caractere == ':' || caractere == '-' || caractere == '(' || caractere == ')' || caractere == '"' || caractere == '\'' || caractere == '/' || caractere == '@' || caractere == '#' || caractere == '$' || caractere == '%' || caractere == '&' || caractere == '*' || caractere == '+' || caractere == '=' || caractere == '_' || caractere == '<' || caractere == '>' || caractere == '[' || caractere == ']'){

            caractere = ' ';
        }
        else{
           caractere = tolower(caractere);
        }
        fprintf(novo, "%c", caractere);
    }

    fclose(velho);
    fclose(novo);
/////////////////////////////////////////////////////////////////////////////////////////////

    Heap *heap = criarHeap(); //criando a heap

    do{
        printf("\n[1]Inserir um elemento na arvore\n");;
        printf("[2]Buscar elemento na AVL\n");
        printf("[3]Imprimir arvore:\n");
        printf("[4]Inserir Heap\n");
        printf("[5]Acessar Heap\n");
        printf("[6]Remover Heap\n");
        printf("[7]Imprimir Heap\n");
        printf("[0]Sair\n");
        scanf("%d", &op);

        switch (op){
        case 1:
            novo = fopen("arquivo_modificado.txt", "r");
            char auxiliar[30];
            for(i=0; i<QUANTIDADE_PALAVRAS; i++){
                fscanf(novo, "%s", auxiliar);
                raiz = inserir_avl(raiz, auxiliar);
            }
            fclose(novo);
            break;
        case 2:
            printf("\nInsira a palavra que deseja buscar: ");
            scanf("%s", b);
            buscar = busca(raiz, b);
            if(buscar){
                printf("Palavra encontrada: %s = %d\n", buscar->info, buscar->qt);
            }else{
                printf("Palavra nao encontrada\n");
            }
            break;
        case 3:
            printf("\nArvore AVL: ");
            imprimir(raiz,1);
            break;
        case 4:
            remover_inserir(raiz, heap);
            break;
        case 5:
            acessar_heap(heap, &acessada);
            printf("\nPalavra: %s - Repeticoes: %d", acessada.palavras, acessada.prio);
            break;
        case 6:
            remover_heap(heap, &removida);
            printf("\nPalavra removida: %s - %d", removida.palavras, removida.prio);
            break;
        case 7:
            imprimir_heap(heap);
            break;
        case 0:
            printf("\nSAINDO!\n");
        default:
            if(op != 0){
                printf("Opcao invalida\n");
            }
        }
    }while(op != 0);
    return 0;
}
No *criarArvore(){
  return NULL;
}
No *inserir_avl(No *raiz, char *palavra){
    if(raiz == NULL){ //verifica se a raiz está nula para inserir o elemento
        raiz = (No *)malloc(sizeof(No));
        strcpy(raiz->info, palavra);
        raiz->esq = NULL;
        raiz->dir = NULL;
        raiz->qt = 1;
        raiz = balancear(raiz);
        return raiz;
    }else{
        if (strcmp(palavra, raiz->info) < 0){ //faz as comparaçoes para determinar a sub-arvore de destino
            raiz->esq = inserir_avl(raiz->esq, palavra);
        }
        else if(strcmp(palavra, raiz->info) > 0){
            raiz->dir = inserir_avl(raiz->dir, palavra);
        }
        else{
            raiz->qt++;
        }
        return raiz;
    }
}
int altura_no(No *raiz){ // retorna a altura do no
    if(raiz == NULL){
        return -1;
    }
    else{
        return raiz->altura;
    }
}
int altura_arvore(No *raiz){ // retorna a altura da maior sub-arvore
    if(raiz == NULL){
        return -1;
    }
    else{
        int esq = altura_arvore(raiz->esq);
        int dir = altura_arvore(raiz ->dir);
        if(esq > dir){
            return esq +1;
        }else{
            return dir+1;
        }
    }
}
int tamanho_avl(No *raiz){ // tamanho AVL
    if(raiz == NULL){
        return 0;
    }else{
        int esq = tamanho_avl(raiz->esq);
        int dir = tamanho_avl(raiz->dir);
        return esq + dir;
    }
}
int maior(int a, int b){
    if(a > b){
        return a;
    }else{
        return b;
    }
}
int fator_balanceamento(No *raiz){//retorna o inteiro que irá determinar qual o tipo de rotação
    if(raiz != NULL){
        return (altura_no(raiz->esq)) - (altura_no(raiz->dir));
    }else{
        return 0;
    }
}
No *rotEsquerda (No *raiz){
    No *aux, *a;

    aux = raiz->dir; // aux recebe a sub-arvore a direita da raiz
    a = aux->esq; // "a" recebe o filho esquerdo de aux

    aux->esq = raiz; // o filho a esquerda de aux passa ser a raiz
    raiz->dir = a; // o filho a direita da raiz passa a ser "a"

    // recalculando o tamanho da arvore
    raiz->altura = maior(altura_no(raiz->esq),altura_no(raiz->dir))+ 1;
    aux->altura = maior(altura_no(aux->esq), altura_no(aux->dir)) + 1;

    return aux;
}
No *rotDireita (No *raiz){
    No *aux, *a;

    aux = raiz-> esq;//aux recebe a sub-arvore a esquerda da raiz
    a = aux->dir;//"a" recebe a sub-arvore a direita

    aux->dir = raiz; // o filho a direita passa a ser a raiz
    raiz->esq = a; //o filho a esquerda passa a ser "a

    raiz->altura = maior(altura_no(raiz->esq), altura_no(raiz->dir)) + 1;//chama a função de comparacao de altura para determinar a altura dos nós
    aux->altura = maior(altura_no(aux->esq), altura_no(aux->dir)) + 1;

    return aux;
}
No *rotEsqDir (No *raiz){
    raiz-> esq = rotEsquerda(raiz->esq);
    return rotDireita(raiz);
}
No *rotDirEsq(No *raiz){
    raiz ->dir = rotDireita(raiz->dir);
    return rotEsquerda(raiz);
}
No *balancear (No *raiz){//função que junto com o fator de balanceamento vai determinar as rotações
    int fb = fator_balanceamento(raiz);

    if(fb < -1 && fator_balanceamento(raiz->dir) <= 0){
        raiz = rotEsquerda(raiz);
    }
    else if(fb > 1 && fator_balanceamento(raiz->esq) >= 0){
        raiz = rotDireita(raiz);
    }
    else if(fb > 1 && fator_balanceamento(raiz->esq) < 0){
        raiz = rotEsqDir(raiz);
    }
    else if (fb < -1 && fator_balanceamento(raiz->dir) > 0){
        raiz = rotDirEsq(raiz);
    }

    return raiz;
}
No *busca (No *raiz, char *chave){
    if(raiz != NULL){
        if(strcmp(chave, raiz-> info) == 0){
            return raiz;
        }else if(strcmp(chave, raiz->info) < 0){
            return busca(raiz->esq, chave);
        }else{
            return busca(raiz->dir, chave);
        }
    }
    return NULL;
}
void imprimir (No *raiz, int n){
    int i;
    if(raiz){
        imprimir(raiz->dir, n+1);
        printf("\n");
        for(i=0; i<n; i++){
            printf("   ");
        }
        printf("%s=%d", raiz->info, raiz->qt);
        imprimir(raiz->esq, n+1);
    }
}
int qt_nos(No *raiz){
    if (raiz == NULL){
        return 0;
    }else{
        return 1 + qt_nos(raiz->esq) + qt_nos(raiz->dir);
    }
}
//funçoes heap
Heap *criarHeap(){
    Heap *heap = (Heap *)malloc(sizeof(Heap));
    heap->palavras = (Texto *)malloc(sizeof(Texto) * TAMANHO_HEAP);
    heap -> quantidade = 0;
    return heap;
}
int inserir_heap(Heap *heap, Texto palavra){
    if(heap_cheia(heap)){//verificando se ainda há espaço para inserir
        return 0;
    }
    heap->palavras[heap->quantidade] = palavra;
    heap->quantidade++;
    balancear_inserir(heap, heap->quantidade);
    return 1;
}
void balancear_inserir(Heap *heap, int quantidade){//balanceando a arvore para que o elemento mais prioritario fique na posicao 0 do vetor
    int i = quantidade-1;
    while(i>0 && heap->palavras[i].prio > heap->palavras[(i-1)/2].prio){
        Texto aux = heap->palavras[i];
        heap->palavras[i] = heap->palavras[(i-1)/2];
        heap->palavras[(i-1)/2] = aux;
        i = (i-1)/2;
    }
}
int remover_heap (Heap *heap, Texto *removida){
    if(heap_vazia(heap)){
        return 0;
    }
    *removida = heap->palavras[0];
    heap->palavras[0] = heap->palavras[heap->quantidade -1];
    heap->quantidade--;
    balancear_remover(heap, heap->quantidade);
    return 1;
}
void balancear_remover(Heap *heap, int quantidade){//balanceando novamente para que o segundo elemento mais prioritario fique na pos 0 do vetor, asssim reorganizando a heap
    int i= 0;
    while(2*i+1 < quantidade){
        int maior = 2*i+1;
        if(2*i+2 < quantidade && heap->palavras[2*i+2].prio > heap->palavras[2*i+1].prio){
            maior = 2*i+2;
        }
        if(heap->palavras[i].prio < heap->palavras[maior].prio){
            Texto aux = heap->palavras[i];
            heap->palavras[i] = heap->palavras[maior];
            heap->palavras[maior] = aux;
            i=maior;
        }else{
            break;
        }
    }
}
int heap_vazia(Heap *heap){
    return heap->quantidade==0;
}
int heap_cheia(Heap *heap){
    return heap->quantidade ==TAMANHO_HEAP;
}
int liberar_heap(Heap *heap){
    free(heap);
    return 1;
}
int acessar_heap(Heap *heap, Texto *acessada){//acessando o elemento mais prioritario
    if(heap_vazia(heap)){
        return 0;
    }
    *acessada = heap->palavras[0];
    return 1;
}
No *remover_inserir(No *raiz, Heap *heap){
    if(raiz)
    {
        remover_inserir(raiz->esq, heap);// chamando a funço para liberar a sub-arvore a esquerda
        remover_inserir(raiz->dir, heap);//chamando a funçao para liberar a sub-arvore a direita

        Texto aux;
        strcpy(aux.palavras, raiz->info);
        aux.prio = raiz->qt;
        inserir_heap(heap, aux);//inserindo o elemento que será liberado posteriormente

        free(raiz->info);//liberando o ponteiro que carrega a informaçao
        free(raiz);//liberando a raiz
    }
    return NULL;
}
void imprimir_heap(Heap *heap){
    Texto aux;
    int i;
    for(i=0; i<heap->quantidade; i++){
        aux = heap->palavras[i];
        printf("[%d] (%s   %d)\n", i, aux.palavras, aux.prio);
    }
}
