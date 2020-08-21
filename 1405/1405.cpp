#include <cstdio>
#include <vector>

using namespace std;

typedef vector<int> lnum;
const int base = 1000 * 1000 * 1000;

void print(lnum a) {
    printf("%d", a.empty() ? 0 : a.back());
    for (int i = (int)a.size() - 2; i >= 0; --i) printf("%09d", a[i]);
    putchar('\n');
}

lnum add(lnum a, lnum b) {
    int carry = 0;
    for (size_t i = 0; i < max(a.size(), b.size()) || carry; ++i) {
        if (i == a.size())
            a.push_back(0);
        a[i] += carry + (i < b.size() ? b[i] : 0);
        carry = a[i] >= base;
        if (carry) a[i] -= base;
    }
    return a;
}

lnum sub(lnum a, lnum b) {
    int carry = 0;
    for (size_t i = 0; i < b.size() || carry; ++i) {
        a[i] -= carry + (i < b.size() ? b[i] : 0);
        carry = a[i] < 0;
        if (carry) a[i] += base;
    }
    while (a.size() > 1 && a.back() == 0) a.pop_back();
    return a;
}

lnum mul(lnum a, lnum b) {
    lnum c(a.size() + b.size());
    for (size_t i = 0; i < a.size(); ++i)
        for (int j = 0, carry = 0; j < (int)b.size() || carry; ++j) {
            long long cur = c[i + j] + a[i] * 1ll * (j < (int)b.size() ? b[j] : 0) + carry;
            c[i + j] = int(cur % base);
            carry = int(cur / base);
        }
    while (c.size() > 1 && c.back() == 0) c.pop_back();
    return c;
}

int n;

int main() {
    scanf("%d", &n);
    lnum cur = vector<int>(1, 2);
    lnum one = vector<int>(1, 1);
    print(cur);
    --n;
    while (n--) {
        cur = add((mul(cur, sub(cur, one))), one);
        print(cur);
    }

    return 0;
}