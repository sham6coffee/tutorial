#include<stdio.h>
int main(void)
{
	for (int num = 127;num > 31;num -= 16)//num��127�ɐݒ�Fnum=32�ɒB����܂ň�����Ƃ�16����
	{
		for (int i = num; i > num - 16;i--)
			printf("%2c  |", i);//num����1�����Ȃ���Ή����镶����\��
		printf("\n");//���s����
		for (int i = num;i > num - 16;i--)
			printf("%3d |", i);//num����1�����Ȃ�����������ʂ̐�����\��
		printf("\n");//���s����
		for (int i = 0;i < 80;i++)
			printf("=");//=��80���ׂ�
		printf("\n");//���s����
	}
	return 0;
}