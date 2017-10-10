#include <stdio.h>

double seqavg(double num){
static double cunt=1;
static double ave;
ave=(ave*(cunt-1)+num)/cunt;
cunt++;
return ave;

}

int main(void)
{
	double num;
	int count=0;
	double average=0;
	
	while(1){
	printf("データを入力しろ\n");
	scanf("%lf",&num);
	getchar();
	count++;
	average=seqavg(num);
	printf("データの個数:%d、ここまでの平均:%f",count,average);
	}
	return 0;
}