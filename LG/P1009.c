#include <stdio.h>

int main() {
    int n;
    int factorial[200] = {0};
    int sum[200] = {0};
    int factorial_len = 1;
    int sum_len = 1;

    scanf("%d", &n);

    factorial[0] = 1;
    sum[0] = 0;

    for (int i = 1; i <= n; i++) {
        int carry = 0;
        for (int j = 0; j < factorial_len; j++) {
            int value = factorial[j] * i + carry;
            factorial[j] = value % 10;
            carry = value / 10;
        }
        while (carry > 0) {
            factorial[factorial_len] = carry % 10;
            carry /= 10;
            factorial_len++;
        }

        carry = 0;
        int max_len = factorial_len > sum_len ? factorial_len : sum_len;
        for (int j = 0; j < max_len; j++) {
            int value = sum[j] + factorial[j] + carry;
            sum[j] = value % 10;
            carry = value / 10;
        }
        sum_len = max_len;
        while (carry > 0) {
            sum[sum_len] = carry % 10;
            carry /= 10;
            sum_len++;
        }
    }

    for (int i = sum_len - 1; i >= 0; i--) {
        printf("%d", sum[i]);
    }

    return 0;
}