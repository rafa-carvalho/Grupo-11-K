#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define max 256
#define max_pontos 500

/*criacao a pilha*/
struct pilha {
    int itens[max_pontos];
    int topo;
};

void iniciar_pilha(struct pilha *p)
{
    p->topo = -1;
}

int pilha_vazia(struct pilha *p)
{
    if(p->topo == -1)
        return 1;
    else
        return 0;
}

int pilha_cheia(struct pilha *p)
{
    if(p->topo == max_pontos-1)
        return 1;
    else
        return 0;
}

void checkin(struct pilha *p, int check)
{
    if(pilha_cheia(p) == 1)
        printf("\nLimite de pontos atingido\n");
    else {
        p->topo++;
        p->itens[p->topo] = check;
    }
}

int gastar(struct pilha *p)
{
    int aux;
    if(pilha_vazia(p) == 1)
        printf("\nVoce não possui nenhum ponto\n");
    else {
        p->topo--;
        return aux;
    }
}

int pontos_total(struct pilha *p)
{
    return p->topo;
}
/*fim*/

struct usuario {
    char email[max];
    char senha[max];
    char nome[max];
    char empresa[max];
    char plano[max];
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

void perfil(char nome_user[max], struct pilha *p)
{
    int opcao_perfil, opcao_compra;
    while (opcao_perfil != 4) {
        printf("\nPerfil: %s", nome_user);
        printf("1-Frequencia\n2-Beneficios\n3-Conquistas\n4-Sair\n>> ");
        scanf("%d", &opcao_perfil);
        switch (opcao_perfil) {
        case 1:
            printf("\n%d pontos\n", pontos_total(p));
            break;
        case 2:
            printf("\n%d pontos\n", pontos_total(p));
            printf("*Pagina com produtos* EX:\n(1) CUPOM 10%% XXX - 10 pontos\n>> ");
            scanf("%d", &opcao_compra);
            switch (opcao_compra) {
            case 1:
                if(pontos_total(p) >= 10) {
                    for(int i = 0; i < 10; i++)
                        gastar(p);
                }
                else
                    printf("Voce nao tem pontos suficiente\n");
                break;
            default:
                break;
            }
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
    /*alocando a pilha*/
    struct pilha *p = (struct pilha*)malloc(sizeof(struct pilha));
    /*fim*/

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
                fgets(user.plano, max, arq);
            }
        }
        fclose(arq);
        /*fim*/
        int opcao;
        char fim;
        while (opcao != 4) {
            printf("\nGYMTECH\n");
            printf("1-Pesquisar\n2-Meus Grupos\n3-Meu Perfil\n4-Check-In\n5-Sair\n>> ");
            scanf("%d", &opcao);
            switch (opcao) {
            case 1:
                buscar();
                break;
            case 2:
                /*grupos*/
                break;
            case 3:
                perfil(user.nome, p);
                break;
            case 4:
                if(strcmp(user.plano, "Basic\n") == 0) {
                    checkin(p, 1);
                }
                else if(strcmp(user.plano, "Silver\n") == 0) {
                    for(int i = 0; i < 2; i++)
                        checkin(p, 1);
                }
                else if(strcmp(user.plano, "Gold\n") == 0) {
                    for(int i = 0; i < 3; i++)
                        checkin(p, 1);
                }
                else if(strcmp(user.plano, "Platinum\n") == 0) {
                    for(int i = 0; i < 4; i++)
                        checkin(p, 1);
                }
                else if(strcmp(user.plano, "Black\n") == 0) {
                    for(int i = 0; i < 5; i++)
                        checkin(p, 1);
                }
                printf("Check-in confirmado!\n");
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

    free(p);
    return 0;
}