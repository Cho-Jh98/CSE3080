#include <stdio.h>
#include <stdlib.h>
#define MAX_LIST_LENGTH 20

typedef struct list_node *list_pointer;
typedef struct list_node{
    int data;
    list_pointer link;
}list_node;
list_pointer ptr = NULL;

void create_newnode(int data);
void move_right(int n);

int main(){
    
    int n, k, i = 0, temp;
    int arr[MAX_LIST_LENGTH] = {0};
    list_pointer curr = NULL, temp_node;
    
    // input n
    printf("n: ");
    scanf("%d", &n);
    
    // create linked list
    for(i = 0; i<n; i++){
        scanf("%d", &temp);
        getchar();
        arr[i] = temp;
    }
    for(i = 0; i<n; i++){
        create_newnode(arr[i]); // data = arr[i]
    }
    curr= ptr;
    
    // input k
    printf("\nk: ");
    scanf("%d", &k);
    
    // push right k times
    for(i = 0; i<k; i++){
        move_right(n);
    }
    
    // print out node
    curr = ptr;
    for(i = 0; i<n; i++){
        printf("%d ", curr->data);
        curr = curr->link;
    }
    printf("\n");
    
    // free nodes
    while(ptr){
        temp_node = ptr;
        ptr = ptr->link;
        free(temp_node);
    }
    
    return 0;
}

void create_newnode(int data){
    
    list_pointer temp = NULL;
    list_pointer curr = ptr;
    
    temp = (list_pointer) malloc(sizeof(list_node));
    temp->link = NULL;
    temp->data = data;
    
    /* curr == header node */
    if(!curr){
        ptr = temp;
    }
    
    /* curr != header node */
    else{
        while(curr->link){
            curr = curr->link;
        }
        curr->link = temp;
    }
}

void move_right(int n){ // n = length of linked list
    
    list_pointer curr = ptr;
    list_pointer trace = ptr;
    
    int i = 0;
    curr = curr->link;
    for(i = 0; i<n-2; i++){
        curr = curr->link; // curr의 이동 횟수: 총 n회
        trace = trace->link; // trace의 이동 횟수: 총 n-1회
    }
    
    curr->link = ptr; // curr을 첫 노드로
    trace->link = NULL; // curr 뒷 노드를 마지막 노드로
    ptr = curr;
}
