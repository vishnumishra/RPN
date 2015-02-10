#include "rpn.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "expr_assert.h"

	

void test_getType_give_2_for_digit(){
	assertEqual(getType('5'),2);
};
void test_getType_give_2_for_digit_1(){
	assertEqual(getType('0'),2);
};

void test_getType_give_2_for_digit_2(){
	assertEqual(getType('9'),2);
};

void test_getType_give_1_for_operator_3(){
	assertEqual(getType('+'),1);
};

void test_getType_give_1_for_operator_4(){
	assertEqual(getType('/'),1);
};

void test_getType_give_1_for_operator_5(){
	assertEqual(getType('-'),1);
};

void test_getType_give_3_for_seprator_6(){
	assertEqual(getType(' '),3);
};

void test_getType_give_0_for_other_7(){
	assertEqual(getType('a'),0);
};

void test_evaluate_eval_a_rpn_notation(){
	char str[256] = "2 3 +";
	Status *status = evaluate(str);
	assertEqual( status->result,5);	
};

void test_evaluate_eval_a_rpn_notation_1(){
	
	char str[256] = "2 3 -";
	Status *status = evaluate(str);
	assertEqual( status->result,-1);	
};

void test_evaluate_eval_a_rpn_notation_2(){
	
	char str[256] = "2 3 *";
	Status *status = evaluate(str);
	assertEqual( status->result,6);	
};


void test_evaluate_eval_a_rpn_notation_3(){
	
	char str[256] = "2 3 /";
	Status *status = evaluate(str);
	assertEqual( status->result,(2/3));	
};

void test_evaluate_eval_a_rpn_notation_4(){
	
	char str[256] = "2 3 4 + -";
	Status *status = evaluate(str);
	assertEqual( status->result,2-(3+4));	
};


void test_evaluate_eval_a_rpn_notation_5(){
	
	char str[256] = "1 2 3 4 5 * * * * ";
	Status *status = evaluate(str);
	assertEqual( status->result,120);	
};

void test_evaluate_eval_a_rpn_notation_6(){
	
	char str[256] = "5 1 2 + 4 * + 3 -";
	Status *status = evaluate(str);
	assertEqual( status->result,14);	
};

void test_evaluate_eval_a_rpn_notation_7(){
	
	char str[256] = "2 2 2 * 2 - 3 + +";
	Status *status = evaluate(str);
	assertEqual( status->result,7);	
};

void test_evaluate_eval_a_rpn_notation_8(){
	
	char str[256] = "2 2 2 2 2 * * 2 + + 2 - *    ";
	Status *status = evaluate(str);
	assertEqual( status->result,20);	
};

void test_evaluate_eval_a_rpn_notation_9(){
	
	char str[256] = "2 2 - 2 2 2 * 2 - - - ";
	Status *status = evaluate(str);
	assertEqual( status->result,0);	
};

void test_evaluate_eval_a_rpn_notation_10(){
	char str[256] = "2 4 + +";
	Status *status = evaluate(str);
	assertEqual(status->error,'+');	
};

void test_evaluate_eval_a_rpn_notation_11(){
	char str[256] = "2 4 + /";
	Status *status = evaluate(str);
	assertEqual(status->error,'/');	
};

void test_evaluate_eval_a_rpn_notation_12(){
	char str[256] = "2 4 3 +";
	Status *status = evaluate(str);
	assertEqual(status->error,-2);	
};

void test_evaluate_eval_a_rpn_notation_13(){
	char str[256] = "2 4 3 + + -";
	Status *status = evaluate(str);
	assertEqual(status->error,'-');	
};

void test_getEnd_give_the_end_of_a_type_1(){
	char* exp  = "2415 + 23 + +";
	assertEqual(getEnd( 0,2,exp), 3) ;
}

void test_evaluate_eval_a_rpn_notation_14(){
	char str[256] = "2 3 *";
	Status *status = evaluate(str);
	assertEqual( status->error,0);	
};

void test_getEnd_give_the_end_of_a_type_2(){
	char* exp  = "2415   + 23 + +";
	assertEqual(getEnd( 4,3,exp), 6) ;
}

void test_getEnd_give_the_end_of_a_type_3(){
	char* exp  = "2415 + 231 + +";
	assertEqual(getEnd( 7,2,exp), 9) ;
}

void test_getEnd_give_the_end_of_a_type_4(){
	char* exp  = "2415 + 231 ++";
	assertEqual(getEnd( 7,2,exp), 9) ;
}

