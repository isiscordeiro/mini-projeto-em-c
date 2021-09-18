// bibliotecas utilizadas
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <ctype.h>
#include <time.h>
#include <locale.h>


// estrutura de cadastro
typedef struct {
    int codigo;
    char cpf[15];
    char nome[50];
    char sexo[20];
    char fone[16];
    char email[80];
    int idade;
    char plano[50];
    int dependente;
    float valor;
    int dia_venc;
    int mes_venc;
} TDados;


typedef struct {
    int mesf;
} Func;


FILE *pdados;


Func f;
TDados d_aux, d_nulo;


// abre o arquivo
void abre_arquivo() {
    pdados = fopen("dados.txt", "r+b");
    if (pdados == NULL) {
        pdados = fopen("dados.txt", "w+b");
    }
}


/*
opção '1'
*/


// insere os dados
void inserir() {
    int resp;
    int i;
    
    do {
        printf("Cadastrar Cliente");
        system("CLS");
        
        // armazena int id
        printf("ID: ");
        scanf("%d", &d_aux.codigo);
        
        // armazena char cpf
        printf("\n> Formato: 000.000.000-00");
        printf("\nCPF: ");
        fflush(stdin);
        gets(d_aux.cpf);
        
        // armazena char nome
        printf("\nNome: ");
        fflush(stdin);
        gets(d_aux.nome);
        
        // armazena char sexo
        fflush(stdin);
        int input;
                
        do {
            printf("\nSexo (1-F/2-M): ");
            scanf("%i", &input);
            if (input == 1) {
                strcpy(d_aux.sexo, "F");
                break;
            } else if (input == 2) {
                strcpy(d_aux.sexo, "M");
                break;
            } else {
                printf("\n[!] Opção inválida\n");
            }
        } while (input != 1 || input != 2);
        
        // armazena char fone
        printf("\n> Formato: (00)00000-0000");
        printf("\nFone: ");
        fflush(stdin);
        gets(d_aux.fone);
        
        // armazena char email
        printf("\nE-mail: ");
        fflush(stdin);
        gets(d_aux.email);
        
        // armazena int idade
        int dia, mes, ano;
        int atual;
        time_t data_ano;
        time(&data_ano);
                
        printf("\n> Formato: DD MM AAAA");
        printf("\nData de Nascimento: ");
        scanf("%d %d %d", &dia, &mes, &ano);
                
        struct tm *data = localtime(&data_ano);
        atual = (data->tm_year + 1900);
        d_aux.idade = atual - ano;
                
        // armazena char plano, int valor
        system("CLS");
        printf("\t\tTipo de plano\n");
        printf("\n1 - Ouro\n2 - Diamante\n3 - Prata\n4 - Esmeralda\n\n");
                
        do {
            printf(">> ");
            scanf("%i", &input);
            if (input == 1) {
                strcpy(d_aux.plano, "Ouro");
                d_aux.valor = 300;
                break;
            } else if (input == 2) {
                strcpy(d_aux.plano, "Diamante");
                d_aux.valor = 400;
                break;
            } else if (input == 3) {
                strcpy(d_aux.plano, "Prata");
                d_aux.valor = 200;
                break;
            } else if (input == 4) {
                strcpy(d_aux.plano, "Esmeralda");
                d_aux.valor = 500;
                break;
            } else {
                printf("\n[!] Opção inválida\n\n");
            }

        } while (input != 1 || input != 2 || input != 3 || input != 4);
        
        // armazena int dependente
        printf("\nDependente(s): ");
        scanf("%d", &d_aux.dependente);
        
        // condições de desconto e aumento
        if((strcmp("F", d_aux.sexo) == 0) && d_aux.idade >= 13 && d_aux.idade < 35) {
            d_aux.valor += ((d_aux.valor*30)/100);
        } if(d_aux.dependente>1) {
            d_aux.valor -= ((d_aux.valor*20)/100);
        } if(d_aux.idade < 13) {
            d_aux.valor -= ((d_aux.valor*30)/100);
        } if(d_aux.idade >= 60) {
            d_aux.valor += ((d_aux.valor*40)/100);
        }
                
        // armaneza int dia_venc, int mes_venc
        printf("\n> Formato: DD MM");
        printf("\nData de Vencimento: ");
        scanf("%d %d", &d_aux.dia_venc, &d_aux.mes_venc);
                
        // armazena dados de terceiros
        char cpft[20];
        char nomet[50];
        int diat;
        int mest;
        int anot;
                
        printf("\n> Formato: 000.000.000-00");
        printf("\nCPF - Terceiro: ");
        fflush(stdin);
        gets(cpft);
        
        printf("\nNome - Terceiro: ");
        fflush(stdin);
        gets(nomet);
                
        printf("\n> Formato: DD MM AAAA");
        printf("\nData de Nascimento - Terceiro: ");
        scanf("%d %d %d", &diat, &mest, &anot);
        
        fseek(pdados, 0, SEEK_END);
        fwrite(&d_aux, sizeof(TDados), 1, pdados);
        
        system("CLS");
        
        printf("[!] Cliente cadastrado com sucesso\n");
        
        printf("\nInforme se deseja cadastrar outro cliente (1-Sim/0-Não): ");
        scanf("%d", &resp);
        
    } while (resp ==1);
    
    system("CLS");
    
}
    
