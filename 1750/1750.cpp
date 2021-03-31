#include <cstdio>
#include <cstring>

using namespace std;

const int MAXC = 12;

int min(int a, int b) {
    return a <= b ? a : b;
}

char lastword[MAXC], word[MAXC];

int common(char *s1, char *s2) {
    int ans = 0;
    for (int i = 0; i < min(strlen(s1), strlen(s2)); ++i) {
        if (s1[i] != s2[i]) break;
        ++ans;
    }
    return ans;
}

int main() {
    int space = 0, cm;
    while (scanf("%s", &word[0]) != EOF) {
        cm = common(word, lastword);
        if (cm == 0) {
            space = 0;
            puts(word);
        } else {
            if (cm > space) ++space;
            else if (cm < space) space = cm;
            for (int i = 0; i < space; ++i) putchar(' ');
            puts(word);
        }
        memcpy(lastword, word, MAXC * sizeof(char));
    }

    return 0;
}