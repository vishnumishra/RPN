#include "rpn.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "expr_assert.h"

	
void test_evaluate_eval_a_rpn_notation(){
	int result;
	char str[256] = "2 3 +";
	result = evaluate(str);
	assertEqual( result,5);	
};

void test_evaluate_eval_a_rpn_notation_1(){
	int result;
	char str[256] = "2 3 -";
	result = evaluate(str);
	assertEqual( result,-1);	
};

void test_evaluate_eval_a_rpn_notation_2(){
	int result;
	char str[256] = "2 3 *";
	result = evaluate(str);
	assertEqual( result,6);	
};


void test_evaluate_eval_a_rpn_notation_3(){
	int result;
	char str[256] = "2 3 /";
	result = evaluate(str);
	assertEqual( result,(2/3));	
};

void test_evaluate_eval_a_rpn_notation_4(){
	int result;
	char str[256] = "2 3 4 + -";
	result = evaluate(str);
	assertEqual( result,2-(3+4));	
};


void test_evaluate_eval_a_rpn_notation_5(){
	int result;
	char str[256] = "1 2 3 4 5 * * * * ";
	result = evaluate(str);
	assertEqual( result,120);	
};

void test_evaluate_eval_a_rpn_notation_6(){
	int result;
	char str[256] = "5 1 2 + 4 * + 3 -";
	result = evaluate(str);
	assertEqual( result,14);	
};

void test_evaluate_eval_a_rpn_notation_7(){
	int result;
	char str[256] = "2 2 2 * 2 - 3 + +";
	result = evaluate(str);
	assertEqual( result,7);	
};

void test_evaluate_eval_a_rpn_notation_8(){
	int result;
	char str[256] = "2 2 2 2 2 * * 2 + + 2 - *";
	result = evaluate(str);
	assertEqual( result,20);	
};

void test_evaluate_eval_a_rpn_notation_9(){
	int result;
	char str[256] = "2 2 - 2 2 2 * 2 - - - ";
	result = evaluate(str);
	assertEqual( result,0);	
};



