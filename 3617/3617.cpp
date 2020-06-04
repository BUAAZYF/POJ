#include <cstdio>

using namespace std;

const int MAX = 2005;

int n, left, right, cnt;
char cows[MAX];
bool getleft;

int main() {
    //freopen("in.txt", "r", stdin);
    scanf("%d\n", &n);
    for (int i = 0; i < n; ++i) scanf("%c\n", &cows[i]);
    left = 0;
    right = n - 1;
    cnt = 0;
    for (int i = 0; i < n; ++i) {
        getleft = false;
        for (int j = 0, bound = (n + 1 - i) / 2; j < bound; ++j) {
            if (cows[left + j] < cows[right - j]) {
                getleft = true;
                break;
            } else if (cows[left + j] > cows[right - j])
                break;
        }
        if (getleft)
            putchar(cows[left++]);
        else
            putchar(cows[right--]);
        ++cnt;
        if (cnt % 80 == 0 && i < n - 1)
            putchar('\n');
    }

    return 0;
}