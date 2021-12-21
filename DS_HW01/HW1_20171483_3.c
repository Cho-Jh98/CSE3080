#include <stdio.h>

int is_prime(int num);
void find_divisor(int num);

int main(){
    
    int num;
    
    /* input number */
    scanf("%d", &num);
    
    if(is_prime(num)){
        printf("Prime number입니다.\n");
    }
    else{
        printf("Prime number가 아닙니다.\n");
        printf("약수는 : ");
        find_divisor(num);
    }
    return 0;
}

int is_prime(int num){
    
    int i, count = 0;
    
    /* find number of divisor */
    for(i = 1; i<=num; i++){
        if(num % i == 0){
            count++; // count number of divisor
        }
    }

    /* prime number has 2 divisor by its definition */
    if(count == 2)
        return 1;
    else
        return 0;
    
}

void find_divisor(int num){
    
    int i;
    
    /* print divisor from largest number, not including 1 for editing purpose */
    for(i = num; i>1 ; i--){
        if(num % i == 0){
            printf("%d, ", i);
        }
    }
    /* 1 is divisor for all positive integer */
    printf("1\n");
}



