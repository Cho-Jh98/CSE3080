#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_ELEMENT 10


typedef struct node *treePointer;
typedef struct node {
    int key;
    treePointer parent;
    treePointer leftChild, rightChild;
}node;


typedef struct queue* queuePointer;
typedef struct queue {
    queuePointer next;
    treePointer element;
}queue;

queuePointer head_queue, rear, front;
int check_point;

queuePointer make_queue(treePointer element);
treePointer make_node(int key, treePointer parent);

void find_overlap(int key);
void insert_tree(int key, treePointer root);
void delete_tree(treePointer root);
void binary_insert(treePointer node, treePointer root);
void top(treePointer root);


void free_queue(queuePointer head_queue);


int main(){
    treePointer Root_node = (treePointer)malloc(sizeof(node));
    Root_node->key = -1;
    Root_node->parent = NULL;
    Root_node->leftChild = NULL;
    Root_node->rightChild = NULL;
    head_queue = make_queue(Root_node);
    head_queue->next = NULL;
    front = head_queue;
    
    
    char menu[10], c;
    int key, select = 1, stop = 1, i = 0;
    
    while(stop){
        for(i = 0; i<10; i++) menu[i] = '\0';
        scanf("%s", menu);
        
        if(!strcmp(menu, "push")){
            select = 1;
        }
        else if(!strcmp(menu, "pop")){
            select = 2;
        }
        else if(!strcmp(menu, "top")){
            select = 3;
        }
        else if(!strcmp(menu, "q")){
            select = 0;
        }
        
        switch(select){
            case 1:
                scanf("%d", &key);
                insert_tree(key, Root_node);
                printf("\n");
                break;
            case 2:
                delete_tree(Root_node);
                printf("\n");
                break;
            case 3:
                top(Root_node);
                printf("\n");
                break;
            case 0:
                stop = 0;
                break;
        }
    }
    return 0;
}

void insert_tree(int key, treePointer root){
    // root??? key == -1 >> empty tree ????????? ????????? key?????? ???????????????.
    if(root->key == -1){
        root->key = key;
        printf("push %d", key);
        head_queue->element = root;
        return;
    }
    
    // ????????? ??????
    check_point = 0;
    find_overlap(key);
    if(check_point){
        printf("Exist number");
        return;
    }
    
    // root??? ?????? ?????? ???
    else if(root->key != -1){
        treePointer inserting_node = make_node(key, root);
        treePointer current_node = root;
        queuePointer new_queue = make_queue(inserting_node);
        queuePointer current_queue = head_queue;
        // tree??? 2??? ????????? ?????? ?????? ???
        if(head_queue->next == NULL){
            current_queue->next = new_queue;
            new_queue->next = NULL;
            if(root->key > key){ // BST ??????????????? ?????? ????????????.
                root->leftChild = inserting_node;
                inserting_node->parent = current_node;
            }
            else{
                root->rightChild = inserting_node;
                inserting_node->parent = current_node;
            }
        }
        else{ // root?????? ?????? ?????? ???
            while(current_queue->next != NULL){
                current_queue = current_queue->next;
            }
            current_queue->next = new_queue;
            new_queue->next = NULL;
            
            binary_insert(inserting_node, root);
        }
        
    }
    printf("push %d", key);
}

// recursive?????? BST??? ??????, ???????????? ??????
void binary_insert(treePointer node, treePointer root){
    
    if(node->key < root->key){ // ??????????????? node??? ?????? root?????? ?????????
        if(root->leftChild == NULL){ // left child??? ??????
            root->leftChild = node;
            node->parent = root;
        }
        else{ // ?????? left child??? ?????? ???????????? ?????? ????????? ?????? recursive?????? ??????
            binary_insert(node, root->leftChild);
        }
    }
    else if(node->key > root->key){
        if(root->rightChild == NULL){
            root->rightChild = node;
            node->parent = root;
        }
        else{
            binary_insert(node, root->rightChild);
        }
    }
}

void top(treePointer root){ // ?????? ??? ?????? ?????? ????????? rightChild??? ?????? ??? ???????????? ????????? ????????? ????????????.
    treePointer current_node = root;
    
    while(current_node->rightChild != NULL){
        current_node = current_node->rightChild;
    }
    
    if(current_node->key == -1){
        printf("The queue is empty");
        return;
    }
    
    printf("Top: %d", current_node->key);
}

void delete_tree(treePointer root){
    queuePointer queue_pointer, fallowup;
    queue_pointer = fallowup = head_queue;
    treePointer node_pointer = root, top;
    
    // root -> key == -1 >> ???????????? tree
    if(head_queue->element->key == -1){
        printf("The queue is empty");
        return;
    }
    
    // rightChilde??? ????????? root node??? ????????? ?????? ??????.
    if(node_pointer->rightChild == NULL){
        top = root;
        // root node ????????? root node ??????
        if(node_pointer->leftChild != NULL){
            root = node_pointer->leftChild;
            printf("POP : %d", top->key);
            root->parent = NULL;
            free(top);
            
            // queue ?????? ??? ??????
            if(queue_pointer->element == top){
                fallowup = queue_pointer;
                fallowup->next = NULL;
                queue_pointer = queue_pointer->next;
                free(fallowup);
            }
            
            while(queue_pointer->next->element != top){
                queue_pointer = queue_pointer->next;
            }
            fallowup = queue_pointer;
            fallowup->next = queue_pointer->next;
            free(queue_pointer);
            return;
        }
        else{
            printf("POP : %d", root->key);
            root->key = -1;
            return;
        }
    }
    else { // right child??? ????????? ????????? ???????????? ????????? ????????????.
        queue_pointer = head_queue;
        top = node_pointer->rightChild;
        while(top->rightChild != NULL){
            top = top->rightChild;
            node_pointer = node_pointer->rightChild;
        }
        //queue ?????? ??? ??????
        while(queue_pointer->next->element != top){
            queue_pointer = queue_pointer->next;
        }
        fallowup = queue_pointer; queue_pointer = queue_pointer->next;
        printf("POP : %d", top->key);
        fallowup->next = queue_pointer->next; node_pointer->rightChild = NULL;
        free(top);
        free(queue_pointer);
    }
}

// tree node ?????? ??????
treePointer make_node(int key, treePointer parent) {
    treePointer temp = (treePointer)malloc(sizeof(node));
    temp->key = key;
    temp->leftChild = NULL;
    temp->rightChild = NULL;
    temp->parent = parent;
    return temp;
}

// queue node ????????????
queuePointer make_queue(treePointer element){
    queuePointer new_queue = (queuePointer)malloc(sizeof(queue));
    
    new_queue->element = element;
    new_queue->next = rear;
    
    return new_queue;
}

// ????????? ?????? ??????
void find_overlap(int key){
    queuePointer current_queue = head_queue;
    if(head_queue->element->key == -1)
        return;
    else if(head_queue->next == NULL){
        if(head_queue->element->key == key){
            check_point = 1;
            return;
        }
    }
    else{
        current_queue = head_queue;
        while(current_queue->next != NULL){
            if(current_queue->element->key == key){
                check_point = 1;
                return;
            }
            else{
                current_queue = current_queue->next;
            }
        }
    }
}
