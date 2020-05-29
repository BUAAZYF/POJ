#include<iostream>
#include<string>
#include<vector>
#include<utility>
#include<algorithm>

using namespace std;

int main(){
    int n, m;
    cin >> n >> m;
    string dna;
    vector<pair<int, string> > diffdna(m);
    for(int i = 0; i < m; ++i){
        cin >> dna;
        int diff = 0;
        for(int j = 0;j < n; ++j){
            for(int k = j + 1; k < n; ++k){
                if(dna[j] > dna[k]) ++diff;
            }
        }
        diffdna[i] = pair<int, string>(diff, dna);
    }

    sort(diffdna.begin(), diffdna.end());
    for(int i = 0; i < m; ++i){
        cout << diffdna[i].second << endl;
    }
    
    return 0;
}