#include <stdio.h>

typedef struct arithmetic_operation // input number and operator
{
    int num[5];
    char operator[5];
}Arithmetic_operation;

void arithmetic(Arithmetic_operation* test);

void make_fraction(int numerator,
                   int denominator,
                   int i,
                   Arithmetic_operation* test);

int gcd(int a, int b);


int main() {

    Arithmetic_operation test = {{0, 0, 0, 0}, {'+', '-', '*', '/'}};
    
    /* input */
    scanf("%d %d %d %d", &test.num[0], &test.num[1], &test.num[2], &test.num[3]);
    
    /* error when devided by 0 */
    if(test.num[1] == 0 || test.num[3] == 0){
        printf("CAN'T DEVIDE WITH 0!!\n");
        return 0;
    }
    
    /* output */
    arithmetic(&test);
    
    return 0;
}

/* find Greatest Common Divisor(gcd) */
int gcd(int a, int b){
    if(b == 0){
        return a;
    }
    else{
        return gcd(b, a % b);
    }
}

/* make reduced fraction and print output */
void make_fraction(int numerator, int denominator, int i, Arithmetic_operation* test){
    
    int is_negative, devide;
    
    is_negative = (numerator * denominator);
    
    /* make both numerator and denominator positive, to find gcd */
    numerator = (numerator >= 0) ? numerator : -numerator;
    denominator = (denominator >= 0) ? denominator : -denominator;
    devide = gcd(numerator, denominator);

    /* devided by gcd to make reduced fraction */
    numerator /= devide;
    denominator /= devide;
    
    /* print output formula */
    printf("(%d / %d) %c (%d / %d) = ", test->num[0], test->num[1], test->operator[i], test->num[2], test->num[3]);
    
    /* print answer */
    if(is_negative < 0){
        printf("-");
    }
    if(denominator == 1)
        printf("%d\n", numerator);
    else{
        printf("%d / %d\n", numerator, denominator);
    }
}


void arithmetic(Arithmetic_operation* test){
    /* denom = denominator(분모), numer = numerator(분자) */
    int denom, numer = 1, i;
    
    /* same denominator from i = 0 to i = 2 */
    denom = test->num[1] * test->num[3];
    
    for(i = 0; i<4; i++){
        switch(i){
            case 0: // plus
                numer = test->num[0] * test->num[3] + test->num[1] * test->num[2];
                break;
                
            case 1: // minus
                numer = test->num[0] * test->num[3] - test->num[1] * test->num[2];
                break;
                
            case 2: // multiply
                numer = test->num[0] * test->num[2];
                break;
                
            case 3: // divide. we have different denominator here.
                numer = test->num[0] * test->num[3];
                denom = test->num[1] * test->num[2];
                
                /* error when devided by 0 */
                if(denom == 0){
                    printf("CAN'T DEVIDE WITH 0!!\n");
                    continue;
                }
                break;
        }
        
        make_fraction(numer, denom, i, test);
    }
}

