#include <cstdio>
#include <vector>

using namespace std;

typedef vector<int> vec;
typedef vector<vec> mat;

const int MOD = 10007;

mat matmul(mat& A, mat& B) {
    mat C(A.size(), vec(B[0].size()));
    for (int i = 0; i < A.size(); ++i)
        for (int k = 0; k < B.size(); ++k)
            for (int j = 0; j < B[0].size(); ++j)
                C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % MOD;
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

int T, N;

int main() {
    scanf("%d", &T);
    mat A(3, vec(3)), B;
    A[0][0] = 2, A[0][1] = 1, A[0][2] = 0;
    A[1][0] = 2, A[1][1] = 2, A[1][2] = 2;
    A[2][0] = 0, A[2][1] = 1, A[2][2] = 2;
    while (T--) {
        scanf("%d", &N);
        B = matpow(A, N);
        printf("%d\n", B[0][0]);
    }

    return 0;
}