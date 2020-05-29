#include<iostream>
#include<string>

using namespace std;

string remove_useless_zeroes(string a){
    int pre_zero = 0, trail_zero = a.size() - 1;
    while(pre_zero < a.size() and a[pre_zero] == '0') ++pre_zero;
    bool has_decimal = false;
    for(int i = 0; i < a.size(); ++i){
        if(a[i] == '.'){
            has_decimal = true;
            break;
        }
    }
    if(has_decimal)
        while(trail_zero >= 0 and a[trail_zero] == '0') --trail_zero;
    return a.substr(pre_zero, trail_zero + 1 - pre_zero);
}

string multiply_real_numbers(string a, string b){
    size_t decimal_point = 0;
    for(size_t i = 0; i < a.size(); ++i){
        if(a[i] == '.'){
            decimal_point += a.size() - i - 1;
            a = a.substr(0, i) + a.substr(i + 1);
            break;
        }
    }
    for(size_t i = 0; i < b.size(); ++i){
        if(b[i] == '.'){
            decimal_point += b.size() - i -1;
            b = b.substr(0, i) + b.substr(i + 1);
            break;
        }
    }
    string ans(a.size() + b.size(), '0');
    for(int i = a.size() - 1; i >= 0 ; --i){
        int cur, carry = 0, idx = b.size() + i;
        for(int j = b.size() - 1; j >= 0; --j){
            cur = (a[i] - '0') * (b[j] - '0') + carry + (ans[idx] - '0');
            ans[idx] = char(cur % 10 + '0');
            carry = cur / 10;
            --idx;
        }
        while(carry > 0){
            cur = carry + (ans[idx] - '0');
            ans[idx] = char(cur % 10 + '0');
            carry = cur / 10;
            --idx;
        }
    }
    if(decimal_point > 0) ans = ans.insert(a.size() + b.size() - decimal_point, ".");
    ans = remove_useless_zeroes(ans);
    return ans;
}

int main(){
    string s;
    int n;
    while(cin >> s >> n){
        s = remove_useless_zeroes(s);
        string ans = s;
        for(int i = 1; i < n;++i){
            ans = multiply_real_numbers(ans, s);
        }
        ans = remove_useless_zeroes(ans);
        if(ans[ans.size() - 1] == '.') ans = ans.substr(0, ans.size() - 1);
        if(ans == "") ans = "0";
        cout << ans << endl;
    }

    return 0;
}