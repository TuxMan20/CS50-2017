#include <stdio.h>
#include <stdlib.h>

int main(void){

int * pk = NULL;
int   k[5] = {5,4,3,2,1,};

pk = &k[0];

char * s = malloc(6);

s[0] = 'd';

printf("%p  %p\n",&pk,pk);

printf("%p  %p %p \n",&s,&s[0],&*s);
}