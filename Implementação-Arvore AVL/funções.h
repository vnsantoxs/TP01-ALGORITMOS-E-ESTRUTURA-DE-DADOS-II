#include <stdio.h>
#include <stdlib.h>

//ESTRUTURA DA ARVORE AVL
typedef struct AVLNode {
    int key;
    struct AVLNode *left, *right, *parent;
    int height;
} AVLNode;

//FUNÇÃO PARA CRIAR UM NOVO NÓ
AVLNode* CreateNode(int key) {
    AVLNode *node = malloc(sizeof(AVLNode));
    if (node){
        node->key = key;
        node->left = NULL;
        node->right = NULL;
        node->parent = NULL;
        node->height = 0;
        return node;
    }else{
        printf("\nNODE CREATION ERROR!");
    }
}

//FUNUÇÃO PARA RETORNAR A ALTURA DO MAIOR NÓ (DIREITO OU ESQUERDO) 
int GetBiggest(AVLNode *node) {
    if (node == NULL) {
        return 0;
    }
    int leftHeight = GetHeight(node->left);
    int rightHeight = GetHeight(node->right);

    return (leftHeight>rightHeight)? leftHeight: rightHeight;
}

//FUNÇÃO PARA RETONAR A ALTURA DE UM NÓ
int GetHeight(AVLNode *node) {
    if (node == NULL) {
        return -1;
    }
    return node->height;
}

//FUNÇÃO DE VERIFICAÇÃO DE BALANCEAMENTO DO NÓ
short GetBalance(AVLNode *node) {
    if (node == NULL) {
        return 0;
    }
    return GetHeight(node->left) - GetHeight(node->right);
}

//FUNÇÃO DE ROTAÇÃO A ESQUERDA
AVLNode* RotateLeft(AVLNode *node) {
    AVLNode *Node1, *Node2;
    Node1 = node->right;
    Node2 = node->left;

    Node1->left = node;
    node->right = Node2;

    node->height = GetBiggest(node)+1;
    Node1->height = GetBiggest(Node1)+1;

    return Node1;
}

//FUNÇÃO DE ROTAÇÃO A DIREITA
AVLNode* RotateRigth(AVLNode *node){
    AVLNode *Node1, *Node2;
    
    Node1 = node->left;
    Node2 = node->right;

    Node1->right = node;
    node->left = Node2;

    node->height = GetBiggest(node)+1;
    Node1->height = GetBiggest(Node1)+1;

    return Node1;
}

//FUNÇÃO DE ROTAÇÃO DUPLA DIREITA-ESQUERDA
AVLNode* RotateRigthLeft(AVLNode *node){
    node->right = RotateRigth(node->right);
    return RotateLeft(node);
}

//FUNÇÃO DE ROTAÇÃO DUPLA ESQUERDA-DIREITA
AVLNode* RotateLeftRigth(AVLNode *node){
    node->left = RotateLeft(node->left);
    return RotateRigth(node);
}

//FUNÇÃO DE BALANCEAMENTO DA ARVORE AVL
AVLNode* BalanceTree (AVLNode *root){
    short NodeB = GetBalance(root);

    if(NodeB < -1 && GetBalance(root->right) <= 0){
        root = RotateLeft(root);

    }else if(NodeB > 1 && GetBalance(root->left) >= 0){
        root = RotateRigth(root);

    }else if(NodeB > 1 && GetBalance(root->left) < 0){
        root = RotateLeftRigth(root);

    }else if(NodeB < -1 && GetBalance(root->right) > 0){
        root = RotateRigthLeft(root);

    }

    return root;
}


//FUNÇÃO DE INSERÇÃO DE NÓ
AVLNode* InsertNode(AVLNode *root, int key){
    if (root == NULL){
        return CreateNode(key);

    }else{
        if(key < root->key){
            root->left = InsertNode(root->left, key);

        }else if(key > root->key){
            root->right = InsertNode(root->right, key);

        }else{
            printf("\nINSERT ERROR, EXISTING NODE");
        }
    }
    root->height = GetBiggest(root)+1;

    return BalanceTree(root);
}

