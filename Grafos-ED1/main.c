#include "grafo.h"

int main(){
    // Abertura do arquivo
    FILE *file;
    file = fopen("grafo.txt", "r");
    // Salvado o tamanho e se o grafo é orientado ou nao
    int tam, orientacao;
    fscanf(file, "%d", &tam);
    // Criando e 0preenchendo o grafo, testando se e orientado ou nao
    TG *grafo = cria();
    //orientacao = eOrientado(grafo);
    int i;
    for(i = 1; i <= tam; i++){
        insere_no(grafo, i);
    }
    
    while(!feof(file)){
        int prim, sec;
        fscanf(file, "%d %d", &prim, &sec);
        insere_viz(grafo, prim, sec);
    }
    // Fechando o arquivo
    fclose(file);


    //##########MENU##########
    int menu = 1, op, no, aresta;
    TNO *p, *l;
    TViz *t;
    
    while(menu == 1){
        printf("\n##########MENU##########\n" \
               "#1 para inserir um no\n" \
               "#2 para imprimir o grafo\n" \
               "#3 para sair\n" \
               "#4 para inserir uma aresta\n" \
               "#5 para retirar um no inteiro\n" \
               "#6 para verificar se o grafo e orientado\n" \
               "#7 para retirar uma aresta especifica\n" \
               "#8 para buscar um no\n" \
               "#9 para buscar uma aresta\n" \
               "#10 para executar a funcao completa do trabalho\n" \
               "########################\n\n");
        
        printf("Operacao: ");
        scanf("%d",&op);
        switch(op){
            case 1:
                printf("No que deseja inserir: ");
                scanf("%d",&no);
                insere_no(grafo, no);
                break;
            case 2:
                imprime(grafo);
                break;
            case 3:
                menu = -1;
                break;
            case 4:
                printf("No que deseja inserir: ");
                scanf("%d",&no);
                printf("\nVizinho: ");
                scanf("%d", &aresta);

                p = busca_no(grafo, no);
                l = busca_no(grafo, aresta);
                if((p)&&(l)){
                    insere_viz( grafo, no, aresta);
                }else{
                    printf("Nao foi possivel inserir o vizinho\n");
                }

                break;
            case 5:
                printf("No que deseja retirar: ");
                scanf("%d",&no);
                retira(grafo, no);
                break;
            case 6:
                if(eOrientado(grafo)){
                    printf("O grafo e orientado\n");
                }else{
                    printf("O grafo nao e orientado\n");
                }
                break;
            case 7:
                printf("No em que deseja retirar: ");
                scanf("%d",&no);
                printf("\nVizinho a ser retirado: ");
                scanf("%d", &aresta);
                if(eOrientado(grafo)){
                    retira_aresta0(grafo, no, aresta);
                }else{
                    retira_aresta1(grafo, no, aresta);
                }
                break;
            case 8:
                printf("No: ");
                scanf("%d", &no);
                p = busca_no(grafo, no);
                if(p){
                    printf("O no %d existe\n", no);
                }else{
                    printf("O no %d nao existe\n", no);
                }
                break;
            case 9:
                printf("No: ");
                scanf("%d", &no);
                printf("Aresta: ");
                scanf("%d", &aresta);
                t = busca_aresta(grafo, no, aresta);
                if(t){
                    printf("A aresta %d do no %d existe\n", aresta, no);
                }else{
                    printf("A aresta %d do no %d nao existe\n", aresta, no);
                }
                break;
            case 10:
                if(eOrientado(grafo)){
                    printf("O grafo e orientado\n"); 
                    conexoesFortes(grafo);
                }else{
                    printf("O grafo nao e orientado\n");
                    ehConexo(grafo);
                }
                break;

        }
    }
    //##########MENU##########

    free(p);
    free(l);
    free(t);

    //imprime(grafo);
    return -1;
}
