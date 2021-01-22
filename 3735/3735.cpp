#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;
typedef long long ll;
typedef vector<ll> vec;
typedef vector<vec> mat;

int n, m, k, x, y;
char op;

mat matmul(mat& A, mat& B) {
    mat C(A.size(), vec(B[0].size()));
    for (int i = 0; i < A.size(); ++i)
        for (int k = 0; k < B.size(); ++k) {
            if (A[i][k] == 0) continue;
            for (int j = 0; j < B[0].size(); ++j)
                C[i][j] = (C[i][j] + A[i][k] * B[k][j]);
        }
    return C;
}

mat matpow(mat A, int n) {
    mat B(A.size(), vec(A.size()));
    for (int i = 0; i < A.size(); ++i) B[i][i] = 1;
    while (n > 0) {
        if (n & 1) B = matmul(B, A);
        A = matmul(A, A);
        n >>= 1;
    }
    return B;
}

int main() {
    mat A, B;
    while (scanf("%d%d%d", &n, &m, &k) != EOF && n) {
        A = mat(n + 1, vec(n + 1, 0));
        for (int i = 0; i <= n; ++i) A[i][i] = 1;
        for (int i = 0; i < k; ++i) {
            while ((op = getchar()) != EOF && op != '\n')
                ;
            op = getchar();
            if (op == 'g') {
                scanf("%d", &x);
                ++A[x - 1][n];
            } else if (op == 'e') {
                scanf("%d", &x);
                A[x - 1] = vec(n + 1, 0);
            } else {
                scanf("%d%d", &x, &y);
                swap(A[x - 1], A[y - 1]);
            }
        }
        if (m != 0)
            B = matpow(A, m);
        else
            B = mat(n + 1, vec(n + 1, 0));
        for (int i = 0; i < n - 1; ++i) printf("%lld ", B[i][n]);
        printf("%lld\n", B[n - 1][n]);
    }

    return 0;
}