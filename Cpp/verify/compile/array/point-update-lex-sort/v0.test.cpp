#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"
#include "verifier.hpp"

#include <cstdio>
int main(){
    Verify v;
    v.push(5)
     .push(3)
     .push(7)
     .push(1)
     .push(5);

    for(int i=0; i<10; i++){
        v.mut(0, 8)
        .mut(1, 8)
        .mut(2, 4)
        .mut(3, 8)
        .mut(4, 8);

        v.mut(0, 5)
        .mut(1, 3)
        .mut(2, 7)
        .mut(3, 1)
        .mut(4, 5);
    }

    if(!v.verify()) return 0;

    int a,b; scanf("%d%d",&a,&b); printf("%d\n",a+b);
    return 0;
}
