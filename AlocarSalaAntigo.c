// void SelecionarSala(){
//     alocarSala(flag_de_sobrou){
//         if(natureza_materia); //-> obg: maior % aluno/sala --> opt: >= 50% sala --> flag
//             --> for(salas)
//                 --> return selecionar a sala --> passou da porcentagem
//                 --> caso passou na porcentagem --> conflitoHorario() --> return true ou false;
//                 --> caso seja true --> vai pra proxima sala 
//                 --> caso seja false --> aloca a sala e verificação se sobrou --> se sobrou --> true;
//         if(tipo_materia == "Computação") // --> seleciona apenas salas do tipo lab
//             --> return alocar a sala --> quanto sobrou --> caso n tenha --> aloca em qualquer uma --> se sobrou -> sobrou = true;
//             --> caso alocou --> conflitoHorario()
//         if(sobrou && natureza_sala == obrigatoria){
//             if(tipo_materia == "Computação") --> seleciona os labs --> verfica se >= 50% --> senao n oferta!
//             else{
//                 --> seleciona qualquer sala que tneha >= 50% --> senao n oferta!
//             }
//         };
//     }
// }

// void SelecionarSala(){} --> principal
// void conflitoHorario(){}
// void alocarSala(){}

// //ERASMO: FUNÇÃO DE CONFLITO DE HORÁRIO, LOOP ALOCARSALA
// //VICTOR: FUNÇÃO ALOCAR SALAS --> IFS()


#include <stdio.h>
#include <stdlib.h>
#include "atribuicao_salas.h"
#include "estruturas_e_funcoes.h"

Sala* SelecionaMelhorSalaTaxaObrigatoria(Sala* s, Materias* m){
    Sala* melhor = NULL;
    double melhorTaxa = -1.0;

    while (s != NULL){
        double taxa = (double)m->alunosDependentes / s->capacidade;
        if(taxa > melhorTaxa){
            melhorTaxa = taxa;
            melhor = s;
        }
        s = s->proxima;   
    }
    
    return melhor;
}


void AlocarSala(No* headMaterias, Sala* headSalas, RelacaoSalaMateriaProfessor** pRel){

    for (No* m = headMaterias; m; m = m->next){

    bool sobrou = false;

    //OBRIGATÓRIA E N COMPUTACAO
    if (strcmp(m->data->tipo, "OBRIGATORIO") == 0 && strcmp(m->data->area, "COMPUTACAO") != 0){
    
        Sala* tSala = headSalas;

        while (tSala != NULL)
        {
            int alunos = m->data->alunosDependentes;
            double taxa = (double)alunos / tSala->capacidade;

            if (taxa >= 0.75 && verificarDisponibilidadeHorario(headMaterias, *m->data)){

                RelacaoSalaMateriaProfessor* novo = malloc(sizeof *novo);
                novo->sala      = tSala;
                novo->materia   = m;
                novo->professor = NULL;
                novo->proxima   = NULL;

                if (*pRel == NULL){
                    *pRel = novo;
                } 
                else{
                    RelacaoSalaMateriaProfessor* tRel = *pRel;
                    while (tRel->proxima) tRel = tRel->proxima;
                    tRel->proxima = novo;
                }

                if(alunos > tSala->capacidade) sobrou = true;
                break;
            }
            
            tSala = tSala->proxima;
        }
    }

    //OPTATIVA E N COMPUTACAO
    if (strcmp(m->data->tipo, "OPTATIVO") == 0 && strcmp(m->data->area, "COMPUTACAO") != 0){
    
        Sala* tSala = headSalas;

        while (tSala != NULL)
        {
            int alunos = m->data->alunosDependentes;
            double taxa = (double)alunos / tSala->capacidade;

            if (taxa >= 0.50 && verificarDisponibilidadeHorario(headMaterias, *m->data)){

                RelacaoSalaMateriaProfessor* novo = malloc(sizeof *novo);
                novo->sala      = tSala;
                novo->materia   = m;
                novo->professor = NULL;
                novo->proxima   = NULL;

                if (*pRel == NULL){
                    *pRel = novo;
                } 
                else{
                    RelacaoSalaMateriaProfessor* tRel = *pRel;
                    while (tRel->proxima) tRel = tRel->proxima;
                    tRel->proxima = novo;
                }

                if(alunos > tSala->capacidade) sobrou = true;
                break;
            }
            
            tSala = tSala->proxima;
        }
    }

    //COMPUTACAO
    if (strcmp(m->data->area, "COMPUTACAO") == 0 && strcmp(m->data->tipo, "OBRIGATORIO") == 0){
    
        Sala* tSala = headSalas;

        while (tSala != NULL)
        {
            int alunos = m->data->alunosDependentes;
            double taxa = (double)alunos / tSala->capacidade;

            if (taxa >= 0.75 && verificarDisponibilidadeHorario(headMaterias, *m->data) && strcmp(tSala->tipo_sala, "laboratorio") == 0){

                RelacaoSalaMateriaProfessor* novo = malloc(sizeof *novo);
                novo->sala      = tSala;
                novo->materia   = m;
                novo->professor = NULL;
                novo->proxima   = NULL;

                if (*pRel == NULL){
                    *pRel = novo;
                } 
                else{
                    RelacaoSalaMateriaProfessor* tRel = *pRel;
                    while (tRel->proxima) tRel = tRel->proxima;
                    tRel->proxima = novo;
                }

                if(alunos > tSala->capacidade) sobrou = true;
                break;
            }
            tSala = tSala->proxima;
        }
    }

    if (strcmp(m->data->area, "COMPUTACAO") == 0 && strcmp(m->data->tipo, "OPTATIVO") == 0){
    
        Sala* tSala = headSalas;

        while (tSala != NULL)
        {
            int alunos = m->data->alunosDependentes;
            double taxa = (double)alunos / tSala->capacidade;

            if (taxa >= 0.50 && verificarDisponibilidadeHorario(headMaterias, *m->data) && strcmp(tSala->tipo_sala, "laboratorio") == 0){

                RelacaoSalaMateriaProfessor* novo = malloc(sizeof *novo);
                novo->sala      = tSala;
                novo->materia   = m;
                novo->professor = NULL;
                novo->proxima   = NULL;

                if (*pRel == NULL){
                    *pRel = novo;
                } 
                else{
                    RelacaoSalaMateriaProfessor* tRel = *pRel;
                    while (tRel->proxima) tRel = tRel->proxima;
                    tRel->proxima = novo;
                }

                if(alunos > tSala->capacidade) sobrou = true;
                break;
            }
            tSala = tSala->proxima;
        }
    }
}
}


void SelecionarSala(No* materias, Sala* salas){

}

int main(){
    return 0;
}