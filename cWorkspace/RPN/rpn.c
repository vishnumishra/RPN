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
	char* operator = "^*/+-)(";int i;
	for(i=0;i<strlen(operator);i++){
		if(operator[i]==a)return 1;
	}
	return 0;
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

void showTokenData(void* t){
	Token toc = *(Token*)t;
	printf("token start_at:  %d | ",toc.start_at);
	printf("token end_at: %d | ",toc.end_at);
	printf("type of token: %d\n",toc.type);
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
		if (cs == 1) t->end_at = i;
		else
			t->end_at = getEnd(i,cs,exp);
		i=t->end_at+1;
		add_to_list(&list,create_node(t));
	};
	return list;
};

void handleOperand(Token t,Stack* s,char* exp,Status *status){
	int *digit=malloc(sizeof(int)),result;
	*digit = atoi(&exp[t.start_at]);
	result = push(*s,(void*)digit);
	(result > 2 ) ? (status->error = -2) : (status->error = 0);
};

void handleOperator(Token t,Stack* s,char* exp,Status *status){
	int *numRef1,*numRef2,*result = malloc(sizeof(int));
	numRef2 = pop(*s);
	numRef1 = pop(*s);
	if(numRef2 == 0 || numRef1 == 0 ) (status->error) = exp[t.start_at];
	else{
		*result = performOperation(*(int*)numRef1,*(int*)numRef2,exp[t.start_at]);
		push(*s,result );
		status->result = *result;
	}
};

void controlOperation(Token t,Stack *s,char* exp,Status *status){
	if(t.type==2)  handleOperand(t,s,exp,status);
	if(t.type==1)  handleOperator(t,s,exp,status);
};

Status *evaluate(char *exp){
	LinkedList list = getTokenList(exp);
	Token data;
	int i;
	Status* status = malloc(sizeof(Status));
	Stack *s = malloc(sizeof(Stack));
	*s = createStack();
	for ( i = 0; i < list.count; ++i){
		data = *(Token*)getElementAt(list, i);
		controlOperation(data,s,exp,status);
	};
	free(s);
	return status;
};
//---------------------------------------------------------v.4---------------------------------------------------------------------------

int getPrecedence(char smbl){
	switch(smbl){
		case '(' : return 1;
		case '-' :case '+' : return 2;
		case '*' :case '/' : return 3;
		case '^' : return 4;
	};
	return 0;
};

int isStackEmpty(Stack *s){
	return (*(s->top))==NULL;
};
char getTop(Stack *s){
	return (*s->top !=0)?*(char*)(*s->top)->data:-1;
};
void handleInfixOperand(Token t,Queue* q,char* exp,Status *status){
	int result,size = t.end_at - t.start_at +1;
	char* str = calloc(1,size);
	memcpy(str,&(exp[t.start_at]),size);
	result = enqueue (*q, str);
	(result > 2 ) ? (status->error = -2) : (status->error = 0);
};
int pushOperator(Stack s,void* data){
	char* op=calloc(sizeof(char),1);
	memcpy(op,data,sizeof(char));
	return push(s,op);
};
void showQueueData(void*d){
	printf("%s\n",d );
};

int isHigherOrEqualPricedence(Stack *s,char op){
	int prevPricedence = isStackEmpty(s)?0:getPrecedence(getTop(s));
	int currentPrecedence = getPrecedence(op);
	return prevPricedence <= currentPrecedence;
}
int isHigherPricedence(Stack *s,char op){
	int prevPricedence = isStackEmpty(s)?0:getPrecedence(getTop(s));
	int currentPrecedence = getPrecedence(op);
	return prevPricedence < currentPrecedence;
}
int isEqualPricedence(Stack *s,char op){
	int prevPricedence = isStackEmpty(s)?0:getPrecedence(getTop(s));
	int currentPrecedence = getPrecedence(op);
	return prevPricedence == currentPrecedence;
}

int isParentheses(char ch){
	return (ch=='('||ch==')');
}

void handleInfixOperator(Token t,Stack* s,Queue* q,char* exp,Status *status){

	if(isStackEmpty(s)||isHigherOrEqualPricedence(s,exp[t.start_at]) || exp[t.start_at] =='('){
		pushOperator(*s,&exp[t.start_at]);
	}
	while(!isStackEmpty(s) && !isParentheses(exp[t.start_at]) && !isHigherOrEqualPricedence(s,exp[t.start_at])){
		enqueue(*q,pop(*s));
		pushOperator(*s,&exp[t.start_at]);
	}
	if(exp[t.start_at] ==')'){
		while(getTop(s) != '('){
			enqueue(*q,pop(*s));
		}
		pop(*s);
	}
};

char* create_string_from_queue(Queue*q){
	char* str = calloc(sizeof(char*),20);
	char *data;
	int i=0,j,length;
	while((*q->head) != 0){
		data = dequeue(*q);
		for(j=0;j<strlen(data);j++){
		str[i++] = data[j];
		}
		str[i] = ' ';
		i++;
	}
	return str;
};

void controlInfixOperation(Token t,Stack *s,Queue *q,char* exp,Status *status){
	if(t.type==2)  handleInfixOperand(t,q,exp,status);
	if(t.type==1)  handleInfixOperator(t,s,q,exp,status);
};


char * infixToPostfix(char * exp){
	LinkedList list = getTokenList(exp);
	Token data;
	int i;
	Status* status = calloc(sizeof(Status),1);
	Stack *s = calloc(sizeof(Stack),1);
	Queue *q = calloc(sizeof(Queue),1);
	*q = createQueue();
	*s = createStack();
	for ( i = 0; i < list.count; ++i){
		data = *(Token*)getElementAt(list, i);
		controlInfixOperation(data,s,q,exp,status);
	};
	while(!isStackEmpty(s)){
		enqueue(*q,pop(*s));
	};
 	free(s);
	return create_string_from_queue(q);
};





