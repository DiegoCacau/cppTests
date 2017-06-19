#include <stdio.h>
#include <stdlib.h>
// Toda estrutura do grafo

typedef struct viz{
    int id_viz;
    struct viz *prox;
}TViz;

typedef struct no{
    int id_no;
    TViz *prim_viz;
    struct no *prox_no;
}TNO;

typedef struct grafo{
    TNO *prim_no;
}TG;

// componente usados na buscaP
static int *pre,*low;
static TNO **pilha;
static int cont;
static int k, N;

// Funcoes para criaçao do grafo

TG *cria(void){

    TG *g = (TG*)malloc(sizeof(TG));
    g->prim_no = NULL;
    return g;
}

//Retorna no, caso exista

TNO *busca_no(TG *g, int no){

    TNO *p = g->prim_no;

    while((p)&&(p->id_no != no)){
        p = p->prox_no;
    }

    return p;
}

//Insere no

void insere_no(TG *g, int no){

    TNO *p = busca_no(g, no);

    if(p) {
        printf("Esse no ja existe\n");
        return;
    }

    p = (TNO*)malloc(sizeof(TNO));
    p->id_no = no;
    p->prim_viz = NULL;
    p->prox_no = g->prim_no;
    g->prim_no = p;
}

// Retorna aresta, caso ela exista

TViz* busca_aresta(TG *g, int no1, int no2){

    TNO* viz1 = busca_no(g, no1);

    if(!viz1){
        return NULL;
    }

    TNO *viz2 = busca_no(g, no2);

    if(!viz2){
        return NULL;
    }

    TViz *p = viz1->prim_viz;

    while((p)&&(p->id_viz!=no2)){
        p=p->prox;
    }

    return p;
}

// Insere vizinho ao no

void insere_viz(TG* g, int no, int id_viz){

    TNO *p = busca_no(g, no);

    if(!p){
        return;
    }

    TNO *l = busca_no(g, id_viz);

    if(!l){
        return;
    }

    TViz *v = p->prim_viz;

    while(v){
        if(v->id_viz == id_viz){
            return;
        }
        v = v->prox;
    }

    v = (TViz*)malloc(sizeof(TViz));
    v->id_viz = id_viz;
    v->prox = p->prim_viz;
    p->prim_viz = v;
}

// Print

void imprime(TG* g){

    TNO *p = g->prim_no;

    while(p){

        printf("%d",p->id_no);
        TViz *viz = p->prim_viz;

        while(viz){
            printf("-> %d", viz->id_viz);
            viz = viz->prox;
        }

        p = p->prox_no;
        printf("\n");
    }
}

// Free

void liberaViz(TViz *q){

    TViz *temp = q;
    while(q){
        temp = q;
        q = q->prox;
        free(temp);
    }
    free(q);

}

void libera(TNO* no){

    TViz *q = no->prim_viz;
    liberaViz(q);
    free(no);

}

void liberaGrafo(TG* g){

    TNO *n = g->prim_no;

    while(n){
        TNO *m = n;
        n = n->prox_no;
    
        libera(m);
    }

    free(g); 
}

// Funcoes para retirar um no do grafo e todas as ligacoes que continham esse id

TViz *retirador_de_viz(TViz* l, int no){

    if(!l) 
        return l;

    TViz *p = l, *ant = NULL;

    if(l->id_viz == no){
        l = l->prox;
        return l;
    }

    while((p)&&(p->id_viz!=no)){
        ant = p;
        p = p->prox;
    }

    if(!p) 
        return l;

    if(!ant) 
        l = l->prox;
    else 
        ant->prox = p->prox;

    free(p);
    return l;

}

TNO *retirador_de_nos(TNO* l, int no){

    if(!l) 
        return l;

    TNO *p = l, *ant = NULL;

    if(l->id_no == no){
        l = l->prox_no;
        return l;
    }

    while((p)&&(p->id_no!=no)){
        ant = p;
        p = p->prox_no;
    }

    if(!p) 
        return l;

    if(!ant) 
        l = l->prox_no;
    else 
        ant->prox_no = p->prox_no;

    free(p);
    return l;

}

