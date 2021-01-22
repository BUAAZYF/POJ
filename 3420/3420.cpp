#include <cstdio>
#include <vector>

using namespace std;

typedef vector<int> vec;
typedef vector<vec> mat;

int N, M;
mat A = mat(5, vec(5));

mat matmul(mat& A, mat& B) {
    mat C(A.size(), vec(B[0].size()));
    for (int i = 0; i < A.size(); ++i)
        for (int k = 0; k < B.size(); ++k)
            for (int j = 0; j < B[0].size(); ++j)
                C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % M;
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
    A[0][0] = A[0][1] = A[0][2] = A[0][4] = 1;
    A[1][0] = 2, A[1][1] = 1;
    A[2][0] = A[2][3] = 1;
    A[3][2] = 1;
    A[4][0] = 1;
    mat B;
    while (scanf("%d%d", &N, &M) != EOF && N) {
        B = matpow(A, N);
        printf("%d\n", B[0][0]);
    }

    return 0;
}