// typedef struct staus Status;
#include "../StackADT/stack.h"
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
