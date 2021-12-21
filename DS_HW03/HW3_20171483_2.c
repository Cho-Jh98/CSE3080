#include <stdio.h>
#include <stdlib.h>
#define MAX_LIST_LENGTH 10

typedef struct list_node *list_pointer;
typedef struct list_node{
    int data;
    list_pointer link;
}list_node;

void add_q(list_pointer front, list_pointer rear, int data);
void rearange_queue(list_pointer front, list_pointer rear);
void print_queue(list_pointer queue1, list_pointer queue2);
void delete_node(list_pointer front, list_pointer rear, list_pointer target);

int main(){
    
    int list[6] = {1, 5, 3, 9, 8, 2};
    int i = 0;
    
    /* queue를 위한 front와 rear 선언 & 메모리 할당 */
    list_pointer front = (list_pointer)malloc(sizeof(list_node));
    list_pointer rear = (list_pointer)malloc(sizeof(list_node));
    
    /* 입력받을 데이터는 모두 양수이니 front와 rear의 data는 -1로 선언 */
    front->data = -1;
    rear->data = -1;
    front->link = rear;
    rear->link = front;
    
    /* linked queue 생성 */
    for(i = 0; i<6; i++){
        add_q(front, rear, list[i]);
    }
    
    rearange_queue(front, rear);
    
    return 0;
}

void add_q(list_pointer front, list_pointer rear, int data){
    
    list_pointer new_node, curr = front;
    new_node = (list_pointer)malloc(sizeof(list_node));
    new_node->data = data;
    new_node->link = NULL;
    
    /* curr을 queue의 rear 앞까지 이동 */
    while (curr->link != rear){
        curr = curr->link;
    }
    
    /* new_node 연결 */
    rear->link = new_node;
    curr->link = new_node;
    new_node->link = rear;
}
//{1, 5, 3, 9, 8, 2};
void rearange_queue(list_pointer front, list_pointer rear){
    
    int search = 0;
    /* max_node : 가장 높은 우선순위의 data를 갖는 node 저장 */
    list_pointer first_node, curr, temp, next;
    
    /* 우선순위 순으로 저장할 새로운 queue의 front, rear 선언 */
    list_pointer printed_f = (list_pointer)malloc(sizeof(list_node));
    list_pointer printed_r = (list_pointer)malloc(sizeof(list_node));
    
    printed_f->link = printed_r;
    printed_f->data = -1;
    printed_r->link = printed_f;
    printed_r->data = -1;

    
    while(front->link != rear){
        first_node = curr = front->link; // first_node와 curr을 front로 초기화
        search = curr->data; // linear search를 위한 search 변수에 data 저장
        temp = first_node;
        
        /* curr가 list를 훑고 지나가면서 search보다 높은 우선순위가 있으면 first_node를 맨 뒤로 보낸다. */
        while(curr->data != -1){
            if(search < curr->data){
                search = curr->data;
                front->link = first_node->link;
                rear->link->link = temp;
                rear->link = temp;
                temp->link = rear;
                break;
            }
            else curr = curr->link;
        }
        /* 만약 first_node의 data가 search와 같으면, 즉 최대값이면 아래와 같은 함수가 진행된다. */
        if(first_node->data == search){
            add_q(printed_f, printed_r, search); // 새로운 queue 생성(first_node를 add한다.)
            delete_node(front, rear, first_node); // first_node에 해당하는 node 삭제
            print_queue(printed_f, front); // 새로운 queue, 기존 queue 출력
        }
    }
    
    /* 새로 만든 queue 메모리 해제 */
    while(printed_f->link != printed_r){
        next = printed_f->link;
        free(printed_f);
        printed_f = next;
    }
}

void delete_node(list_pointer front, list_pointer rear, list_pointer target){
        
    
    if (front->link == rear && rear->link == front) // 비어있는 queue
        return;

    list_pointer curr = front;
    
    while(curr->link != target){ // curr을 target(max_node) 전 node로 이동
        curr = curr-> link;
    }
    
    /* target 제거 */
    curr->link = target->link;
    if(target->link == rear){
        rear->link = curr;
    }
    free(target);
}

void print_queue(list_pointer queue1, list_pointer queue2){
    list_pointer curr = queue1->link;
    
    /* front와 rear의 data는 -1임을 이용 */
    while(curr->data != -1){
        printf("%d ", curr->data);
        curr = curr->link;
    }
    printf("/ ");
    
    curr = queue2->link;
    while(curr->data != -1){
        printf("%d ", curr->data);
        curr = curr->link;
    }
    printf("\n");
}
