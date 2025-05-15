#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define BUFSIZE 1024 //ファイルから読み込む一行の最大文字数
#define MAX_SEQ_NUM 30 //一つの転写因子に対して与えられる結合部位配列の最大数
#define MAX_GENE_NUM 8 /*与えられるプロモータ領域の最大遺伝子数*/

char g_motif[MAX_SEQ_NUM][BUFSIZE]; //転写因子の結合部位配列を保存する配列

struct promoter{
  char name[BUFSIZE];
  char seq[BUFSIZE];
}g_pro[MAX_GENE_NUM]; //遺伝子のプロモータ領域を保存する構造体

//グローバル変数はローカル変数と区別するため、全部大文字にするかg_を先頭につけるのが一般的

int read_multi_seq(char* filename){
  int seq_num = 0;
  char buffer[BUFSIZE];
  FILE *fp = fopen(filename,"r");

  if(fp == NULL){
    printf("motif_region_file open error.\n");
    exit(1); //ファイルが開けなかった場合プログラムを終了
  }

  while(fscanf(fp, "%s", buffer) != EOF){ //プログラムから一行ずつ読み込む
    if(buffer[strlen(buffer)-1]=='\n'){
      buffer[strlen(buffer)-1]='\0'; //改行を切り落とす
    }
    strcpy(g_motif[seq_num],buffer); //結合部位配列を保存
    seq_num++;
  }

  return seq_num;
}

int read_promoter(char *filename){
  int gene_num = 0;  
  char buffer[BUFSIZE];
  FILE *fp = fopen(filename,"r");

  if(fp == NULL){
    printf("scorefile open error.\n");
    exit(1);
  }

  while(fscanf(fp, "%s", buffer) != EOF){
    if(buffer[strlen(buffer)-1]=='\n'){
      buffer[strlen(buffer)-1]='\0';
    }
    
    if(buffer[0]=='>'){
      strcpy(g_pro[gene_num].name,buffer+1); 
    }else{
      strcpy(g_pro[gene_num].seq,buffer);
      gene_num++;
    }    
  }
  return gene_num;
}

int base_to_index(char base) {
    if (base == 'A') return 0;
    if (base == 'C') return 1;
    if (base == 'G') return 2;
    if (base == 'T') return 3;
    return -1; // エラー処理（ありえない塩基）
}


int main(int argc, char* argv[]){
  int seq_num = read_multi_seq(argv[1]); //１番目の引数で指定した転写因子の複数の結合部位配列を読み込む

  printf("motif region:\n");
  for(int i = 0; i < seq_num; i++){
    printf("%s\n",g_motif[i]); //読み込んだ転写因子の結合部位配列を表示
  }
  printf("\n");

  int SEQ_LENGTH=0;
for(int i=0;i<30;i++){
if(g_motif[i][0]=='\0'){
  break;
}
SEQ_LENGTH++;
}

  int NUM_SEQUENCES=0;
for(int i=0;i<30;i++){
if(g_motif[0][i]=='\0'){
  break;
}
NUM_SEQUENCES++;
}
int table[4][BUFSIZE] = {0};
 for (int i = 0; i < SEQ_LENGTH; ++i) {
        for (int j = 0; j < NUM_SEQUENCES; ++j) {
            int idx = base_to_index(g_motif[i][j]);
            if (idx != -1) {
                table[idx][j]++;
            }
        }
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < NUM_SEQUENCES; j++) {
            printf("%d\t", table[i][j]);
        }
        printf("\n");
    }
printf("\n");
float pi[4][BUFSIZE]={0};
for (int i = 0; i < 4; i++) {
        for (int j = 0; j < NUM_SEQUENCES; j++) {
          pi[i][j]=(float)(table[i][j]+1)/(float)(SEQ_LENGTH+4);  
          printf("%f\t", pi[i][j]);
        }
        printf("\n");
    }
printf("\n");
#define ALL 24314210
float q[4]={0};
q[0]=(float)7519429/ALL;
q[1]=(float)4637676/ALL;
q[2]=(float)4637676/ALL;
q[3]=(float)7519429/ALL;

for(int i=0;i<4;i++){
  printf("%f\t",q[i]);
  printf("\n");
}
printf("\n");


float si[4][BUFSIZ];
for (int i = 0; i < 4; i++) {
        for (int j = 0; j < NUM_SEQUENCES; j++) {
          si[i][j]=(float)log(pi[i][j]/q[i]);  
          printf("%f\t", si[i][j]);
        }
        printf("\n");
    }
printf("\n");




  int gene_num = read_promoter(argv[2]);  //２番目の引数で指定した遺伝子のプロモータ領域を読み込む
  
  printf("promoter_sequence:\n");
  for(int i = 0; i < gene_num; i++){
    printf(">%s\n", g_pro[i].name); //読み込んだプロモータ領域を表示
    printf("%s\n", g_pro[i].seq);
  }

  return 0;
}