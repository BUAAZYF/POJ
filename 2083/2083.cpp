#include <cstdio>

using namespace std;

const int MAX = 729;

int n;
const int len[8] = {0, 1, 3, 9, 27, 81, 243, 729};
char board[MAX][MAX];

void printfracal(int n, int x, int y){
    if (n == 1){
        board[x][y] = 'X';
        return;
    }
    printfracal(n - 1, x, y);
    printfracal(n - 1, x + len[n - 1] * 2, y);
    printfracal(n - 1, x, y + len[n - 1] * 2);
    printfracal(n - 1, x + len[n - 1] * 2, y + len[n - 1] * 2);
    printfracal(n - 1, x + len[n - 1], y + len[n - 1]);
}

int main() {
    for (int i = 0; i < MAX; ++i)
        for( int j = 0; j < MAX; ++j)
            board[i][j] = ' ';
    printfracal(7, 0, 0);
    while (scanf("%d\n", &n) != EOF && n != -1) {
        for(int i = 0; i < len[n]; ++i){
            for(int j = 0; j < len[n]; ++j) putchar(board[i][j]);
            putchar('\n');
        }
        printf("-\n");
    }

    return 0;
}