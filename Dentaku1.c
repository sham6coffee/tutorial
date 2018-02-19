#include<stdio.h>
#include<stdlib.h>

#define TAX 1.08

int main(void) {


	int input;
	int output = 0;
	int sum = 0;

	while (1) {
		while (1) {
			printf("0-9,10=del,11=enter:");
			scanf("%d", &input);
			getchar();
			printf("input:%d\n", input);
			if (input >= 0 && input <= 11)break;
			else {
				printf("error\n");
			}
		}
		if (input < 10) {
			output = output * 10 + input;

		}
		else if (input == 10) {
			output = (output - (output % 10)) / 10;
		}
		else {
			sum += output;
			output = 0;
		}
		printf("output:%d\n", output);
		printf("sum:%d\n", sum);
		printf("sum(include Tax):%.2f\n", (double)(sum*TAX));
	}


	return 0;
}
