#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define DELAY 100000
#define MAX_FRASE_LENGTH 100

void ler_texto(char * buffer, int length) {
    fgets(buffer, length, stdin);
    strtok(buffer, "\n");

}

void limparArquivo(const char *nomeArquivo) {
    remove(nomeArquivo);
}

void limpartodosOsArquivos() {
    remove("BOLETO.txt");
    remove("CRITICAS.tx");
}

void limpar_entrada() {
 char c;
 while ((c = getchar()) != '\n' && c != EOF) {}
}

void printSpaces(int n) {
    for (int i = 0; i < n; i++) {
        printf(" ");
    }
}

/////////////////////////

bool validar_nome(const char* nome) {
    for (int i = 0; i < strlen(nome); i++) {
        if (!isalpha(nome[i]) && !isspace(nome[i])) {
            return false;
        }
    }
    return true;
}

void capturar_nome(char* nome) {
    while (true) {
        printf("Digite seu nome: ");
        fgets(nome, 100, stdin);
        
        // Remover o caractere de nova linha '\n' do final da string
        nome[strcspn(nome, "\n")] = '\0';

        if (validar_nome(nome)) {
            return;
        } else {
            printf("Nome inválido. Por favor, digite apenas letras e espaços.\n");
        }
    }
}

////////////////////////

bool validar_cpf(const char* cpf) {
    // Verifica se o CPF possui 11 dígitos
    if (strlen(cpf) != 11) {
        return false;
    }

    // Verifica se todos os dígitos são iguais
    bool todos_iguais = true;
    for (int i = 1; i < 11; i++) {
        if (cpf[i] != cpf[0]) {
            todos_iguais = false;
            break;
        }
    }
    if (todos_iguais) {
        return false;
    }

    // Verifica os dígitos verificadores
    int soma = 0;
    for (int i = 0; i < 9; i++) {
        if (!isdigit(cpf[i])) {
            return false;
        }
        soma += (cpf[i] - '0') * (10 - i);
    }

    int digito_verificador_1 = 11 - (soma % 11);
    if (digito_verificador_1 > 9) {
        digito_verificador_1 = 0;
    }

    if ((cpf[9] - '0') != digito_verificador_1) {
        return false;
    }

    soma = 0;
    for (int i = 0; i < 10; i++) {
        if (!isdigit(cpf[i])) {
            return false;
        }
        soma += (cpf[i] - '0') * (11 - i);
    }

    int digito_verificador_2 = 11 - (soma % 11);
    if (digito_verificador_2 > 9) {
        digito_verificador_2 = 0;
    }

    if ((cpf[10] - '0') != digito_verificador_2) {
        return false;
    }

    return true;
}


void capturar_cpf(char* cpf) {
    while (true) {
        printf("Digite o CPF (apenas números): ");
        scanf("%s", cpf);

        if (validar_cpf(cpf)) {
            return;
        } else {
          system("clear");
            printf("CPF inválido. Por favor, tente novamente.\n");
        }
    }
}

/////////////////////////////





//INT MAIN







////////////////////////////