//FUNÇÃO DE REMOÇÃO DE UM NÓ
AVLNode* RemoveNode(AVLNode *root, int key) {
    if(root == NULL){
        return NULL;

    } else {
        if(root->key == key) {
            if(root->left == NULL && root->right == NULL) {
                free(root);
                return NULL;

            }else{
                if(root->left != NULL && root->right != NULL){
                    AVLNode *aux = root->left;

                    while(aux->right != NULL){
                        aux = aux->right;
                    }

                    root->key = aux->key;
                    aux->key = key;
                    root->left = RemoveNode(root->left, key);
                    return root;

                }else{
                    AVLNode *aux;
                    if(root->left != NULL){
                        aux = root->left;

                    }else{
                        aux = root->right;
                    }
                    free(root);
                    return aux;
                }
            }
        }else{
            if(key < root->key){
                root->left = RemoveNode(root->left, key);
            }
            else{
                root->right = RemoveNode(root->right, key);
            }
        }

        root->height = GetBiggest(root) + 1;
        BalanceTree(root);
        return root;
    }
}

//FUNÇÃO DE IMPRESSÃO DA ARVORE EM NIVEIS
void ShowG(AVLNode* root, int level) {
    if (root == NULL) {
        return;
    }

    ShowG(root->right, level + 1);

    for (int i = 0; i < level; i++) {
        printf("    ");
    }
    printf("--/[%d]\n", root->key);

    ShowG(root->left, level + 1);
}

//FUNÇÃO DE IMPRESSÃO PRE ORDEM
void ShowPRE(AVLNode *root) {
    if(root == NULL) {
        return;
    }
    printf("[%d] ", root->key);
    ShowPRE(root->left);
    ShowPRE(root->right);
}

//FUNÇÃO DE IMPRESSÃO EM ORDEM
void ShowINO(AVLNode *root) {
    if(root == NULL) {
        return;
    }
    ShowINO(root->left);
    printf("[%d] ", root->key);
    ShowINO(root->right);
}

//FUNÇÃO DE IMPREÇÃO POS ORDEM
void ShowPOS(AVLNode *root) {
    if(root == NULL) {
        return;
    }
    ShowPOS(root->left);
    ShowPOS(root->right);
    printf("[%d] ", root->key);
}


//FUNÇAO DE BUSCA 
void SearchNode(AVLNode **root, int key, AVLNode **found_node) {

    if (*root == NULL || (*root)->key == key) {
        *found_node = *root;
        return;
    }if ((*root)->key < key) {
        SearchNode(&((*root)->right), key, found_node);

    }else {
        SearchNode(&((*root)->left), key, found_node);

    }
}

//FUNÇÃO DE ENCONTRAR MINIMO
AVLNode* FindMinimum(AVLNode *root) {
    if (root == NULL) {
        return NULL;
    }if (root->left == NULL) {
        return root;
    }
    return FindMinimum(root->left);
}

//FUNÇÃO DE ENCONTRAR MAXIMO
AVLNode* FindMaximum(AVLNode *root) {
    if (root == NULL) {
        return NULL;
    }if (root->right == NULL) {
        return root;
    }
    return FindMaximum(root->right);
}

//FUNÇÃO DE ENCONTRAR SUCESSOR DO NÓ
AVLNode* FindSuccessor(AVLNode *node) {
    if (node == NULL) {
        return NULL;
    }
    if (node->right != NULL) {
        return FindMinimum(node->right);
    }

    AVLNode *parent = node->parent;
    while (parent != NULL && node == parent->right) {
        node = parent;
        parent = parent->parent;
    }
    return parent;
}

//FUNÇÃO DE ENCONTRAR PREDECESSOR DO ŃÓ
AVLNode* FindPredecessor(AVLNode *node) {
    if (node == NULL) {
        return NULL;
    }
    if (node->left != NULL) {
        return FindMaximum(node->left);
    }

    AVLNode *parent = node->parent;
    while (parent != NULL && node == parent->left) {
        node = parent;
        parent = parent->parent;
    }
    return parent;
}
