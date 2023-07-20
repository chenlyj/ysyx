#include <stdio.h>
#include "ex32.h"
#include <time.h>
List *List_create()
{
    return calloc(1, sizeof(List));
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
void showList(List *list){
    ListNode *cur = list->first;
    int cnt=1;
    while(cur != NULL){
        printf("Num%d : %d\n",cnt,*(int *)cur->value);
        cur = cur->next;
        cnt++;
    }
}
List *BubbleSort(List *list){
    List *SortedList = ListReplicate(list);
    for(int i=0;i<SortedList->count;i++){
        ListNode *cur = SortedList->first;
        if(cur==NULL) return NULL;
        ListNode *nxt = cur->next;
        while(nxt!=NULL){
            if(*(int *)nxt->value < *(int *)cur->value) {
                if(cur==SortedList->first) {
                    cur->next = nxt->next;
                    nxt->next->prev = cur;
                    nxt->prev = NULL;
                    nxt->next = cur;
                    cur->prev = nxt;
                    SortedList->first = nxt;
                }
                else if(nxt == SortedList->last){
                    cur->prev->next = nxt;
                    nxt->prev = cur->prev;
                    cur->next = NULL;
                    cur->prev = nxt;
                    nxt->next = cur;
                    SortedList->last = cur;
                }
                else{
                    cur->prev->next = nxt;
                    nxt->prev = cur->prev;
                    cur->next = nxt->next;
                    cur->prev = nxt;
                    nxt->next->prev = cur;
                    nxt->next = cur;
                }
            }
            cur = nxt;
            nxt = nxt->next;
        }
    }
    return SortedList;
}
List *Merge(List *left,List *right){
    List *Res = calloc(1,sizeof(List));
    if(left == NULL) return right;
    if(right == NULL) return left;
    ListNode *i = left->first;
    ListNode *j = right->first;
    while(!(i == NULL && j == NULL)){
        if(j==NULL){
            List_push(Res,i->value);
            i = i->next;
        }
        else if(i==NULL){
            List_push(Res,j->value);
            j = j->next;
        }
        else if(*(int *)(i->value) <= *(int *)(j->value)){
            List_push(Res,i->value);
            i = i->next;
        }
        else if(*(int *)(i->value) > *(int *)(j->value)){
            List_push(Res,j->value);
            j = j->next;
        }
    }
    return Res;
}
List *MergeSort(List *list){
    int middle = list->count/2;
    if(list->count<=1) return list;
    List **SplitLists = ListSplit(list,middle);
    List *LeftSorted = MergeSort(*SplitLists);
    List *RightSorted = MergeSort(*(SplitLists+1));
    List *MergeList = Merge(LeftSorted,RightSorted);
    free((void *)SplitLists);
    // free((void *)*(SplitLists+1));
    free((void *)LeftSorted);
    free((void *)RightSorted);
    return MergeList;
}
// List *BottomupMergeSort(List *list){
//     for(int width = 2;width*width <= list->count;width *=2){
//         ListNode *cur = list->first;
//         int cnt = 0;
//         while(cnt < width){
            
//         }
//     }
// }
void List_sorted_insert(List_sorted *list,void *value){
    ListNode *cur = list->first;
    if(list->first == NULL){
        ListNode *tmp = calloc(1,sizeof(ListNode));
        tmp->next = NULL;
        tmp->prev = NULL;
        tmp->value = value;
        list->first = tmp;
        list->last = tmp;
        list->count = 1;
    }
    while(cur!=NULL){
        if(*(int *)cur->value < *(int *)value){
            if(cur == list->last){
                ListNode *new = calloc(1,sizeof(ListNode));
                new->value = value;
                new->prev = cur;
                cur->next = new;
                list->last = new;
                list->count += 1;
                break;
            }
            else{
                cur = cur->next;
            }
        }
        else{
            ListNode *new = calloc(1,sizeof(ListNode));
            if(cur == list->first){
                new->value = value;
                new->next = cur;
                cur->prev = new;
                list->first = new;
                list->count += 1;
            }
            else{
                new->value = value;
                new->next = cur;
                new->prev = cur->prev;
                cur->prev->next = new;
                cur->prev = new;
                list->count += 1;
            }
            break;
        }
    }
}

void showList_sorted(List_sorted *list){
    ListNode *cur = list->first;
    int cnt=1;
    while(cur != NULL){
        printf("Num%d : %d\n",cnt,*(int *)cur->value);
        cur = cur->next;
        cnt++;
    }
}

int main(){
    List *num1 = calloc(1,sizeof(List));
    List *num2 = calloc(1,sizeof(List));
    List_sorted *num3 = calloc(1,sizeof(List_sorted));
    clock_t start, end;
    clock_t ss,es;
    double tsum = 0;
    double cpu_time_used;
    int len = 0;
    printf("Please input the length of the list:");
    scanf("%d",&len);
    for(int i = 0;i<len;i++){
        int *a = calloc(1,sizeof(int));
        //scanf("%d",a);
        *a = rand()%len;
        List_push(num1,a);
        List_push(num2,a);
        ss = clock();
        List_sorted_insert(num3,a);
        es = clock();
        tsum += ((double) (es - ss)) / CLOCKS_PER_SEC;
    }
    printf("Start sorting:\n");
    printf("Bubble Sort:\n");
    start = clock();
    List *SortedList1 = BubbleSort(num1);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    //showList(SortedList1);
    printf("Bubble Sort time:%f\n",cpu_time_used);
    printf("Merge Sort:\n");
    start = clock();
    List *SortedList2 = MergeSort(num2);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    //showList(SortedList2);
    printf("Merge Sort time:%f\n",cpu_time_used);

    showList_sorted(num3);
    printf("List_sorted time:%f\n",tsum);
    return 0;
}