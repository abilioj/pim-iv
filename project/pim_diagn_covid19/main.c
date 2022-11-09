#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE 200 //tamanho do camos de dados text

/* ---------------------- dados Paciente -----------------------------
    - Nome; CPF; Telefone; Endereço (rua, número, bairro, cidade, estado e CEP)
    - Data de nascimento; E mail; Data do diagnóstico.
    - Comorbidade do paciente (diabetes, obesidade, hipertensão,tuberculose, outros)
*/

//- Estrutuda de dados de paciente
struct dados_paciente
{
    char nome[SIZE];
    char email[SIZE];
    int numero, diaNas, mesNas, anoNas;
    char cpf[11], telefone[15], cep[10], diaDiag[11];
    char rua[SIZE], bairro[SIZE], cidade[SIZE], estado[SIZE], comorbidade[10], quais[SIZE];
};
struct dados_paciente paciente;

// Variaveis Globais
// - ponteiro para struct que armazena data e hora
struct tm *data_hora_atual;

// - variável do tipo time_t para armazenar o tempo em segundos
time_t segundos;

//declaração dos metodos
void menu();
void cadastrar_paciente();
void listar_pacientes();
void listar_pacientes_comorbidade();

int main()
{
    menu();
    printf("\n");
    return 0;
}

void menu(){
    int op;
    do{
        system("cls");
        printf(" -------------------- Menu de Opcoes -------------------- ");
        printf("\n 1 - Cadastrar Paciente \n 2 - Listar todos os Pacientes \n 3 - Listar Pacientes com Comorbidade");
        printf("\n 0 - Sair\n");
        scanf("%d", &op);
        switch(op){
        case 0:
            printf("Fechando! Ate logo...\n\n");
            break;
        case 1:
            cadastrar_paciente();
            break;
        case 2:
            break;
        case 3:
            break;
        default:
            printf("Opcao invalida.\n\n");
        }
    }while(op != 0);
}

void cadastrar_paciente()
{
    int op, dataAtual[3];
    //obtendo o tempo em segundos atual da maquina
    time(&segundos);
    //para converter de segundos para o tempo local
    //utilizamos a função localtime
    data_hora_atual = localtime(&segundos);
    dataAtual[0] = data_hora_atual->tm_mday;
    dataAtual[1] = data_hora_atual->tm_mon+1;
    dataAtual[2] = data_hora_atual->tm_year+1900;

    do{
        system("cls");
        printf(" -------------------- Cadastrar Paciente -------------------- ");
        printf("\n\tData Atual: %d/%d/%d \n", dataAtual[0], dataAtual[1], dataAtual[2]);

        printf("\n\tNome:");
        printf("\n\tCPF:");
        printf("\n\tTelefone:");

        printf("\n\n\n\n Digite: 1) - Para Cadastrar novamente um Paciente ou 0) - Sair dessa opcao\n");
        scanf("%d", &op);

    } while (op != 0);
}
