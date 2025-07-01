#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define READ 10 // Le uma palavra do terminal e a coloca em um local especifico da memoria.

#define WRITE 11 // Escreve no terminal uma palavra de um local especifico da memoria.

#define LOAD 20 // Carrega no acumulador uma palavra de um local especifico da memoria.

#define STORE 21 // Armazena em um local especifico da memoria uma palavra do acumulador.

#define ADD 30 // Adiciona uma palavra de um local especifico da memoria a palavra no
               // acumulador (o resultado fica no acumulador).

#define SUBTRACT 31 // Subtrai da palavra no acumulador, uma palavra
                    // em um local especifico da memoria (o resultado
                    // fica no acumulador).

#define DIVIDE 32 // Divide uma palavra em um local especifico da
                  // memoria pela palavra no acumulador (o resultado
                  // fica no acumulador).

#define MULTIPLY 33 // Multiplica uma palavra em um local especifico da
                    // memoria pela palavra no acumulador (o resultado
                    // fica no acumulador).

#define BRANCH 40 // Desvia para um local especifico da memoria.

#define BRANCHNEG 41 // Desvia para um local especifico da memoria
                     // se o acumulador for negativo.

#define BRANCHZERO 42 // Desvia para um local especifico da memoria
                      // se o acumulador for zero.

#define HALT 43 // Termino, i.e., o programa completou sua tarefa

#define MEMORIA 100 // Define o tamanho da memoria para 100

#define SENTINELA -99999 // comando de FIM

#define MAX 9999 // escala maxima de valor

int contadorInstrucao = 0; // apenas conta os comandos e joga na mesma posicao para a memoria

int registradorInstrucao; // variavel que guarda o comando

int memoria[MEMORIA] = {0}; // vetor de memoria

int codigoOperacao; // codigo da operacao (dois digitos a esquerda)

int operando; // codigo de operando (dois digitos a direita)

int acumulador = 0; // registrador acumulador -> inicia com 0 pq podemos usar ADD e adicionar acumulador += memoria[operando]

void simpletron() // funcao que inicializa e chama a funcao de arquivar comandos
{
    printf("*** Bem vindo ao Simpletron! ***\n");
    printf("*** Por favor digite uma instrucao (ou palavra ***\n");
    printf("*** de dados) de seu programa por vez. Digitarei o ***\n");
    printf("*** numero da posicao e um ponto de interrogacao ***\n");
    printf("*** (?). Digite entao a palavra para aquela posicao ***\n");
    printf("*** Digite o valor sentinela -99999 para encerrar a ***\n");
    printf("*** digitacao de seu programa. ***\n");

    comandosArq();
}

void comandosArq() // funcao que arquiva os comandos
{
    while (contadorInstrucao < MEMORIA && registradorInstrucao != SENTINELA) // enquanto nn estourar a memoria (100) E o registrador != -99999
    {
        printf("%d ? ", contadorInstrucao);

        scanf("%d", &registradorInstrucao);

        if (registradorInstrucao <= SENTINELA || registradorInstrucao > MAX)
        {
            printf("\n*** Comando fora de escala ***\n"); // fim do programa
            break;
        }

        else
        {
            memoria[contadorInstrucao] = registradorInstrucao; // passa pra memoria os comandos
            contadorInstrucao++;
        }
    }
    printf("*** Carregamento do programa concluido *** *** Inicio da execucao do programa ***");

    contadorInstrucao = 0; // quando acabar a memoria OU vir o comando de fim -> reseta as variaveis de comando (contador e reg)

    comandosEx();
}

