#include<stdio.h>
#include<stdlib.h>
typedef struct node{
    int data;
    struct node* next;
}NODE;
NODE* CreateNode(){
    NODE *head=NULL;
    head=(NODE*)malloc(sizeof(NODE));
    int s;
    while(s=scanf("%d",&head->data)!=EOF){
        NODE* p=(NODE*)malloc(sizeof(NODE));
        p->data=s;
        head->next=p;
        p->next=NULL;
    }
    return head;
}
int length(NODE* list){
    NODE* p=list;
    int count=0;
    while(p!=NULL){
        count++;
        p=p->next;
    }
    return count;
}
NODE* SearchNode(NODE*list,int k,int length){
    NODE* p=list;
    int i=0;
    while(i<length-k){
        i++;
        p=p->next;
    }
    return p;
}
void PrintfNode(NODE* p){
    printf("%d",p->data);
}
int main(){
    NODE* head=CreateNode();
    int len=length(head);
    int k;
    scanf("%d",&k);
    NODE* p=SearchNode(head,k,len);
    PrintfNode(p);
    return 0;
}