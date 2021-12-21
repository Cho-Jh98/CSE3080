
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FALSE 0
#define TRUE 1

typedef struct node {
    struct node* left_node;
    struct node* right_node;
    int data;
}node;
typedef node* p_node;

p_node new_node(int val);
p_node make_tree(int start, int end, int* arr, int* is_same);

void in_order(p_node root);
void post_order(p_node root);
void Free_Tree(p_node root);


int main() {
    int arr[150];
    int n, is_same = 0;
    // input number of nodes(data)
    scanf("%d", &n);
    getchar();
    
    // input data(arr)
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    
    // make size tree with data in arr
    p_node root = make_tree(0, n - 1, arr, &is_same);
    
    if(is_same){
        printf("cannot construct BST\n");
        return 0;
    }
    else {
        printf("Inorder:");
        in_order(root);
        printf("\n");
        printf("Postorder:");
        post_order(root);
        printf("\n");
    }
    Free_Tree(root);
    return 0;
}


// make a new node
p_node new_node(int data) {
    p_node newNode = (p_node)malloc(sizeof(node));
    newNode->data = data;
    newNode->left_node = NULL;
    newNode->right_node = NULL;
    return newNode;
}

p_node make_tree(int start, int end, int* arr, int* is_same) {// start+1 ~ end : range where childs are | start : root | arr : array
    
    p_node root_node = new_node(arr[start]); // make root node
    
    int data = arr[start];
    int exist_larger_data = FALSE, index = -1;
    
    if (start >= end) // end of array
        return root_node;
    
    for (int i = start + 1; i <= end; i++) { // arr 내부의 data 크기 검사
        if(data == arr[i]){
            *is_same = 1;
            return root_node;
        }
        if (!exist_larger_data && (data <= arr[i])) { // arr 다음 data가 현재 data보다 크거나 같음
            if(data <= arr[i]){
                index = i;
                exist_larger_data = TRUE;
            }
            break;
        }
    }
    
    if (index == -1) { // root 보다 큰 데이터가 없을 때 >> start+1부터의 arr를 모두 make tree로
        root_node->left_node = make_tree(start + 1, end, arr, is_same);
    }
    else if(index == start + 1){
        // arr[start+1]가 root data보다 큼
        root_node->right_node = make_tree(start + 1, end, arr, is_same);
    }
    else if (index > start+1) { // 큰 데이터가 root 보다 2 이상 떨어져 있을 때
            
        // root data보다 작은 arr[start+1 : index-1]를 left child로
        root_node->left_node = make_tree(start + 1, index - 1, arr, is_same);
            
        // root data보다 큰 arr[index:end]를 right child로
        root_node->right_node = make_tree(index, end, arr, is_same);
    }
    return root_node;
}

void in_order(p_node root){
    if (!root) return;
    in_order(root->left_node);
    printf(" %d", root->data);
    in_order(root->right_node);
}

void post_order(p_node root){
    if (!root) return;
    post_order(root->left_node);
    post_order(root->right_node);
    printf(" %d", root->data);
}

// free nodes
void Free_Tree(p_node root){
    if (!root) return;
    p_node left = root->left_node;
    p_node right = root->right_node;
    free(root);
    Free_Tree(left);
    Free_Tree(right);
}