// função auxiliar
int procura(int codigop) {
    int p = 0;
    int i;
    
    rewind(pdados);
    fread(&d_aux, sizeof(TDados), 1, pdados);
    
    while (feof(pdados) == 0) {
        if (d_aux.codigo == codigop) {
            return p;
        } else {
            fread(&d_aux, sizeof(TDados), 1, pdados);
            p++;
        }
    }
    
    return -1;
    
}


// função auxiliar
void mostra(int pos) {
    fseek(pdados, pos*sizeof(TDados), SEEK_SET);
    fread(&d_aux, sizeof(TDados), 1, pdados);
    
    printf("\n");
    printf("ID.................: %d\n", d_aux.codigo);
    printf("CPF................: %s\n", d_aux.cpf);
    printf("Nome...............: %s\n", d_aux.nome);
    printf("Sexo...............: %s\n", d_aux.sexo);
    printf("Fone...............: %s\n", d_aux.fone);
    printf("E-mail.............: %s\n", d_aux.email);
    printf("Idade..............: %d\n", d_aux.idade);
    printf("Plano..............: %s\n", d_aux.plano);
    printf("Dependente(s)......: %d\n", d_aux.dependente);
    printf("Valor do Plano.....: R$%.2f\n", d_aux.valor);
    printf("Vencimento do Plano: %d/%d\n", d_aux.dia_venc, d_aux.mes_venc);
    
}


/*
opção '2'
*/


