gcc -c stack.c stackNode.c test.c
gcc -o stack_test test.c stackNode.c stack.c
./stack_test
