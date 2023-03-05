#include <stdio.h>
#include <string.h>

#define MAXLEN 10000

int shift_or(char *text, int textlen, char *pattern, int patlen) {//recebe 4 par�metros: o texto a ser pesquisado (text),
    //o comprimento do texto (textlen), o padr�o a ser encontrado (pattern) e o comprimento do padr�o (patlen)
    int m = patlen; //Vari�vel m que � igual ao comprimento do padr�o
    long pattern_mask[256]; //vetor pattern_mask de long que cont�m 256 elementos
    long R = ~1; //A vari�vel R � definida como ~1, o que torna uma m�scara de bits que representa o padr�o em branco.
    // se o comprimento do padr�o for 0 ou maior que 63, a fun��o retorna -1.

    if (m == 0)
        return -1;
    if (m > 63) {
        printf("Pattern is too long!\n");
        return -1;
    }
    //cada elemento corresponde a um caractere ASCII
    for (int i = 0; i <= 255; ++i)//criar a tabela de deslocamento
        pattern_mask[i] = ~0;

    //se um caractere do texto corresponder ao caractere correspondente no padr�o,
    //o bit correspondente na m�scara de bits ser� definido como 1.
    for (int i = 0; i < m; ++i)
        pattern_mask[pattern[i]] &= ~(1L << i);//comparar o padr�o com o texto

    //percorre o texto e compara o padr�o com cada subcadeia de caracteres do texto.
    for (int i = 0; i < textlen; ++i) { //encontrar todas as ocorr�ncias do padr�o no texto.
        R |= pattern_mask[text[i]];
        R <<= 1;
        if ((R & (1L << m)) == 0)
            return i - m + 1;
    }

    return -1;
}

int main() { //l� a sequ�ncia de DNA e padr�o de pesquisa da entrada do usu�rio e
    //chama a fun��o shift_or para buscar o padr�o na sequ�ncia.
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

