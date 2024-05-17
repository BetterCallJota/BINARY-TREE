#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definimos la estructura del nodo del arbol
struct NodoEstudiante {
    int codigo;
    char nombres[50];
    char apellidos[50];
    char fecha_nacimiento[11];
    struct NodoEstudiante* izquierda;
    struct NodoEstudiante* derecha;
};

typedef struct NodoEstudiante NodoEstudiante;

// Declaracion de la funcion guardarRegistro
void guardarRegistro(NodoEstudiante* nodo, FILE* archivo);

// Funcion para crear un nuevo nodo del arbol
NodoEstudiante* crearNodo(int codigo, const char* nombres, const char* apellidos, const char* fecha_nacimiento) {
    // Reservamos espacio en la memoria para el nuevo nodo
    NodoEstudiante* nuevo_nodo = (NodoEstudiante*)malloc(sizeof(NodoEstudiante));
    // Asignamos los valores proporcionados al nuevo nodo
    nuevo_nodo->codigo = codigo;
    strcpy(nuevo_nodo->nombres, nombres);
    strcpy(nuevo_nodo->apellidos, apellidos);
    strcpy(nuevo_nodo->fecha_nacimiento, fecha_nacimiento);
    nuevo_nodo->izquierda = NULL;
    nuevo_nodo->derecha = NULL;
    // Devolvemos el nuevo nodo creado
    return nuevo_nodo;
}

// Funcion para insertar un nuevo estudiante en el arbol
NodoEstudiante* insertarEstudiante(NodoEstudiante* raiz, int codigo, const char* nombres, const char* apellidos, const char* fecha_nacimiento) {
    // Si la raiz es nula, creamos un nuevo nodo y lo devolvemos como raiz del arbol
    if (raiz == NULL) {
        return crearNodo(codigo, nombres, apellidos, fecha_nacimiento);
    }

    // Si el codigo del estudiante es menor o igual al codigo del nodo actual, lo insertamos en la rama izquierda
    if (codigo <= raiz->codigo) {
        raiz->izquierda = insertarEstudiante(raiz->izquierda, codigo, nombres, apellidos, fecha_nacimiento);
    }
    // De lo contrario, lo insertamos en la rama derecha
    else {
        raiz->derecha = insertarEstudiante(raiz->derecha, codigo, nombres, apellidos, fecha_nacimiento);
    }

    // Devolvemos la raiz del arbol despues de la insercion
    return raiz;
}

// Funcion para imprimir el arbol en orden (inorden)
void recorrerInorden(NodoEstudiante* nodo) {
    // Si el nodo actual no es nulo, procedemos a imprimir el arbol
    if (nodo != NULL) {
        // Primero imprimimos los nodos de la rama izquierda
        recorrerInorden(nodo->izquierda);
        // Luego imprimimos los datos del nodo actual
        printf("Apellidos: %s, Codigo: %d, Nombres: %s, Fecha de Nacimiento: %s\n", nodo->apellidos, nodo->codigo, nodo->nombres, nodo->fecha_nacimiento);
        // Finalmente, imprimimos los nodos de la rama derecha
        recorrerInorden(nodo->derecha);
    }
}

// Funcion para buscar el nodo con el codigo dado y eliminarlo del arbol
NodoEstudiante* eliminarEstudiante(NodoEstudiante* raiz, int codigo) {
    // Si la raiz es nula, simplemente la devolvemos
    if (raiz == NULL) {
        return raiz;
    }

    // Si el codigo del estudiante es menor que el codigo del nodo actual, buscamos en la rama izquierda
    if (codigo < raiz->codigo) {
        raiz->izquierda = eliminarEstudiante(raiz->izquierda, codigo);
    }
    // Si el codigo del estudiante es mayor que el codigo del nodo actual, buscamos en la rama derecha
    else if (codigo > raiz->codigo) {
        raiz->derecha = eliminarEstudiante(raiz->derecha, codigo);
    }
    // Si encontramos el nodo con el codigo dado
    else {
        // Si el nodo tiene al menos un hijo nulo, lo eliminamos y devolvemos el otro hijo
        if (raiz->izquierda == NULL) {
            NodoEstudiante* temp = raiz->derecha;
            free(raiz);
            return temp;
        } else if (raiz->derecha == NULL) {
            NodoEstudiante* temp = raiz->izquierda;
            free(raiz);
            return temp;
        }

        // Si el nodo tiene ambos hijos, buscamos el sucesor en orden (el nodo mas pequeno en la rama derecha)
        NodoEstudiante* sucesor = raiz->derecha;
        while (sucesor->izquierda != NULL) {
            sucesor = sucesor->izquierda;
        }

        // Copiamos los datos del sucesor al nodo actual
        raiz->codigo = sucesor->codigo;
        strcpy(raiz->nombres, sucesor->nombres);
        strcpy(raiz->apellidos, sucesor->apellidos);
        strcpy(raiz->fecha_nacimiento, sucesor->fecha_nacimiento);

        // Eliminamos el sucesor
        raiz->derecha = eliminarEstudiante(raiz->derecha, sucesor->codigo);
    }

    // Devolvemos la raiz del arbol despues de la eliminacion
    return raiz;
}

