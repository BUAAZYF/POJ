#include <cctype>
#include <cstdio>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

const int MAX = 55;

int t, side, atom_cnt, start;
string name, chemical_eq;
vector<map<string, int> > molecules[2];
set<string> atoms[2];
map<string, int> atoms_idx;
vector<int> cnt, coefficients;
vector<vector<int> > alt_coefficients[2];
vector<vector<int> > alt_cnt[2];

void init() {
    molecules[0].clear();
    molecules[1].clear();
    molecules[0].push_back(map<string, int>());
    atoms[0].clear();
    atoms[1].clear();
    atoms_idx.clear();
    cnt.clear();
    coefficients.clear();
    alt_coefficients[0].clear();
    alt_coefficients[1].clear();
    alt_cnt[0].clear();
    alt_cnt[1].clear();
    side = 0;
    atom_cnt = 1;
    start = 1;
    name = "";
}

void formeq(int idx, int side, vector<int> cnt, vector<int> coefficients) {
    if (idx == molecules[side].size()) {
        alt_cnt[side].push_back(cnt);
        alt_coefficients[side].push_back(coefficients);
        return;
    }
    if (start > 1) {
        for (map<string, int>::iterator it = molecules[side][idx].begin(); it != molecules[side][idx].end(); ++it)
            cnt[atoms_idx[it->first]] += (start - 1) * it->second;
    }
    for (int i = start; i <= 9; ++i) {
        coefficients[idx] = i;
        for (map<string, int>::iterator it = molecules[side][idx].begin(); it != molecules[side][idx].end(); ++it)
            cnt[atoms_idx[it->first]] += it->second;
        formeq(idx + 1, side, cnt, coefficients);
    }
}

int main() {
    freopen("in.txt", "r", stdin);
    scanf("%d", &t);
    while (t-- > 0) {
        getchar();
        cin >> chemical_eq;
        init();
        int i = 0, j, n = chemical_eq.size();
        while (i < n) {
            if (isupper(chemical_eq[i])) {
                if (name != "") {
                    if (molecules[side][molecules[side].size() - 1].find(name) == molecules[side][molecules[side].size() - 1].end())
                        molecules[side][molecules[side].size() - 1][name] = 0;
                    atoms[side].insert(name);
                    molecules[side][molecules[side].size() - 1][name] += atom_cnt;
                }
                name = "";
                atom_cnt = 1;
                name += chemical_eq[i];
                ++i;
                if (i < n && islower(chemical_eq[i])) name += chemical_eq[i++];
            } else if (isdigit(chemical_eq[i])) {
                atom_cnt = chemical_eq[i++] - '0';
                if (atom_cnt == 9) start = 8;
            } else if (chemical_eq[i] == '+' || chemical_eq[i] == '=') {
                if (name != "") {
                    if (molecules[side][molecules[side].size() - 1].find(name) == molecules[side][molecules[side].size() - 1].end())
                        molecules[side][molecules[side].size() - 1][name] = 0;
                    atoms[side].insert(name);
                    molecules[side][molecules[side].size() - 1][name] += atom_cnt;
                }
                if (chemical_eq[i] == '=') side = 1;
                molecules[side].push_back(map<string, int>());
                name = "";
                atom_cnt = 1;
                ++i;
            }
        }
        if (name != "") {
            if (molecules[side][molecules[side].size() - 1].find(name) == molecules[side][molecules[side].size() - 1].end())
                molecules[side][molecules[side].size() - 1][name] = 0;
            atoms[side].insert(name);
            molecules[side][molecules[side].size() - 1][name] += atom_cnt;
        }
        if (molecules[side][molecules[side].size() - 1].empty()) molecules[side].pop_back();
        if (atoms[0].size() != atoms[1].size()) {
            printf("IMPOSSIBLE\n");
            continue;
        }
        bool same = true;
        for (set<string>::iterator it1 = atoms[0].begin(), it2 = atoms[1].begin(); it1 != atoms[0].end(); ++it1, ++it2) {
            if (*it1 != *it2) {
                same = false;
                break;
            }
        }
        if (!same) {
            printf("IMPOSSIBLE\n");
            continue;
        }
        i = 0;
        for (set<string>::iterator it = atoms[0].begin(); it != atoms[0].end(); ++it, ++i) atoms_idx[*it] = i;
        for (side = 0; side < 2; ++side) {
            cnt = vector<int>(atoms[side].size(), 0);
            coefficients = vector<int>(molecules[side].size(), 0);
            formeq(0, side, cnt, coefficients);
        }
        bool found = false, issame;
        for (i = 0; i < alt_cnt[0].size(); ++i) {
            for (j = 0; j < alt_cnt[1].size(); ++j) {
                issame = true;
                for (int k = 0; k < alt_cnt[0][i].size(); ++k) {
                    if (alt_cnt[0][i][k] != alt_cnt[1][j][k]) {
                        issame = false;
                        break;
                    }
                }
                if (issame) {
                    found = true;
                    break;
                }
            }
            if (found) break;
        }
        if (!found) {
            printf("IMPOSSIBLE\n");
            continue;
        }
        for (int k = 0; k < alt_coefficients[0][i].size(); ++k) printf("%d ", alt_coefficients[0][i][k]);
        for (int k = 0; k < alt_coefficients[1][j].size() - 1; ++k) printf("%d ", alt_coefficients[1][j][k]);
        printf("%d\n", alt_coefficients[1][j][alt_coefficients[1][j].size() - 1]);
    }

    return 0;
}