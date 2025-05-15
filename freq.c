#include <stdio.h>
#include <string.h>

#define NUM_SEQUENCES 23
#define SEQ_LENGTH 16

int base_to_index(char base) {
    if (base == 'A') return 0;
    if (base == 'C') return 1;
    if (base == 'G') return 2;
    if (base == 'T') return 3;
    return -1; // エラー処理（ありえない塩基）
}

int main(void) {
char* sequences[NUM_SEQUENCES] = {
"CATCCTAAAAAGGAAA",
"ATGCCTAAACAGGTAG",
"CGTCCTAAACAGGACA",
"TCGCCTAAATAAGTAA",
"ACTCCTAAATAGGCTA",
"TTGCCTAAAGCGGTAA",
"TTTCCTAATCGGTTGT",
"TATCCTAATGTGGTAT",
"ACTCCTATATAAATCG",
"TTTCCTAGACCGGTCA",
"ATGCCTTAACGGGTAA",
"ATACCTTATGTGGTAT",
"TTACCTCATCCAGCCT",
"TTGCCCAAAAGGGACA",
"ATACCCAAAGTAGAAA",
"GTTCCCAATCAGGAGA",
"CCACCCAATCCAGTAA",
"AGTCCCAATCGGGTCA",
"TGACCCAATATGGTAT",
"TATCCCATTAAGGTAA",
"AGTCCCATTAGGGTAA",
"GTTCCCTATCGGGTAA",
"TTACCCGATTTGGAAT"
    };

    int table[4][SEQ_LENGTH] = {0}; // A, C, G, T
 for (int i = 0; i < NUM_SEQUENCES; ++i) {
        for (int j = 0; j < SEQ_LENGTH; ++j) {
            int idx = base_to_index(sequences[i][j]);
            if (idx != -1) {
                table[idx][j]++;
            }
        }
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < SEQ_LENGTH; j++) {
            printf("%d\t", table[i][j]);
        }
        printf("\n");
    }

    return 0;
}

