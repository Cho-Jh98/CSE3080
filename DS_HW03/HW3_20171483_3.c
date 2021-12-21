#include <stdio.h>
#include <stdlib.h>
#define MAX_ADDRESS_LENGTH 100
#define MAX_MENU_LENGTH 20

/* favorite_list 저장을 위한 linked list */
typedef struct _favorite_list *pfavorite;
typedef struct _favorite_list{
    char* address;
    pfavorite link;
}favorite_list;

/* 페이지 이동을 위한 linked list와 내부 객체 함수 구현 */
typedef struct Page *p_Page;
typedef struct Page{
    
    char* home_address;
    char* web_address;
    pfavorite favorite_address;
    
    p_Page next_web_page;
    p_Page prev_web_page;
    
    void (*go)(p_Page head_page, p_Page *current_page, char* web_address, pfavorite favorite_list);
    void (*forward)(p_Page head_page, p_Page *current_page);
    void (*backward)(p_Page head_page, p_Page *current_page);
    void (*Home)(p_Page head_page, p_Page *current_page, char* home_address, pfavorite favorite_list);
    void (*Change_home)(p_Page head_page, char* new_home_address);
    void (*history)(p_Page head_page, p_Page current_page);
    void (*add_favorites)(p_Page head_page, char* favorite_address);
    void (*list_favorites)(p_Page head_page);
    void (*quit)(p_Page head_page);
    
}Address;

/* 각 함수들의 선언 */
void go(p_Page Adress, p_Page *current_page, char* web_address, pfavorite favorite_list);
void forward(p_Page Adress, p_Page *current_page);
void backward(p_Page Adress, p_Page *current_page);
void Home(p_Page Adress, p_Page *current_page, char* home_address, pfavorite favorite_list);
void Change_home(p_Page Adress, char* new_home_address);
void history(p_Page Adress, p_Page current_page);
void add_favorites(p_Page Adress, char* favorite_address);
void list_favorites(p_Page Adress);
void quit(p_Page Adress);

/* 함수를 선택하기 위한 menu_list 구조체 선언 */
typedef struct menu_list{
    char* go;
    char* forward;
    char* backward;
    char* Home;
    char* Change_home;
    char* history;
    char* add_favorites;
    char* list_favorites;
    char* quit;
}menu_list;

/* menu 이동을 위한 string 비교 */
int string_compare(char* s1, char* s2);
/* 페이지 노드 생성 함수, 내부에 함수 선언이 들어 있다. */
p_Page create_Address(char* home_address, char* new_address, pfavorite favorite_list);
/* menu와 address 입력 */
void get_menu(char* menu, char* address);
void string_copy(char* s1, char* s2);

int main(){
    
    char home_address[MAX_ADDRESS_LENGTH] = "http://cs.sogang.ac.kr"; // 기본 홈페이지
    char menu[MAX_MENU_LENGTH], new_address[MAX_ADDRESS_LENGTH];
    int num_menu = 1;
    
    pfavorite favorite_list = NULL;
    
    menu_list list; // 구조체 문자열 선언
    list.go = "go";
    list.forward = "forward";
    list.backward = "backward";
    list.Home = "Home";
    list.Change_home = "Change_home";
    list.history = "history";
    list.add_favorites = "add_favorites";
    list.list_favorites = "list_favorites";
    list.quit = "quit";
    
    p_Page head_page = create_Address(home_address, home_address, favorite_list); // 헤더노드 생성
    p_Page current_page = head_page;
    
    printf("%s\n", home_address); // 처음 주소 출력
    while(num_menu){
         /* menu, address 초기화 */
        for(int i = 0; i<MAX_MENU_LENGTH; i++)
            menu[i] = '\0';
        for(int i = 0; i<MAX_ADDRESS_LENGTH; i++)
            new_address[i] = '\0';
         /* 메뉴 이동 */
        get_menu(menu, new_address);
        if(string_compare(menu, list.go)){
            head_page->go(head_page, &current_page, new_address, favorite_list);
        }
        else if(string_compare(menu, list.forward)){
            head_page->forward(head_page, &current_page);
        }
        else if(string_compare(menu, list.backward)){
            head_page->backward(head_page, &current_page);
        }
        else if(string_compare(menu, list.Home)){
            head_page->Home(head_page, &current_page, head_page->home_address, favorite_list);
        }
        else if(string_compare(menu, list.Change_home)){
            head_page->Change_home(head_page, new_address);
        }
        else if(string_compare(menu, list.add_favorites)){
            head_page->add_favorites(head_page, new_address);
        }
        else if(string_compare(menu, list.list_favorites)){
            head_page->list_favorites(head_page);
        }
        else if(string_compare(menu, list.history)){
            head_page->history(head_page, current_page);
        }
        else if(string_compare(menu, list.quit)){
            head_page->quit(head_page);
            num_menu = 0;
        }
        else{ // default
            printf("wrong input, try again\n");
            num_menu = 1;
        }
    }
}

