#include "estruturas_e_funcoes.h"
#include "ler_dados_materias.h"
#include "ler_dados_aluno.h"

int main()
{
    No *disciplinas = CreateNewNode();

    carregarDados(disciplinas);
    controleHistoricoAluno();

    return 0;
}