void comandosEx() // funcao que executa os comandos
{
    int retornoOperacao = 1;

    while (contadorInstrucao < MEMORIA && retornoOperacao == 1)
    {

        registradorInstrucao = memoria[contadorInstrucao];

        codigoOperacao = registradorInstrucao / 100; // pega os dois primeiros digitos

        operando = registradorInstrucao % 100; // pega os dois ultimos digitos

        switch (codigoOperacao) // executa os comandos e faz a verificao de provaveis erros de sintaxe -> ao encontrar erro ele despeja() e da fim no programa
        {

        case READ: // arquiva um numero na memoria

            printf("\nInforme um numero: ");

            scanf("%d", &memoria[operando]);

            if (memoria[operando] <= SENTINELA || memoria[operando] > MAX)
            {
                printf("\n*** Comando fora de escala ***\n");

                despejar();
                retornoOperacao = 0;
            }

            break;

        case WRITE: // mostra um numero da memoria

            printf("\nValor em %d: %d", operando, memoria[operando]);

            break;

        case LOAD: // joga um numero para o acumulador

            acumulador = memoria[operando];

            break;

        case STORE: // joga na memoria o valor do acumulador

            memoria[operando] = acumulador;

            break;

        case ADD: // add um numero da memoria com acumulador -> resultado no acumulador

            acumulador += memoria[operando];

            if (acumulador < SENTINELA || acumulador > MAX)
            {
                printf("\nAcumulador fora de escala (ADD)");
                despejar();
                retornoOperacao = 0;
            }

            break;

        case SUBTRACT: // sub um numero da memoria com acumulador -> resultado no acumulador

            acumulador -= memoria[operando];

            if (acumulador < SENTINELA || acumulador > MAX)
            {
                printf("\nAcumulador fora de escala (SUB)");
                despejar();
                retornoOperacao = 0;
            }

            break;

        case DIVIDE: // div um numero da memoria com acumulador -> resultado no acumulador

            if (memoria[operando] == 0)
            {
                printf("\nNao pode dividir por zero!");
                despejar();
                retornoOperacao = 0;
                break;
            }

            acumulador /= memoria[operando];

            break;

        case MULTIPLY: // mul um numero da memoria com acumulador -> resultado no acumulador

            acumulador *= memoria[operando];

            if (acumulador < SENTINELA || acumulador > MAX)
            {
                printf("\nAcumulador fora de escala (MUL)");
                despejar();
                retornoOperacao = 0;
            }

            break;

        case BRANCH: //  jump para a posicao operando

            contadorInstrucao = operando;

            break;

        case BRANCHNEG: // jump se o acumulador for negativo

            if (acumulador < 0)
            {
                contadorInstrucao = operando;
            }
            break;

        case BRANCHZERO: // jump se o acumulador for zero (tipo o flag de Assembly)

            if (acumulador == 0)
            {
                contadorInstrucao = operando;
            }

            break;

        case HALT: // fim do programa -> despejar na memoria o programa!
            despejar();
            retornoOperacao = 0; // ja que eh o fim do programa, tudo que vier dps eh descartado!
            break;

        default: // se nao reconhecer o comando (a lista de comandos esta em #define) -> despeja na memoria e coloca fim na execucao dos programas
            despejar();
            retornoOperacao = 0;
            break;
        }

        contadorInstrucao++;
    }

    printf("\n\n\n\n\n*** Execucao do Simpletron encerrada ***\n\n\n");
}

void despejar() // simula a memoria
{
    printf("\n\n\nREGISTROS:\n");
    printf("acumulador: %d\n", acumulador);
    printf("contadorInstrucao: %d\n", contadorInstrucao);
    printf("registroInstrucao: %d\n", registradorInstrucao);
    printf("codigoOperacao: %d\n", codigoOperacao);
    printf("operando: %d\n", operando);

    printf("\nMEMORIA:\n");

    printf("       ");
    for (int i = 0; i < 10; i++)
    {
        printf("%d      ", i); // mostra o numero da coluna
    }

    printf("\n");

    for (int i = 0; i < MEMORIA; i += 10)
    {
        printf("%02d  ", i); // mostra o numero como dois algarismos (linha)

        for (int j = 0; j < 10; j++)
        {
            printf(" %+05d ", memoria[i + j]); // mostra o numero com o sinal + e numero com 4 algarismos
        }
        printf("\n");
    }
}

void simpletron_automatico()
{
    printf("\n\n(Iniciando simpletron automatico)\n");

    ler_arquivo();
}

void ler_arquivo()
{
    char nome[20];

    printf ("\nO arquivo de comando deve estar na mesma pasta que o 'simpletron.exe'!!\n");
    
    printf ("\nInforme o nome do arquivo a ser lido (escreva o nome do arquivo pessoal ou 'comandos.txt'): ");
    scanf ("%s", nome);



    FILE *file = fopen(nome, "r");

    if (file == NULL)
    {
        printf("\n\nNao foi encontrado o arquivo 'comandos.txt'\n\n");

        printf ("\nColoque o seu arquivo ou o arquivo 'comandos.txt' na mesma pasta que o arquivo 'simpletron.exe'\n\n\n");

        return;
    }

    char ler_comando[10];

    if (strcmp (nome, "comandos.txt") == 0)
    {
        printf ("\n\nOs comandos do arquivo 'comandos.txt' sao codigos para somar dois numeros!\n\n");
        printf ("\tGuarda o primeiro numero na posicao 50\n");
        printf ("\tGuarda o segundo numero na posicao 51\n");
        printf ("\tO resultado (acumulador) eh guardado na posicao 52\n\n");
    }

    while (fgets(ler_comando, sizeof(ler_comando), file) != NULL)
    {
        ler_comando[4] = '\0';

        registradorInstrucao = atoi (ler_comando);

        memoria[contadorInstrucao] = registradorInstrucao; // passa pra memoria os comandos
        contadorInstrucao++;
    
    }
    

    contadorInstrucao = 0; // quando acabar a memoria OU vir o comando de fim -> reseta as variaveis de comando (contador e reg)

    comandosEx();

    fclose(file);
}

int main()
{

    simpletron_automatico();

    return 0;
}
