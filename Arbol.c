#include <stdio.h>
#include <stdlib.h>

// Definición de la estructura del nodo del árbol
typedef struct TreeNode {
    int rnt_code;
    int expiration_date;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// Función para crear un nuevo nodo del árbol
TreeNode* createNode(int rnt_code, int expiration_date) {
    // Reservar memoria para el nuevo nodo
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    if (newNode == NULL) {
        // Manejar el error si no se puede reservar memoria
        printf("Error: No se pudo reservar memoria para el nuevo nodo.\n");
        exit(EXIT_FAILURE);
    }

    // Inicializar los valores del nodo
    newNode->rnt_code = rnt_code;
    newNode->expiration_date = expiration_date;
    newNode->left = NULL;
    newNode->right = NULL;

    // Devolver el nuevo nodo creado
    return newNode;
}

// Árbol principal
typedef struct MainTree {
    TreeNode* root;
} MainTree;

// Subárbol
typedef struct SubTree {
    TreeNode* root;
} SubTree;

// Función para insertar un nodo en el árbol principal
void insertMainTree(MainTree* mainTree, int rnt_code, int expiration_date) {
    // Verificar si el árbol está vacío
    if (mainTree->root == NULL) {
        // Si está vacío, el nuevo nodo se convierte en la raíz del árbol
        mainTree->root = createNode(rnt_code, expiration_date);
    } else {
        // Si el árbol no está vacío, buscar la posición adecuada para insertar el nuevo nodo
        TreeNode* currentNode = mainTree->root;
        while (1) {
            // Comparar el código RNT del nodo actual con el código RNT del nuevo nodo
            if (rnt_code < currentNode->rnt_code) {
                // Si el código RNT del nuevo nodo es menor, seguir por el hijo izquierdo
                if (currentNode->left == NULL) {
                    // Si no hay hijo izquierdo, insertar el nuevo nodo aquí
                    currentNode->left = createNode(rnt_code, expiration_date);
                    break;
                } else {
                    // Si hay un hijo izquierdo, avanzar al siguiente nodo
                    currentNode = currentNode->left;
                }
            } else if (rnt_code > currentNode->rnt_code) {
                // Si el código RNT del nuevo nodo es mayor, seguir por el hijo derecho
                if (currentNode->right == NULL) {
                    // Si no hay hijo derecho, insertar el nuevo nodo aquí
                    currentNode->right = createNode(rnt_code, expiration_date);
                    break;
                } else {
                    // Si hay un hijo derecho, avanzar al siguiente nodo
                    currentNode = currentNode->right;
                }
            } else {
                // Si el código RNT ya existe en el árbol, no se puede insertar duplicados
                printf("Error: El código RNT %d ya existe en el árbol principal.\n", rnt_code);
                break;
            }
        }
    }
}

// Función para insertar un nodo en el subárbol basado en la fecha de vencimiento
void insertSubTree(SubTree* subTree, int rnt_code, int expiration_date) {
    // Verificar si el subárbol está vacío
    if (subTree->root == NULL) {
        // Si está vacío, el nuevo nodo se convierte en la raíz del subárbol
        subTree->root = createNode(rnt_code, expiration_date);
    } else {
        // Si el subárbol no está vacío, buscar la posición adecuada para insertar el nuevo nodo
        TreeNode* currentNode = subTree->root;
        while (1) {
            // Comparar la fecha de vencimiento del nodo actual con la fecha de vencimiento del nuevo nodo
            if (expiration_date < currentNode->expiration_date) {
                // Si la fecha de vencimiento del nuevo nodo es menor, seguir por el hijo izquierdo
                if (currentNode->left == NULL) {
                    // Si no hay hijo izquierdo, insertar el nuevo nodo aquí
                    currentNode->left = createNode(rnt_code, expiration_date);
                    break;
                } else {
                    // Si hay un hijo izquierdo, avanzar al siguiente nodo
                    currentNode = currentNode->left;
                }
            } else if (expiration_date > currentNode->expiration_date) {
                // Si la fecha de vencimiento del nuevo nodo es mayor, seguir por el hijo derecho
                if (currentNode->right == NULL) {
                    // Si no hay hijo derecho, insertar el nuevo nodo aquí
                    currentNode->right = createNode(rnt_code, expiration_date);
                    break;
                } else {
                    // Si hay un hijo derecho, avanzar al siguiente nodo
                    currentNode = currentNode->right;
                }
            } else {
                // Si la fecha de vencimiento ya existe en el subárbol, no se puede insertar duplicados
                printf("Error: La fecha de vencimiento %d ya existe en el subárbol.\n", expiration_date);
                break;
            }
        }
    }
}

// Función para realizar el recorrido preorden del árbol
void preorderTraversal(TreeNode* node) {
    if (node != NULL) {
        // Imprimir los valores del nodo actual
        printf("%d %d\n", node->rnt_code, node->expiration_date);
        // Recorrer el hijo izquierdo en preorden
        preorderTraversal(node->left);
        // Recorrer el hijo derecho en preorden
        preorderTraversal(node->right);
    }
}

// Función para realizar el recorrido inorden del árbol
void inorderTraversal(TreeNode* node) {
    if (node != NULL) {
        // Recorrer el hijo izquierdo en inorden
        inorderTraversal(node->left);
        // Imprimir los valores del nodo actual
        printf("%d %d\n", node->rnt_code, node->expiration_date);
        // Recorrer el hijo derecho en inorden
        inorderTraversal(node->right);
    }
}

// Función para realizar el recorrido posorden del árbol
void postorderTraversal(TreeNode* node) {
    if (node != NULL) {
        // Recorrer el hijo izquierdo en posorden
        postorderTraversal(node->left);
        // Recorrer el hijo derecho en posorden
        postorderTraversal(node->right);
        // Imprimir los valores del nodo actual
        printf("%d %d\n", node->rnt_code, node->expiration_date);
    }
}

int main() {
    // Crear árbol principal y subárbol
    MainTree mainTree;
    mainTree.root = NULL;

    SubTree subTree;
    subTree.root = NULL;

    // Insertar nodos en el árbol principal
    insertMainTree(&mainTree, 10, 20240517);
    insertMainTree(&mainTree, 5, 20240518);
    insertMainTree(&mainTree, 15, 20240516);

    // Insertar nodos en el subárbol
    insertSubTree(&subTree, 20, 20240519);
    insertSubTree(&subTree, 8, 20240520);
    insertSubTree(&subTree, 25, 20240515);

    // Realizar recorridos
    printf("Recorrido Preorden en árbol principal:\n");
    preorderTraversal(mainTree.root);

    printf("\nRecorrido Inorden en árbol principal:\n");
    inorderTraversal(mainTree.root);

    printf("\nRecorrido Posorden en árbol principal:\n");
    postorderTraversal(mainTree.root);

    printf("\nRecorrido Preorden en subárbol:\n");
    preorderTraversal(subTree.root);

    printf("\nRecorrido Inorden en subárbol:\n");
    inorderTraversal(subTree.root);

    printf("\nRecorrido Posorden en subárbol:\n");
    postorderTraversal(subTree.root);

    return 0;
}
