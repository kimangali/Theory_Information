
#include<bits/stdc++.h>

using namespace std;

#define pii pair<int, int>
#define F first
#define S second
#define pb push_back
#define ll long long

const int inf = 2e9 + 1;
const int mod = 1e9 + 7;
const int N = 100 + 1;
int n;
int used[260];
string decoded[260];
vector<pair<double, char> > v;
struct node {
    string code;
    vector<pair<char, int> > prob;
} g[10000];

void build(int v, node x){
    if(x.prob.size() == 1){
        decoded[x.prob[0].F] = code;
        return;
    }

}

int main(){
    // ios_base :: sync_with_stdio(0), cin.tie(0), cout.tie(0);
    for(int i = 0; i < 260; i++){
        used[i] = 0;
    }
    string s = "Eerie eyes seen near lake.";
    int n = s.size();
    for(int i = 0; i < n; i++){
        int x = s[i];
        used[x]++;
    }
    vector<pair<double, char> > v;
    for(int i = 0; i < 260; i++){
        if(used[i]){
            v.pb({char(i), used[i]});
        }
    }
    sort(v.rbegin(), v.rend());
    n = v.size();
    build();
}
