#include "ex32.h"
#include <stdio.h>
List *List_create()
{
    return calloc(1, sizeof(List));
}

void List_destroy(List *list)
{
    LIST_FOREACH(list, first, next, cur) {
        if(cur->prev) {
            free(cur->prev);
        }
    }

    free(list->last);
    free(list);
}


void List_clear(List *list)
{
    LIST_FOREACH(list, first, next, cur) {
        free(cur->value);
    }
}


void List_clear_destroy(List *list)
{
    List_clear(list);
    List_destroy(list);
}


void List_push(List *list, void *value)
{
    ListNode *node = calloc(1, sizeof(ListNode));
    if(node==NULL) return ;

    node->value = value;

    if(list->last == NULL) {
        list->first = node;
        list->last = node;
    } else {
        list->last->next = node;
        node->prev = list->last;
        list->last = node;
    }

    list->count++;
    return;
}

void *List_pop(List *list)
{
    ListNode *node = list->last;
    return node != NULL ? List_remove(list, node) : NULL;
}

void List_unshift(List *list, void *value)
{
    ListNode *node = calloc(1, sizeof(ListNode));
    if(node==NULL) return;

    node->value = value;

    if(list->first == NULL) {
        list->first = node;
        list->last = node;
    } else {
        node->next = list->first;
        list->first->prev = node;
        list->first = node;
    }

    list->count++;
    return;
}

void *List_shift(List *list)
{
    ListNode *node = list->first;
    return node != NULL ? List_remove(list, node) : NULL;
}

void *List_remove(List *list, ListNode *node)
{
    void *result = NULL;

    //check(list->first && list->last, "List is empty.");
    if(node==NULL){
        printf("Node can't be NULL\n");
        return result;
    }

    if(node == list->first && node == list->last) {
        list->first = NULL;
        list->last = NULL;
    } else if(node == list->first) {
        list->first = node->next;
        if(list->first == NULL){
            printf("Invalid list, somehow got a first that is NULL.");
            return NULL;
        }
        list->first->prev = NULL;
    } else if (node == list->last) {
        list->last = node->prev;
        if(list->last == NULL){
            printf("Invalid list, somehow got a first that is NULL.");
            return NULL;
        }
        list->last->next = NULL;
    } else {
        ListNode *after = node->next;
        ListNode *before = node->prev;
        after->prev = before;
        before->next = after;
    }

    list->count--;
    result = node->value;
    free(node);
    return result;
}

List *ListReplicate(List *list)
{
    List *list_new = calloc(1,sizeof(List));
    list_new->count = list->count;
    if (list->first != NULL) {
        ListNode *current = list->first;
        ListNode *new_node = calloc(1, sizeof(ListNode));
        new_node->value = current->value;
        list_new->first = new_node;

        current = current->next;
        ListNode *prev_node = new_node;

        while (current != NULL) {
            new_node = calloc(1, sizeof(ListNode));
            new_node->value = current->value;
            new_node->prev = prev_node;
            prev_node->next = new_node;

            current = current->next;
            prev_node = new_node;
        }

        list_new->last = new_node;
    }

    return list_new; 
}
List *ListCat(List *list1,List *list2){
    List *l1 = ListReplicate(list1);
    List *l2 = ListReplicate(list2);
    l1->last->next = l2->first;
    l2->first->prev = l1->last;
    l1->last = l2->last;
    l1->count += l2->count;
    return l1;
}
void showList(List *list){
    ListNode *cur = list->first;
    int cnt=1;
    while(cur != NULL){
        printf("Num%d : %s\n",cnt,(char *)cur->value);
        cur = cur->next;
        cnt++;
    }
}
List **ListSplit(List *list,int cnt){
    List **SplitLists = calloc(2,sizeof(List *));
    *SplitLists = List_create();
    *(SplitLists+1) = List_create();
    int pt=1;
    ListNode *cur = list->first;
    while(cur != NULL){
        if(pt <= cnt) List_push(*SplitLists,cur->value);
        else List_push(*(SplitLists+1),cur->value);
        pt++;
        cur = cur->next;
    }
    return SplitLists;
}
int main(int argc,char *argv[]){
    List *list = List_create();
    char *name[]={"cjh","ming","hong"};
    List_push(list,name[0]);
    List_push(list,name[1]);
    List_push(list,name[2]);
    printf("List1\n");
    showList(list);
    // printf("%s\n",(char *)List_pop(list));
    List *list2 = ListReplicate(list);
    printf("List2\n");
    showList(list2);
    // printf("%d\n",list2->count);
    // list->count--;
    // printf("%d\n",list->count);
    // printf("%d\n",list2->count);
    list->first->value = "change";
    printf("List1\n");
    showList(list);
    printf("List2\n");
    showList(list2);
    printf("\n");
    List *list3 = ListCat(list,list2);
    showList(list3);
    //printf("%p %p\n",list->first->value,list2->first->value);
    List **SplitLists = ListSplit(list3,3);
    printf("Splited lists:\n");
    showList(*SplitLists);
    printf("\n");
    showList(*(SplitLists+1));
    return 0;
}