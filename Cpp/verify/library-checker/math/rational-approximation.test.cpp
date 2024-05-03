#define PROBLEM "https://judge.yosupo.jp/problem/rational_approximation"
#include "../../../Include/nachia/math/rational-number-search.hpp"
#include <iostream>

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    using std::cin;
    using std::cout;
    int T; cin >> T;
    for(int t=0; t<T; t++){
        long long N, x, y; cin >> N >> x >> y;
        auto ser = nachia::RationalNumberSearch(N);
        long long a = 0, b = 1, c = 1, d = 0;
        while(ser.hasNext()){
            auto f = ser.getNext();
            if(f.num * y == f.den * x){
                a = f.num; b = f.den;
                c = f.num; d = f.den;
                break;
            }
            if(f.num * y <= f.den * x){
                a = f.num; b = f.den;
                ser.give(true);
            } else {
                c = f.num; d = f.den;
                ser.give(false);
            }
        }
        cout << a << ' ' << b << ' ' << c << ' ' << d << '\n';
    }
    return 0;
}