void alterar() {
    int codigoalt, op, conf, resp, posicao, input;
    
    do {
        printf("\t\t\tEditar Cliente\n\n");
        printf("ID do Cliente: ");
        scanf("%d", &codigoalt);
        posicao = procura(codigoalt);
        if (posicao == -1) {
            printf("\n[!] Cliente não encontrado\n");
        } else {
            mostra(posicao);
            printf("\n");
            printf("1- CPF\n2- Nome\n3- Fone\n4- E-mail\n5- Plano\n6- Dependente(s)\n7- Vencimento do Plano\n0- Sair\n");
            printf("\nEscolha uma opção para editar: ");
            scanf("%d", &op);
            switch(op) {
                case 1:
                printf("\nInforme se deseja alterar o CPF do Cliente (1-Sim/0-Não): ");
                scanf("%d", &conf);
                if (conf == 1) {
                    printf("\nNovo CPF: ");
                    fflush(stdin);
                    gets(d_aux.cpf);
                } else {
                    printf("\n[!] Alteração cancelada\n");
                    printf("\nPressione ENTER para continuar...");
                    getch();
                    main();
                }
                break;
                case 2:
                printf("\nInforme se deseja alterar o Nome (1-Sim/0-Não): ");
                scanf("%d", &conf);
                if (conf == 1) {
                    printf("\nNovo Nome: ");
                    fflush(stdin);
                    gets(d_aux.nome);
                } else {
                    printf("\n[!] Alteração cancelada\n");
                    printf("\nPressione ENTER para continuar...");
                    getch();
                    main();
                }
                break;
                case 3:
                printf("\nInforme se deseja alterar o Fone (1-Sim/0-Não): ");
                scanf("%d", &conf);
                if (conf == 1) {
                    printf("\nNovo Fone: ");
                    fflush(stdin);
                    gets(d_aux.fone);
                } else {
                    printf("\n[!] Alteração cancelada\n");
                    printf("\nPressione ENTER para continuar...");
                    getch();
                    main();
                }
                break;
                case 4:
                printf("\nInforme se deseja alterar o E-mail (1-Sim/0-Não): ");
                scanf("%d", &conf);
                if (conf == 1) {
                    printf("\nNovo E-mail: ");
                    fflush(stdin);
                    gets(d_aux.email);
                } else {
                    printf("\n[!] Alteração cancelada\n");
                    printf("\nPressione ENTER para continuar...");
                    getch();
                    main();
                }
                break;
                case 5:
                printf("\nInforme se deseja alterar o Plano (1-Sim/0-Não): ");
                scanf("%d", &conf);
                if (conf == 1) {
                    printf("\n\t\tTipo de plano\n");
                    printf("\n1 - Ouro\n2 - Diamante\n3 - Prata\n4 - Esmeralda\n\n");
                    do {
                        printf(">> ");
                        scanf("%i", &input);
                        if (input == 1) {
                            strcpy(d_aux.plano, "Ouro");
                            d_aux.valor = 300;
                            break;
                        } else if (input == 2) {
                            strcpy(d_aux.plano, "Diamante");
                            d_aux.valor = 400;
                            break;
                        } else if (input == 3) {
                            strcpy(d_aux.plano, "Prata");
                            d_aux.valor = 200;
                            break;
                        } else if (input == 4) {
                            strcpy(d_aux.plano, "Esmeralda");
                            d_aux.valor = 500;
                            break;
                        } else {
                            printf("\n[!] Opção inválida\n\n");
                        }
                    } while (input != 1 || input != 2 || input != 3 || input != 4);
                                                
                    // condições de desconto e aumento
                    if((strcmp("F", d_aux.sexo) == 0) && d_aux.idade >= 13 && d_aux.idade < 35) {
                        d_aux.valor += ((d_aux.valor*30)/100);
                    } if(d_aux.dependente > 1){
                        d_aux.valor -= ((d_aux.valor*20)/100);
                    } if(d_aux.idade < 13){
                        d_aux.valor -= ((d_aux.valor*30)/100);
                    } if(d_aux.idade>=60){
                        d_aux.valor += ((d_aux.valor*40)/100);        
                    }
                                                
                } else {
                    printf("\n[!] Alteração cancelada\n");
                    printf("\nPressione ENTER para continuar...");
                    getch();
                    main();
                }
                break;
                case 6:
                printf("\nInforme se deseja alterar o(s) Dependente(s) (1-Sim/0-Não): ");
                scanf("%d", &conf);
                if (conf == 1) {
                    printf("\nNovo número de Dependentes: ");
                    scanf("%d", &d_aux.dependente);
                                                
                    // condições de desconto e aumento
                    if((strcmp("F", d_aux.sexo) == 0) && d_aux.idade >= 13 && d_aux.idade < 35) {
                        d_aux.valor += ((d_aux.valor*30)/100);
                    } if(d_aux.dependente > 1){
                        d_aux.valor -= ((d_aux.valor*20)/100);
                    } if(d_aux.idade < 13){
                        d_aux.valor -= ((d_aux.valor*30)/100);
                    } if(d_aux.idade>=60){
                        d_aux.valor += ((d_aux.valor*40)/100);        
                    }
                                                
                } else {
                    printf("\n[!] Alteração cancelada\n");
                    printf("\nPressione ENTER para continuar...");
                    getch();
                    main();
                }
                break;
                case 7:
                printf("\nInforme se deseja alterar o Vencimento do Plano (1-Sim/0-Não): ");
                scanf("%d", &conf);
                if (conf == 1) {
                    printf("\nNova data do Vencimento do Plano: ");
                    scanf("%d %d", &d_aux.dia_venc, &d_aux.mes_venc);
                } else {
                    printf("\n[!] Alteração cancelada\n");
                    printf("\nPressione ENTER para continuar...");
                    getch();
                    main();
                }
                break;
                case 0:
                main();
                break;
                default:
                printf("\n[!] Opção inválida\n");
                system("CLS");
                break;
            }
                    
            system("CLS");
            printf("[!] Processando...\n");
            fseek(pdados, posicao*sizeof(TDados), SEEK_SET);
            fwrite(&d_aux, sizeof(TDados), 1, pdados);
            mostra(posicao);        
        }
                        
        printf("\nInforme se deseja alterar o registro de outro cliente (1-Sim/0-Não): ");
        scanf("%d", &resp);
        system("CLS");
                
    } while (resp == 1);
    
}


/*
opção '3'
*/


void remover() {
    int codigorem, conf, resp, posicao;
    d_nulo.codigo = 0;
    
    do {
        printf("\t\t\tRemover Cliente\n\n");
        printf("ID: ");
        scanf("%d", &codigorem);
        posicao = procura(codigorem);
        if (posicao == -1) {
            printf("\n[!] Cliente não encontrado\n");
        } else {
            mostra(posicao);
            printf("\nInforme se deseja remover esse cliente (1-Sim/0-Não): ");
            scanf("%d", &conf);
        } if (conf == 1) {
            fseek(pdados, posicao*sizeof(TDados),SEEK_SET);
            fwrite( &d_nulo, sizeof(TDados), 1, pdados);
            printf("\n[!] Cliente removido com sucesso\n");
        } if (conf == 2) {
            printf("\n[!] Operação cancelada\n");
        }
        
        printf("\nInforme se deseja remover outro cliente (1-Sim/0-Não): ");
        scanf("%d", &resp);
        system("CLS");
        
    } while (resp ==1);
    
}


/*
opção '4'
*/


