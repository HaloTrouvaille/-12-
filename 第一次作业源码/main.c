#include "stdio.h"
#include "add.h"
#include "sub.h"
#include "mul.h"
#include "div.h"

int main(){
    int sum = 0, difference = 0, product = 0, quotient = 0;
    printf("This is a simple four arithmetic program!\n");
    sum = add(1, 2);
    difference = sub(2, 1);
    product = mul(1, 2);
    quotient = div(4, 1);
    printf("sum = %d\tdifference = %d\tproduct = %d\tquotient = %d\n", sum, difference, product, quotient);
    return 0;
}