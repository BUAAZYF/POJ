#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

const int MAX = 100005;

struct state {
  int len, link;
  int next[26];
  state() {memset(next, 0, sizeof(next)); }
}st[MAX * 2];

string S, T;
int sz, last;

void sam_init() {
  st[0].len = 0;
  st[0].link = -1;
  sz = 0;
  ++sz;
  last = 0;
}

void sam_extend(int c) {
  int cur = sz++;
  st[cur].len = st[last].len + 1;
  int p = last;
  while (p != -1 && !st[p].next[c]) {
    st[p].next[c] = cur;
    p = st[p].link;
  }
  if (p == -1) st[cur].link = 0;
  else {
    int q = st[p].next[c];
    if (st[p].len + 1 == st[q].len) st[cur].link = q;
    else {
      int clone = sz++;
      st[clone].len = st[p].len + 1;
      memcpy(st[clone].next, st[q].next, sizeof(st[q].next));
      st[clone].link = st[q].link;
      while (p != -1 && st[p].next[c] == q) {
        st[p].next[c] = clone;
        p = st[p].link;
      }
      st[q].link = st[cur].link = clone;
    }
  }
  last = cur;
}

string lcs(const string &S, const string &T) {
  sam_init();
  for (int i = 0; i < S.size(); ++i) sam_extend(S[i] - 'a');
  int v = 0, l = 0, best = 0, bestpos = 0;
  for (int i = 0; i < T.size(); ++i) {
    while (v && !st[v].next[T[i] - 'a']) {
      v = st[v].link;
      l = st[v].len;
    }
    if (st[v].next[T[i] - 'a']) {
      v = st[v].next[T[i] - 'a'];
      ++l;
    }
    if (l > best) {
      best = l;
      bestpos = i;
    }
  }
  return T.substr(bestpos - best + 1, best);
}

int main() {
    cin >> S >> T;
    printf("%d\n", lcs(S, T).size());

    return 0;
}