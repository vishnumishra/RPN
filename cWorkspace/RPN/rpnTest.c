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





