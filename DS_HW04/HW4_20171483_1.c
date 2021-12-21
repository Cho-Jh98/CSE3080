#include <stdio.h>
#include <stdlib.h>


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

queuePointer head_queue, front;
int check_point; // 중복값 체크

void dln(treePointer root, int key);
queuePointer make_queue(treePointer element);
treePointer make_node(int key, treePointer parent);

void find_overlap(int key);
void insert_tree(int key, treePointer root);
void delete_tree(treePointer root);

void free_queue(queuePointer head_queue);


int main(){
    treePointer Root_node = (treePointer)malloc(sizeof(node));
    Root_node->key = -1;
    Root_node->parent = NULL;
    Root_node->leftChild = NULL;
    Root_node->rightChild = NULL;
    head_queue = make_queue(Root_node);
    head_queue->next = NULL;
    head_queue->element = Root_node;
    front = head_queue;
    
    char menu;
    int key, stop = 1;
    
    while(stop){
        scanf("%c", &menu);
        
        switch(menu){
            case 'i':
                scanf("%d", &key);
                insert_tree(key, Root_node);
                printf("\n");
                break;
            case'd':
                delete_tree(Root_node);
                printf("\n");
                break;
            case 'q':
                stop = 0;
                break;
        }
    }
    return 0;
}

void insert_tree(int key, treePointer root){
    
    int temp;
    
    if(root->key == -1){
        root->key = key;
        printf("insert %d", key);
        return;
    }
    
    // 중복값 체크
    find_overlap(key);
    if(check_point == 1){
        printf("Exist number");
        check_point = 0;
        return;
    }
    
    queuePointer current_queue = head_queue;
    treePointer inserting_node = make_node(key, root);
    treePointer current_node = root;
    queuePointer new_queue = make_queue(inserting_node);
    
    // tree에 값이 1개일 때
    if((root->key != -1) && (head_queue->next == NULL)){
        head_queue->next = new_queue;
        // root의 값이 더 클 때
        if(head_queue->element->key > new_queue->element->key){
            root->leftChild = inserting_node;
            inserting_node->parent = root;
        }
        // root의 값이 더 작을 때
        else{
            temp = root->key;
            root->key = inserting_node->key;
            inserting_node->key = temp;
            root->leftChild = inserting_node;
            inserting_node->parent = root;
        }
    }
    // Tree에 값이 2개 이상일 때
    else if(head_queue->next != NULL){
        // queue 연결
        current_queue = head_queue;
        while(current_queue->next == NULL){
            current_queue = current_queue->next;
        }
        current_queue->next = new_queue;
        
        // front를 이용해 남는 자리에 child 추가
        if(front->element->leftChild == NULL){
            front->element->leftChild = inserting_node;
            inserting_node->parent = front->element;
        }
        else if(front->element->rightChild == NULL){
            front->element->rightChild = inserting_node;
            inserting_node->parent = front->element;
        }
        else{
            front = front->next;
            if(front->element->leftChild == NULL){
                root->leftChild = inserting_node;
                inserting_node->parent = front->element;
            }
            else if(front->element->rightChild == NULL){
                root->rightChild = inserting_node;
                inserting_node->parent = front->element;
            }
        }
        
        // 추가한 노드에 대해 max heap 정렬
        while ((inserting_node->parent != NULL)&&(inserting_node->parent->key < inserting_node->key))
        {
            if(inserting_node->parent == NULL) break;
            else{
                //swap the key
                int temp = inserting_node->parent->key;
                inserting_node->parent->key = inserting_node->key;
                inserting_node->key = temp;
                inserting_node = inserting_node->parent;
            }
        }
    }
    // insert한 값 출력
    printf("insert %d", key);
}

    
void delete_tree(treePointer root){
    queuePointer current_queue, fallowup;
    current_queue = fallowup = head_queue;
    treePointer deleted_node, last_node = front->element;
    int temp;
    // root->key == -1 >> empty heap
    if(root->key == -1){
        printf("heap is empty");
        return;
    }
    
    else{
        // 전체 tree에서 root에만 값이 있을 때
        if((root->leftChild == NULL) && (root->leftChild == NULL)){
            printf("Delete %d", root->key);
            root->key = -1;
        }
        // root, root->leftChild에 값이 있을 때
        else if(root->leftChild != NULL){
            printf("Delete %d", root->key);
            root->key = root->leftChild->key;
            free(root->leftChild);
            root->leftChild = NULL;
            return;
        }
        // root, left, right 모두 값이 있을 때
        else if((root->leftChild != NULL) && (root->leftChild != NULL)){
            printf("Delete %d", root->key);
            root->key = root->rightChild->key;
            free(root->rightChild);
            root->rightChild = NULL;
            return;
        }

        // tree에 3개 이상일 때
        else{
            printf("Delete %d", root->key);
            temp = root->key;
            // 마지막으로 추가한 node 탐색 후 root와 값 변경
            if(front->element->leftChild != NULL && front->element->rightChild != NULL){
                last_node = front->element->rightChild;
                root->key = last_node->key;
                free(last_node);
                front->element->rightChild = NULL;
                last_node = front->element->leftChild;
            }
            else if(front->element->leftChild != NULL && front->element->rightChild == NULL){
                last_node = front->element->leftChild;
                root->key = last_node->key;
                free(last_node);
                front->element->leftChild = NULL;
            }
            
            else{
                while(current_queue->next != front){
                    current_queue = current_queue->next;
                }
                last_node = current_queue->element->rightChild;
                last_node = front->element->leftChild;
                root->key = last_node->key;
                free(last_node);
                front->element->leftChild = NULL;
            }
            last_node = root;
        }
        // 삭제 후 max heap 정렬
        while (last_node->parent != NULL && last_node->parent->key < last_node->key) {
            //swap the key
            if(last_node->parent == NULL) break;
            else{
                int temp = last_node->parent->key;
                last_node->parent->key = last_node->key;
                last_node->key = temp;
                last_node = last_node->parent;
            }
        }

    }

}
// tree node 생성 함수
treePointer make_node(int key, treePointer parent) {
    treePointer temp = (treePointer)malloc(sizeof(node));
    temp->key = key;
    temp->leftChild = NULL;
    temp->rightChild = NULL;
    temp->parent = parent;
    return temp;
}
// queue pointer 생성 함수
queuePointer make_queue(treePointer element){
    queuePointer new_queue = (queuePointer)malloc(sizeof(queue));
    
    new_queue->element = element;
    new_queue->next = NULL;
    
    return new_queue;
}

// 중복값 체크 함수 : queue를 이용해 입력되었던 값 전부 체크한다.
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
        while(current_queue != NULL){
            if(current_queue->element->key == key){
                check_point = 1;
                return;
            }
            current_queue = current_queue->next;
        }
    }
}
