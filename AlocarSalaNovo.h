#ifndef ALLOCARSALANOVO_C
#define ALLOCARSALANOVO_C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "estruturas_e_funcoes.h"
#include "atribuicao_salas.h"

void inserirRelacao(RelacaoSalaMateriaProfessor **pRel, Sala *s, No *m){
    RelacaoSalaMateriaProfessor *novo = (RelacaoSalaMateriaProfessor *) malloc(sizeof(RelacaoSalaMateriaProfessor));
    novo->sala = s;
    novo->materia = (No *) malloc(sizeof(No));
    *novo->materia = *m;
    novo->materia->next = NULL;
    novo->professor = NULL;
    novo->proxima = NULL;

    if (*pRel == NULL){
        *pRel = novo;
    } 
    else{
        novo->proxima = *pRel;
        *pRel = novo;
    }
}

bool selecionarESalvar(No *headMaterias, RelacaoSalaMateriaProfessor **pRel, No *m, Sala *headSalas, double minTaxa, bool labFilter)
{
    for (Sala *s = headSalas; s; s = s->proxima) {
        if (labFilter && strcmp(s->tipo_sala, "laboratorio") != 0) continue;

        double taxa = (double)m->data->alunosDependentes / s->capacidade;
        if (taxa < minTaxa) continue;
        else if (taxa > 1.0) continue;

        RelacaoSalaMateriaProfessor *aux = *pRel;

        if (aux != NULL){
            while (aux && strcmp(aux->sala->nome_sala, s->nome_sala) != 0){
                aux = aux->proxima;
            }

            if (aux && !verificarDisponibilidadeHorario(aux->materia, *m->data)) continue;
        }

        inserirRelacao(pRel, s, m);
        m->data->alunosDependentes -= s->capacidade;

        return true;
    }
    return false;
}


Sala* SelecionaMelhorSalaTaxaObrigatoria(Sala* s, Materias* m, RelacaoSalaMateriaProfessor **pRel){
    Sala* melhor = NULL;
    double melhorTaxa = -1.0;

    while (s != NULL){
        double taxa = (double)m->alunosDependentes / s->capacidade;
        if(taxa > melhorTaxa){
            RelacaoSalaMateriaProfessor *aux = *pRel;

            if (aux != NULL){
                while (aux && strcmp(aux->sala->nome_sala, s->nome_sala) != 0){
                    aux = aux->proxima;
                }

                if (aux && !verificarDisponibilidadeHorario(aux->materia, *m)) {
                    s = s->proxima;
                    continue;
                }
            }

            melhorTaxa = taxa;
            melhor = s;
        }
        s = s->proxima;   
    }
    
    return melhor;
}

void AlocarSala(No *headMaterias, Sala *headSalas, RelacaoSalaMateriaProfessor **pRel)
{
    for (No *m = headMaterias; m; m = m->next) {
        if (strcmp(m->data->cod_comp, "TCC0296") == 0) continue;
        bool alocou = false;

        double minTaxa = strcmp(m->data->tipo, "OBRIGATORIO") == 0 ? 0.75 : 0.50;

        bool isComputacao = strcmp(m->data->area, "COMPUTACAO") == 0;

        alocou = selecionarESalvar(headMaterias, pRel, m, headSalas, minTaxa, isComputacao);
        
        if (!alocou) {
            if(isComputacao && minTaxa == 0.5){
                alocou = selecionarESalvar(headMaterias,pRel,m,headSalas,minTaxa,false);
            }
            if(minTaxa == 0.5 && !alocou){
                Sala* melhorSala = SelecionaMelhorSalaTaxaObrigatoria(headSalas, m->data, pRel);
                if(melhorSala != NULL){
                    inserirRelacao(pRel,melhorSala,m);
                    m->data->alunosDependentes -= melhorSala->capacidade;
                }
        }
        }
        else if(m->data->alunosDependentes > 0){
            selecionarESalvar(headMaterias,pRel,m,headSalas,0.50,isComputacao);
        }
    }
}

#endif
