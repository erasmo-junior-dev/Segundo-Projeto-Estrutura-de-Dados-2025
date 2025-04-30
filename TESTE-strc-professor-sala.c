#include <stdio.h>
#include <stdlib.h>

typedef struct Materia{
} Materia;

typedef struct NodeMaterias{
    Materia* materia;       
    struct Node* next;
} NodeMaterias;

typedef struct Professor{
    char nome[256];
    NodeMaterias* lista_materias;   
    char titulacao[50];
} Professor;

typedef struct Sala{
    char nome_sala[50];
    int capacidade;
    char tipo_sala[50];
} Sala;

int main() {
    return 0;
}
