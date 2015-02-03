#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "rpn.h"
#include "../StackADT/stack.h"

//48 to 57 -> 0-9
// space 32;
int performOperation(int num1,int num2,char operator){
	int result;
	switch(operator){
		case '*':
			result = num1*num2;break;
		case '+':
			result =num1+num2;break;
		case '-':
			result =num1-num2;break;
		case '/':
			result =num1/num2;break;
	}			
	return result;
};

int evaluate(char *expression){
	int i,result,length = strlen(expression);
	int *a ;
	int num1,num2,num3;
	Stack s = createStack();
	for(i=0;i<length;i++){
		a = malloc(sizeof(int));
		
		if(expression[i] >=48 && expression[i] <= 57 ){
			*a = (expression[i] -'0');
			push(s,(void*)a);
		};

		if(expression[i] >='*' && expression[i] <= '/'){
			num2 = 	*(int*)(pop(s));
			num1 =  *(int*)(pop(s));
			// printf("%d\t%d\n",num1,num2);
			result = performOperation(num1,num2,expression[i]);
			push(s,&result);
		};
	}
	return result ;
};
