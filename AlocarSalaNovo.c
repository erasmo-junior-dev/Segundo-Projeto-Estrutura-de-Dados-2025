#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "estruturas_e_funcoes.h"
#include "atribuicao_salas.h"

void inserirRelacao(RelacaoSalaMateriaProfessor **pRel, Sala *s, No *m){
    RelacaoSalaMateriaProfessor *novo = malloc(sizeof *novo);
    novo->sala = s;
    novo->materia = m;
    novo->professor = NULL;
    novo->proxima = NULL;

    if (*pRel == NULL){
        *pRel = novo;
    } 
    else{
        RelacaoSalaMateriaProfessor *t = *pRel;
        while (t->proxima) t = t->proxima;
        t->proxima = novo;
    }
}

bool selecionarESalvar(No *headMaterias, RelacaoSalaMateriaProfessor **pRel, No *m, Sala *headSalas, double minTaxa, bool labFilter)
{
    int alunos = m->data->alunosDependentes;
    for (Sala *s = headSalas; s; s = s->proxima) {
        if (labFilter && strcmp(s->tipo_sala, "laboratorio") != 0) continue;

        double taxa = (double)alunos / s->capacidade;
        if (taxa < minTaxa) continue;

        if (!verificarDisponibilidadeHorario(headMaterias, *m->data)) continue;

        inserirRelacao(pRel, s, m);

        return true;
    }
    return false;
}

void AlocarSala(No *headMaterias, Sala *headSalas, RelacaoSalaMateriaProfessor **pRel)
{
    for (No *m = headMaterias; m; m = m->next) {
        bool alocou = false;
        double minTaxa = strcmp(m->data->tipo, "OBRIGATORIO") == 0 ? 0.75 : 0.50;

        bool isComputacao = strcmp(m->data->area, "COMPUTACAO") == 0;

        alocou = selecionarESalvar(headMaterias, pRel, m, headSalas, minTaxa, isComputacao);
        
        if (!alocou) {
            //ainda n fiz essa lógica
        }
    }
}
