#include "calculate.h"
#include<stdio.h>
int main()
{
	int num1, num2, result;
	char operator;
	printf("Enter Number 1: ");
	scanf("%d",&num1);
	printf("Enter Operator You Want: ");
	scanf(" %c",&operator);
	printf("Enter Number 2: ");
	scanf("%d",&num2);
	
	switch(operator)
	{
		case '+':
			result = add(num1, num2);
			break;
		case '-':
			result = sub(num1, num2);
			break;
		case '*':
			result = mul(num1, num2);
			break;
		case '/':
			if(num2 != 0)
			{
				result = div(num1, num2);
			}
			break;
	}
	printf("Result = %d\n",result);
}	
