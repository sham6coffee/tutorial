#include <stdio.h>
#include <stdlib.h> /*** malloc, free, exitのために必要 ***/

#define	KINDS_NUMBERS	26
#define MAX_CHANCES	6

int main(void){
  char input; /*** aはユーザ入力***/
  /*** correctは正解．ここで具体的な正解も設定する***/
  char *correct="committee";
  char yomisute; /*** 読み捨て用 ***/
  int i; /*** iはループを回すため*/
  int hits=0; /*** 正答回数，0に設定 ***/
  /*** currentは解答状況表示用，後で%sを用いて表示する ***/
  char *current;
  int mistakes=0; /*** ミスを数えるため ***/
  int prev_hits; /*** 不正解判定のために、前の正解回数を記憶 ***/
  int already[KINDS_NUMBERS]; /*** 既にタイプしたことのある数を扱う ***/
  int num_chars; /***正解の文字数を保持するため ***/
  char *p_str; 

  /*** 正解correctの文字数を計算する ***/
  /*** 文字数を保持する変数num_charsを0に初期化し、***/
  /*** 文字列を走査する変数p_strをcorrectに初期化する。***/
  /*** *p_strが終端文字でない限り、***/
  /*** p_strとnum_charsをインクリメントする ***/
  for(num_chars=0, p_str=correct; *p_str!='\0'; num_chars++, p_str++);
  /*** 暫定正解表示用領域を確保 ***/
  current=malloc((num_chars+1)*sizeof(char));
  if(current==NULL){
    printf("Out of Memory\n");
    exit(1);
  }
  /***解答状況表示用配列の各要素を'?'に設定 ***/
  /***ただし後で%sを用いて表示できるように設定する***/
  for(i=0;i<num_chars;i++){
    current[i]='?'; 
  }
  current[i]='\0';

  /*** 配列alreadyの全要素を0に設定 ***/
  for(i=0;i<KINDS_NUMBERS;i++){
    already[i]=0;
  }

  while(1){
    printf("Word: ");
    /*** 解の表示 ***/
    /*** NUM_CHARS個の正解がまだ当てられていない場合には ***/
    /*** currentの全要素が'?'になっている。***/
    /*** そうでなければ(当てられていれば)、***/
    /*** 正解と同じ文字になっている。***/
    /*** %sを用いてcurrentを表示する ***/
    printf("%s\n", current);
    printf("Your chances: %d\n", MAX_CHANCES-mistakes);/*** 残されたチャンス数の表示 ***/
    printf("Already typed keys:");/*** 既にタイプした文字を表示 ***/
    /*** ループ中で配列alreadyの要素を適切に書き換えてあるので ***/
    /*** 配列alreadyの要素が1のときにその添字に対応する文字を表示すれば良い ***/
    for(i=0;i<KINDS_NUMBERS;i++){
      if(already[i]==1){
	printf("%c, ",i+'a');
      }
    }
    printf("\n");
    printf("Guess a word by %d characters from a to z.: ", num_chars); /*** 設問表示 ***/
    scanf("%c", &input); /*** ユーザ入力 ***/
    scanf("%c", &yomisute); /*** 読み捨て ***/
    printf("\n");
    /*** ユーザ入力が既にタイプされたことがあるかを判定 ***/
    /*** タイプされた文字に対応する添字の要素が0であれば ***/
    /*** 初めてタイプされた ***/
    /*** タイプされた文字に対応する添字の要素が1であれば，***/
    /*** 既にタイプされたことがある ***/
    /*** ユーザ入力が既にタイプされたことがあるならば， ***/
    /*** そんなメッセージを表示 ***/
    if(already[input-'a']==1){
      printf("Character you typed had already typed.\n");
    }
    /*** ユーザ入力の文字が初めてタイプされたならば ***/
    /*** 既タイプリストのための配列alreadyの更新 ***/
    /*** 正解か否かの判定 ***/
    /*** 正解ならば正解表示用変数current[i]を ***/
    /*** 正解に相当する文字に更新して ***/
    /*** 正解回数をインクリメント ***/
    /*** 正解でない場合にはミス数をインクリメント ***/
    /*** NUM_CHARS回正解したらそんなメッセージ表示してループ脱出 ***/
    /*** MAX_CHANCES回ミスしたらそんなメッセージ表示してループ脱出 ***/
    else{
      already[input-'a']=1;
      prev_hits=hits;
      for(i=0;i<num_chars;i++){
	if(input==correct[i]){
	  current[i]=correct[i];
	  hits++;
	}
      }
      if(prev_hits==hits){
	mistakes++;
      }
      if(hits==num_chars){
	printf("Bingo!\n");
	break;
      }
      if(mistakes==MAX_CHANCES){
	printf("Sorry, the correct word is ");
	/***%sを用いてcorrectを表示する***/
	printf("%s", correct);
	printf("\n");
	break;
      }
    }
  }

  free(current);
  return 0;
}
