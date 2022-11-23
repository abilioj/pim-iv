#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
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
    char cpf[11], telefone[15], cep[10], dataDiag[11];
    char rua[SIZE], bairro[SIZE], cidade[SIZE], estado[SIZE], comorbidade[10], quais[SIZE];
};

struct dados_paciente paciente;

// Variaveis Globais
// - ponteiro de manipular arquivos
FILE *file;
// - ponteiro para struct que armazena data e hora
struct tm *data_hora_atual;
// - variavel do tipo time_t para armazenar o tempo em segundos
time_t segundos;
int count = 0;
// - variavel de url do arquivo txt que guadar os dados Pacientes
char urlArquivosPacientes[] = "dadosPacientes.txt";
// - variavel de url do arquivo txt que guadar os dados Pacientes Diagnosticados com comobidade Risco
char urlArquivosPacientesRisco[] = "dadosPacientesRisco.txt";

//declaração dos metodos
void menu();
void login();
void cadastrar_paciente();
void listar_pacientes();
void listar_pacientes_risco();
void Salvar_no_arquivo();
void Salvar_no_arquivo_risco(int idade);
void lendo_arquivo_risco();

int main(){
    setlocale(LC_ALL, "Portuguese");
    login();
    menu();
    printf("\n");
    return 0;
}

void menu(){
    int op;
    do
    {
        system("cls");
        printf(" -------------------- Menu de Opcoes -------------------- ");
        printf("\n 1 - Cadastrar Paciente \n 2 - Listar todos os Pacientes \n 3 - Listar Pacientes com Comorbidade");
        printf("\n 0 - Sair\n");
        scanf("%d", &op);
        switch(op)
        {
        case 0:
            printf("Fechando! Ate logo...\n\n");
            break;
        case 1:
            cadastrar_paciente();
            break;
        case 2:
            listar_pacientes();
            break;
        case 3:
            listar_pacientes_risco();
            break;
        default:
            printf("Opcao invalida.\n\n");
        }
    }
    while(op != 0);
}

void cadastrar_paciente(){
    int op, opCom, dataAtual[3],anoAtual,idade;
    char textDataAtual[40];
    //obtendo o tempo em segundos atual da maquina
    time(&segundos);
    //para converter de segundos para o tempo local
    //utilizamos a função localtime
    data_hora_atual = localtime(&segundos);
    anoAtual = (data_hora_atual->tm_year+1900);
    strftime(textDataAtual,40,"%d/%m/%Y.",data_hora_atual);

    do
    {
        system("cls");
        printf(" -------------------- Cadastrar Paciente -------------------- ");
        printf("\n\tData Atual: %s \n", textDataAtual);
        printf("\n\tNome:");
        scanf(" %s", &paciente.nome);
        setbuf(stdin, NULL);//limpa o buffer de entrada do teclado
        printf("\n\tCPF:");
        scanf(" %s", &paciente.cpf);
        setbuf(stdin, NULL);//limpa o buffer de entrada do teclado
        printf("\n\tTelefone:");
        scanf(" %s", &paciente.telefone);
        setbuf(stdin, NULL);//limpa o buffer de entrada do teclado
        printf("\n\tEmail:");
        scanf(" %s", &paciente.email);
        setbuf(stdin, NULL);//limpa o buffer de entrada do teclado
        printf("\n\tData de nascimento:");
        printf("\n\tDia: ");
        scanf("%d", &paciente.diaNas);
        setbuf(stdin, NULL);//limpa o buffer de entrada do teclado
        printf("\n\tMes: ");
        scanf("%d", &paciente.mesNas);
        setbuf(stdin, NULL);//limpa o buffer de entrada do teclado
        printf("\n\tAno: ");
        scanf("%d", &paciente.anoNas);
        setbuf(stdin, NULL);//limpa o buffer de entrada do teclado
        printf("\tCEP: ");
        scanf(" %s", &paciente.cep);
        setbuf(stdin, NULL);//limpa o buffer de entrada do teclado
        printf("\tRua: ");
        scanf(" %s", &paciente.rua);
        setbuf(stdin, NULL);//limpa o buffer de entrada do teclado
        printf("\tNumero: ");
        scanf("%d", &paciente.numero);
        setbuf(stdin, NULL);//limpa o buffer de entrada do teclado
        printf("\tBairro: ");
        scanf(" %s", &paciente.bairro);
        setbuf(stdin, NULL);//limpa o buffer de entrada do teclado
        printf("\tCidade: ");
        scanf(" %s", &paciente.cidade);
        setbuf(stdin, NULL);//limpa o buffer de entrada do teclado
        printf("\tEstado: ");
        scanf(" %s", &paciente.estado);
        setbuf(stdin, NULL);//limpa o buffer de entrada do teclado

        strcpy(paciente.dataDiag,textDataAtual);

        printf("O paciente tem alguma comorbidade? 1. Sim / 0. Não ");
        scanf("%d",&opCom);
        setbuf(stdin, NULL);//limpa o buffer de entrada do teclado
        if(opCom==1)
        {
            strcpy(paciente.comorbidade, "SIM");
            printf("Quais? ");
            scanf(" %s", &paciente.quais);
            setbuf(stdin, NULL);//limpa o buffer de entrada do teclado
        }
        else
        {
            strcpy(paciente.comorbidade, "NÂO");
            strcpy(paciente.quais, "...");
        }
        //aqui chamar a função se salva os dados no arquivo
        Salvar_no_arquivo();

        idade = anoAtual - paciente.anoNas;
        if(idade >=65 || opCom == 1 ) Salvar_no_arquivo_risco(idade);

        printf("\n\n\n\n Digite: 1) - Para Cadastrar novamente um Paciente ou 0) - Sair dessa opcao\n");
        scanf("%d", &op);
        setbuf(stdin, NULL);//limpa o buffer de entrada do teclado
    }
    while (op != 0);
}

