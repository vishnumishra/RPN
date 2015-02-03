#include "rpn.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "expr_assert.h"

	
void test_evaluate_eval_a_rpn_notation(){
	char str[256] = "2 3 +";
	Status status = evaluate(str);
	assertEqual( status.result,5);	
};

void test_evaluate_eval_a_rpn_notation_1(){
	
	char str[256] = "2 3 -";
	Status status = evaluate(str);
	assertEqual( status.result,-1);	
};

void test_evaluate_eval_a_rpn_notation_2(){
	
	char str[256] = "2 3 *";
	Status status = evaluate(str);
	assertEqual( status.result,6);	
};


void test_evaluate_eval_a_rpn_notation_3(){
	
	char str[256] = "2 3 /";
	Status status = evaluate(str);
	assertEqual( status.result,(2/3));	
};

void test_evaluate_eval_a_rpn_notation_4(){
	
	char str[256] = "2 3 4 + -";
	Status status = evaluate(str);
	assertEqual( status.result,2-(3+4));	
};


void test_evaluate_eval_a_rpn_notation_5(){
	
	char str[256] = "1 2 3 4 5 * * * * ";
	Status status = evaluate(str);
	assertEqual( status.result,120);	
};

void test_evaluate_eval_a_rpn_notation_6(){
	
	char str[256] = "5 1 2 + 4 * + 3 -";
	Status status = evaluate(str);
	assertEqual( status.result,14);	
};

void test_evaluate_eval_a_rpn_notation_7(){
	
	char str[256] = "2 2 2 * 2 - 3 + +";
	Status status = evaluate(str);
	assertEqual( status.result,7);	
};

void test_evaluate_eval_a_rpn_notation_8(){
	
	char str[256] = "2 2 2 2 2 * * 2 + + 2 - *";
	Status status = evaluate(str);
	assertEqual( status.result,20);	
};

void test_evaluate_eval_a_rpn_notation_9(){
	
	char str[256] = "2 2 - 2 2 2 * 2 - - - ";
	Status status = evaluate(str);
	assertEqual( status.result,0);	
};

void test_evaluate_eval_a_rpn_notation_10(){
	char str[256] = "2 4 + +";
	Status status = evaluate(str);
	assertEqual(status.error,'+');	
};

void test_evaluate_eval_a_rpn_notation_11(){
	char str[256] = "2 4 + /";
	Status status = evaluate(str);
	assertEqual(status.error,'/');	
};

void test_evaluate_eval_a_rpn_notation_12(){
	char str[256] = "2 4 3 +";
	Status status = evaluate(str);
	assertEqual(status.error,1);	
};

void test_evaluate_eval_a_rpn_notation_13(){
	char str[256] = "2 4 3 + + -";
	Status status = evaluate(str);
	assertEqual(status.error,'-');	
};


