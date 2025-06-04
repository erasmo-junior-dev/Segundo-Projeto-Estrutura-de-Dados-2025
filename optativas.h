#ifndef OPTATIVAS_H
#define OPTATIVAS_H

#include "estruturas_e_funcoes.h"
#include <string.h>

void optativa(No *materias, OptativasEnfase *optativas)
{
    int i = 0;

    No *aux;

    strcpy(optativas[i].enfase, "COMPUTACAO VISUAL");

    aux = SearchElement("COMP404", materias);
    optativas[i].optativas[0] = aux->data;

    aux = SearchElement("COMP390", materias);
    optativas[i].optativas[1] = aux->data;

    aux = SearchElement("COMP393", materias);
    optativas[i].optativas[2] = aux->data;

    aux = SearchElement("COMP396", materias);
    optativas[i].optativas[3] = aux->data;

    aux = SearchElement("COMP400", materias);
    optativas[i].optativas[4] = aux->data;

    i = 1;

    strcpy(optativas[i].enfase, "SISTEMAS INTELIGENTES");

    aux = SearchElement("COMP404", materias);
    optativas[i].optativas[0] = aux->data;

    aux = SearchElement("COMP390", materias);
    optativas[i].optativas[1] = aux->data;

    aux = SearchElement("COMP393", materias);
    optativas[i].optativas[2] = aux->data;

    aux = SearchElement("COMP397", materias);
    optativas[i].optativas[3] = aux->data;

    aux = SearchElement("COMP401", materias);
    optativas[i].optativas[4] = aux->data;

    i = 2;

    strcpy(optativas[i].enfase, "SISTEMAS DE COMPUTACAO");

    aux = SearchElement("COMP404", materias);
    optativas[i].optativas[0] = aux->data;

    aux = SearchElement("COMP391", materias);
    optativas[i].optativas[1] = aux->data;

    aux = SearchElement("COMP394", materias);
    optativas[i].optativas[2] = aux->data;

    aux = SearchElement("COMP398", materias);
    optativas[i].optativas[3] = aux->data;

    aux = SearchElement("COMP402", materias);
    optativas[i].optativas[4] = aux->data;

    i = 3;

    strcpy(optativas[i].enfase, "SISTEMAS DE INFORMACAO");

    aux = SearchElement("COMP389", materias);
    optativas[i].optativas[0] = aux->data;

    aux = SearchElement("COMP392", materias);
    optativas[i].optativas[1] = aux->data;

    aux = SearchElement("COMP395", materias);
    optativas[i].optativas[2] = aux->data;

    aux = SearchElement("COMP399", materias);
    optativas[i].optativas[3] = aux->data;

    aux = SearchElement("COMP403", materias);
    optativas[i].optativas[4] = aux->data;

    return;
}

#endif