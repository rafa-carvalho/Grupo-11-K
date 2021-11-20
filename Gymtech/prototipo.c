#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define max_email 256
#define max_senha 64

struct usuario {
    char email[max_email];
    char senha[max_senha];
};

char validacao_login(char email[max_email], char senha[max_senha])
{
    FILE *arq;
    char email_atual[max_email], senha_atual[max_senha], checagem = 'F';
    arq = fopen("registros.txt", "r");
    while(fgets(email_atual, max_email, arq) != NULL) {
        if(strcmp(email_atual, email) == 0) {
            /*email_existente*/
            fgets(senha_atual, max_senha, arq);
            if(strcmp(senha_atual, senha) == 0)
                checagem = 'V';
        }
    }
    fclose(arq);
    return checagem;
}

int main(int argc, char const *argv[])
{
    struct usuario user;
    printf("\nLOGIN\n");
    printf("Email: ");
    fgets(user.email, max_email, stdin);
    printf("Senha: ");
    fgets(user.senha, max_email, stdin);
    if(validacao_login(user.email, user.senha) == 'V') {
        printf("Logado com sucesso!\n");
        int opcao;
        char fim;
        while (opcao != 4) {
            printf("\nGYMTECH\n");
            printf("1-Feed\n2-Meus Grupos\n3-Meu Perfil\n4-Sair\n>> ");
            scanf("%d", &opcao);
            switch (opcao) {
            case 1:
                /* feed */
                break;
            case 2:
                /* grupos */
                break;
            case 3:
                /* perfil */
                break;
            case 4:
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