// Retira um vertice especifico

void retira(TG* g, int x){

    TNO* no =  g->prim_no;
    g->prim_no = retirador_de_nos(no, x);

    while(no){
        TViz *viz = no->prim_viz;
        no->prim_viz = retirador_de_viz(viz, x);
        no = no->prox_no;
    }

}


// Caso orientado

void retira_aresta1(TG* g, int no, int x){
    TNO *p = busca_no(g,no);
    if(p){
        p->prim_viz = retirador_de_viz(p->prim_viz, x);
    }
}

// Caso nao orientado

void retira_aresta0(TG* g, int no, int x){

    TNO *p = busca_no(g,no);

    if(p){
        p->prim_viz = retirador_de_viz(p->prim_viz, x);
    }
    p = busca_no(g,x);
    if(p){
        p->prim_viz = retirador_de_viz(p->prim_viz, no);
    }
}

// Testa de uma aresta existe

int testaAresta(TG *g, int no, int viz){

    TNO* p = g->prim_no;

    while((p)&&(p->id_no != no)){
        p = p->prox_no;
    }

    if(p == NULL)
        return 0;


    TViz *l = p->prim_viz;

    while((l)&&(l->id_viz != viz)){
        l = l->prox;
    }

    if((l == NULL)){
        return 0;
    }
    else{
        return 1;
    }
}

// Testa se e orientado

int eOrientado(TG *g){

    TNO *atual = g->prim_no;

    while(atual){

        TViz *viz_atual = atual->prim_viz;

        while(viz_atual){

            int aux = testaAresta(g, viz_atual->id_viz, atual->id_no);
            if(aux == 0)
                return 1;
            
            viz_atual = viz_atual->prox;
        }

        atual = atual->prox_no;
    }
    return 0;
}


// Copia o grafo

TG* copiaDados(TG* g, int tamanho){

    TG *copia = cria();
    int i;
    for(i = 1; i <= tamanho; i++){
        if(busca_no(g,i))
            insere_no(copia, i);
    }

    TNO *p = g->prim_no;
    TNO *p2 = copia->prim_no;

    while(p){

        TViz *viz = p->prim_viz;
        while(viz){

            insere_viz(copia,p2->id_no,viz->id_viz);
            viz = viz->prox;

        }

        p = p->prox_no;
        p2 = p2->prox_no;
    }

    return copia;
}



/*
Baseado no capítulo 6.7 do livro Data Structures and Algorithms, De Aho, Hopcroft, Ullman,
e no algoritmo de Tarjan.
*/
static void fortes( TG *g, int i, int *posicoes)
{   
    //criacao de variaveis
    TNO  *no;
    TViz *viz;
    int min, id_viz;
 
    pre[i] = cont;
    cont++;

    min = pre[i];
    no = busca_no(g,i+1);

    // caso o no exista
    if(no){

        pilha[N] = no;
        N++;
        viz = no->prim_viz;

        for(viz; viz != NULL; viz = viz->prox){

            id_viz = viz->id_viz;

            if (pre[id_viz - 1] == -1) {

                fortes( g, id_viz-1, posicoes);
                if (low[id_viz-1] < min) 
                    min = low[id_viz-1];
            }
            else if ((pre[id_viz-1] < pre[i]) && (posicoes[id_viz-1] == -1)) {
                if (pre[id_viz-1] < min) 
                    min = pre[id_viz-1];
            }
        }

        low[i] = min;

        if (low[i] == pre[i]) {

            do{

                --N;
                no = pilha[N];
                posicoes[no->id_no - 1] = k;

            } 
            while (no->id_no - 1 != i);

            k++;
        }
    }

}