int string_compare(char *s1, char* s2)
{
    unsigned char c1, c2;

    while (1) {
        /* s1, s2 문자열에서 순서대로 한글자씩 저장 */
        c1 = *s1++;
        c2 = *s2++;
        
        if(c1 == '\0' && c2 == '\0')
            break;
        
        if (c1 != c2)
            return 0;
    }
    /* 루프를 빠져나오면 두 문자열이 같다는 의미이므로 1을 리턴 */
    return 1;
}

void get_menu(char* menu, char* address){
    
    char temp;
    int i, j;
    
    for(i = 0; i<MAX_MENU_LENGTH; i++){
        temp = getchar();
        if(temp == '\n'){ // 주소 없이 메뉴 입력 종료
            menu[i] = '\0';
            break;
        }
        else if(temp == ' '){ // 메뉴 입력 후 주소 입력
            for(j = 0; j<MAX_ADDRESS_LENGTH; j++){
                temp = getchar();
                address[j] = temp; // 주소에 한 문자씩 저장
                if(temp == '\n') { // 주소 입력 종료
                    address[j] = '\0';
                    menu[i] = '\0';
                    break;
                }
            }
            return;
        }
        else menu[i] = temp; // menu에 한 문자씩 저장
    }
}


/* 초기화된 클래스의 객체 생성 */
p_Page create_Address(char* home_address, char* new_address, pfavorite favorite_list){
    
    p_Page new_page = (p_Page)malloc(sizeof(Address)); // 새로운 page node 생성
    char* empty = {"empty list"};
    favorite_list = (pfavorite)malloc(sizeof(favorite_list)); // 새로운 favorite_list 생성
    favorite_list->address = empty;
    favorite_list->link = NULL;
    
    
    new_page->next_web_page = NULL;
    new_page->prev_web_page = NULL;

    new_page->home_address = home_address;
    new_page->web_address = new_address;
    new_page->favorite_address = favorite_list;
    
    /* class 함수 */
    new_page->go = go;
    new_page->forward = forward;
    new_page->backward = backward;
    new_page->Home = Home;
    new_page->Change_home = Change_home;
    new_page->history = history;
    new_page->add_favorites = add_favorites;
    new_page->list_favorites = list_favorites;
    new_page->quit = quit;
    
    return new_page;
}


void go(p_Page head_page, p_Page *current_page, char* new_address, pfavorite favorite_list){
    
    char save_current_page[MAX_ADDRESS_LENGTH];
    for(int i = 0; i<MAX_ADDRESS_LENGTH; i++)
        save_current_page[i] = '\0';
    string_copy(save_current_page, new_address);
    
    p_Page new_page = create_Address(head_page->home_address, save_current_page, favorite_list);
    // 객체 생성해서 포인터로 new_page에 넣어주기
    
    //head_page에 처음 들어갈 때
    if(!(head_page->next_web_page)){
        head_page->next_web_page = new_page;
        new_page->prev_web_page = head_page;
        new_page->next_web_page = NULL;
    }
    
    // current_page와 head_page 사이에 다른 page가 있을 때 사이 노드 삭제
    else if((*current_page)->next_web_page != NULL){
        p_Page next = (*current_page);
        while(next){
            next = (*current_page)->next_web_page; // next = current_page 다음 페이지
            next->next_web_page->prev_web_page = *current_page; // next의 다음 페이지 -> current_page
            (*current_page)->next_web_page = next->next_web_page; // current_page -> (next의 다음 페이지
            free(next); // next 제거
        }
    }
    /* current_page 다음에 new_page 연결 */
    else{
        new_page->next_web_page = NULL;
        new_page->prev_web_page = (*current_page);
        (*current_page)->next_web_page = new_page;
    }
    
    *current_page = new_page;
    printf("%s\n", (*current_page)->web_address);
}

