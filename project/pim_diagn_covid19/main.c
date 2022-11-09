#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE 200

/* ---------------------- dados Paciente -----------------------------
    - Nome; CPF; Telefone; Endereço (rua, número, bairro, cidade, estado e CEP)
    - Data de nascimento; E mail; Data do diagnóstico.
    - Comorbidade do paciente (diabetes, obesidade, hipertensão,tuberculose, outros)
*/

//Estrutuda de dados de paciente
struct dados_paciente
{
    char nome[SIZE];
    char email[SIZE];
    int numero, dia, mes, ano;
    char cpf[SIZE], telefone[SIZE], cep[SIZE], diag[SIZE];
    char rua[SIZE], bairro[SIZE], cidade[SIZE], estado[SIZE], comorbidade[10], quais[SIZE];
};
struct dados_paciente pac;

//declaração dos metodos
void menu();
void cadastrar_paciente();
void listar_pacientes();

int main()
{
    menu();
    printf("\n");
    return 0;
}

void menu(){
   int op;

    do{
        //system("cls");
        printf("\n1 - Cadastrar Paciente \n 2 - Listar Paciente");
        printf("\n0 - Sair\n");
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
        case 4:
            break;
        default:
            printf("Opcao invalida.\n\n");
        }
    }while(op != 0);
}

void cadastrar_paciente(){
}
