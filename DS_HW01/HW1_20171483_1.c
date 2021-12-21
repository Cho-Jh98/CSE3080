#include <stdio.h>
#define MAX_NUM 50

int is_well_formed(char* text);
void make_well_formed(char* text);
char pop(char* text);
void push(char* text, char ch);
int is_empty(char* text);
char see_top_stack(char* text);
int string_length(char* text);

int main(){

    char palindrome[MAX_NUM + 1] = {};
    int i;
    
    for(i = 0; i<MAX_NUM; i++){
        palindrome[i] = getchar(); // Assume there is no space in input
        if(palindrome[i] == '\n'){
            palindrome[i] = '\0';
            break;
        }
    }
  
    if(!is_well_formed(palindrome)){
        make_well_formed(palindrome);
    }

    return 0;
}

int is_well_formed(char* text){
    char stack[MAX_NUM + 1], popped_ch;
    int i = 0, str_len;
    
    str_len = string_length(text);
    
    for(i = 0; i<str_len; i++){
        // if text[i] is not brackets, skip
        if(text[i] != '(' && text[i] != '{' && text[i] != '['
           && text[i] != ')' && text[i] != '}' && text[i] != ']')
            continue;
        // if text[i] == opening brackets, push it to the stack
        if(text[i] == '(' || text[i] == '{' || text[i] == '['){
            push(stack, text[i]);
        }
        
        else{ // if text[i] == closing bracket
            if(is_empty(stack)){ // and there is no opening bracket in stack it is not well-formed
                printf("Not well formed string\n");
                return 0;
            }
            else{ // if stack is not empty,
                popped_ch = pop(stack); // pop one element in stack,
                /* and compare with text[i]
                   if it doesn't match with closing bracket, it is not well-formed */
                if(popped_ch == '(' && text[i] != ')'){
                    printf("Not well formed string\n");
                    return 0;
                }
                else if(popped_ch == '{' && text[i] != '}'){
                    printf("Not well formed string\n");
                    return 0;
                }
                else if(popped_ch == '[' && text[i] != ']'){
                    printf("Not well formed string\n");
                    return 0;
                }
            }
        }
    }
    
    if(is_empty(stack)){ // if stack is empty, it means every bracket has matching one, and well formed
        printf("Well formed string\n");
        return 1;
    }
    else{
        printf("Not well formed string\n");
        return 0;
    }
}


/* make_well_formed() has same algorithm with is_well_form() function
   but we push text[i] to new_string and if it has no matching brackets, push a matching element
   after we pushed all the matching bracket, print new_string() */
void make_well_formed(char* text){
    char stack[MAX_NUM + 1]={0}, popped_ch, new_string[MAX_NUM*2 + 1]={0}, temp;
    int i = 0, str_len = 0, count = 0;
    
    str_len = string_length(text);
    
    for(i = 0; i<str_len; i++){
        
        // if text[i] is not brackets, skip
        if(text[i] != '(' && text[i] != '{' && text[i] != '['
           && text[i] != ')' && text[i] != '}' && text[i] != ']'){
            push(new_string, text[i]);
            continue;
        }
        
        // if text[i] == opening brackets, push it to the stack and new_string.
        else if(text[i] == '(' || text[i] == '{' || text[i] == '['){
            push(stack, text[i]);
            push(new_string, text[i]);
        }
        
        // text[i] == closing bracket
        else{
            /* if text[i] is closing bracket and stack is empty,
               push opening and closing bracket into new_string in that order. */
            if(is_empty(stack)){
                
                if(text[i] == '}'){
                    push(new_string, '{');
                    push(new_string, '}');
                }
                else if(text[i] == ')'){
                    push(new_string, '(');
                    push(new_string, ')');
                }
                else if(text[i] == ']'){
                    push(new_string, '[');
                    push(new_string, ']');
                }
                count++; // count the number of added brackets
            }
            else{
                /* text[i] is closing bracket and stack is not empty */
                temp = see_top_stack(stack); // don't pop(stack) yet
                
                if(text[i] == '}'){
                    if(temp == '{'){ // text[i] == see_top_stack(stack)
                        pop(stack); // if brackets match, pop. but when it doesn't leave it.
                        push(new_string, '}');
                    }
                    else{ // text[i] != see_top_stack(stack)
                        push(new_string, '{');
                        push(new_string, '}');
                        count++; // count the number of added brackets
                    }
                }
                else if(text[i] == ')'){
                    if(temp == '('){
                        pop(stack);
                        push(new_string, ')');
                    }
                    else{
                        push(new_string, '(');
                        push(new_string, ')');
                        count++; // count the number of added brackets
                    }
                }

                else if(text[i] == ']'){
                    if(temp == '['){
                        pop(stack);
                        push(new_string, ']');
                    }
                    else{
                        push(new_string, '[');
                        push(new_string, ']');
                        count++; // count the number of added brackets
                    }
                }
            }
        }
    }
    
    while(!is_empty(stack)){ // while loop for leaved brackets in stack
        popped_ch = pop(stack);
        /* push matching bracket into new_string */
        if(popped_ch == '('){
            push(new_string, ')');
        }
        else if(popped_ch == '{'){
            push(new_string, '}');
        }
        else if(popped_ch == '['){
            push(new_string, ']');
        }
        count++; // count the number of added brackets
        
    }
    printf("추가되는 괄호수 : %d\n", count);
    printf("%s\n", new_string);

}


char pop(char* text){
    
    int str_len = string_length(text);
    char output_char;
    
    output_char = text[str_len-1]; // save top element in stack to output_char
    text[str_len-1] = '\0'; // to remove element the top element in stack
    
    return output_char;
}

char see_top_stack(char* text){
    /* we don not remove top element as we did in pop() function. */
    int str_len = string_length(text);
    
    return text[str_len-1];
}

void push(char* text, char ch){
    
    int str_len = string_length(text);
    text[str_len] = ch; // save input element in top of the stack
}

int is_empty(char* text){
    
    if(text[0] == '\0') // if first element in string is NULL than it's empty
        return 1;
    else return 0;
}

int string_length(char* text){ // count the number of element in one string
    
    int i=0, length=0;
    
    while(text[i]){
        length += 1;
        i++;
    }
    return length;
}
