#include<bits/stdc++.h>

using namespace std;

int used[260];
string encoded[260];
vector<pair<int, char> > v;

struct node {
    int id;
    string code;
    vector<pair<int, char> > prob;
    int tot = 0;
};

vector<node> steps[100];

void printChar(char c){
    if(c == ' ') cout << "Space";
    else if(c == '\n') cout << "Endline";
    else if(c == '\t') cout << "Endline";
    else cout << c;
}

void build(int j, node x){
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

    steps[j].push_back({x.id+1, x.code + '1', ss, x.tot - res});
    steps[j].push_back({x.id+2, x.code + '0', ff, res});
    build(j+1, {x.id+2, x.code + '1', ss, x.tot - res});
    build(j+1, {x.id+4, x.code + '0', ff, res});
}

void printStep(int i){
    cout << "Step " << i << ".\n";

    for(int j = 0; j < steps[i].size(); j++){
        cout << "Node" << steps[i][j].id << ": (" << steps[i][j].code << ") ";
        for(int k = 0; k < steps[i][j].prob.size(); k++){
            printChar(steps[i][j].prob[k].second);
            if(k != steps[i][j].prob.size()-1) cout << ", ";
        }
        cout << " - sum " << steps[i][j].tot << endl;
    }
    cout << endl;
}

int main(){
    string s = "";
    string textchar;

    ifstream infile;
    infile.open("Text.txt");

    while(getline(infile, textchar)){
        s += textchar;
    }
    
    for(int i = 0; i < 260; i++){
        used[i] = 0;
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
    build(1, {0, "", v, n});
    int ind = 1;
    while(steps[ind].size() > 0){
        printStep(ind);
        ind++;
    }

    // Task3
    cout << "symbol\t|\tprobability\t|\tcodeword\n";
    for(int i = 0; i < v.size(); i++){
        if(!check[v[i].second]){
            printChar(v[i].second);
            cout << "\t|\t" << 1.0*v[i].first/n << "\t\t|\t" << encoded[v[i].second] << endl;
            check[v[i].second] = 1;
        }
    }
    cout << endl;

    // Task4
    string compressed = "";
    for(int i = 0; i < n; i++){
        compressed += encoded[s[i]];
    }
    cout << compressed << endl << endl;

    // Task5
    int len = compressed.size();
    int sum1 = 0, sum2 = 0;
    for(int i = 0; i < n; i++){
        sum1 += used[s[i]] * encoded[s[i]].size();
        sum2 += used[s[i]];
    }
    for(int i =0; i < n; i++){
        cout << s[i] << '\t' << used[s[i]] << '\t' << encoded[s[i]] << "(" << encoded[s[i]].size() << ")" << endl;
    }
    cout << "Number of bits in the original text: " << n*8 << "bits\n";
    cout << "Number of bits in the compressed text: " << len << "bits\n";
    cout << "Compression ratio = " << fixed << setprecision(3) << 1.0*n*8/len <<  endl;
    cout << "Average code length = " << fixed << setprecision(3) << 1.0*sum1/sum2 << endl;
    cout << endl;

    ofstream MyFile("new.txt");

    MyFile << compressed;

    MyFile.close();
}