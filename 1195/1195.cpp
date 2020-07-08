#include <cstdio>
#include <vector>

using namespace std;

typedef pair<int, int> Pr;

struct FenwickTree2D {
    vector<vector<long> > bit;
    int n, m;

    FenwickTree2D(int s){
        m = n = s + 1;
        bit = vector<vector<long> >(m, vector<long>(n, 0));
    }

    long sum(int x, int y) {
        long ans = 0;
        for (int i = x; i >= 0; i = (i & (i + 1)) - 1)
            for (int j = y; j >= 0; j = (j & (j + 1)) - 1)
                ans += bit[i][j];
        return ans;
    }

    long sumrange(int L, int B, int R, int T){
        return sum(R, T) - sum(L - 1, T) - sum(R, B - 1) + sum(L - 1, B - 1);
    }

    void add(int x, int y, int delta) {
        for (int i = x; i < n; i = i | (i + 1))
            for (int j = y; j < m; j = j | (j + 1))
                bit[i][j] += delta;
    }
};

int instruction, S, X, Y, A, L, B, R, T;

int main() {
    scanf("%d%d", &instruction, &S);
    FenwickTree2D ft(S);
    while(scanf("%d", &instruction) & instruction != 3){
        if(instruction == 1) {
            scanf("%d%d%d", &X, &Y, &A);
            ft.add(X + 1, Y + 1, A);
        }else{
            scanf("%d%d%d%d", &L, &B, &R, &T);
            printf("%ld\n", ft.sumrange(L + 1, B + 1, R + 1, T + 1));
        }
    }

    return 0;
}