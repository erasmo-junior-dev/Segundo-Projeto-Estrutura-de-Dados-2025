#ifndef ATRIBUICAO_SALAS_H
#define ATRIBUICAO_SALAS_H

#include "estruturas_e_funcoes.h"

void pegarDado(char *dado, char *dias, char *turno, char *horario, bool chave)
{
    int i = 0, j = 0, k = 0, l = 0;

    while (dado[i] < 'A')
    {
        dias[j++] = dado[i++];
    }

    *turno = dado[i++];

    while (dado[i] < 'A' && i < strlen(dado))
    {
        horario[l++] = dado[i++];
    }
    
    if (chave == true)
    {
        i = 0, j = 0, k = 0, l = 0;
        memset(horario, 0, sizeof(horario));

        *turno = dado[i++];

        while (dado[i] < 'A' && i < strlen(dado))
        {
            horario[l++] = dado[i++];
        }
    }

    return;
}

bool verificarDisponibilidadeHorario(No *lista_de_materias, Materias materia)
{
    char diasMat[6], turnoMat, horarioMat[7];
    memset(diasMat, 0, sizeof(diasMat));
    memset(horarioMat, 0, sizeof(horarioMat));

    pegarDado(materia.horario, diasMat, &turnoMat, horarioMat, false);

    while (lista_de_materias != NULL)
    {   
       char diasMatAnalise[6], turnoMatAnalise, horarioMatAnalise[7];

       pegarDado(lista_de_materias->data->horario, diasMatAnalise, &turnoMatAnalise, horarioMatAnalise, false);

       for (int i = 0; i < strlen(diasMat); i++)
       {
           for (int j = 0; j < strlen(diasMatAnalise); j++)
           {
               if (diasMat[i] == diasMatAnalise[j])
               {
                   if (turnoMat == turnoMatAnalise)
                   {
                       for (int k = 0; k < strlen(horarioMat); k++)
                       {
                           for (int l = 0; l < strlen(horarioMatAnalise); l++)
                               if (horarioMat[k] == horarioMatAnalise[l]) return false;
                       }
                   }
               }
           }
       }

       memset(diasMatAnalise, 0, sizeof(diasMatAnalise));
       memset(horarioMatAnalise, 0, sizeof(horarioMatAnalise));

       lista_de_materias = lista_de_materias->next;
    }

    return true;
}

#endif