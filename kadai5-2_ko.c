#include<stdio.h>
int main(void)
{
	for (int num = 127;num > 31;num -= 16)//numを127に設定：num=32に達するまで一周ごとに16減る
	{
		for (int i = num; i > num - 16;i--)
			printf("%2c  |", i);//numから1引きながら対応する文字を表示
		printf("\n");//改行する
		for (int i = num;i > num - 16;i--)
			printf("%3d |", i);//numから1引きながら引いた結果の数字を表示
		printf("\n");//改行する
		for (int i = 0;i < 80;i++)
			printf("=");//=を80個並べる
		printf("\n");//改行する
	}
	return 0;
}