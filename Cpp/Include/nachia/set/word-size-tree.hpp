#pragma once

#include <vector>
#include <string>

namespace nachia{

struct WordsizeTree{
    using Word = unsigned long long;
    static constexpr int W = 64;
    int N;
    std::vector<std::vector<Word>> A;
    static int highBit(Word x){
        if(x == 0) return 0;
        return W-1 - __builtin_clzll(x);
    }
    static int lowBit(Word x){
        if(x == 0) return W;
        return __builtin_ctzll(x);
    }
    WordsizeTree(int length){
        N = length;
        int n = length;
        do {
            std::vector<Word> a(n/W+1,0);
            A.emplace_back(std::move(a));
            n /= W;
        } while(n);
    }
    WordsizeTree(const std::string& binStr = ""){
        N = binStr.size();
        int n = N;
        {
            std::vector<Word> a(n/W+1);
            for(int i=0; i<n; i++) if(binStr[i] == '1'){
                a[i/W] |= (Word)1 << (i%W);
            }
            A.emplace_back(std::move(a));
            n /= W;
        }
        while(n){
            std::vector<Word> a(n/W+1,0);
            for(int i=0; i<=n; i++){
                if(A.back()[i]) a[i/W] |= (Word)1 << (i%W);
            }
            A.emplace_back(std::move(a));
            n /= W;
        }
    }
    void insert(int x){
        for(auto& a : A){
            a[x/W] |= (Word)1 << (x % W);
            x /= W;
        }
    }
    void erase(int x){
        for(auto& a : A){
        a[x/W] &= ~((Word)1 << (x % W));
        if(a[x/W]) return;
        x /= W;
        }
    }
    int count(int x) const {
        return (int)((A[0][x/W] >> (x%W)) & 1);
    }
    int noLessThan(int x) const {
        if(x < 0) x = 0;
        if(N <= x) return N;
        int d = 0, i = x;
        while(true){
            if(d >= (int)A.size()) return N;
            if(i/W >= (int)A[d].size()) return N;
            Word m = A[d][i/W] & ((~(Word)0) << (i%W));
            if(!m){ d++; i /= W; i++; }
            else{
                int to = lowBit(m);
                i = i/W*W + to;
                if(d == 0) break;
                i *= W;
                d--;
            }
        }
        return i;
    }
    int noGreaterThan(int x) const {
        if(x < 0) return -1;
        if(N <= x) x = N-1;
        int d = 0, i = x;
        while(true){
            if(i < 0) return -1;
            if(d >= (int)A.size()) return -1;
            Word m = A[d][i/W] & ~((~(Word)1) << (i%W));
            if(!m){ d++; i /= W; i--; }
            else{
                int to = highBit(m);
                i = i/W*W + to;
                if(d == 0) break;
                i *= W;
                i += W-1;
                d--;
            }
        }
        return i;
    }
};

} // namespace nachia