void test_getEnd_give_the_end_of_a_type_5(){
	char* exp  = "2415 ++++ 231 ++  ";
	assertEqual(getEnd( 5,2,exp), 5) ;
}

void test_getTockenList_give_the_list_of_token(){
	char* exp = "23 4 + - 3 * 5";
	LinkedList list =  getTokenList(exp);
	Token t = *(Token*)(list.head)->data;
	assertEqual(t.start_at, 0);
	assertEqual(t.end_at, 1);
};

void test_getTockenList_give_the_list_of_token_1(){
	char* exp = "2366+ 4 + - 3 * 5";
	LinkedList list =  getTokenList(exp);
	Token t = *(Token*)(list.head)->data;
	assertEqual(t.start_at, 0);
	assertEqual(t.end_at, 3);
};

void test_getTockenList_give_the_list_of_token_2(){
	char* exp = "2366 + 4 + - 3 * 5";
	LinkedList list =  getTokenList(exp);
	Token t = *(Token*)getElementAt(list,2);
	assertEqual(t.start_at, 5);
	assertEqual(t.end_at, 5);
};
void test_getTockenList_give_the_list_of_token_3(){
	char* exp = "2366 ++++ 4 + - 3 * 5";
	LinkedList list =  getTokenList(exp);
	Token t = *(Token*)getElementAt(list,2);
	assertEqual(t.start_at, 5);
	assertEqual(t.end_at, 5);
};
void test_getTockenList_give_the_list_of_token_4(){
	char* exp = "2366 ++++ 4 + - 3 * 5";
	LinkedList list =  getTokenList(exp);
	Token t = *(Token*)getElementAt(list,3);
	assertEqual(t.start_at, 6);
	assertEqual(t.end_at, 6);
};

void test_getTockenList_give_the_list_of_token_5(){
	char* exp = "2366 ++++ 4 + - 3 * 420";
	LinkedList list =  getTokenList(exp);
	Token t = *(Token*)getElementAt(list,17);
	assertEqual(t.start_at, 20);
	assertEqual(t.end_at, 22);
	assertEqual(t.type, 2);
};

void test_is_digit_tell_the_string_is_digit_or_not(){
	assertEqual(isDigit('2'),1);
};
void test_is_digit_tell_the_string_is_digit_or_not_1(){
	assertEqual(isDigit('*'),0);
};
void test_is_digit_tell_the_string_is_digit_or_not_2(){
	assertEqual(isDigit('g'),0);
};

void test_Pseudo_test_evaluate(){
	char* exp  = "2415 23 +";
	evaluate(exp);
}

void test_isOperator_tell_the_given_char_is_operator_or_not(){
	assertEqual(isOperator('+'),1);
};

void test_isOperator_tell_the_given_char_is_operator_or_not_2(){
	assertEqual(isOperator('^'),1);
};

void test_isOperator_tell_the_given_char_is_operator_or_not_3(){
	assertEqual(isOperator('a'),0);
};

void test_isOperator_tell_the_given_char_is_operator_or_not_4(){
	assertEqual(isOperator('@'),0);
};

void test_isOperator_tell_the_given_char_is_operator_or_not_5(){
	assertEqual(isOperator('1'),0);
};

void test_isOperator_tell_the_given_char_is_operator_or_not_6(){
	assertEqual(isOperator('$'),0);
};

void test_infix_to_postFix_convert_exp(){
	char* infix = "3 + 4 / ( 1 - 5 ) ^ 2 ^ 3",*result;
	char* postfix = "3 4 1 5 - 2 3 ^ ^ / + ";
	result = infixToPostfix(infix);
	assertEqual(strcmp(postfix,result),0);
};
void test_infix_to_postFix_convert_exp_02(){
	char* infix = "3+4/(1-5)^2^3",*result;
	char* postfix = "3 4 1 5 - 2 3 ^ ^ / + ";
	result = infixToPostfix(infix);
	assertEqual(strcmp(postfix,result),0);
};
void test_getPrecedence_give_the_pricedence_of_the_operator(){
	int result = getPrecedence('+');
	assertEqual(result,2);
}
void test_getPrecedence_give_the_pricedence_of_the_operator_1(){
	int result = getPrecedence('*');
	assertEqual(result,3);
}
void test_getPrecedence_give_the_pricedence_of_the_operator_2(){
	int result = getPrecedence('^');
	assertEqual(result,4);
}
void test_getPrecedence_give_the_pricedence_of_the_operator_3(){
	int result = getPrecedence('(');
	assertEqual(result,1);
}

