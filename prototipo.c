#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define max 256

struct usuario {
    char email[max];
    char senha[max];
    char nome[max];
    char empresa[max];
    int frequencia;
};

char validacao_login(char email[max], char senha[max])
{
    FILE *arq;
    char email_atual[max], senha_atual[max], checagem = 'F';
    arq = fopen("registros.txt", "r");
    while(fgets(email_atual, max, arq) != NULL) {
        if(strcmp(email_atual, email) == 0) {
            /*email_existente*/
            fgets(senha_atual, max, arq);
            if(strcmp(senha_atual, senha) == 0)
                checagem = 'V';
        }
    }
    fclose(arq);
    return checagem;
}

void ranking_empresas(char empresa_user[max])
{
    FILE *arq;
    char empresa[max];
    int i = 1;
    arq = fopen("ranking.txt", "r");
    while(fgets(empresa, max, arq) != NULL) {
        if(strcmp(empresa, empresa_user) == 0) {
            printf("%d lugar\n", i);
            break;
        }
        i++;
    }
    fclose(arq);
}

void perfil(char nome_user[max], int frequencia)
{
    int opcao_perfil;
    while (opcao_perfil != 4) {
        printf("\nPerfil: %s", nome_user);
        printf("1-Frequencia\n2-Beneficios\n3-Conquistas\n4-Sair\n>> ");
        scanf("%d", &opcao_perfil);
        switch (opcao_perfil) {
        case 1:
            printf("%d pontos\n", frequencia);
            break;
        case 2:
            printf("%d pontos\n", frequencia);
            printf("*Pagina com produtos* EX:\n(1) CUPOM 10%% XXX - xxx pontos\n>> ");
            break;
        case 3:
            /*pagina de trofeus e conquistas*/
            break;
        default:
            break;
        }
    }
}

void buscar()
{
    char nome_buscado[max];
    printf(">> ");
    scanf(" %[^\n]s", nome_buscado);
    FILE *arq;
    char nome[max], checagem = 'F';
    arq = fopen("registros.txt", "r");
    while(fgets(nome, max, arq) != NULL) {
        for(int i = 0; i < strlen(nome); i++) {
            if(nome[i] == '\n')
                nome[i] = NULL;
        }
        if(strcmp(nome, nome_buscado) == 0) {
            printf("Resultados...\n");
            checagem = 'V';
        }
    }
    fclose(arq);
    if(checagem == 'F')
        printf("Nenhum resultado encontrado.\n");
}

int main(int argc, char const *argv[])
{
    struct usuario user;
    /*cadastro feito pela propria empresa*/
    printf("\nLOGIN\n");
    printf("Email: ");
    fgets(user.email, max, stdin);
    printf("Senha: ");
    fgets(user.senha, max, stdin);
    if(validacao_login(user.email, user.senha) == 'V') {
        printf("Logado com sucesso!\n");
        /*coleta das informações do perfil*/
        FILE *arq;
        char email_atual[max], senha_atual[max];
        arq = fopen("registros.txt", "r");
        while(fgets(email_atual, max, arq) != NULL) {
            if(strcmp(email_atual, user.email) == 0) {
                fgets(senha_atual, max, arq);
                fgets(user.nome, max, arq);
                fgets(user.empresa, max, arq);
                fscanf(arq, "%d", &user.frequencia);
            }
        }
        fclose(arq);
        /*fim*/
        int opcao;
        char fim;
        while (opcao != 4) {
            printf("\nGYMTECH\n");
            printf("1-Pesquisar\n2-Meus Grupos\n3-Meu Perfil\n4-Ranking Empresa\n5-Sair\n>> ");
            scanf("%d", &opcao);
            switch (opcao) {
            case 1:
                buscar();
                break;
            case 2:
                /*grupos*/
                break;
            case 3:
                perfil(user.nome, user.frequencia);
                break;
            case 4:
                printf("Ranking: %s", user.empresa);
                ranking_empresas(user.empresa);
                break;
            case 5:
                printf("Voce tem certeza? (S) (N)\n>> ");
                scanf(" %c", &fim);
                break;
            default:
                break;
            }
            if (fim == 'S' || fim == 's')
                break;
            else
                opcao = 0;
        }
    }
    else
        printf("Login invalido\n");
    return 0;
}