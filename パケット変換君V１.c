#include <stdio.h>
#include<stdlib.h>

#define BYTE 3
#define FF 255
int main(void) {
	FILE *fp;
	int bango;
	int hosu;
	int check1=0;
	int check2 = 0;
	int checksum=0;
	int buff[BYTE];
	int i;
	char sss[BYTE];
	char flag;
	fp=fopen("word.txt", "w");
	
	while (1) {
		printf("�ԍ�:");
		scanf("%x", &bango);
		getchar();
		printf("�␔:");
		scanf("%x", &hosu);
		getchar();
		check1 = bango + hosu;
		if (check1 == FF) {
			printf("OK\n");
		}
		else {
			printf("�a��ff�ɂȂ�Ȃ�\n");
			continue;
		}


		for (i = 0;i < BYTE;i++) {
			printf("[%d]:", i);
			scanf("%x", &buff[i]);
			getchar();
			check2 += buff[i];
			//printf("%d\n", buff[i]);
			sss[i] = buff[i];
			//printf("%c\n", sss[i]);
		}
		//�����\��
		for (i = 0;i < BYTE;i++) {
			printf("%c", sss[i]);
		}
		printf("\n");
		//
		check2 = check2 % 256;
		
		scanf("%x",&checksum);
		getchar();
		
		if (check2 == checksum) {
			printf("OK\n");
			for (i = 0;i < BYTE;i++) {
			fprintf(fp,"%c",sss[i]);
			}
		}
		else {
			printf("�`�F�b�N�T���s�K\n");
		}
		
		check2 = 0;
		printf("continue?(y/n):\n");
		scanf("%c",&flag);
		getchar();
		if(flag!='y')break;
		
	}
	
	return 0;
}