#include <stdio.h>

int main() {
    int n, m, hx, hy;
    scanf("%d %d %d %d", &n, &m, &hx, &hy);

    int blocked[25][25] = {0};
    long long dp[25][25] = {0};
    //标记马能跳到的位置
    int dx[8] = {1, 2, 2, 1, -1, -2, -2, -1};
    int dy[8] = {2, 1, -1, -2, -2, -1, 1, 2};

    blocked[hx][hy] = 1;//马的位置
    for (int i = 0; i < 8; i++) {
        int x = hx + dx[i];
        int y = hy + dy[i];
        if (x >= 0 && x <= n && y >= 0 && y <= m) {
            blocked[x][y] = 1;
        }
    }

    if (!blocked[0][0]) {
        dp[0][0] = 1;
    }

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            if (blocked[i][j]) {
                continue;
            }
            if (i == 0 && j == 0) {
                continue;
            }
            if (i > 0) {
                dp[i][j] += dp[i - 1][j];
            }
            if (j > 0) {
                dp[i][j] += dp[i][j - 1];
            }
        }
    }

    printf("%lld", dp[n][m]);
    return 0;
}