void listar() {
    printf("\t\tTela de Listagem Geral\n\n");
    
    rewind(pdados);
    fread(&d_aux, sizeof(TDados), 1, pdados);
    
    if (feof(pdados) != 0) {
        printf("[!] Lista vazia\n");
    }
        
    while (feof(pdados) == 0) {
        if (d_aux.codigo != 0) {
            printf("ID.................: %d\n", d_aux.codigo);
            printf("CPF................: %s\n", d_aux.cpf);
            printf("Nome...............: %s\n", d_aux.nome);
            printf("Sexo...............: %s\n", d_aux.sexo);
            printf("Fone...............: %s\n", d_aux.fone);
            printf("E-mail.............: %s\n", d_aux.email);
            printf("Idade..............: %d\n", d_aux.idade);
            printf("Plano..............: %s\n", d_aux.plano);
            printf("Dependente(s)......: %d\n", d_aux.dependente);
            printf("Valor do Plano.....: R$%.2f\n", d_aux.valor);
            printf("Vencimento do Plano: %d/%d\n", d_aux.dia_venc, d_aux.mes_venc);
            printf("--------------------\n");        
        }
                
        fread(&d_aux, sizeof(TDados), 1, pdados);
                
    }
    
    printf("\nPressione ENTER para continuar...");
    getch();
    system("CLS");
    
}


/*
opção '5'
*/


void plano() {    
}


/*
opção '6'
*/


int procura_venc(int str3) {
    int p = 0;
    
    rewind(pdados);
    
    fread(&d_aux, sizeof(TDados), 1, pdados);
    
    while (feof(pdados) == 0) {
        if (d_aux.mes_venc == str3) {
            return p;
        } else {
            fread(&d_aux, sizeof(TDados), 1, pdados);
            p++;
        }
    }
    
    return -1;
    
}

void mostre_venc(int pos) {
    fseek(pdados, pos*sizeof(TDados), SEEK_SET);
    fread(&d_aux, sizeof(TDados), 1, pdados);
    
    printf("\n");
    
    while (feof(pdados) == 0) {
        if(d_aux.mes_venc == f.mesf) {
            printf("ID.................: %d\n", d_aux.codigo);
            printf("CPF................: %s\n", d_aux.cpf);
            printf("Nome...............: %s\n", d_aux.nome);
            printf("Sexo...............: %s\n", d_aux.sexo);
            printf("Fone...............: %s\n", d_aux.fone);
            printf("E-mail.............: %s\n", d_aux.email);
            printf("Idade..............: %d\n", d_aux.idade);
            printf("Plano..............: %s\n", d_aux.plano);
            printf("Dependente(s)......: %d\n", d_aux.dependente);
            printf("Valor do Plano.....: R$%.2f\n", d_aux.valor);
            printf("Vencimento do Plano: %d/%d\n", d_aux.dia_venc, d_aux.mes_venc);
            printf("--------------------\n");        
        }
                
        fread(&d_aux, sizeof(TDados), 1, pdados);
    }
    
    printf("\nPressione ENTER para continuar...");
    getch();
    
}


void vencimento() {
    int resp, posicao;
    
    do {
        system("CLS");
        printf("\t\tListagem por Vencimento\n\n");
        printf("Informe o mês que deseja buscar: ");
        scanf("%d", &f.mesf);
        posicao = procura_venc(f.mesf);
        if (posicao == -1) {
            printf("\n[!] Mês não encontrado\n");
            printf("\nPressione ENTER para continuar...");
            getch();
        } else {
            mostre_venc(posicao);
            printf("\nInforme se deseja consultar outro mês (1-Sim/0-Não): ");
            scanf("%d", &resp);
        }
                
    } while (resp == 1);
    
}
    
/*
menu principal
*/
    
main() {
    int op;
    abre_arquivo();
    
    setlocale(LC_ALL, "Portuguese");
    
    do {
        system("CLS");
        printf("\t\t\tTela Inicial");
        printf("\n\nNúcleo Seguros\n\n");
        printf("1- Cadastrar Cliente\n");
        printf("2- Editar Cliente\n");
        printf("3- Remover Cliente\n");
        printf("4- Listagem Geral\n");
        printf("5- Listar por Plano\n");
        printf("6- Listagem dos Vencimentos do Plano de Saúde do Mês\n");
        printf("0- Sair \n");
        printf("\nEscolha uma opção: ");
        scanf("%d", &op);
        
        switch(op) {
        case 1:
            system("cls");
            inserir();
            break;
        case 2:
            system("cls");
            alterar();
            break;
        case 3:
            system("cls");
            remover();
            break;
        case 4:
            system("cls");
            listar();
            break;
        case 5:
            system("cls");
            plano();
            break;
        case 6:
            system("cls");
            vencimento();
            break;
        case 0:
            system("cls");
            fclose(pdados);
            break;
        default:
            printf("\n[!] Opção inválida");
            break;
        }
                 
    } while (op != 0);
    
}