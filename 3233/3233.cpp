#include <cstdio>
#include <vector>

using namespace std;

typedef vector<int> vec;
typedef vector<vec> mat;

int n, k, m, cur;

mat matmul(mat& A, mat& B) {
    mat C(A.size(), vec(B[0].size()));
    for (int i = 0; i < A.size(); ++i)
        for (int k = 0; k < B.size(); ++k)
            for (int j = 0; j < B[0].size(); ++j)
                C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % m;
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
    scanf("%d%d%d", &n, &k, &m);
    mat A(n << 1, vec(n << 1));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) scanf("%d", &A[i][j]);
        A[n + i][i] = A[n + i][n + i] = 1;
    }
    A = matpow(A, k + 1);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cur = A[n + i][j] % m;
            if (i == j) cur = (cur + m - 1) % m;
            printf("%d%c", cur, j + 1 == n ? '\n' : ' ');
        }
    }

    return 0;
}