#include <climits>
#include <cstdio>
#include <vector>

using namespace std;

int inline max(int a, int b) {
    return a >= b ? a : b;
}

int maxPartSum(vector<int>& nums) {
    int maxVal = nums[0], curVal = nums[0];
    for (int i = 1; i < nums.size(); ++i) {
        if (curVal < 0)
            curVal = nums[i];
        else
            curVal += nums[i];
        maxVal = max(maxVal, max(nums[i], curVal));
    }
    return maxVal;
}

int sumOfSubMatrix(vector<vector<int> >& mat, int n) {
    int maxSum = INT_MIN;
    for (int i = 0; i < n; ++i) {
        vector<int> dp(mat[i]);
        maxSum = max(maxSum, maxPartSum(dp));
        for (int j = i + 1; j < n; ++j) {
            for (int k = 0; k < n; ++k) dp[k] += mat[j][k];
            maxSum = max(maxSum, maxPartSum(dp));
        }
    }

    return maxSum;
}

int main() {
    // freopen("in.txt", "r", stdin);
    int n;
    scanf("%d", &n);
    vector<vector<int> > matrix(n, vector<int>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            scanf("%d", &matrix[i][j]);
    printf("%d\n", sumOfSubMatrix(matrix, n));

    return 0;
}