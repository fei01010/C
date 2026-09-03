#include <iostream>
using namespace std;

// 多项式链表节点结构体定义
typedef struct PNode {
    float coef;   // 系数
    int expn;     // 指数
    struct PNode *next; // 后继指针
} PNode, *Polynomial;

// 1. 创建多项式（按指数升序输入）
void CreatePolyn(Polynomial &P, int n) {
    // 初始化头结点
    P = new PNode;
    P->next = NULL;
    PNode *s, *pre, *q;
    pre = P; // pre始终指向当前节点的前驱，用于插入

    cout << "请依次输入" << n << "个项的系数和指数（按指数升序输入，空格分隔）：" << endl;
    for (int i = 0; i < n; i++) {
        float c;
        int e;
        cin >> c >> e;
        s = new PNode;
        s->coef = c;
        s->expn = e;
        s->next = NULL;

        // 按指数升序插入节点（保证链表有序）
        q = P->next;
        pre = P;
        while (q != NULL && q->expn < e) {
            pre = q;
            q = q->next;
        }
        pre->next = s;
        s->next = q;
    }
}

// 2. 打印多项式
void PrintPolyn(Polynomial P) {
    PNode *p = P->next;
    if (p == NULL) {
        cout << "0" << endl;
        return;
    }
    // 打印第一项（处理符号）
    if (p->coef > 0) {
        if (p->coef != 1) cout << p->coef;
        if (p->expn == 0) cout << "";
        else if (p->expn == 1) cout << "x";
        else cout << "x^" << p->expn;
    } else {
        if (p->coef != -1) cout << p->coef;
        else cout << "-";
        if (p->expn == 0) cout << "";
        else if (p->expn == 1) cout << "x";
        else cout << "x^" << p->expn;
    }
    p = p->next;
    // 打印后续项
    while (p != NULL) {
        if (p->coef > 0) {
            cout << "+";
            if (p->coef != 1) cout << p->coef;
        } else {
            cout << "-";
            if (p->coef != -1) cout << -p->coef;
        }
        if (p->expn == 0) cout << "";
        else if (p->expn == 1) cout << "x";
        else cout << "x^" << p->expn;
        p = p->next;
    }
    cout << endl;
}

// 3. 核心：多项式加法 Pa = Pa + Pb（你提供的算法完整实现）
void AddPolyn(Polynomial &Pa, Polynomial &Pb) {
    PNode *p1 = Pa->next, *p2 = Pb->next;
    PNode *p3 = Pa, *r;
    float sum;

    while (p1 && p2) {
        if (p1->expn == p2->expn) { // 指数相等，同类项合并
            sum = p1->coef + p2->coef;
            if (sum != 0) { // 系数和不为0，修改Pa节点，删除Pb节点
                p1->coef = sum;
                p3->next = p1;
                p3 = p1;
                p1 = p1->next;
                r = p2;
                p2 = p2->next;
                delete r;
            } else { // 系数和为0，同时删除Pa、Pb节点
                r = p1;
                p1 = p1->next;
                delete r;
                r = p2;
                p2 = p2->next;
                delete r;
            }
        } else if (p1->expn < p2->expn) { // Pa项指数更小，直接链接Pa节点
            p3->next = p1;
            p3 = p1;
            p1 = p1->next;
        } else { // Pb项指数更小，直接链接Pb节点
            p3->next = p2;
            p3 = p2;
            p2 = p2->next;
        }
    }
    // 拼接剩余未遍历的节点
    p3->next = p1 ? p1 : p2;
    // 释放Pb的头结点
    delete Pb;
    Pb = NULL; // 避免野指针
}

// 4. 主函数：测试流程
int main() {
    Polynomial Pa, Pb;
    int na, nb;

    // 输入多项式Pa
    cout << "===== 输入多项式Pa =====" << endl;
    cout << "请输入Pa的项数：";
    cin >> na;
    CreatePolyn(Pa, na);

    // 输入多项式Pb
    cout << "===== 输入多项式Pb =====" << endl;
    cout << "请输入Pb的项数：";
    cin >> nb;
    CreatePolyn(Pb, nb);

    // 打印原始多项式
    cout << "\n原始多项式：" << endl;
    cout << "Pa = ";
    PrintPolyn(Pa);
    cout << "Pb = ";
    PrintPolyn(Pb);

    // 执行加法
    AddPolyn(Pa, Pb);

    // 打印结果
    cout << "\n加法结果 Pa = Pa + Pb：" << endl;
    cout << "Pa = ";
    PrintPolyn(Pa);

    return 0;
}