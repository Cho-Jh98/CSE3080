#include <stdio.h>
#define MAX_LENGTH 31

void get_word(char* arr);


int main(){
    
    char word[MAX_LENGTH];
    get_word(word);
    printf("%s\n", word);
    
    return 0;
}

void get_word(char* arr){
    
    int i, j = 1;
    char temp;
    arr[0] = getchar();
    for(i = 0; i<MAX_LENGTH; i++){
        temp = getchar(); // save input charactor to temp
        
        /* if temp is same with previous input(which is saved to array), continue;
           Whether they are upper or lower case doesn't matter; */
        if((temp - arr[j-1] == 32) || (temp - arr[j-1] == -32)){
            continue;
        }
        else if(temp != '\n'){ // until input is enter, save temp to array.
            arr[j++] = temp;
        }
        else if(temp == '\n'){ // if input is enter, break the loop.
            break;
        }
    }
}