// Chama a busca em profundidade e o algoritomo de Tarjan
int buscaP( TG *g, int *posicoes, int tamanho)
{
    int i;

    //alocacao das variaveis usadas
    pre = (int*) malloc( tamanho * sizeof (int));
    low = (int*) malloc( tamanho * sizeof (int));
    pilha = (TNO**) malloc( tamanho * sizeof (TNO));

    //inicia as variaveis
    for (i = 0; i < tamanho; ++i)
      pre[i] = posicoes[i] = -1;

    k = N = cont = 0;

    // busca em profundidade + Algoritmo de Tarjan
    for (i = 0; i < tamanho; ++i)
        if (pre[i] == -1)
            fortes( g, i, posicoes);  

    //libera o que foi usado    
    free(pre); 
    free(low); 
    free( pilha);

    //retorna a quantidade de grafos fortemente conexos
    return k;
}



// Encontra as conexoes fortes
void conexoesFortes(TG *g){

    TNO *atual = g->prim_no;
    int contador =0, marcador=0, proximo, soma=0, j;

    while(atual){

        if(atual->id_no > contador)
            contador = atual->id_no;

        atual = atual->prox_no;

    }

    if (contador < 2)
        return;

    int* posicoes = (int*) malloc(contador * sizeof(int));
    int al = buscaP(g,posicoes, contador);

    for(j = 0; j < contador; j++)
    {
        if(posicoes[j] != -1)
        printf("Vertice: %d, Valor:%d\n", (j+1),posicoes[j]);

    }

    free(posicoes);
}

// Encontra os pontos de articulacao
void pontoArticular(TG* g, int contador){

    TNO *atual = g->prim_no;
    int quantidade, antes, i;
    int* posicoes = (int*) malloc(contador * sizeof(int));

    antes = buscaP(g,posicoes, contador);

    for (i = 1; i <= contador; ++i)
    {
        if(busca_no(g,i)){

            TG* copia = copiaDados(g,contador);
            retira(copia,i);

            quantidade = buscaP(copia,posicoes, contador);

            if(quantidade>antes)
                printf("Ponto de articulacao: %d\n", i);

            free(copia);
        }
    }

    free(posicoes);
}


// Encontra as pontes do grafo
void pontes(TG* g, int contador){

    TNO *atual = g->prim_no;
    int quantidade, antes, i, j;
    int* posicoes = (int*) malloc(contador * sizeof(int));

    antes = buscaP(g,posicoes, contador);

    for(i = 1; i <= contador; ++i)
    {
        
        for(j = i+1; j<=contador; j++){

            if((i!=j)&&(busca_no(g,i))&&(busca_no(g,j))&&(busca_aresta(g,i,j))){

                TG* copia = copiaDados(g,contador);
                retira_aresta1(copia, i, j);
                retira_aresta1(copia, j, i);
                quantidade = buscaP(copia,posicoes, contador);

                if(quantidade>antes)
                    printf("Ponte: %d %d\n", i, j);

                free(copia);
            }
        }    
    }

    free(posicoes);
}

// Testa se e conexo, se for procura as pontes e pontos de articulacao
void ehConexo(TG *g){

    TNO *atual = g->prim_no;
    int tamanho =0, marcador=0, proximo, soma=0, j;

    while(atual){
        if(atual->id_no > tamanho)
            tamanho = atual->id_no;
        atual = atual->prox_no;
    }

    if(tamanho < 2)
        return;

    int* posicoes = (int*) malloc(tamanho * sizeof(int));

    int al = buscaP(g,posicoes, tamanho);

    if(al > 1){
        printf("O grafo nao eh conexo.\n");
        for(j = 0; j < tamanho; j++)
        {
            if(posicoes[j] != -1)
                printf("Vertice: %d, Valor:%d\n", (j+1),posicoes[j]);

        }

    }
    else{
        pontes(g, tamanho);
        pontoArticular(g, tamanho);
    }

    free(posicoes); 

}



