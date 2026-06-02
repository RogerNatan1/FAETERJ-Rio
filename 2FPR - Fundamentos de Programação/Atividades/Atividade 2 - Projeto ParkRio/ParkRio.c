/*
 * ParkRio - Sistema de Gerenciamento de Estacionamento
 * Trabalho II - Fundamentos de Programação 2026/1
 *
 * Estrutura da matriz 3D: vagas[ANDARES][FILAS][COLUNAS]
 *   - ANDARES = 10  (índices 0 a 9, letras A a J)
 *   - FILAS   = 8   (índices 0 a 7)
 *   - COLUNAS = 10  (índices 1 a 10)
 *   - Total: 10 × 8 × 10 = 800 vagas
 *   - Andares 0-3 (A-D): mensalistas
 *   - Andares 4-9 (E-J): rotativos
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

/* =========================================================
 * CONSTANTES
 * ========================================================= */
#define ANDARES  10
#define FILAS     8
#define COLUNAS  10
#define MAX_PLACA  8   /* ex: "ABC1D23\0" */
#define MAX_FONE  15
#define ANDAR_ROTATIVO_INICIO 4  /* andares 0-3: mensalistas; 4-9: rotativos */
#define MENSALIDADE 500.00

/* =========================================================
 * STRUCTS
 * ========================================================= */

/* Data simples para controle de vencimento */
typedef struct {
    int dia;
    int mes;
    int ano;
} Data;

/* Cada vaga na matriz */
typedef struct {
    char  id[8];          /* ex: "B0104"                          */
    int   ocupada;        /* 0 = livre, 1 = ocupada               */
    int   tipo;           /* 0 = vaga de mensalista, 1 = rotativo */
    char  placa[MAX_PLACA];
    char  telefone[MAX_FONE]; /* só para mensalistas              */
    Data  cadastro;           /* data de cadastro/vencimento      */
    time_t entrada;           /* timestamp da entrada (rotativo)  */
} Vaga;

/* =========================================================
 * VARIÁVEL GLOBAL: MATRIZ TRIDIMENSIONAL
 *
 * vagas[andar][fila][coluna]
 * Acesso: vagas[2][0][3] = andar C, fila 1, coluna 4 -> "C0104"
 * ========================================================= */
Vaga vagas[ANDARES][FILAS][COLUNAS];

/* =========================================================
 * FUNÇÕES AUXILIARES
 * ========================================================= */

/* Gera o ID da vaga a partir da posição na matriz */
void gerarId(char *id, int andar, int fila, int coluna) {
    /* Letra do andar: 0->A, 1->B, etc. */
    char letra = 'A' + andar;
    /* Fila e coluna com base 1 para exibição */
    sprintf(id, "%c%02d%02d", letra, fila + 1, coluna + 1);
}

/* Inicializa toda a matriz com valores padrão */
void inicializarMatriz(void) {
    int a, f, c;
    for (a = 0; a < ANDARES; a++) {
        for (f = 0; f < FILAS; f++) {
            for (c = 0; c < COLUNAS; c++) {
                gerarId(vagas[a][f][c].id, a, f, c);
                vagas[a][f][c].ocupada = 0;
                /* Andares 0-3 são reservados a mensalistas */
                vagas[a][f][c].tipo = (a < ANDAR_ROTATIVO_INICIO) ? 0 : 1;
                strcpy(vagas[a][f][c].placa, "");
                strcpy(vagas[a][f][c].telefone, "");
                vagas[a][f][c].cadastro.dia = 0;
                vagas[a][f][c].cadastro.mes = 0;
                vagas[a][f][c].cadastro.ano = 0;
                vagas[a][f][c].entrada = 0;
            }
        }
    }
}

/* Retorna 1 se as datas têm o mesmo dia do mês (vencimento) */
int mesmosDia(Data d1, Data d2) {
    return d1.dia == d2.dia;
}

/* Obtém a data atual */
Data dataAtual(void) {
    time_t agora = time(NULL);
    struct tm *t = localtime(&agora);
    Data d;
    d.dia = t->tm_mday;
    d.mes = t->tm_mon + 1;
    d.ano = t->tm_year + 1900;
    return d;
}


/* =========================================================
 * BUSCA DE VAGAS
 * ========================================================= */

