#include <cmath>
#include <cstdio>

using namespace std;

const int BOX = 6;

int boxes[BOX + 1];
int sum, ans, leftarea, used;

inline int max(int a, int b) {
    return a >= b ? a : b;
}

inline int min(int a, int b) {
    return a <= b ? a : b;
}

int main() {
    // freopen("in.txt", "r", stdin);
    while (true) {
        sum = ans = 0;
        for (int i = 0; i < BOX; ++i) {
            scanf("%d", &boxes[i + 1]);
            sum += boxes[i + 1];
        }
        if (sum == 0) return 0;
        ans += boxes[6];

        ans += boxes[5];
        if (boxes[5] != 0) boxes[1] = max(0, boxes[1] - 11 * boxes[5]);

        ans += boxes[4];
        if (boxes[4] != 0) {
            leftarea = boxes[4] * 20;
            used = min(boxes[2], boxes[4] * 5);
            boxes[2] -= used;
            leftarea -= used * 4;
            boxes[1] = max(0, boxes[1] - leftarea);
        }

        ans += (int)ceil(boxes[3] / 4.0);
        boxes[3] %= 4;
        if (boxes[3] != 0) {
            if (boxes[3] == 1) {
                used = min(5, boxes[2]);
                leftarea = 27 - used * 4;
            } else if (boxes[3] == 2) {
                used = min(3, boxes[2]);
                leftarea = 18 - used * 4;
            } else if (boxes[3] == 3) {
                used = min(1, boxes[2]);
                leftarea = 9 - used * 4;
            }
            boxes[2] -= used;
            boxes[1] = max(0, boxes[1] - leftarea);
        }

        ans += (int)ceil(boxes[2] / 9.0);
        boxes[2] %= 9;
        if (boxes[2] != 0) {
            leftarea = 36 - boxes[2] * 4;
            boxes[1] = max(0, boxes[1] - leftarea);
        }

        ans += (int)ceil(boxes[1] / 36.0);

        printf("%d\n", ans);
    }

    return 0;
}