#include <stdio.h>
#include <string.h>

#define MAXLEN 10000

int shift_or(char *text, int textlen, char *pattern, int patlen) {//recebe 4 parâmetros: o texto a ser pesquisado (text),o comprimento do texto (textlen), o padrão a ser encontrado (pattern) e o comprimento do padrão (patlen)
    int m = patlen; //Variável m que é igual ao comprimento do padrão
    long pattern_mask[256]; //vetor pattern_mask de long que contém 256 elementos
    long R = ~1; //A variável R é definida como ~1, o que torna uma máscara de bits que representa o padrão em branco.
    // se o comprimento do padrão for 0 ou maior que 63, a função retorna -1.

    if (m == 0)
        return -1;
    if (m > 63) {
        printf("Pattern is too long!\n");
        return -1;
    }
    //cada elemento corresponde a um caractere ASCII
    for (int i = 0; i <= 255; ++i)//criar a tabela de deslocamento
        pattern_mask[i] = ~0;

    //se um caractere do texto corresponder ao caractere correspondente no padrão, o bit correspondente na máscara de bits será definido como 1.
    for (int i = 0; i < m; ++i)
        pattern_mask[pattern[i]] &= ~(1L << i);//comparar o padrão com o texto

    //percorre o texto e compara o padrão com cada subcadeia de caracteres do texto.
    for (int i = 0; i < textlen; ++i) { //encontrar todas as ocorrências do padrão no texto.
        R |= pattern_mask[text[i]];
        R <<= 1;
        if ((R & (1L << m)) == 0)
            return i - m + 1;
    }

    return -1;
}

int main() { //lê a sequência de DNA e padrão de pesquisa da entrada do usuário e chama a função shift_or para buscar o padrão na sequência.
    char dna[MAXLEN], pattern[MAXLEN];
    int dnalen, patlen, pos;

    printf("Enter DNA sequence: ");
    scanf("%s", dna);
    dnalen = strlen(dna);

    printf("Enter pattern to search: ");
    scanf("%s", pattern);
    patlen = strlen(pattern);

    pos = shift_or(dna, dnalen, pattern, patlen);

    if (pos == -1)
        printf("Pattern not found.\n");
    else
        printf("Pattern found at position %d.\n", pos);

    return 0;
}