int main() {
    setlocale(LC_ALL, "Portuguese");

    char num, op = 0, op2 = 0, opcomprafc = 0, opcomprafm = 0, i = 1, saida = 0, saidaprincipal = 0;
    int numcadFC3 = 15, numcadFC6 = 30, numcadFC9 = 30, numcadFM3 = 30, numcadFM6 = 30;
    int numcadfc = 0, numcadfm = 0;
    int precoFC = 560, precoFM = 30;
    char nome[100], ch, critica[300], cpf[12];
    char op3 = 0;
    FILE * fp;
    char linha[100];

    char * animacao[] = {

        "__  _",
        "\\ `/ |",
        " \\__`!",
        " / ,' `-.__________________",
        "'-'\\_____  CARREGANDO... LI`-.",
        "    <____()-=O=O=O=O=O=[]====--)",
        "     `.___ ,-----,_______...-'",
        "          /    .''",
        "         /   .'",
        "        /  .'",
        "        `-'",
    };
  
  char * qrcode[] = {
                                    
 "  ▄▄▄▄▄▄▄  ▄▄▄▄▄▄▄ ▄   ▄ ▄   ▄▄ ▄  ▄  ▄ ▄▄▄▄▄▄▄  \n",
 "  █ ▄▄▄ █ ▀██▄▀█ ▀ ▄▀█▀▀ ▄█ ██▄█▄ ▄█ █  █ ▄▄▄ █  \n",
 "  █ ███ █ ▀▀▀▀▄▄▄▄▀▀▀▀███▄█▀   ▀██  ▄██ █ ███ █  \n",
 "  █▄▄▄▄▄█ █ ▄ █ ▄ ▄ █ █ ▄ █▀█ ▄ ▄▀▄ ▄ ▄ █▄▄▄▄▄█  \n",
 "  ▄▄▄▄▄ ▄▄▄ ▀▀█▀ ▀▄ █▀█▄▄▄██▀▄▀▄█▀▀ █▀▀▄ ▄ ▄ ▄   \n",
 "  ▀  ▀▄▀▄ ███▄█▀▀█ ▀▄▄▄ ▄██▄▄▄ ▄▀ ▄ ▄█▀▄▄█ ▄▄▀▀  \n",
 "  ▀█▄█▀█▄ ▄▄▀▄  ▀▀▄▀█  █▄ █▀▄▀▀ ██▀█▄▀▀ ▄  ▄▀    \n",
 "  ██▀   ▄ █▀▄ ▄▀▀█▄█▄ ▄▀ ▀▄▄▄▄▄▀█▀ ▄▄██▄▄█▀ ▀▀▀  \n",
 "  ▀▄ █ ▄▄█  ██▀ ▀ ▄▀██  ▄▄█ ▄▄▀▄▀█▀▄▄▀▀  ▄▀▄▀▀▀  \n",
 "  █  ▀ ▀▄▄▄▄█▄▀▀▀▀▄█▄██ ▀ ▄▄▄█▀▄▀▀▄█▄▀▀▄▄█▄ ▄▀▀  \n",
 "  ▄  ▄██▄█▄▄ ██  ▀▄▄█ ▄█▄█▄  ▀▀▄██▀ █▀▄█▄█▄▄▀    \n",
 "  ▀ ▄▀█ ▄ █▀▀ ▄█▀█▄ ▄▀█ ▄ █▄▄▀▀▀▀▀▄█▄██ ▄ █ █▀▀  \n",
 "  ▄ ▄▀█▄▄▄█▄▄█▄▄  ▄ █ █▄▄▄█▀ ▀▀▀▀▄▀▄█ █▄▄▄█▄▀    \n",
 "  ▀▀▀▄▀▀▄█ █▀▄█▄ █▄▀▄▀  ▀█ ▀▄▀▀▀▀  ▄▄ █▀ ▄▄▀▀▀▀  \n",
 "   ██▀ █▄ ▄██▄▀   ▄ ▄▀█   █    ▀▄▄▀█ ▀█▀▀▀▄▄▀    \n",
 "  ▀ █  ▄▄▀ ▀▀ █▀▀█▄▀▄▀ ██▀▀▄▄█ █▀ ▀▄ ▀▀▀ ▀ ▄█▀▀  \n",
 "  ▀▄▄██▀▄ ▄ ▀ █ ▀ ▄▀▄▀▀▄ ██ ▄▄▀▄▀█▀█▄  ▀█ ▄▄▀▀▀  \n",
 "  ▀  ▀█▀▄▀█▀█▀   █▄ ▄▀█ █▄▀▄▄█ ▀▀▄█▄▄  ▀ █ ██▀▀  \n",
 "  ▄▀▀██ ▄▄ ▄▄█   ███▄ ██▄▄█▄▀█▀▀▀█▀█▀▀▄███▄▄▀▄▀  \n",
 "  ▄▄▄▄▄▄▄ ██▀ ███▄▄  ██ ▄ ██ ▄▀▀▀▄█▄▄▄█ ▄ █ ▀▀▀  \n",
 "  █ ▄▄▄ █ ▄▄▄▄█▄██▄ ▄ █▄▄▄██ ▄▀▄█ ▀▀▄ █▄▄▄█▄▀█   \n",
 "  █ ███ █ ██ ▄█  █▄ ▄██▄▄█▀ ▄█▀▀▀ ▀▄▄▀▄▀ ▄▀ ▄▀▄  \n",
 "  █▄▄▄▄▄█ █▀█▄▀  ██▄▄▀▀▄ ▄▄▄▄ ▀██▄▀   ▄▀▄▀▀▄▀▄   \n",
  
};
  
    char * Aviaofrontal[] = {
        "                                   |\n",
        "                             --====|====--\n",
        "                                   |\n",
        "                               .-\"\"\"\"\"-.\n",
        "                             .'_________'.\n",
        "                            /_/_|__|__|_\\_\\\n",
        "                           ;'-._       _.-';\n",
        "         ------------------|    `-. .-'    |------------------\n",
        "         ``\"\"--..__  ___  ;        '        ;  ___  __..--\"\"``\n",
        "                 `\"-// \\\\.._\\             /_..// \\\\-\"`\n",
        "                    \\\\_//    '._       _.'    \\\\_//\n",
        "                     `\"`        ``---``        `\"`\n",
        "   _____                      __  ___    _      __    _                \n",
        "  / ___/____ ___  ____ ______/ /_/   |  (_)____/ /   (_)___  ___  _____\n",
        "  \\__ \\/ __ `__ \\/ __ `/ ___/ __/ /| | / / ___/ /   / / __ \\/ _ \\/ ___/\n",
        " ___/ / / / / / / /_/ / /  / /_/ ___ |/ / /  / /___/ / / / /  __(__  ) \n",
        "/____/_/ /_/ /_/\\__,_/_/   \\__/_/  |_/_/_/  /_____/_/_/ /_/\\___/____/  \n\n"
    };

  do{
    saidaprincipal = 0;
    system("clear");
    for (int i = 0; i < 17; i++) {
        printSpaces(10);
        printf("%s", Aviaofrontal[i]);
    }

    capturar_nome(nome);
    capturar_cpf(cpf);
    system("clear");
    printf("\nBem vindo, %s!\n", nome);
  
        do {
            system("clear");
            op2 = 0;
            saida = 0;
            printf("\n                       ███╗   ███╗███████╗███╗   ██╗██╗   ██╗\n");
            printf("                       ████╗ ████║██╔════╝████╗  ██║██║   ██║\n");
            printf("                       ██╔████╔██║█████╗  ██╔██╗ ██║██║   ██║\n");
            printf("                       ██║╚██╔╝██║██╔══╝  ██║╚██╗██║██║   ██║\n");
            printf("                       ██║ ╚═╝ ██║███████╗██║ ╚████║╚██████╔╝\n");
            printf("                       ╚═╝     ╚═╝╚══════╝╚═╝  ╚═══╝ ╚═════╝ \n\n");

            printf("O que você deseja?\n\nDigite e pressione enter:\n");
            printf("'1' para comprar uma passagem\n");
            printf("'2' para realizar críticas ou elogio\n");
            printf("'3' para ver boleto\n");
            printf("'4' para ver críticas\n");
            printf("'5' para voltar ao menu principal\n");
            printf("'6' para encerrar o programa\n\n");
            scanf("%c", &op);
          
            switch (op) {
            case '1':
                system("clear");
                op = 0;
                printf("\nVoos disponíveis:\nDigite:\n\n");
                printf("'1' para FORMOSA p/ LOS SANTOS\n");
                printf("'2' para FORMOSA p/ CRIXÁS\n");
                printf("'3' para FORMOSA p/ METRÓPOLIS\n\n");
                printf("Digite qualquer caracter para voltar ao menu:\n");
                limpar_entrada();
                scanf("%c", & op2); 

                switch (op2) {
                case '1': //FORMOSA PARA LOS SANTOS
                    system("clear");
                    op2 = 0;
                    printf("FORMOSA p/ LOS SANTOS, R$ 30\n\nSem datas disponíveis:\n\nRetornando ao menu principal...");
                    fflush(stdout);
                    sleep(5);
                    saida = 1;
                   
                    break;

                case '2': //FORMOSA PARA CRIXÁS
                    system("clear");
                    op2 = 0;
                    printf("FORMOSA p/ CRIXÁS, R$ 560\n\nDatas disponíveis:\n\nDigite:\n\n");
                    printf("'1' para 03/07/2023\n");
                    printf("'2' para 06/07/2023\n");
                    printf("'3' para 09/07/2023\n\n");
                    printf("Digite qualquer caracter para voltar ao menu:\n");
                    limpar_entrada();
                    scanf("%c", & opcomprafc);

                    switch (opcomprafc) {
                    case '1':

                        system("clear");
                        opcomprafm = 0;
                        
                        if (numcadFC3 == 0){
                            printf("FORMOSA p/ CRIXÁS, R$ 30\n\nNão há mais passagens disponíveis:\n\nRetornando ao menu principal...");
                            fflush(stdout);
                            sleep(5);
                            saida = 1;
                          } else {
                          
                        printf("%d Cadeiras disponíveis:\n", numcadFC3);
                        printf("Digite quantas cadeiras deseja comprar:");
                        scanf("%d", & numcadfc);

                        while (numcadfc > numcadFC3 || numcadfc < 1) {
                            printf("Por favor digite um valor válido\n");
                            scanf("%d", & numcadfc);
                        }

                        numcadFC3 = numcadFC3 - numcadfc;

                      for (int i = 0; i < 50; i++) { //Animacao
                        for (int j = 0; j < 11; j++) {
                            printSpaces(i);
                            printf("%s\n", animacao[j]);
                        }
                        
                        usleep(DELAY); // pausa a execução do programa por um tempo
                        printf("\033[H\033[J"); // limpa o console

                    }
                      
                      fp = fopen("BOLETO.txt", "a");
                        system("clear");
                        fprintf(fp, "Nome: %s\n", nome);
                        fprintf(fp, "CPF: %s\n", cpf);
                        fprintf(fp, "Passagem Formosa p/ Crixás\n");
                        fprintf(fp, "Data: 03/07/2023\n");
                        fprintf(fp, "Número de cadeiras compradas: %d.\n", numcadfc);
                        fprintf(fp, "Preço a pagar: %d\n", precoFC * numcadfc);
                        fprintf(fp, "Método de pagamento único: PIX: a72eb275-3ea9-4ba6-8116-cfc2f95210b2\n\n");

                        for (int i = 0; i < 23; i++) {
                          fprintf(fp, "%s", qrcode[i]);
                        }

                        fprintf(fp, "\n");
                      
                        fclose(fp);
    
                        printf("Passagem comprada com sucesso!\n\n");
                        printf("CPF: %s\n", cpf);
                        printf("Passagem Formosa p/ Crixás\n");
                        printf("Data: 03/07/2023\n");
                        printf("Boleto gerado e salvo nos seus fps\n\n");
                        printf("Nome: %s\n", nome);
                        printf("Número de cadeiras compradas: %d.\n", numcadfc);
                        printf("Preço a pagar: %d\n", precoFC * numcadfc);
                        printf("Método de pagamento único: PIX: a72eb275-3ea9-4ba6-8116-cfc2f95210b2\n");

                        for (int i = 0; i < 23; i++) {
                          printf("%s", qrcode[i]);
                        }

                    sleep(5);
                    saida = 1;
                        }
                        break;

                    case '2':

                        system("clear");
                        opcomprafm = 0;
                        
                        if (numcadFC6 == 0){
                            printf("FORMOSA p/ CRIXÁS, R$ 30\n\nNão há mais passagens disponíveis:\n\nRetornando ao menu principal...");
                            fflush(stdout);
                            sleep(5);
                            saida = 1;
                          } else {
                          
                        printf("%d Cadeiras disponíveis:\n", numcadFC6);
                        printf("Digite quantas cadeiras deseja comprar:");
                        scanf("%d", & numcadfc);
                        while (numcadfc > numcadFC6 || numcadfc < 1) {
                            printf("Por favor digite um valor válido\n");
                            scanf("%d", & numcadfc);
                        }
                        printf("Passagem comprada com sucesso!\n");
                      
                        numcadFC6 = numcadFC6 - numcadfc;
                      
                      for (int i = 0; i < 50; i++) { //Animacao
                        for (int j = 0; j < 11; j++) {
                            printSpaces(i);
                            printf("%s\n", animacao[j]);
                        }

                        usleep(DELAY); // pausa a execução do programa por um tempo
                        printf("\033[H\033[J"); // limpa o console

                    }
                      
                      fp = fopen("BOLETO.txt", "a");
                        system("clear");
                        fprintf(fp, "Nome: %s\n", nome);
                        fprintf(fp, "CPF: %s\n", cpf);
                        fprintf(fp, "Passagem Formosa p/ Crixás\n");
                        fprintf(fp, "Data: 06/07/2023\n");
                        fprintf(fp, "Número de cadeiras compradas: %d.\n", numcadfc);
                        fprintf(fp, "Preço a pagar: %d\n", precoFC * numcadfc);
                        fprintf(fp, "Método de pagamento único: PIX: a72eb275-3ea9-4ba6-8116-cfc2f95210b2\n\n");

                        for (int i = 0; i < 23; i++) {
                          fprintf(fp, "%s", qrcode[i]);
                        }

                        fprintf(fp, "\n");
                      
                        fclose(fp);
    
                        printf("Passagem comprada com sucesso!\n\n");
                        printf("CPF: %s\n", cpf);
                        printf("Passagem Formosa p/ Crixás\n");
                        printf("Data: 06/07/2023\n");
                        printf("Boleto gerado e salvo nos seus fps.\n\n");
                        printf("Nome: %s\n", nome);
                        printf("Número de cadeiras compradas: %d.\n", numcadfc);
                        printf("Preço a pagar: %d\n", precoFC * numcadfc);
                        printf("Método de pagamento único: PIX: a72eb275-3ea9-4ba6-8116-cfc2f95210b2\n");

                        for (int i = 0; i < 23; i++) {
                          printf("%s", qrcode[i]);
                        }
                  
                    sleep(5);
                    saida = 1;
                        }
                        break;

                    case '3':

                        system("clear");
                        opcomprafm = 0;
                        
                        if (numcadFC9 == 0){
                            printf("FORMOSA p/ CRIXÁS, R$ 30\n\nNão há mais passagens disponíveis:\n\nRetornando ao menu principal...");
                            fflush(stdout);
                            sleep(5);
                            saida = 1;
                          } else {
                      
                        printf("%d Cadeiras disponíveis:\n", numcadFC9);
                        printf("Digite quantas cadeiras deseja comprar:");
                        scanf("%d", & numcadfc);
                        while (numcadfc > numcadFC9 || numcadfc < 1) {
                            printf("Por favor digite um valor válido\n");
                            scanf("%d", & numcadfc);
                        }
                        printf("Passagem comprada com sucesso!\n");
                      
                        numcadFC9 = numcadFC9 - numcadfc;

                      for (int i = 0; i < 50; i++) { //Animacao
                        for (int j = 0; j < 11; j++) {
                            printSpaces(i);
                            printf("%s\n", animacao[j]);
                        }

                        usleep(DELAY); // pausa a execução do programa por um tempo
                        printf("\033[H\033[J"); // limpa o console

                    }
                      fp = fopen("BOLETO.txt", "a");
                        system("clear");
                        fprintf(fp, "Nome: %s\n", nome);
                        fprintf(fp, "CPF: %s\n", cpf);
                        fprintf(fp, "Passagem Formosa p/ Crixás\n");
                        fprintf(fp, "Data: 09/07/2023\n");
                        fprintf(fp, "Número de cadeiras compradas: %d.\n", numcadfc);
                        fprintf(fp, "Preço a pagar: %d\n", precoFC * numcadfc);
                        fprintf(fp, "Método de pagamento único: PIX: a72eb275-3ea9-4ba6-8116-cfc2f95210b2\n\n");

                        for (int i = 0; i < 23; i++) {
                          fprintf(fp, "%s", qrcode[i]);
                        }

                        fprintf(fp, "\n");
                      
                        fclose(fp);
    
                        printf("Passagem comprada com sucesso!\n\n");
                        printf("CPF: %s\n", cpf);
                        printf("Passagem Formosa p/ Crixás\n");
                        printf("Data: 09/07/2023\n");
                        printf("Boleto gerado e salvo nos seus arquvios\n\n");
                        printf("Nome: %s\n", nome);
                        printf("Número de cadeiras compradas: %d.\n", numcadfc);
                        printf("Preço a pagar: %d\n", precoFC * numcadfc);
                        printf("Método de pagamento único: PIX: a72eb275-3ea9-4ba6-8116-cfc2f95210b2\n");

                        for (int i = 0; i < 23; i++) {
                          printf("%s", qrcode[i]);
                        }
                  
                    sleep(5);
                    saida = 1;
                    }
                    break;

                    default:
                      saida = 1;
                    break;
                      
                    }
                  
                    break;

                case '3': //FORMOSA PARA METROPOLIS

                    system("clear");
                    op2 = 0;
                    printf("FORMOSA p/ METRÓPOLIS, R$ 30\n\nDatas disponíveis:\n\nDigite:\n\n");
                    printf("'1' para 03/07/2022\n");
                    printf("'2' para 06/07/2022\n\n");
                    printf("Digite qualquer caracter para voltar ao menu:\n");
                    limpar_entrada();
                    scanf("%c", &opcomprafm);

                    switch (opcomprafm) {

                    case '1':
                        system("clear");
                        opcomprafm = 0;
                      
                      if (numcadFM3 == 0){
                          printf("FORMOSA p/ METRÓPOLIS, R$ 30\n\nNão há mais passagens disponíveis:\n\nRetornando ao menu principal...");
                          fflush(stdout);
                          sleep(5);
                          saida = 1;
                        } else {
                        
                        printf("%d Cadeiras disponíveis:\n", numcadFM3);
                        printf("Digite quantas cadeiras deseja comprar:");
                        scanf("%d", & numcadfm);

                        while (numcadfm > numcadFM3 || numcadfm < 1) {
                            printf("Por favor digite um valor válido\n");
                            scanf("%d", & numcadfm);
                        }
    
                        numcadFM3 = numcadFM3 - numcadfm;

                      for (int i = 0; i < 50; i++) { //Animacao
                        for (int j = 0; j < 11; j++) {
                            printSpaces(i);
                            printf("%s\n", animacao[j]);
                        }

                        usleep(DELAY); // pausa a execução do programa por um tempo
                        printf("\033[H\033[J"); // limpa o console

                    }
                      
                      fp = fopen("BOLETO.txt", "a");
                        system("clear");
                        fprintf(fp, "Nome: %s\n", nome);
                        fprintf(fp, "CPF: %s\n", cpf);
                        fprintf(fp, "Passagem Formosa p/ Metrópolis\n");
                        fprintf(fp, "Data: 03/07/2023\n");
                        fprintf(fp, "Número de cadeiras compradas: %d.\n", numcadfm);
                        fprintf(fp, "Preço a pagar: %d\n", precoFM * numcadfm);
                        fprintf(fp, "Método de pagamento único: PIX: a72eb275-3ea9-4ba6-8116-cfc2f95210b2\n\n");

                        for (int i = 0; i < 23; i++) {
                          fprintf(fp, "%s", qrcode[i]);
                        }

                        fprintf(fp, "\n");
                      
                        fclose(fp);
    
                        printf("Passagem comprada com sucesso!\n\n");
                        printf("Boleto gerado e salvo nos seus arquvios\n\n");
                        printf("Nome: %s\n", nome);
                        printf("CPF: %s\n", cpf);
                        printf("Passagem Formosa p/ Metrópolis\n");
                        printf("Data: 03/07/2023\n");
                        printf("Número de cadeiras compradas: %d.\n", numcadfm);
                        printf("Preço a pagar: %d\n", precoFM * numcadfm);
                        printf("Método de pagamento único: PIX: a72eb275-3ea9-4ba6-8116-cfc2f95210b2\n");

                        for (int i = 0; i < 23; i++) {
                          printf("%s", qrcode[i]);
                        }
                  
                    sleep(5);
                    saida = 1;
                    }
                        break;

                    case '2':

                        system("clear");
                        opcomprafm = 0;
                      
                      if (numcadFM6 == 0){
                          printf("FORMOSA p/ METRÓPOLIS, R$ 30\n\nNão há mais passagens disponíveis:\n\nRetornando ao menu principal...");
                          fflush(stdout);
                          sleep(5);
                          saida = 1;
                        } else {

                        printf("%d Cadeiras disponíveis:\n", numcadFM6);
                        printf("Digite quantas cadeiras deseja comprar:");
                        scanf("%d", & numcadfm);
                      
                        while (numcadfm > numcadFM6 || numcadfm < 1) {
                            printf("Por favor digite um valor válido\n");
                            scanf("%d", & numcadfm);
                        }

                      numcadFM6 = numcadFM6 - numcadfm;
                      
                      for (int i = 0; i < 50; i++) { //Animacao
                        for (int j = 0; j < 11; j++) {
                            printSpaces(i);
                            printf("%s\n", animacao[j]);
                        }

                        usleep(DELAY); // pausa a execução do programa por um tempo
                        printf("\033[H\033[J"); // limpa o console

                    }
                      
                      fp = fopen("BOLETO.txt", "a");
                        system("clear");
                        fprintf(fp, "Nome: %s\n", nome);
                        fprintf(fp, "CPF: %s\n", cpf);
                        fprintf(fp, "Passagem Formosa p/ Metrópolis\n");
                        fprintf(fp, "Data: 06/07/2023\n");
                        fprintf(fp, "Número de cadeiras compradas: %d.\n", numcadfm);
                        fprintf(fp, "Preço a pagar: %d\n", precoFM * numcadfm);
                        fprintf(fp, "Método de pagamento único: PIX: a72eb275-3ea9-4ba6-8116-cfc2f95210b2\n\n");
                      
                        for (int i = 0; i < 23; i++) {
                          fprintf(fp, "%s", qrcode[i]);
                        }
                      
                        fprintf(fp, "\n");
                      
                        fclose(fp);
    
                        printf("Passagem comprada com sucesso!\n");
                        printf("Boleto gerado e salvo nos seus arquvios\n\n");
                        printf("Nome: %s\n", nome);
                        printf("CPF: %s\n", cpf);
                        printf("Passagem Formosa p/ Metrópolis\n");
                        printf("Data: 06/07/2023\n");
                        printf("Número de cadeiras compradas: %d.\n", numcadfm);
                        printf("Preço a pagar: %d\n", precoFM * numcadfm);
                        printf("Método de pagamento único: PIX: a72eb275-3ea9-4ba6-8116-cfc2f95210b2\n");
                      
                        for (int i = 0; i < 23; i++) {
                          printf("%s", qrcode[i]);
                        }
                  
                    sleep(5);
                    saida = 1;
                      break;
                    }
                  }
                  
                 default:
                      saida = 1;
                 break;
                }
              break;

            case '2': // Lógica para realizar críticas ou elogios
              op = 0;
              system("clear");
              printf("Escreva alguma crítica ou sugestão: (até 300 caracteres):");
              
              limpar_entrada();
              ler_texto(critica, 300);
              
              fp = fopen("CRITICAS.txt", "a");
              fprintf(fp, "Crítica anônima: %s\n", critica);
              fprintf(fp, "\n");
              fclose(fp);
              
              printf("Critica feita, muito obrigado!");

              fflush(stdout);
              sleep(2);
              saida = 1;
              
                break;

            case '3':
              system("clear");
              fp = fopen("BOLETO.txt", "r");
              if (fp == NULL) {
                printf("Não há boletos, compre uma passagem para gerar um.\n");
                
              } else {
              
              fp = fopen("BOLETO.txt", "r");
              // Lê e exibe o conteudo linha por linha
              while (fgets(linha, sizeof(linha), fp) != NULL) {
                  printf("%s", linha);
              }
              fclose(fp);
              
              }

              fflush(stdout);
              sleep(1);
              
              limpar_entrada();
              printf("Digite qualquer caracter para voltar ao menu:\n");
              scanf("%c", &op3);
              switch(op3){
                default:
                  saida = 1;
                break;
              }
              
            break;

            case '4':
              system("clear");
              fp = fopen("CRITICAS.txt", "r");
              if (fp == NULL) {
                printf("Não há críticas, deseja ser o primeiro?\n");
                
              } else {
              
              fp = fopen("CRITICAS.txt", "r");
              // Lê e exibe o conteudo linha por linha
              while (fgets(linha, sizeof(linha), fp) != NULL) {
                  printf("%s", linha);
              }
              fclose(fp);
              
              }

              fflush(stdout);
              sleep(1);
              
              limpar_entrada();
              printf("Digite qualquer caracter para voltar ao menu:\n");
              scanf("%c", &op3);
              switch(op3){
                default:
                  saida = 1;
                break;
              }
              
            break;
              
            case '5':
              saidaprincipal = 1;
              limpar_entrada();
            break;

              
            case '6': //ENCERRAR O PROGRAMA
              op = 0;
              system("clear");
              printf("Programa encerrado.\n\nObrigado por escolher a Smart AirLines. Pedro e Luiz agradecem seu apoio.\n");
              
              limparArquivo("BOLETO.txt");
              limparArquivo("CRITICAS.txt");
                break;

            default:
              saida = 1;
              op = 0;
            break;
            }

        } while (saida == 1);

  }while (saidaprincipal == 1);
  
    atexit(limpartodosOsArquivos);
  
    return 0;
}