/*
 * Localiza a vaga mais próxima disponível para o tipo informado.
 * "Mais próxima" = menor índice de andar, depois fila, depois coluna.
 * Para mensalistas: andares 0-3 (tipo==0)
 * Para rotativos:   andares 4-9 (tipo==1)
 *
 * Retorna 1 se encontrou e preenche *pa, *pf, *pc com os índices.
 */
int buscarVagaDisponivel(int tipoVaga, int *pa, int *pf, int *pc) {
    int inicioAndar = (tipoVaga == 0) ? 0 : ANDAR_ROTATIVO_INICIO;
    int fimAndar    = (tipoVaga == 0) ? ANDAR_ROTATIVO_INICIO : ANDARES;
    int a, f, c;

    for (a = inicioAndar; a < fimAndar; a++) {
        for (f = 0; f < FILAS; f++) {
            for (c = 0; c < COLUNAS; c++) {
                if (!vagas[a][f][c].ocupada) {
                    *pa = a; *pf = f; *pc = c;
                    return 1;
                }
            }
        }
    }
    return 0; /* sem vagas disponíveis */
}

/* Busca vaga ocupada por uma placa específica no setor rotativo */
int buscarPlacaRotativo(const char *placa, int *pa, int *pf, int *pc) {
    int a, f, c;
    for (a = ANDAR_ROTATIVO_INICIO; a < ANDARES; a++) {
        for (f = 0; f < FILAS; f++) {
            for (c = 0; c < COLUNAS; c++) {
                if (vagas[a][f][c].ocupada &&
                    strcmp(vagas[a][f][c].placa, placa) == 0) {
                    *pa = a; *pf = f; *pc = c;
                    return 1;
                }
            }
        }
    }
    return 0;
}

/* Busca vaga de mensalista pela placa */
int buscarPlacaMensalista(const char *placa, int *pa, int *pf, int *pc) {
    int a, f, c;
    for (a = 0; a < ANDAR_ROTATIVO_INICIO; a++) {
        for (f = 0; f < FILAS; f++) {
            for (c = 0; c < COLUNAS; c++) {
                if (vagas[a][f][c].ocupada &&
                    strcmp(vagas[a][f][c].placa, placa) == 0) {
                    *pa = a; *pf = f; *pc = c;
                    return 1;
                }
            }
        }
    }
    return 0;
}

/* =========================================================
 * CÁLCULO DE TARIFA ROTATIVA
 * ========================================================= */

double calcularTarifa(time_t entrada, time_t saida) {
    double horas = difftime(saida, entrada) / 3600.0;
    double dias  = horas / 24.0;

    if (horas <= 0.5)  return 6.00;
    if (horas <= 1.0)  return 10.00;
    if (horas <= 2.0)  return 15.00;
    if (horas <= 4.0)  return 25.00;
    if (horas <= 6.0)  return 35.00;
    if (horas <= 8.0)  return 50.00;
    if (horas <= 24.0) return 100.00;

    /* 2ª diária em diante: R$50 por dia adicional */
    int diarias = (int)dias;
    return 100.00 + (diarias - 1) * 50.00;
}

/* =========================================================
 * VERIFICAÇÃO DE VENCIMENTO DE MENSALISTAS
 * Percorre todos os andares de mensalistas e libera vagas
 * com pagamento em atraso (mesmo dia do mês = cobrança).
 * ========================================================= */
void verificarVencimentos(void) {
    Data hoje = dataAtual();
    int a, f, c;
    for (a = 0; a < ANDAR_ROTATIVO_INICIO; a++) {
        for (f = 0; f < FILAS; f++) {
            for (c = 0; c < COLUNAS; c++) {
                Vaga *v = &vagas[a][f][c];
                if (v->ocupada && mesmosDia(v->cadastro, hoje)) {
                    printf("[Cobranca] Vaga %s - Placa %s - R$ %.2f vence hoje!\n",
                           v->id, v->placa, MENSALIDADE);
                    /* Simulacao: se nao pagar, libera a vaga */
                    /* Em producao, aqui entraria logica de pagamento real */
                }
            }
        }
    }
}