void test_getPrecedence_give_the_pricedence_of_the_operator_4(){
	int result = getPrecedence('-');
	assertEqual(result,2);
}

void test_handleInfixOperand_enque_the_operand_into_queue_1(){
	Token t={0,1,2},t1={5,5,2};
	char* exp = "23 + 5",*data,*data1;
	Queue q = createQueue();
	Status* s  = malloc(sizeof(Status));
	handleInfixOperand(t,&q,exp,s);
	handleInfixOperand(t1,&q,exp,s);
	data = (char*)((*(q.head))->data);
	data1 = (char*)((*(q.tail))->data);
	assertEqual(strcmp(data,"5"),0);
	assertEqual(strcmp(data1,"23"),0);
	free(s);
};

void test_isStackEmpty_tell_that_stack_is_empty_or_not(){
	Stack s=createStack();
	int data[]={2,33,43};
	assertEqual(isStackEmpty(&s),1);
	push(s,&data[0]);
	push(s,&data[1]);
	assertEqual(isStackEmpty(&s),0);
	pop(s);pop(s);
	assertEqual(isStackEmpty(&s),1);
};

void test_handleInfixOperator_enque_the_operand_into_queue_2(){
	char* exp = "2 + 5",*data,*data1;
	LinkedList list=getTokenList(exp);
	Token t = *(Token*)getElementAt(list, 4);
	Token t1 = *(Token*)getElementAt(list, 2);
	Stack *stack = calloc(sizeof(stack),1);
	Queue q = createQueue();
	Status* s  = calloc(sizeof(Status),1);
	*stack = createStack();
	
	handleInfixOperand(*(Token*)(*list.head).data,&q,exp,s);
	handleInfixOperand(t,&q,exp,s);

	handleInfixOperator(t1,stack,&q,exp,s);
	data = (char*)((*(q.head))->data);
	data1 = (char*)((*(q.tail))->data);

	assertEqual(strcmp(data1,"2"),0);
	assertEqual(strcmp(data,"5"),0);
	free(stack);free(s);
};

void test_handleInfixOperator_enque_the_operand_into_queue_3(){
	char exp[20] = "7 + ( 9 * 2 )";
	char result[20] = "7 9 2 * + ";
	char* string =  infixToPostfix(exp);
	assertEqual(strcmp(result,string),0);
};
void test_handleInfixOperator_enque_the_operand_into_queue_4(){
	char exp[20] = "7 * ( 9 + 2 )";
	char result[20] = "7 9 2 + * ";
	char* string =  infixToPostfix(exp);
	assertEqual(strcmp(result,string),0);
};

void test_handleInfixOperator_enque_the_operand_into_queue_5(){
	char exp[20] = "71 + 4 / 62";
	char result[20] = "71 4 62 / + ";
	char* string =  infixToPostfix(exp);
	assertEqual(strcmp(result,string),0);
};

void test_isHigherOrEqualPricedence_tell_that_theCurrent_operator_pricedence_is_higher_or_not_1(){
	char* data = "*+/-";
	Stack *s=malloc(sizeof(Stack));
	*s = createStack();
	push(*s, &data[0]);
	assertEqual(isHigherOrEqualPricedence(s,'/'), 1);
}
void test_isHigherOrEqualPricedence_tell_that_theCurrent_operator_pricedence_is_higher_or_not_2(){
	char* data = "*+/-^";
	Stack *s=malloc(sizeof(Stack));
	*s = createStack();
	push(*s, &data[0]);
	assertEqual(isHigherOrEqualPricedence(s,'-'), 0);
}

void test_isHigherOrEqualPricedence_tell_that_theCurrent_operator_pricedence_is_higher_or_not_3(){
	char* data = "*+/-^";
	Stack *s=malloc(sizeof(Stack));
	*s = createStack();
	push(*s, &data[0]);
	assertEqual(isHigherOrEqualPricedence(s,'^'), 1);
}

void test_create_string_from_queue_create_the_string(){
	Queue *q=calloc(sizeof(Queue),1);
	char *str = calloc(sizeof(char*),2);
	char *result = calloc(sizeof(char*),8);
	str = "71\09\0-\0";
	*q=createQueue();
	enqueue(*q,&str[0]);
	enqueue(*q,&str[3]);
	enqueue(*q,&str[5]);
	result = create_string_from_queue(q);
	assertEqual(strcmp(result,"71 9 - "), 0);
};










