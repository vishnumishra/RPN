#include "../StackADT/stack.h"
#include "../Queue/queue.h"
typedef struct status {
  int error;
  int result;
}Status;

typedef struct token{
	int start_at;
	int end_at;
	int type;// 1 = operator, 2=operand, 3 = seprator,4=null;
}Token;

Status* evaluate(char *expression); 
int getEnd(int i,int cs, char* exp);
int getType(char a);
LinkedList getTokenList(char* exp);
int performOperation(int num1,int num2,char optr);
int isDigit(char);
int isOperator(char a);
int getType(char a);
void handleOperand(Token t,Stack* s,char* exp,Status *status);
char * infixToPostfix(char * expression);
int getPrecedence(char smbl);
void handleInfixOperand(Token t,Queue* q,char* exp,Status *status);

