#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUTOS 50
#define MAX_ADICAO 10

typedef struct {
    char codigo[10];
    char nome[50];
    float preco;
    int quantidade_disponivel;
    int status;
    int n_vendas;
    int n_compras;
} Produto;

int verificarExistencia(Produto* produtos, int tamanho, char *codigo) {
    for (int i = 0; i < tamanho; i++) {
        if (strcmp(produtos[i].codigo, codigo) == 0) {
            return i;
        }
    }
    return -1;
}

int inserir(Produto* produtos, int *tamanho, Produto novo, int quantidade) {
    if (*tamanho >= MAX_PRODUTOS) {
        return 0;
    }

    if (verificarExistencia(produtos, *tamanho, novo.codigo) != -1) {
        return 0;
    }

    strcpy(produtos[*tamanho].codigo, novo.codigo);
    strcpy(produtos[*tamanho].nome, novo.nome);
    produtos[*tamanho].preco = novo.preco;
    produtos[*tamanho].quantidade_disponivel = quantidade;
    produtos[*tamanho].status = 1;
    produtos[*tamanho].n_vendas = 0;
    produtos[*tamanho].n_compras = 0;
    (*tamanho)++;
    return 1;
}

int remover(Produto* produtos, int *tamanho, char *codigo) {
    int indice = verificarExistencia(produtos, *tamanho, codigo);
    if (indice == -1) {
        return 0;
    }

    for (int i = indice; i < (*tamanho) - 1; i++) {
        produtos[i] = produtos[i + 1];
    }

    (*tamanho)--;
    return 1;
}

void relatorioMaisVendidos(Produto* produtos, int tamanho) {
    Produto temp;
    for (int i = 0; i < tamanho-1; i++) {
        for (int j = 0; j < tamanho-i-1; j++) {
            if (produtos[j].n_vendas < produtos[j+1].n_vendas) {
                temp = produtos[j];
                produtos[j] = produtos[j+1];
                produtos[j+1] = temp;
            }
        }
    }
    printf("Lista ordenada dos produtos mais vendidos:\n");
    for (int i = 0; i < tamanho; i++) {
        printf("%s - %d vendas\n", produtos[i].nome, produtos[i].n_vendas);
    }
}

void relatorioMaisComprados(Produto* produtos, int tamanho) {
    Produto temp;
    for (int i = 0; i < tamanho-1; i++) {
        for (int j = 0; j < tamanho-i-1; j++) {
            if (produtos[j].n_compras < produtos[j+1].n_compras) {
                temp = produtos[j];
                produtos[j] = produtos[j+1];
                produtos[j+1] = temp;
            }
        }
    }
    printf("Lista ordenada dos produtos mais comprados:\n");
    for (int i = 0; i < tamanho; i++) {
        printf("%s - %d compras\n", produtos[i].nome, produtos[i].n_compras);
    }
}

void extratoConta(Produto* produtos, int tamanho) {
    printf("Extrato da conta da padaria:\n");
    for (int i = 0; i < tamanho; i++) {
        printf("Produto: %s | Comprados: %d | Vendidos: %d\n", produtos[i].nome, produtos[i].n_compras, produtos[i].n_vendas);
    }
}

void produtosEmEstoque(Produto* produtos, int tamanho) {
    printf("Produtos em estoque:\n");
    for (int i = 0; i < tamanho; i++) {
        if (produtos[i].status == 1) {
            printf("%s - Disponível: %d\n", produtos[i].nome, produtos[i].quantidade_disponivel);
        }
    }
}

void comprarProduto(Produto* produtos, int tamanho) {
    char codigo[10];
    int quantidade;
    printf("Digite o codigo do produto que deseja comprar: ");
    scanf("%s", codigo);
    getchar();
    int indice = verificarExistencia(produtos, tamanho, codigo);
    if (indice != -1) {
        printf("Digite a quantidade que deseja comprar: ");
        scanf("%d", &quantidade);
        getchar();
        produtos[indice].quantidade_disponivel += quantidade;
        produtos[indice].n_compras += quantidade;
        printf("Compra realizada com sucesso!\n");
    } else {
        printf("Produto não encontrado!\n");
    }
}

