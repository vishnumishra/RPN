#include "rpn.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "expr_assert.h"


void test_evaluate_eval_a_rpn_notation(){
	int result;
	result = evaluate("2 3 +");
	assertEqual( result,5);	
};