# include <stdio.h>
# include <stdlib.h>
# define MAX_ARR 10

typedef struct node *node_pointer;
typedef struct node {
    int data;
    node_pointer next;
}node;

node_pointer node_arr[MAX_ARR];

FILE *fp; // read
FILE *sp; // output
int size;
int visited[MAX_ARR];

node_pointer make_node(int data);
int** make_adj_mat(void);
void make_adj_list(int** adj_mat);
void dfs(int v);

int main(){
    
    sp = fopen("output.txt", "a");
    int** adj_mat;
    
    adj_mat = make_adj_mat();

    make_adj_list(adj_mat);
    
    for(int i = 0; i<size; i++){
        if(node_arr[i] != NULL){
            if(!visited[i]){
                dfs(i);
                fprintf(sp, "\n");
            }
            
        }
    }
    fclose(sp);
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
    
    // 행렬 data 입력
    for(row = 0; row<size; row++){
        for(col = 0; col<size; col++){
            fscanf(fp, "%d", &temp);
            adj_matrix[row][col] = temp;
        }
    }
    
    fclose(fp);
    return adj_matrix;
}


node_pointer make_node(int data){
    /*make node*/
    node_pointer a = (node_pointer)malloc(sizeof(node));
    a->data = data;
    a->next = NULL;
    return a;
}

void make_adj_list(int** adj_mat){
    
    int row = 0, col = 0;
    node_pointer temp = NULL;
    
    /* 행렬 data 이용해서 graph를 linked representation으로 구현 */
    for(row = 0; row<size; row++){
        for(col = 0; col<size; col++){
            
            if(adj_mat[row][col] == 1){
                if(node_arr[row] == NULL){
                    node_arr[row] = make_node(row);
                    temp = make_node(col);
                    node_arr[row]->next = temp;
                }
                else if(node_arr[row] != NULL){
                    temp = node_arr[row];
                    while(temp->next != NULL){
                        temp = temp->next;
                    }
                    temp->next = make_node(col);
                }
                
                else if(node_arr[col] == NULL){
                    node_arr[col] = make_node(col);
                    temp = make_node(row);
                    node_arr[col]->next = temp;
                }
                else if(node_arr[col] != NULL){
                    temp = node_arr[col];
                    while(temp->next != NULL){
                        temp = temp->next;
                    }
                    temp->next = make_node(row);
                }
            }
        }
    }
}

void dfs(int v){ // dfs 알고리즘
    node_pointer w;
    
    visited[v] = 1;
    fprintf(sp, "%d ", v);
    for(w=node_arr[v]; w; w=w->next){
        if(!visited[w->data]){
            dfs(w->data);
        }
    }
}
