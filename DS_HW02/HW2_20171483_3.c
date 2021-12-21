#include <stdio.h>

int get_number(int* arr);
int make_equation(int* arr, char* cal, int num, int tar, int* iter, int* count);
void print_equation(int* arr, char* cal);
int do_calculate(int*arr, char*cal);


int main(){
    
    int arr[10], iter = 0;
    int count = 0;
    int target = 0, len;
    char cal[9] = {'\0'};
    printf("enter number array : ");
    len = get_number(arr);
    if(!len){
        printf("too many number");
        return 0;
    }
    printf("enter target number : ");
    scanf("%d", &target);
    
    make_equation(arr, cal, len, target, &iter, &count);
    if(count == 0) // if there is no equation for target number,
        printf("None\n");
    
    
    return 0;
}

int get_number(int* arr){
    
    int i;
    char temp;
    
    for(i = 0; i<11; i++){
        temp = getchar();
        if(temp == '\n'){
            return i; // length of array
        }
        arr[i] = temp - '0';
    }
    return 0;
}

int make_equation(int* arr, char* cal, int len, int tar, int* iter, int* count){
    
    int i = 0;
    int ans = 0;
    /* exit condition of recursive function */
    /* if we have *iter 9, it means we have 9 operator*/
    if (*iter == len-1){
        ans = do_calculate(arr, cal);
        if(ans == tar){
            print_equation(arr, cal);
            *count += 1; // if this function returns count == 0, it means there is no equation for target number.
                         // count++ if there is matching equation for target number
        }
    }
    
    else{
        for(i = 0; i<4; i++){ // for operators, '+', '-', '*', ' '. And ' ' is to combine numbers
            switch(i){
                case 0:
                    cal[*iter] = '+';
                    *iter += 1;
                    make_equation(arr, cal, len, tar, iter, count);
                    *iter -= 1; // *iter - 1 for other operator.
                    break;
                case 1:
                    cal[*iter] = '-';
                    *iter += 1;
                    make_equation(arr, cal, len, tar, iter, count);
                    *iter -= 1;
                    break;
                case 2:
                    cal[*iter] = '*';
                    *iter += 1;
                    make_equation(arr, cal, len, tar, iter, count);
                    *iter -= 1;
                    break;
                case 3:
                    cal[*iter] = ' ';
                    *iter += 1;
                    make_equation(arr, cal, len, tar, iter, count);
                    *iter -= 1;
                    break;
                default:
                    *iter += 1;
                }
            }
    }
    return *count;
}


int do_calculate(int*arr, char*cal){
    int i = 1, j;
    int temp;
    /* new int array and char arry to save result of '*' and ' ' calculation
       Creating new arrays because we don't want to mess up with original arrays, that are used for printing equations. */
    int temp_arr[10];
    char temp_cal[9];
    for(i = 0; i<9; i++){
        temp_arr[i] = arr[i];
        temp_cal[i] = cal[i];
    }
    temp_arr[9] = arr[9];
    
    /* ' ' and '*' operator needs to be done first(' ' first, '*' later */
    /* for ' ' operator, 1 2 bcomes 1 * 10 + 2 */
    for(i = 0; i<10; i++){
        if(temp_cal[i] == ' '){
            temp_arr[i] = temp_arr[i] * 10 + temp_arr[i+1];
            j = i;
            for(j = i; j<8; j++){ // after calculation of ' ', pull the rest of numbers and operators
                temp_arr[j+1] = temp_arr[j+2];
                temp_cal[j] = temp_cal[j+1];
            }
            i--;
        }
    }
    for(i = 0; i<10; i++){
        if(temp_cal[i] == '*'){
            temp_arr[i] = temp_arr[i] * temp_arr[i+1];
            int j = i;
            for(j = i; j<8; j++){ // after calculation of '*', pull the rest of numbers and operators
                temp_arr[j+1] = temp_arr[j+2];
                temp_cal[j] = temp_cal[j+1];
            }
            i--;
        }
    }
    
    /* Do the rest of operator ('+', '-') */
    temp = temp_arr[0];
    i = 1;
    while(temp_arr[i] != '\0'){
        if(temp_cal[i-1] == '+'){
            temp = temp+temp_arr[i];
        }
        else if(temp_cal[i-1] == '-'){
            temp = temp-temp_arr[i];
        }
        i++;
    }
    
    return temp;
}

/* print the equation */
void print_equation(int* arr, char* cal){
    
    int i = 0;
    while(arr[i] != '\0'){
        printf("%d", arr[i]);
        if(cal[i] != ' '){
            printf("%c", cal[i]);
        }
        i++;
    }
    printf("\n");
}
