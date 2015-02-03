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

Status evaluate(char *exp){
	int i,length = strlen(exp),*a ,error;
	void * num1,*num2;
	Status status;
	Stack s = createStack();
	for(i=0;i<length;i++){
		a = malloc(sizeof(int));
		if(exp[i] >=48 && exp[i] <= 57 ){
			*a = (exp[i] -'0');
			push(s,(void*)a);
		}
		if(exp[i] >='*' && exp[i] <= '/'){
			num2 = 	(pop(s));
			num1 =  (pop(s));
			if(num1 == NULL || num2 == NULL) error = exp[i];
			else{
				status.result = performOperation(*(int*)num1,*(int*)num2,exp[i]);
				push(s,&(status.result));
			}
		}
		if(s.list->count > 1  )error = 1;
	};
	status.error = error;
	free(a);
	return status ;
};
