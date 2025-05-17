#ifndef ATRIBUICAO_SALAS_H
#define ATRIBUICAO_SALAS_H

#include "estruturas_e_funcoes.h"

bool horariosConflitam(const char *h1, const char *h2) {
    char dias1[10], dias2[10];
    char turno1 = '\0', turno2 = '\0';
    char blocos1[10], blocos2[10];
    
    int i = 0, j = 0;

    while (h1[i] && h1[i] >= '0' && h1[i] <= '9')
        dias1[j++] = h1[i++];
    dias1[j] = '\0';
    turno1 = h1[i++];
    j = 0;
    while (h1[i] && h1[i] >= '0' && h1[i] <= '9')
        blocos1[j++] = h1[i++];
    blocos1[j] = '\0';

    i = 0; j = 0;
    
    while (h2[i] && h2[i] >= '0' && h2[i] <= '9')
        dias2[j++] = h2[i++];
    dias2[j] = '\0';
    turno2 = h2[i++];
    j = 0;
    while (h2[i] && h2[i] >= '0' && h2[i] <= '9')
        blocos2[j++] = h2[i++];
    blocos2[j] = '\0';

    for (int d1 = 0; dias1[d1]; d1++) {
        for (int d2 = 0; dias2[d2]; d2++) {
            if (dias1[d1] == dias2[d2]) {
                if (turno1 == turno2) {
                    for (int b1 = 0; blocos1[b1]; b1++) {
                        for (int b2 = 0; blocos2[b2]; b2++) {
                            if (blocos1[b1] == blocos2[b2]) {
                                return true;
                            }
                        }
                    }
                }
            }
        }
    }

    return false;
}

bool verificarDisponibilidadeHorario(No *lista_de_materias, Materias novaMateria)
{
    while (lista_de_materias != NULL) {
        if (horariosConflitam(lista_de_materias->data->horario, novaMateria.horario)) {
            return false;
        }
        lista_de_materias = lista_de_materias->next;
    }
    return true;
}

#endif