// Funcion para guardar los registros en un archivo de texto
void guardarRegistros(NodoEstudiante* raiz) {
    FILE* archivo = fopen("registros.txt", "w");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }
    guardarRegistro(raiz, archivo);
    fclose(archivo);
}

// Funcion para imprimir el arbol en orden y guardar los registros en un archivo de texto
void recorrerInordenYGuardar(NodoEstudiante* raiz) {
    printf("\nRecorrido Inorden:\n");
    recorrerInorden(raiz);
    guardarRegistros(raiz);
    printf("\nRegistros guardados en el archivo 'registros.txt'.\n");
}

// Funcion para guardar un registro en un archivo de texto
void guardarRegistro(NodoEstudiante* nodo, FILE* archivo) {
    if (nodo != NULL) {
        guardarRegistro(nodo->izquierda, archivo);
        fprintf(archivo, "Apellidos: %s, Codigo: %d, Nombres: %s, Fecha de Nacimiento: %s\n", nodo->apellidos, nodo->codigo, nodo->nombres, nodo->fecha_nacimiento);
        guardarRegistro(nodo->derecha, archivo);
    }
}

int main() {
    // Creamos la raiz del arbol
    NodoEstudiante* raiz = NULL;

    int opcion;
    int codigo;
    char nombres[50];
    char apellidos[50];
    char fecha_nacimiento[11];

    do {
        printf("\nMENU:\n");
        printf("1. Insertar estudiante\n");
        printf("2. Mostrar todos los estudiantes\n");
        printf("3. Eliminar estudiante\n");
        printf("4. Guardar registros en archivo de texto\n");
        printf("5. Salir\n");
        printf("Ingrese su opcion: ");
        scanf("%d", &opcion);

        switch(opcion) {
            case 1:
                printf("\nIngrese los apellidos del estudiante: ");
                getchar(); // Limpiar el buffer del teclado
                fgets(apellidos, sizeof(apellidos), stdin); // Leer la entrada con espacios
                apellidos[strcspn(apellidos, "\n")] = 0; // Eliminar el salto de linea al final
                printf("Ingrese el codigo del estudiante: ");
                scanf("%d", &codigo);
                printf("Ingrese los nombres del estudiante: ");
                scanf("%s", nombres);
                printf("Ingrese la fecha de nacimiento del estudiante (YYYY-MM-DD): ");
                scanf("%s", fecha_nacimiento);
                raiz = insertarEstudiante(raiz, codigo, nombres, apellidos, fecha_nacimiento);
                printf("Estudiante insertado con exito.\n");
                break;
            case 2:
                recorrerInordenYGuardar(raiz);
                break;
            case 3:
                printf("\nIngrese el codigo del estudiante a eliminar: ");
                scanf("%d", &codigo);
                raiz = eliminarEstudiante(raiz, codigo);
                printf("Estudiante eliminado con exito.\n");
                break;
            case 4:
                guardarRegistros(raiz);
                break;
            case 5:
                printf("\nSaliendo del programa...\n");
                break;
            default:
                printf("\nOpcion no valida. Por favor, ingrese una opcion valida.\n");
        }
    } while (opcion != 5);

    // Liberar la memoria asignada para el arbol

    return 0;
}