//Entrada de veiculos
void entradaMensalista(void) {
    char placa[MAX_PLACA];
    int a, f, c;

    printf("Informe a placa do veiculo: ");
    scanf("%7s", placa);

    if (buscarPlacaMensalista(placa, &a, &f, &c)) {
        /* Mensalista já cadastrado */
        printf("Bem-vindo! Sua vaga e: %s\n", vagas[a][f][c].id);
    } else {
        /* Novo mensalista */
        printf("Placa nao encontrada. Realizando novo cadastro...\n");

        if (!buscarVagaDisponivel(0, &a, &f, &c)) {
            printf("[ERRO] Sem vagas de mensalista disponiveis.\n");
            return;
        }

        Vaga *v = &vagas[a][f][c];
        strcpy(v->placa, placa);

        printf("Informe o telefone de contato: ");
        scanf("%14s", v->telefone);

        /* Data de cadastro = hoje */
        v->cadastro = dataAtual();
        v->ocupada  = 1;

        printf("Cadastro realizado! Vaga atribuida: %s\n", v->id);
        printf("Vencimento todo dia %02d do mes. Mensalidade: R$ %.2f\n",
               v->cadastro.dia, MENSALIDADE);
    }
}

void entradaRotativo(void) {
    char placa[MAX_PLACA];
    int a, f, c;

    printf("Informe a placa do veiculo: ");
    scanf("%7s", placa);

    /* Verifica se já está estacionado */
    if (buscarPlacaRotativo(placa, &a, &f, &c)) {
        printf("[ERRO] Veiculo com placa %s ja se encontra estacionado na vaga %s.\n",
               placa, vagas[a][f][c].id);
        printf("Informe outra placa.\n");
        return;
    }

    if (!buscarVagaDisponivel(1, &a, &f, &c)) {
        printf("[ERRO] Sem vagas rotativas disponiveis.\n");
        return;
    }

    Vaga *v = &vagas[a][f][c];
    strcpy(v->placa, placa);
    v->entrada = time(NULL);
    v->ocupada = 1;

    printf("Vaga rotativa atribuida: %s\n", v->id);
}


//Saida do veiculo
void saidaRotativo(void) {
    char placa[MAX_PLACA];
    int a, f, c;

    printf("Informe a placa do veiculo: ");
    scanf("%7s", placa);

    if (!buscarPlacaRotativo(placa, &a, &f, &c)) {
        printf("[ERRO] Veiculo nao encontrado no setor rotativo.\n");
        return;
    }

    Vaga *v = &vagas[a][f][c];
    time_t saida = time(NULL);
    double tarifa = calcularTarifa(v->entrada, saida);

    printf("Saida registrada - Vaga: %s | Placa: %s\n", v->id, v->placa);
    printf("Valor a pagar: R$ %.2f\n", tarifa);

    /* Libera a vaga */
    strcpy(v->placa, "");
    v->ocupada = 0;
    v->entrada = 0;
}

void saidaMensalista(void) {
    char placa[MAX_PLACA];
    int a, f, c;

    printf("Informe a placa do veiculo mensalista: ");
    scanf("%7s", placa);

    if (!buscarPlacaMensalista(placa, &a, &f, &c)) {
        printf("[ERRO] Mensalista nao encontrado.\n");
        return;
    }

    printf("Saida registrada - Vaga: %s | Placa: %s\n",
           vagas[a][f][c].id, vagas[a][f][c].placa);
    /* Vaga de mensalista não é liberada na saída — apenas na falta de pagamento */
}

// exibirMenu

void exibirMenu(void) {
    printf("\n===== ParkRio =====\n");
    printf("1. Entrada - Mensalista\n");
    printf("2. Entrada - Rotativo\n");
    printf("3. Saida   - Mensalista\n");
    printf("4. Saida   - Rotativo\n");
    printf("5. Verificar vencimentos\n");
    printf("0. Encerrar\n");
    printf("Opcao: ");
}

/* =========================================================
 * MAIN
 * ========================================================= */

int main(void) {
    const char *ARQUIVO = "parkrio_dados.bin";
    int opcao;

    carregarArquivo(ARQUIVO);

    do {
        exibirMenu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: entradaMensalista();    break;
            case 2: entradaRotativo();      break;
            case 3: saidaMensalista();      break;
            case 4: saidaRotativo();        break;
            case 5: verificarVencimentos(); break;
            case 0: printf("Encerrando...\n"); break;
            default: printf("Opcao invalida.\n");
        }

    } while (opcao != 0);

    salvarArquivo(ARQUIVO);
    return 0;
}
