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

// componente conexos
static int *pre,*low;
static TNO **stack;
static int cnt;
static int k, N;

// Funcoes para criaçao do grafo

TG *cria(void){
    TG *g = (TG*)malloc(sizeof(TG));
    g->prim_no = NULL;
    return g;
}

TNO *busca_no(TG *g, int no){
    TNO *p = g->prim_no;
    while((p)&&(p->id_no != no)){
        p = p->prox_no;
    }
    return p;
}

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

// Funcoes para retirar um no do grafo e todas as ligacoes que continham esse id

TViz *retirador_de_viz(TViz* l, int no){
    if(!l) return l;
    TViz *p = l, *ant = NULL;
    if(l->id_viz == no){
        l = l->prox;
        return l;
    }
    while((p)&&(p->id_viz!=no)){
        ant = p;
        p = p->prox;
    }
    if(!p) return l;
    if(!ant) l = l->prox;
    else ant->prox = p->prox;
    free(p);
    return l;
}

TNO *retirador_de_nos(TNO* l, int no){
    if(!l) return l;
    TNO *p = l, *ant = NULL;
    if(l->id_no == no){
        l = l->prox_no;
        return l;
    }
    while((p)&&(p->id_no!=no)){
        ant = p;
        p = p->prox_no;
    }
    if(!p) return l;
    if(!ant) l = l->prox_no;
    else ant->prox_no = p->prox_no;
    free(p);
    return l;
}

void retira(TG* g, int x){
    TNO* no =  g->prim_no;
    g->prim_no = retirador_de_nos(no, x);
    while(no){
        TViz *viz = no->prim_viz;
        no->prim_viz = retirador_de_viz(viz, x);
        no = no->prox_no;
    }
}

// Retira um vertice especifico

void retira_aresta1(TG* g, int no, int x){
    TNO *p = busca_no(g,no);
    if(p){
        p->prim_viz = retirador_de_viz(p->prim_viz, x);
    }
}

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

// Testa para saber se e orientado ou nao

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

int eOrientado(TG *g){
    TNO *atual = g->prim_no;
    while(atual){
        TViz *viz_atual = atual->prim_viz;
        while(viz_atual){
            int aux = testaAresta(g, viz_atual->id_viz, atual->id_no);
            if(aux == 1){
                return 1;
            }
            viz_atual = viz_atual->prox;
        }
        atual = atual->prox_no;
    }
    return 0;
}

void buscaConexoes(TG *g, int id, int *vetor, int tamanho, int marcador){
    int ida, volta;

    
    for (int j = 0; j < (tamanho); j++)
    {
        
        if(id != j){

            ida = testaAresta(g, id+1, j+1);
            volta = testaAresta(g, j+1, id+1);

            if((ida || volta)&&(vetor[j] == 0)){
                vetor[j] = marcador;
                buscaConexoes(g, j, vetor,tamanho, marcador);
            } 
        }
    
    }

}



