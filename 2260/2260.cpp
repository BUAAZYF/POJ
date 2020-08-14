#include <cstdio>

using namespace std;

const int MAX = 105;

int n, sum, rowodd, colodd;
bool iscorrupt, mat[MAX][MAX];

int main() {
    while (scanf("%d", &n) != EOF && n) {
        rowodd = colodd = -1;
        iscorrupt = false;
        for (int i = 0; i < n; ++i) {
            sum = 0;
            for (int j = 0; j < n; ++j) {
                scanf("%d", &mat[i][j]);
                sum += mat[i][j];
            }
            if (sum % 2 == 1) {
                if (rowodd != -1) iscorrupt = true;
                rowodd = i;
            }
        }
        if (!iscorrupt) {
            for (int j = 0; j < n; ++j) {
                sum = 0;
                for (int i = 0; i < n; ++i) sum += mat[i][j];
                if (sum % 2 == 1) {
                    if (colodd != -1) iscorrupt = true;
                    colodd = j;
                }
            }
        }
        if (iscorrupt || rowodd == -1 && colodd > -1 || rowodd > -1 && colodd == -1) printf("Corrupt\n");
        else if (rowodd == -1 && colodd == -1) printf("OK\n");
        else printf("Change bit (%d,%d)\n", rowodd + 1, colodd + 1);
    }

    return 0;
}