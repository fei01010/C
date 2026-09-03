#include<stdio.h>
#include"polynomial.h"

void Input(Polynomial& PL, double C[], int E[], int n ) {
    Polynomial newTerm, p, pre;
    int e;
    double c;
    while (1) {
        printf ("请输入一项(coef, exp):");
        scanf ("%g", "%d", c, e);
        if(e < 0) break;
        p = PL->link;
        pre = PL;
        while (p != NULL && p->exp > e){
            pre = p;
            p = p->link;
        }
        if(p != NULL && p->exp == e)
            printf("已有与指数%d相等的项,输入作废\n", e);
        else{
            newTerm = (Term*)malloc(sizeof(Term));
            newTerm->coef = c;
            newTerm->exp = e;
            newTerm->link = p;
            pre->link = newTerm;
        }
    }
}

void Output(Polynomial& PL){
    Polynomial p;
    bool h = true;
    printf("The polynomial is:\n");
    for(p = PL->link;p != NULL;p = p->link){
        if(h == 1){
            if(p->coef < 0)printf("-");
            h=0;
        }
        else if(p->coef > 0)printf("+");
        else printf("-");
        if(p->exp == 0||fabs(p->coef) != 1)
            printf("%g", fabs(p->coef));
        switch(p->exp){
            case 0:break;
            case 1:
                printf("X");
                break;
            default:
                printf("X^%d", p->exp);
        }
    }
    printf("\n");
}

int main(){
    return 0;
}