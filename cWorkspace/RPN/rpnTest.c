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

void test_Pseudo_test_evaluate(){
	char* exp  = "2415 23 +";
	evaluate(exp);
}



