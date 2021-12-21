#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_ARR 100


typedef struct node *node_pointer;
typedef struct node {
    int data;
    int weight;
    node_pointer next;
}node;

typedef struct edge{
    /* from, to : 노드 번호
       w : weight */
    int from, to, w; // 방향성은 없지만 code 작성의 이해를 돕기 위해 설정한 변수명
}edge;

typedef struct edge *edgepointer;
typedef struct edgelist {
    edge data[MAX_ARR];
    int num;
}edgelist;

edgelist edge_list;
edgelist spanned_list;
node_pointer krudscal_arr[MAX_ARR]; // MST node
node_pointer node_arr[MAX_ARR]; // original node

FILE *fp; //read
FILE *out; // output
int size;
int visited[MAX_ARR]; // for original graph DFS
int krudscal_visited[MAX_ARR]; // for MST graph DFS
int cost; // sum of weight


node_pointer make_node(int data, int weight);
int** make_adj_mat(void);
void make_adj_list(int** adj_mat);
void make_krudscal(int** adj_mat);
int check_cycle(int to);

void dfs(int v);
void sort(void);


int main(){
    
    out = fopen("output.txt", "a");
    int** adj_mat;
    
    adj_mat = make_adj_mat();
    make_adj_list(adj_mat);
    
    sort();
    make_krudscal(adj_mat);
    
    for(int i = 0; i<size; i++){ // dfs
        if(krudscal_arr[i] != NULL){
            if(!krudscal_visited[i]){
                dfs(i);
            }
        }
    }
    // input cost to output.txt
    fprintf(out, "\n%d\n", cost);
    
    fclose(out);
    return 0;
}

int** make_adj_mat(void){
    
    int **adj_matrix, temp = 0, row, col;
    fp = fopen("input.txt", "r");

    if(fp == NULL){
        printf("No file\n");
        return 0;
    }
    fscanf(fp, "%d", &size);
    // 2차원 행렬 동적할당
    adj_matrix = (int**)malloc(sizeof(int*) * size);
    for(int i = 0; i<size; i++){
        adj_matrix[i] = (int*)malloc(sizeof(int) * size);
    }
    // 2차원 행렬에 weight값 저장
    for(row = 0; row<size; row++){
        for(col = 0; col<size; col++){
            fscanf(fp, "%d", &temp);
            if(temp != -1){
                adj_matrix[row][col] = temp;
            }
            else
                adj_matrix[row][col] = 0;
        }
    }

    fclose(fp);
    return adj_matrix;
}

void make_adj_list(int** adj_mat){
    
    int row = 0, col = 0;
    node_pointer temp = NULL;
    
    /* 행렬 data 이용해서 graph를 linked representation으로 구현 */
    for(row = 0; row<size; row++){
        for(col = 0; col<size; col++){
            
            if(adj_mat[row][col]){
                if(node_arr[row] == NULL){
                    node_arr[row] = make_node(row, 0);
                    temp = make_node(col, adj_mat[row][col]);
                    node_arr[row]->next = temp;
                }
                else if(node_arr[row] != NULL){
                    temp = node_arr[row];
                    while(temp->next != NULL){
                        temp = temp->next;
                    }
                    temp->next = make_node(col, adj_mat[row][col]);
                }
                if(node_arr[col] == NULL){
                    node_arr[col] = make_node(col, 0);
                    temp = make_node(row, adj_mat[row][col]);
                    node_arr[col]->next = temp;
                }
                else if(node_arr[col] != NULL){
                    temp = node_arr[col];
                    while(temp->next != NULL){
                        temp = temp->next;
                    }
                    temp->next = make_node(row, adj_mat[row][col]);
                }
            }
        }
    }
    // edge weight를 edge_list.data[] 행렬에 저장
    edge_list.num = 0;
    for(row = 0; row<size; row++){
        for(col = row; col<size; col++){
            if(adj_mat[row][col]){
                edge_list.data[edge_list.num].from = row;
                edge_list.data[edge_list.num].to = col;
                edge_list.data[edge_list.num].w = adj_mat[row][col];
                edge_list.num++;
            }
        }
    }
}

void make_krudscal(int** adj_mat){
    
    int i = 0, p, from, to;
    int arr[MAX_ARR] = {0};
    
    for(i = 0; i<size; i++){
        arr[i] = i;
    }
    
    node_pointer temp;
    // 지금 넘겨받은 edge_list 는 sort() 함수를 통해 오름차순 정렬된 data이다.
    for(i = 0; i<edge_list.num; i++){
        from = edge_list.data[i].from;
        to = edge_list.data[i].to;
        
        /* cycle check을 위해 arr 행렬을 사용한다.
           행렬의 index는 각 노드의 최상위 root의 번호를 저장한다.
           만약 arr에 저장되어 있는 node 번호가 같으면 이어져 있는 node,
           아니면 이어야 하는 node 이다. */
        from = arr[from];
        to = arr [to];

        if(arr[from] == arr[to]){ // 이미 이어진 node 일 경우
            continue; // 이 경우를 건너 뛰고 다음 weight로 넘어감
        }
        
        else if(arr[from]!=arr[to]){ // 서로 이어지지 않은 node일 경우
            /* 다른 노드 들 중 새로 이어질 node와 연결 되어있는 경우를 찾아서
               해당 node의 최상위 root 번호를 from으로 바꿔준다 */
            for (p = 0; p < size; p++)
                if (arr[p] == to)
                    arr[p] = from;
            cost += edge_list.data[i].w; // 새로 이어진 node의 link weight를 더한다.
        }
        
        // node 연결
        if(krudscal_arr[from] == NULL){
            krudscal_arr[from] = make_node(from, 0);
            temp = make_node(to, adj_mat[from][to]);
            krudscal_arr[from]->next = temp;
        }
        else if(krudscal_arr[from] != NULL){
            temp = krudscal_arr[from];
            while(temp->next != NULL){
                temp = temp->next;
            }
            temp->next = make_node(to, adj_mat[from][to]);
        }
        if(krudscal_arr[to] == NULL){
            krudscal_arr[to] = make_node(to, 0);
            temp = make_node(from, adj_mat[from][to]);
            krudscal_arr[to]->next = temp;
        }
        else if(krudscal_arr[to] != NULL){
            temp = krudscal_arr[to];
            while(temp->next != NULL){
                temp = temp->next;
            }
            temp->next = make_node(from, adj_mat[from][to]);
        }
    }
    
    return;
}

void sort(void){ // 오름차순 정렬
    
    int i, j;
    edge temp;
    for (i = 1; i < edge_list.num; i++){
        for (j = 0; j < edge_list.num - 1; j++){
            if (edge_list.data[j].w > edge_list.data[j + 1].w)
            {
                temp = edge_list.data[j];
                edge_list.data[j] = edge_list.data[j + 1];
                edge_list.data[j + 1] = temp;
            }
        }
    }
    return;
}


void dfs(int v){
    node_pointer w;
    
    krudscal_visited[v] = 1;
    fprintf(out, "%d ", v);
    for(w=krudscal_arr[v]; w; w=w->next){
        if(!krudscal_visited[w->data]){
            dfs(w->data);
        }
    }
}

node_pointer make_node(int data, int weight){
    /*make node*/
    node_pointer a = (node_pointer)malloc(sizeof(node));
    a->data = data;
    a->next = NULL;
    a->weight = weight;
    return a;
}
