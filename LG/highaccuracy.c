#include <stdio.h>
#include <string.h>

#define MAXD 5000

typedef struct {
    int d[MAXD]; // 倒序：d[0] 是个位
    int len; // 当前有效位数
} BigInt;

void bi_zero(BigInt *a) {
    memset(a->d, 0, sizeof(a->d));
    a->len = 1;
}

void bi_one(BigInt *a) {
    bi_zero(a);
    a->d[0] = 1;
}

// a = a * x, x 是普通 int
void bi_mul_int(BigInt *a, int x) {
    int carry = 0;
    for (int i = 0; i < a->len; i++) {
        long long v = 1LL * a->d[i] * x + carry;
        a->d[i] = (int)(v % 10);
        carry = (int)(v / 10);
    }
    while (carry > 0) {
        a->d[a->len++] = carry % 10;
        carry /= 10;
    }
}

// a = a + b
void bi_add(BigInt *a, const BigInt *b) {
    int carry = 0;
    int maxLen = (a->len > b->len) ? a->len : b->len;
    for (int i = 0; i < maxLen; i++) {
        int v = a->d[i] + b->d[i] + carry;
        a->d[i] = v % 10;
        carry = v / 10;
    }
    a->len = maxLen;
    while (carry > 0) {
        a->d[a->len++] = carry % 10;
        carry /= 10;
    }
}

void bi_print(const BigInt *a) {
    for (int i = a->len - 1; i >= 0; i--) {
        printf("%d", a->d[i]);
    }
    printf("\n");
}

int main() {
    int n;
    scanf("%d", &n);

    BigInt fac, sum;
    bi_one(&fac); // fac = 1
    bi_zero(&sum); // sum = 0

    for (int i = 1; i <= n; i++) {
        bi_mul_int(&fac, i); // fac = i!
        bi_add(&sum, &fac); // sum += i!
    }

    bi_print(&sum);
    return 0;
}