TG* copiaDados(TG* g, int tamanho){
    TG *copia = cria();
    int i;
    for(i = 1; i <= tamanho; i++){
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

void pontes(TG* g, int tamanho){
    TG* copia = copiaDados(g,tamanho);
    int* posicoes = (int*) malloc(tamanho * sizeof(int));
    int contador =0, marcador=1,proximo, id_ponte;

    TNO *p = copia->prim_no;
    while(p){
        TViz *vizSalvo = p->prim_viz;       
        TViz *viz = p->prim_viz;
        int contador=0;
        while(viz){
            contador++;
            viz = viz->prox;
        }

        if(contador > 1)
        {    
            for (int i = 1; i <= contador; i++)
            {

                viz = p->prim_viz;
                p->prim_viz=NULL;
                for (int j = 1; j <= contador; j++)
                {   
                    if(viz)
                    {
                        
                        if (j!=i)
                        {
                            TViz* v = (TViz*)malloc(sizeof(TViz));
                            v->id_viz = viz->id_viz;
                            v->prox = p->prim_viz;
                            p->prim_viz = v;
                        }
                        else{
                            id_ponte = viz->id_viz;
                        }
                        viz = viz->prox;
                    }         
                }

                for (int k=0; k< tamanho; k++)
                    posicoes[k]=0;

                posicoes[0]=marcador;
                buscaConexoes(copia,0,posicoes,tamanho, marcador);
                for (int k=0; k< tamanho; k++)
                    if(posicoes[k] == 0){
                        proximo = k;
                        marcador++;
                        posicoes[k]=marcador;
                        buscaConexoes(copia,k,posicoes,tamanho, marcador);
                    }

                if((marcador > 1)&&(p->id_no!=id_ponte)){
                    printf("Ponte: %d %d\n", p->id_no,id_ponte);
                    marcador = 1;
                }    
 
                liberaViz(p->prim_viz);
                p->prim_viz = vizSalvo;
            }
        }
        p = p->prox_no;
    }
    free(copia);
}

void buscaConexoes2(TG *g, int id, int *vetor, int tamanho, int marcador, int pular){
    int ida, volta;
    
    for (int j = 0; j < (tamanho); j++)
    {
        
        if((id != j)&&(j != pular)&&(id != pular)){
            ida = testaAresta(g, id+1, j+1);
            volta = testaAresta(g, j+1, id+1);

            if((ida || volta)&&(vetor[j] == 0)){
                vetor[j] = marcador;
                buscaConexoes2(g, j, vetor,tamanho, marcador,pular);
            } 
        }
    
    }

}

void pontoArticular(TG* g, int tamanho){
    int* posicoes = (int*) malloc(tamanho * sizeof(int));
    int contador =0, marcador=1,proximo, id_ponte;

    for (int i = 1; i <= tamanho; i++)
    {
        TG* copia = copiaDados(g,tamanho);
        retira(copia, i);

        for (int k=0; k< tamanho; k++)
            posicoes[k]=0;

        posicoes[i-1]=marcador;
        buscaConexoes2(copia,0,posicoes,tamanho, marcador,i-1);
        for (int k=0; k< tamanho; k++)
            if(posicoes[k] == 0){
                proximo = k;
                marcador++;
                posicoes[k]=marcador;
                buscaConexoes2(copia,k,posicoes,tamanho, marcador,i-1);
            }
        if(marcador > 1){
            printf("Ponto de Articulacao: %d\n", i);
            marcador = 1;
        }

        free(copia);
    }
    
    
}




/*adaptado da figura 5.15 do livro de Aho, Hopcroft e Ullman
https://www.ime.usp.br/~pf/algoritmos_para_grafos/aulas/tarjan.html*/
static void strongR( TG *g, int v, int *sc) 
{ 
   TNO  *u; 
   TViz *a; 
   int min, w;

   pre[v] = cnt++;
   min = pre[v]; 
   u = busca_no(g,v+1);
   if(u){
    stack[N++] = u;
       a = u->prim_viz;
       for (a ; a != NULL; a = a->prox) { 
          w = a->id_viz;
          if (pre[w -1] == -1) {
             strongR( g, w-1, sc);
             if (low[w-1] < min) min = low[w-1]; 
          }
          else if (pre[w-1] < pre[v] && sc[w-1] == -1) {
             if (pre[w-1] < min) min = pre[w-1]; 
          }
       }
       low[v] = min;
       if (low[v] == pre[v]) {               
          do {
             u = stack[--N];
             sc[u->id_no - 1] = k;
          } while (u->id_no - 1 != v);
          k++;
       }
   }
   
}

int GRAPHscT( TG *g, int *sc, int tamanho)
{
    int v; 
    pre = (int*) malloc( tamanho * sizeof (int));
    low = (int*) malloc( tamanho * sizeof (int));
    stack = (TNO**) malloc( tamanho * sizeof (TNO));

    for (v = 0; v < tamanho; ++v) 
      pre[v] = sc[v] = -1;

    k = N = cnt = 0;
    for (v = 0; v < tamanho; ++v) 
        if (pre[v] == -1)
            strongR( g, v, sc);

    free(pre); free(low); free( stack);
    return k;
}


void conexoesFortes(TG *g){
    TNO *atual = g->prim_no;
    int contador =0, marcador=0, proximo, soma=0;
    while(atual){
        if(atual->id_no > contador)
            contador = atual->id_no;
        atual = atual->prox_no;
        
    }

    if (contador < 2)
        return;

    int* posicoes = (int*) malloc(contador * sizeof(int));
    
    int al = GRAPHscT(g,posicoes, contador);
   
    for (int j = 0; j < contador; j++)
    {   
        if(posicoes[j] != -1)
        printf("Vertice: %d, Valor:%d\n", (j+1),posicoes[j]);
        
    }
    
    free(posicoes);
}

void ehConexo(TG *g){
    TNO *atual = g->prim_no;
    int contador =0, marcador=1,proximo;
    while(atual){
        if(atual->id_no > contador)
            contador = atual->id_no;
        atual = atual->prox_no;
        
    }

    if (contador < 2)
        return;

    int* posicoes = (int*) malloc(contador * sizeof(int));

    for (int i=0; i< contador; i++)
        posicoes[i]=0;

    
    posicoes[0]=marcador;
    buscaConexoes(g,0,posicoes,contador, marcador);
    for (int i=0; i< contador; i++)
        if(posicoes[i] == 0){
            proximo = i;
            marcador++;
            posicoes[i]=marcador;
            buscaConexoes(g,i,posicoes,contador, marcador);
        }

    for (int j = 0; j < marcador; j++)
    {
        int quantidade=0;
        for (int i=0; i< contador; i++)
            if(posicoes[i] == j+1)
            {    
                quantidade++;
            }

        //componentes conexas    
        if(quantidade >= 2)
        {    
            printf("%s\n", "Componentes conexas:");
            for (int i=0; i< contador; i++){
                if(posicoes[i] == j+1)
                {    
                    printf("%d\n",i+1);
                }    
            }
            printf("\n\n");
        }
        
    }
    
    free(posicoes);

    pontes(g, contador);
    pontoArticular(g, contador);
   

}



