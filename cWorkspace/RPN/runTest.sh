#! /bin/bash

input=$1
# clear
echo ${input}
ctest rpn.c rpnTest.c ../StackADT/stack.c ../StackADT/linkedList.c  ../Queue/queue.c {$input}
