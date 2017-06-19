/*
    Alunos: Diego Carrico Cacau
            Vitor Hardoim
*/

#include "grafo.h"

int main(){
    // Abertura do arquivo
    FILE *file;
    file = fopen("grafo.txt", "r");
    // Salvado o tamanho
    int tam;
    fscanf(file, "%d", &tam);
    // Criando e preenchendo o grafo, testando se e orientado ou nao
    TG *grafo = cria();
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
        printf("\n################## MENU ###################\n" \
               "# 1 para inserir um no                    #\n" \
               "# 2 para inserir um vizinho em um no      #\n" \
               "# 3 para retirar um no inteiro            #\n" \
               "# 4 para retirar uma aresta especifica    #\n" \
               "# 5 para buscar um no                     #\n" \
               "# 6 para buscar uma aresta                #\n" \
               "# 7 para verificar se o grafo e orientado #\n" \
               "# 8 para resposta completa                #\n" \
               "# 9 para imprimir o grafo                 #\n" \
               "# 10 para sair                            #\n" \
               "###########################################\n\n");

        printf("Operacao: ");
        scanf("%d",&op);
        switch(op){
            case 1:
                printf("No que deseja inserir: ");
                scanf("%d",&no);
                insere_no(grafo, no);
                break;
            case 2:
                printf("No em que deseja inserir: ");
                scanf("%d",&no);
                printf("Vizinho: ");
                scanf("%d", &aresta);

                p = busca_no(grafo, no);
                l = busca_no(grafo, aresta);
                if((p)&&(l)){
                    if(eOrientado(grafo)){
                        insere_viz(grafo, no, aresta);
                    }else{
                        insere_viz(grafo, no, aresta);
                        insere_viz(grafo, aresta, no);
                    }
                }
                else{
                    printf("Nao foi possivel inserir o vizinho\n");
                }

                break;
            case 3:
                printf("No que deseja retirar: ");
                scanf("%d",&no);
                retira(grafo, no);
                break;
            case 4:
                printf("No em que deseja retirar: ");
                scanf("%d",&no);
                printf("\nVizinho a ser retirado: ");
                scanf("%d", &aresta);
                if(eOrientado(grafo)){
                    retira_aresta1(grafo, no, aresta);
                }else{
                    retira_aresta0(grafo, no, aresta);
                }
                break;
            case 5:
                printf("No: ");
                scanf("%d", &no);
                p = busca_no(grafo, no);
                if(p){
                    printf("O no %d existe\n", no);
                }else{
                    printf("O no %d nao existe\n", no);
                }
                break;
            case 6:
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
            case 7:
                if(eOrientado(grafo)){
                    printf("O grafo e orientado\n");
                }else{
                    printf("O grafo nao e orientado\n");
                }
                break;
            case 8:
                if(eOrientado(grafo)){
                    printf("O grafo e orientado\n");
                    conexoesFortes(grafo);
                }else{
                    printf("O grafo nao e orientado\n");
                    ehConexo(grafo);
                }
                break;
            case 9:
                imprime(grafo);
                break;
            case 10:
                menu = -1;
                liberaGrafo(grafo);
                break;
        }
    }
    return -1;
}
