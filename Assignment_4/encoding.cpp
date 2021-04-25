#include<bits/stdc++.h>

using namespace std;

int used[260];
string encoded[260];
vector<pair<int, char> > v;
int nodeStep = 1;
string compressed;

struct node {
    string code;
    vector<pair<int, char> > prob;
    int tot = 0;
} tree[10000];

vector<node> steps[100];

void printChar(char c){
    if(c == ' ') cout << "Space";
    else if(c == '\n') cout << "Endline";
    else cout << c;
}

void build(int v, int j, node x){
    tree[v] = x;

    if(x.prob.size() == 1){
        if(x.code == "") encoded[x.prob[0].second] = x.code = "0";
        else encoded[x.prob[0].second] = x.code;
        return;
    }

    // Dividing massive into two parts
    vector<pair<int, char> > ss, ff;
    int res = 0;
    for(int i = 0; i < x.prob.size(); i++){
        if(res >= (x.tot + 1)/2) ss.push_back(x.prob[i]);
        else ff.push_back(x.prob[i]), res += x.prob[i].first;
    }

    steps[j].push_back({x.code + '1', ss, x.tot - res});
    steps[j].push_back({x.code + '0', ff, res});
    build(v*2+1, j+1, {x.code + '1', ss, x.tot - res});
    build(v*2, j+1, {x.code + '0', ff, res});
}

void printStep(int i){
    cout << "Step " << i << ".\n";

    for(int j = 0; j < steps[i].size(); j++){
        cout << "Node" << nodeStep++ << ": (" << steps[i][j].code << ") ";
        for(int k = 0; k < steps[i][j].prob.size(); k++){
            printChar(steps[i][j].prob[k].second);
            if(k != steps[i][j].prob.size()-1) cout << ", ";
        }
        cout << " - sum " << steps[i][j].tot << endl;
    }
    cout << endl;
}

int main(){
    // ios_base :: sync_with_stdio(0), cin.tie(0), cout.tie(0);
    for(int i = 0; i < 260; i++){
        used[i] = 0;
    }
    
    string s = "";
    string textchar;

    ifstream infile;
    infile.open("txt/text.txt");

    while(getline(infile, textchar)){
        s += textchar;
    }

    int n = s.size();
    for(int i = 0; i < n; i++){
        int x = s[i];
        used[x]++;
    }
    for(int i = 0; i < 260; i++){
        if(used[i])
            v.push_back({used[i], char(i)});
    }
    cout << "Current string: " << s << endl << endl;

    // Task1
    int check[260] = {0};
    sort(v.rbegin(), v.rend());
    for(int i = 0; i < v.size(); i++){
        if(!check[v[i].second]){
            printChar(v[i].second);
            cout << " = " << fixed << setprecision(3) << 1.0*v[i].first/n << endl;
            check[v[i].second] = 1;
        }
    }
    cout << endl;
    for(int i = 0; i < 260; i++){
        check[i] = 0;
    }

    // Task2
    build(1, 1, {"", v, n});
    int ind = 1;
    while(steps[ind].size() > 0){
        printStep(ind);
        ind++;
    }

    //writing to decompres.txt file
    string to_file = "";

    for(int i = 1; i < 10000; i++){
        if(!tree[i].prob.empty()){
            to_file += to_string(i) + ",";
            for(int j = 0; j < tree[i].prob.size(); j++){
                to_file.push_back(tree[i].prob[j].second);
                to_file += " ";
            }
            to_file += "\n";
        }
    }
    ofstream MyFile("txt/algorithm.txt");
    MyFile << to_file;
    MyFile.close();

    // Task4
    for(int i = 0; i < n; i++){
        compressed += encoded[s[i]];
    }
    cout << compressed << endl << endl;

    ofstream MyFile2("txt/encoded.txt");
    MyFile2 << compressed;
    MyFile2.close();

}