void forward(p_Page head_page, p_Page *current_page){
    /* 가장 최근 페이지 일 때 */
    if((*current_page)->next_web_page == NULL){
        printf("Can't forward\n");
        printf("%s\n", (*current_page)->web_address);
    }
    else{
        (*current_page) = (*current_page)->next_web_page;
        printf("%s\n", (*current_page)->web_address);
    }
}

void backward(p_Page head_page, p_Page *current_page){
    /* 현재 페이지가 헤더노드일 때 */
    if((*current_page)->prev_web_page == NULL){
        printf("Can't backward\n");
        printf("%s\n", (*current_page)->web_address);
    }
    else{
        (*current_page) = (*current_page)->prev_web_page;
        printf("%s\n", (*current_page)->web_address);
    }
}

void Home(p_Page head_page, p_Page *current_page, char* home_address, pfavorite favorite_list){
    
    /* home 페이지를 갖는 새로운 node 생성 */
    p_Page new_page = create_Address(head_page->home_address, home_address, favorite_list);
    
    /* new_page와 current_page 연결 */
    new_page->next_web_page = NULL;
    new_page->prev_web_page = (*current_page);
    (*current_page)->next_web_page = new_page;
    
    (*current_page) = new_page;
    printf("%s\n", (*current_page)->web_address);
    
}

void Change_home(p_Page head_page, char* new_home_address){
    
    p_Page temp = head_page;
    
    /* 모든 node의 home_address 변경 */
    while(temp){
        temp->home_address = new_home_address;
        temp = temp->next_web_page;
    }
}

void history(p_Page head_page, p_Page current_page){
    
    /* 헤더노드부터 web_address를 모두 출력 */
    p_Page temp = head_page;
    while(temp != current_page){
        printf("%s\n", temp->web_address);
        temp = temp->next_web_page;
    }
    printf("%s\n", current_page->web_address);
}

void add_favorites(p_Page head_page, char* favorite_web_address){
    
    /* 헤더노드의 favorite_list에 favorite_web_address 저장 */
    pfavorite new_favorite = (pfavorite)malloc(sizeof(favorite_list));
    new_favorite->link = NULL;
    new_favorite->address = favorite_web_address;
    
    pfavorite curr = head_page->favorite_address;
    
    while(curr->link){
        curr = curr->link;
    }
    curr->link = new_favorite;
}

void list_favorites(p_Page head_page){
    
    pfavorite curr = head_page->favorite_address;
    
    if(!(curr->link)){
        printf("%s\n", curr->address);
    }
    else{
        curr = curr->link;
        while(curr){
            printf("%s\n", curr->address);
            curr = curr->link;
        }
    }
}

void quit(p_Page head_page){
    p_Page page_temp = head_page;
    pfavorite favorite_temp = head_page->favorite_address;
    
    /* 헤더노드의 favorite_list 헤제 */
    while(head_page->favorite_address){
        favorite_temp = head_page->favorite_address;
        head_page->favorite_address = head_page->favorite_address->link;
        free(favorite_temp);
    }
    
    /* page_list 헤제 */
    while(head_page){
        page_temp = head_page;
        head_page = head_page->next_web_page;
        free(page_temp->favorite_address);
        free(page_temp);
    }

}

void string_copy(char* s1, char* s2){
    unsigned char c1, c2;

    while (1) {
        /* s1, s2 문자열에서 순서대로 한글자씩 저장 */
        c1 = '\0';
        c2 = *s2++;
        *s1++ = c2;
        
        if(c1 == '\0' && c2 == '\0')
            break; // 두개 모두 문자열이 끝나면 함수 종료
    }
}
