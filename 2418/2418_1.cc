#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<map>

using namespace std;


struct cmp_str{
    bool operator()(char const *a, char const *b){
        return std::strcmp(a, b) < 0;
    }
};

int main(){
    map<const char*, int, cmp_str> cnt;
    int sum = 0;
    char buffer[30];
    while(fgets(buffer, 30, stdin)){
        buffer[strlen(buffer) - 1] = '\0';
        char* name = (char*) malloc(strlen(buffer) * sizeof(char));
        strcpy(name, buffer);
        if(cnt.find(name) == cnt.end()) cnt[name] = 0;
        cnt[name] += 1;
        ++sum;
    }
    for(map<const char*, int>::iterator it = cnt.begin(); it != cnt.end(); ++it){
        printf("%s %.4f\n", it->first, float(it->second) / sum * 100);
    }

    return 0;
}