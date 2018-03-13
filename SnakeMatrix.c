/* 以左下角为起点，打印蛇形矩阵 */

#include <stdio.h>

int main() {
    int n;
    scanf("%d",&n);

    int nline;          // 当前行的行号
    int matrix[n][n];
    int count;
    int i, j;
    int isodd;          // 当前行的奇偶性

    nline = 0;
    count = 1;
    i = n-1, j = 0;
    while (count <= n * n) {
        isodd = nline++ % 2;
        if (isodd == 1) {
            while (i < n && j < n)
                matrix[i++][j++] = count++;
            /* 越界调整，if语句顺序不得调换 */
            if (j > n-1) {
                i -= 2;
                j -= 1;
            }
            if (i > n-1)
                i--;
        } else {
            while (i >= 0 && j >= 0)
                matrix[i--][j--] = count++;
            if (i < 0) {
                i += 1;
                j += 2;
            }
            if (j < 0)
                j++;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)  
            printf("%4d", matrix[i][j]);
        printf("\n");
    }
    return 0;
}         


