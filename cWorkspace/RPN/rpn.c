#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "rpn.h"

// ---------------------conventions-------------------------------
// 1 = operator, 2=operand, 3 = seprator,4=null;

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

int isDigit(char a){
	return (a>='0' && a<='9');
};

int isOperator(char a){
	return (a >= '*' && a <= '/');
}

int isSeprator(char a){
	return a ==' ';
}

int getType(char a){
	int result;
	if(isDigit(a))return 2;
	if(isOperator(a))return 1;
	if(isSeprator(a))return 3;
	return 0;
}

int getEnd(int i,int cs, char* exp){
	int ps=cs;
	while(ps == cs ){
		cs=	getType(exp[++i]);
	}
	return i-1;
}

Token *createToken(){
	Token *newTocken = malloc(sizeof(Token));
	return newTocken;
}

void showData(void* t){
	Token toc = *(Token*)t;
	printf("list data start  %d\n",toc.start_at);
	printf("%d\n",toc.end_at);
	printf("type %d\n",toc.type);
};

LinkedList getTokenList(char* exp){
	int i=0,cs;
	Token *t;
	LinkedList list = createList();
	while(i < strlen(exp)){
		cs =getType(exp[i]);
		t = createToken();
		t->type = cs;
		t->start_at = i;
		t->end_at = getEnd(i,cs,exp);
		i=t->end_at+1;
		add_to_list(&list,create_node(t));
	};
	return list;
};

int handleOperand(Token t,Stack* s,char* exp){
	int *digit,result,size = t.end_at - t.start_at +1;
	char* str = malloc(size);
	digit = malloc(sizeof(int));
	memcpy(str,&exp[t.start_at],size);
	*digit = atoi(str);
	result = push(*s,(void*)digit);
	return (result)?1:-2;
};

int handleOperator(Token t,Stack* s,char* exp){
	int *numRef1,*numRef2;
	int* result = malloc(sizeof(int));
	char operand = exp[t.start_at];
	numRef2 = pop(*s);
	numRef1 = pop(*s);
	if(numRef2 == 0 || numRef1 == 0 ) return -1;
	*result = performOperation(*(int*)numRef1,*(int*)numRef2,exp[t.start_at]);
	push(*s,result );
	return *result;
}

int perform(Token t,Stack *s,char* exp){
	int result;
	if(t.type==2) result = handleOperand(t,s,exp);
	if(t.type==1) result = handleOperator(t,s,exp);
	return result; // -2 toFew operand -1 to many operator;
};

int evaluate(char *exp){
	LinkedList list = getTokenList(exp);
	Token data;
	int i,result;
	Stack *s = malloc(sizeof(Stack));
	*s = createStack();
	for ( i = 0; i < list.count; ++i){
		data = *(Token*)getElementAt(list, i);
		result = perform(data,s,exp);
	};
	return result;
};