void listar_pacientes(){
    system("cls");
    printf(" -------------------- listar Paciente -------------------- \n\n");
    lendo_arquivo();
    printf("\n");
    system("pause");
}

void listar_pacientes_risco(){
    system("cls");
    printf(" -------------------- listar Paciente comobidade (Risco) -------------------- \n\n");
    lendo_arquivo_risco();
    printf("\n");
    system("pause");
}

void login(){
    char user[20], password[20];
    printf("\n");
    printf("  **   **  **   **   ****  ******        ******    ****    **   **       ****  **   ** \n");
    printf("  **   **  ***  **    **    **  **        **  **    **     *** ***        **   **   ** \n");
    printf("  **   **  **** **    **    **  **        **  **    **     *******        **    ** **  \n");
    printf("  **   **  ** ****    **    *****   **    *****     **     *******  **    **    ** **  \n");
    printf("  **   **  **  ***    **    **            **        **     ** * **        **     ***   \n");
    printf("  **   **  **   **    **    **            **        **     **   **        **     ***   \n");
    printf("   *****   **   **   ****  ****          ****      ****    **   **       ****     *    \n");
    printf("\n=====================================================================================\n");
    printf("\n                              Faça seu login                                         \n");
    printf("\n=====================================================================================\n");

    while(1)
    {
        printf("Digite seu usuário: ");
        (void)!scanf("%s",user);
        setbuf(stdin, NULL);//limpa o buffer de entrada do teclado
        printf("Digite sua senha: ");
        (void)!scanf("%s",password);
        setbuf(stdin, NULL);//limpa o buffer de entrada do teclado
        //Verifica o usuario e a senha pra entra no sistema
        if(strcmp(user,"admin") == 0 && strcmp(password, "admin") == 0)
        {
            (void)!system("clear");
            break;
        }
        system("cls");
        printf("Seu usuário ou senha está incorreto. Por favor tente novamente.");
        system("pause");
        exit(0);
    }
}

void Salvar_no_arquivo(){
    file = fopen(urlArquivosPacientes,"a");
    if(file == NULL)   //valida se foi possivel abri o arquivo
    {
        printf("Erro, nao foi possivel abrir o arquivo\n e o programa sera fechado!\n");
        system("pause");
        exit(0);
    }
    fprintf(file,"%s ",paciente.nome);
    fprintf(file," %s ", &paciente.cep);
    fprintf(file," %s ", &paciente.cpf);
    fprintf(file," %s ", &paciente.telefone);
    fprintf(file," %s ", &paciente.email);
    fprintf(file," %d", paciente.diaNas);
    fprintf(file,"/%d/", paciente.mesNas);
    fprintf(file,"%d ", paciente.anoNas);
    fprintf(file," %s ", &paciente.rua);
    fprintf(file," %d ", paciente.numero);
    fprintf(file," %s ", &paciente.bairro);
    fprintf(file," %s ", &paciente.cidade);
    fprintf(file," %s ", &paciente.estado);
    fprintf(file," %s ", &paciente.comorbidade);
    fprintf(file," %s ", &paciente.dataDiag);
    fprintf(file," %s \n\n", &paciente.quais);
    fclose(file);
}

void Salvar_no_arquivo_risco(int idade){
    file = fopen(urlArquivosPacientesRisco,"a");
    if(file == NULL)   //valida se foi possivel abri o arquivo
    {
        printf("Erro, nao foi possivel abrir o arquivo\n e o programa sera fechado!\n");
        system("pause");
        exit(0);
    }
    fprintf(file,"idade: %d \n",idade);
    fprintf(file,"cep: %s \n\n", &paciente.cep);
    printf("\n\nO Paciente pertencente ao grupo de risco.");
    fclose(file);
}

void lendo_arquivo(){
    file = fopen(urlArquivosPacientes,"rt");
    if(file == NULL)   //valida se foi possivel abri o arquivo
    {
        printf("Erro, nao foi possivel abrir o arquivo\n e o programa sera fechado!\n");
        system("pause");
        exit(0);
    }
    //while(fscanf(file,"%s %s \n",paciente.nome,paciente.cep) != -1)
    //    printf("%s %s \n",paciente.nome,paciente.cep);

    char linha[500];
    char *result;
    while(!feof(file))
    {
        result = fgets(linha,500,file);//lendo linha por linha do arquivo
        if(result) printf("%s",linha);
    }
    fclose(file);
}

void lendo_arquivo_risco(){
    file = fopen(urlArquivosPacientesRisco,"rt");
    if(file == NULL)   //valida se foi possivel abri o arquivo
    {
        printf("Erro, nao foi possivel abrir o arquivo!\n");
        return;
    }
    char linha[500];
    char *result;
    while(!feof(file))
    {
        result = fgets(linha,500,file);//lendo linha por linha do arquivo
        if(result) printf("%s",linha);
    }
    fclose(file);
}
