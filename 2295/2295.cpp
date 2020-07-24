#include <cstdio>
#include <cmath>

using namespace std;

const int MAX = 1005;

double inline max(int a, int b) {
    return a >= b ? a : b;
}

int t, nums[2], x[2], sign, num, side;
char c;

int main() {
    // freopen("in.txt", "r", stdin);
    scanf("%d\n", &t);
    while (t-- > 0) {
        nums[0] = nums[1] = x[0] = x[1] = 0;
        side = 0;
        sign = 1;
        num = 0;
        while ((c = getchar()) != EOF && c != '\n') {
            switch (c) {
                case '=':
                    nums[side] += sign * num;
                    side = 1;
                    sign = 1;
                    num = 0;
                    break;
                case '+':
                    nums[side] += sign * num;
                    num = 0;
                    sign = 1;
                    break;
                case '-':
                    nums[side] += sign * num;
                    num = 0;
                    sign = -1;
                    break;
                case 'x':
                    x[side] += sign * (num == 0 ? 1 : num);
                    num = 0;
                    break;
                default:
                    num = num * 10 + (c - '0');
                    break;
            }
        }
        nums[side] += sign * num;
        nums[1] -= nums[0];
        x[0] -= x[1];
        if (x[0] == 0) {
            if (nums[1] == 0)
                printf("IDENTITY\n");
            else
                printf("IMPOSSIBLE\n");
        } else
            printf("%d\n", nums[1] / x[0] >= 0 ? nums[1] / x[0] : nums[1] / x[0] - 1);
    }

    return 0;
}