#include<iostream>
#include<string>
#include<utility>
#include<cctype>
#include<cstring>

using namespace std;

int main(){
    int upper_count[26];
    memset(upper_count, 0, sizeof(int) * 26);
    string str;
    for(int r = 0; r < 4; ++r){
        getline(cin, str);
        for(size_t i = 0; i < str.size(); ++i){
            if(isupper(str[i])) ++upper_count[str[i] - 'A'];
        }
    }
    int maxheight = 0;
    for(int i = 0;i < 26;++i){
        maxheight = max(maxheight, upper_count[i]);
    }
    for(int i = maxheight;i > 0; --i){
        string cur = "";
        for(int j = 25;j >= 0; --j){
            if(upper_count[j] < i){
                if(cur == "") continue;
                cur = "  " + cur;
            }
            else{
                if(cur == "") cur = "*";
                else cur = "* " + cur;
            }
        }
        cout << cur << endl;
    }

    for(int i = 0; i < 25; ++i){
        cout << char('A' + i) << " ";
    }
    cout << 'Z';

    return 0;
}