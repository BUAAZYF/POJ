#include <algorithm>
#include <cstdio>
#include <queue>

using namespace std;

const int MAX = 50005;
const int MAXT = 1000005;

struct cow {
    int start;
    int end;
    int id;
    friend bool operator<(cow a, cow b) {
        return a.start < b.start || a.start == b.start && a.end < b.end;
    }
} cows[MAX];

struct stall_item {
    int time;
    int id;
    stall_item(int t, int i) : time(t), id(i) {}
    friend bool operator<(const stall_item a, const stall_item b) {
        return a.time > b.time || a.time == b.time && a.id < b.id;
    }
};

int n;
int stalls[MAX];
priority_queue<stall_item> stall_time;

int main() {
    // freopen("in.txt", "r", stdin);
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d%d", &cows[i].start, &cows[i].end);
        cows[i].id = i;
    }
    sort(cows, cows + n);
    int nid;
    for (int i = 0; i < n; ++i) {
        nid = stall_time.size();
        if (!stall_time.empty() && stall_time.top().time < cows[i].start) {
            nid = stall_time.top().id;
            stall_time.pop();
        }
        stalls[cows[i].id] = nid;
        stall_item item(cows[i].end, nid);
        stall_time.push(item);
    }

    printf("%d\n", static_cast<int>(stall_time.size()));
    for (int i = 0; i < n; ++i) printf("%d\n", stalls[i] + 1);

    return 0;
}