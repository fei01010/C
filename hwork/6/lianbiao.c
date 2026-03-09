#include<stdio.h>
#include<stdlib.h>
typedef struct Node{
    int data;
    struct Node* next;
}Node;
Node* DeleteNode1(Node *head, int x) {
    while (head != NULL && head->data == x) {
        Node *q = head;  
        head = head->next;  
        free(q);        
    }
    Node *p = head;    
    while (p!=NULL&&p->next != NULL) {
        if (p->next->data == x) {
            Node *temp = p->next;
            p->next = p->next->next;  
            free(temp);                     
        } else {
            p = p->next;  
        }
    }
    return head;
}  
Node* DeleteNode2(Node* head, int x) {
    if (head == NULL) {
        return NULL;
    }
    while (head != NULL && head->data == x) {
        Node* temp = head;
        head = head->next;  
        free(temp);        
    }
    if (head == NULL) {
        return NULL;
    }
    head->next = DeleteNode2(head->next, x);
    return head;
}
