#include "estruturas_e_funcoes.h"
#include "ler_dados_materias.h"
#include "ler_dados_aluno.h"
#include "ler_dados_professores.h"
#include "atribuicao_salas.h"

int main()
{
    No *lista_de_disciplinas = CreateNewNode();
    lista_de_disciplinas = carregarDados(lista_de_disciplinas);

    Sala *lista_de_salas = carregarDadosSalas();

    controleHistoricoAluno(lista_de_disciplinas);

    Professor *lista_de_professores = carregarDadosProfessores(lista_de_disciplinas);

    return 0;
}
