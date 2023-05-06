#include <stdio.h>
#include "funções.h"

int main(){
    int option, key;
    AVLNode *Max, *Min, *root = NULL;
    do
    {
        printf("\n\n\txxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\t▓▓▓");
        printf("\n\t|\t   <<<ARVORE BINARIA AVL>>>\t\t|      ▓▓▓▓▓");
        printf("\n\t|\t\tBALANCEAMENTO: %d\t\t|     ▓▓▓▓▓▓▓",GetBalance(root));
        printf("\n\t|[1] INSERIR\t\t[2] EXCLUIR\t\t|    ▓▓▓▓▓▓▓▓▓\n\t|[3] BUSCAR\t\t[4] ARVORE GRAFICA\t|   ▓▓▓▓▓▓▓▓▓▓▓\n\t|[5] MAXIMO E MINIMO\t[6] IMPRIMIR PRE-ORDEM  |  ▓▓▓▓▓▓▓▓▓▓▓▓▓\n\t|[7] IMPRIMIR ORDEM\t[8] IMPRIMIR POS-ORDEM  | ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓\n\t|[9] SUCESSORPREDECESSOR[0] Sair\t\t|\t███");
        printf("\n\txxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\t███");
        printf("\nOPÇÃO: ");
        scanf("%d", &option);
        switch (option)
        {
        case 0:
            printf("\nSAINDO!\n");
            free(root);
            break;
        case 1:
            if(GetBalance(root) >= 2 || GetBalance(root) <= -2){
                printf("\nARVORE DESBALANCEADA PARA A INSERÇÃO");
            }else{
                printf("\nDIGITE A CHAVE: ");
                scanf("%d", &key);
                root = InsertNode(root, key);
                printf("\nINSERÇÃO REALIZADA!");
            }
            break;
        case 2:
            if(GetBalance(root) >= 2 || GetBalance(root) <= -2){
                printf("\nARVORE DESBALANCEADA PARA A REMOÇÃO");
            }else{
                printf("\nDIGITE A CHAVE: ");
                scanf("%d", &key);
                RemoveNode(root, key);
                printf("\nREMOÇÃO REALIZADA!");
            }
            break;
        case 3:
            if(root == NULL){
                printf("\nARVORE VAZIA");
            }else{
                if(GetBalance(root) >= 2 || GetBalance(root) <= -2){
                printf("\nARVORE DESBALANCEADA PARA A BUSCA");
                }else{
                    printf("\nDIGITE A CHAVE: ");
                    scanf("%d", &key);
                    AVLNode *found_node = NULL;
                    SearchNode(&root, key, &found_node);
                    if (found_node != NULL) {
                        printf("\n%d ENCONTRADO", key);
                    }
                    else {
                        printf("\n%d NÃO ENCONTRADO", key);
                    }
                }
            }
            break;
        case 4:
            if(root == NULL){
                printf("\nARVORE VAZIA");
            }else{
                ShowG(root,0);
            }
            break;
        case 5:
            if(root == NULL){
                printf("\nARVORE VAZIA");
            }else{
                Max = FindMaximum(root);
                Min = FindMinimum(root);
                printf("\n\tMAXIMO: %d MINIMO: %d", Max->key, Min->key);
            }
            break;
        case 6:
            if(root == NULL){
                printf("\nARVORE VAZIA");
            }else{
                ShowPRE(root);
            }
            break;
        case 7:
            if(root == NULL){
                    printf("\nARVORE VAZIA");
                }else{
                    ShowINO(root);
                }
                break;
        case 8:
            if(root == NULL){
                    printf("\nARVORE VAZIA");
                }else{
                    ShowPOS(root);
                }
                break;
        case 9:
            if(root == NULL){
                printf("\nARVORE VAZIA");
            }else{
                AVLNode *suc, *pre;
                suc = FindSuccessor(root);
                pre = FindPredecessor(root);
                printf("\nSUCESSOR: %d", suc->key);
                printf("\nPREDECESSOR: %d", pre->key);
                break;
            }
        default:
            printf("\nOPÇÃO INVALIDA!");
        }
    } while (option != 0);
    
    return 0;
}