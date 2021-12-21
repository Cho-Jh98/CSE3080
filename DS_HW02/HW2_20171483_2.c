#include <stdio.h>
#define MAX_STRING 31

void fail(char* pat, int* failure);
void pmatch(char* str, char* pat);

int char_len(char* str);
int arr_len(int* arr);

void get_string(char* string);
void pop(int* top, char* str);
void push(int* top, char* str, char input_char);

int main(){
    
    char string[MAX_STRING];
    char pattern[MAX_STRING];
    
    /* string and pattern input */
    printf("string : ");
    get_string(string);
    printf("pattern : ");
    get_string(pattern);
        
    pmatch(string, pattern);
    printf("\n");
    
    return 0;
}

void pmatch(char *str, char *pat){
    
    int i = 0, j = 0, top = -1, count = 0;
    /* get string length */
    int lens = char_len(str);
    int lenp = char_len(pat);
    
    int failure[MAX_STRING];
    /* for string which pat is deleted */
    char left_string[MAX_STRING] = {0};
    
    /* calculate failure function */
    fail(pat, failure);
    
    /* push the character whenever i++, and pop() when j == lenp, which means that pat is in str */
    /* use count variable to decide how many times we use pop() */
    while(i<lens && j<lenp){

        if(str[i] == pat[j]){
            push(&top, left_string, str[i]);
            i++; j++;
            count++;
        }
        else if (j == 0){
            push(&top, left_string, str[i]);
            count = 0;
            i++;
        }
        else {
            j = failure[j-1] + 1;
            count = 0;
        }
        
        /* if j==lenp, it means there is pat is in str until current i index.
           Doesn't change whether we pop the previous index,
           because it uses failure funtion to check whether pat is in str */
        if(j == lenp){
            j = failure[j-1] + 1;
            for(int k = 0; k < count; k++){
                pop(&top, left_string);
            }
            count = 0;
        }
    }
    /* from 0 to top, print the character saved in stack */
    printf("%s", left_string);
}

void get_string(char* string){
    
    for(int i = 0; i<MAX_STRING; i++){
        string[i] = getchar();
        if(string[i] == '\n'){
            string[i] = '\0';
            return;
        }
    }
}

int arr_len(int* arr){
    
    int i;
    for(i = 0; arr[i] != '\0'; i++);
    return i;
}

int char_len(char* str){
    
    int i;
    for(i = 0; str[i] != '\0'; i++);
    return i;
}

void fail(char* pat, int* failure){
    int i, n = char_len(pat);
    failure[0] = -1;
    
    for(int j = 1; j < n; j++){
        i = failure[j-1];
        while(pat[i] != pat[i+1] && i>=0)
            i = failure[i];
        
        if(pat[j] == pat[i+1])
            failure[j] = i+1;
        
        else failure[j] = -1;
    }
}

void pop(int* top, char* str){
    if(*top == -1){
        printf("empty");
        return;
    }
    str[*top] = '\0';
    *top -= 1;
}
void push(int* top, char* str, char input_char){
    if(*top == MAX_STRING-1){
        printf("Full");
        return;
    }
    *top += 1;
    str[*top] = input_char;
}