void venderProduto(Produto* produtos, int tamanho) {
    char codigo[10];
    int quantidade;
    printf("Digite o codigo do produto que deseja vender: ");
    scanf("%s", codigo);
    getchar();
    int indice = verificarExistencia(produtos, tamanho, codigo);
    if (indice != -1) {
        printf("Digite a quantidade que deseja vender: ");
        scanf("%d", &quantidade);
        getchar();
        if (produtos[indice].quantidade_disponivel >= quantidade) {
            produtos[indice].quantidade_disponivel -= quantidade;
            produtos[indice].n_vendas += quantidade;
            printf("Venda realizada com sucesso!\n");
        } else {
            printf("Quantidade insuficiente em estoque!\n");
        }
    } else {
        printf("Produto não encontrado!\n");
    }
}

int main() {
    Produto produtos[MAX_PRODUTOS];
    int tamanho = 0;
    int opcao;
    int continuar = 1;

    do {
        printf("\nMenu Principal - Padaria\n");
        printf("1. Inserir Produto;\n");
        printf("2. Remover Produto;\n");
        printf("3. Buscar Produto;\n");
        printf("4. Comprar Produto\n");
        printf("5. Vender Produto;\n");
        printf("6. Relatorio de Produtos Mais Vendidos;\n");
        printf("7. Relatorio de Produtos Mais Comprados;\n");
        printf("8. Extrato da Conta da Padaria;\n");
        printf("9. Produtos em Estoque;\n");
        printf("10. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); 

        switch (opcao) {
            case 1: {
                int qtd;
                printf("Digite a quantidade de produtos que deseja adicionar (ou 0 para cancelar): ");
                scanf("%d", &qtd);
                getchar(); 
                if (qtd == 0) {
                    continuar = 0;
                    break;
                }
                if (qtd > MAX_ADICAO) {
                    printf("Você pode adicionar no máximo %d produtos por vez.\n", MAX_ADICAO);
                    break;
                }
                for (int i = 0; i < qtd; i++) {
                    Produto novo;
                    printf("Digite o codigo do novo produto: ");
                    scanf("%s", novo.codigo);
                    getchar(); 
                    printf("Digite o nome do novo produto: ");
                    fgets(novo.nome, sizeof(novo.nome), stdin);
                    novo.nome[strcspn(novo.nome, "\n")] = '\0'; 
                    printf("Digite o preço do novo produto (No formato - Ex: 5.00): ");
                    scanf("%f", &novo.preco);
                    printf("Digite a quantidade disponível do produto: ");
                    scanf("%d", &novo.quantidade_disponivel);
                    getchar();
                    if (inserir(produtos, &tamanho, novo, novo.quantidade_disponivel)) {
                        printf("Produto inserido com sucesso!!\n");
                    } else {
                        printf("Falha ao inserir o produto!\n");
                    }
                }
                break;
            }
            case 2: {
                char codigo[10];
                printf("Digite o codigo do produto a ser removido: ");
                scanf("%s", codigo);
                if (remover(produtos, &tamanho, codigo)) {
                    printf("Produto removido com sucesso!!\n");
                } else {
                    printf("Falha ao remover o produto!\n");
                }
                break;
            }
            case 3: {
                char codigo[10];
                printf("Digite o codigo do produto a buscar: ");
                scanf("%s", codigo);
                int indice = verificarExistencia(produtos, tamanho, codigo);
                if (indice != -1) {
                    printf("Produto encontrado:\n");
                    printf("Codigo: %s\n", produtos[indice].codigo);
                    printf("Nome: %s\n", produtos[indice].nome);
                    printf("Preco: %.2f\n", produtos[indice].preco);
                    printf("Quantidade Disponivel: %d\n", produtos[indice].quantidade_disponivel);
                    printf("Status: %d\n", produtos[indice].status);
                } else {
                    printf("Produto não encontrado!\n");
                }
                break;
            }
            case 4:
                comprarProduto(produtos, tamanho);
                break;
            case 5:
                venderProduto(produtos, tamanho);
                break;
            case 6:
                relatorioMaisVendidos(produtos, tamanho);
                break;
            case 7:
                relatorioMaisComprados(produtos, tamanho);
                break;
            case 8:
                extratoConta(produtos, tamanho);
                break;
            case 9:
                produtosEmEstoque(produtos, tamanho);
                break;
            case 10:
                printf("Sistema Encerrado!\n");
                continuar = 0; 
                break;
            default:
                printf("Opção inválida, tente novamente!\n");
        }
    } while (opcao != 10 && continuar);

    return 0;
}
