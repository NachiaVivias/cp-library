#define PROBLEM "https://judge.yosupo.jp/problem/predecessor_problem"
#include "../../../Include/nachia/set/word-size-tree.hpp"
#include "../../../Include/nachia/misc/fastio.hpp"

int main(){
    using nachia::cin;
    using nachia::cout;
    int N; cin >> N;
    int Q; cin >> Q;
    std::string s; cin >> s;
    auto structure = nachia::WordsizeTree(s);

    for(int i=0; i<Q; i++){
        int c, k; cin >> c >> k;
        if(c == 0) structure.insert(k);
        else if(c == 1) structure.erase(k);
        else if(c == 2) cout << (char)('0'+structure.count(k)) << '\n';
        else if(c == 3) cout << structure.noLessThan(k) << '\n';
        else if(c == 4) cout << structure.noGreaterThan(k) << '\n';
    }

    return 0;
}
