#pragma once
#include <vector>
#include <algorithm>
#include "../bit/bit-operations.hpp"

namespace nachia{

struct WaveletMatrix{
    using u64 = unsigned long long;
    struct WordBlock{ u64 table; int ptr; };
    int n;
    int S;
    int logS;
    std::vector<std::vector<WordBlock>> Table;

    WaveletMatrix() {}
  
    WaveletMatrix(int maxVal, std::vector<int> A){
        S = 1; logS = 0;
        n = A.size();
        while(S <= maxVal){ S *= 2; logS += 1; }
        Table.resize(logS);
        for(int d=logS-1; d>=0; d--){
            std::vector<WordBlock> tableBuf(n/64+2,{0,0});
            for(int i=0; i<n; i++) tableBuf[i/64].table |= (u64)((A[i]>>d) & 1) << (i%64);
            for(int i=1; i<=n/64+1; i++) tableBuf[i].ptr = tableBuf[i-1].ptr + Popcount(tableBuf[i-1].table);
            std::vector<int> buf;
            for(int b : {0,1<<d}) for(int a : A) if((a&(1<<d))==b) buf.push_back(a);
            std::swap(Table[d],tableBuf);
            std::swap(A,buf);
        }
    }
    int getLevelRank(int level, int p) const {
        int res = Table[level][p/64].ptr + Popcount(Table[level][p/64].table & ~(~(u64)0 << (p%64)));
        return res;
    }
    int getLeftPointer(int level, int p) const {
        return p - getLevelRank(level,p);
    }
    int getRightPointer(int level, int p) const {
        return n - Table[level].back().ptr + getLevelRank(level,p);
    }
    int get(int p) const {
        int res = 0;
        for(int d=logS-1; d>=0; d--){
            res *= 2;
            if(Table[d][p/64].table & ((u64)1 << (p%64))){
                res |= 1;
                p = getRightPointer(d,p);
            }
            else{
                p = getLeftPointer(d,p);
            }
        }
        return res;
    }
    int count(int l, int r, int val) const {
        for(int d=logS-1; d>=0; d--){
            if(val & (1<<d)){
                l = getRightPointer(d,l);
                r = getRightPointer(d,r);
            }
            else{
                l = getLeftPointer(d,l);
                r = getLeftPointer(d,r);
            }
        }
        return r - l;
    }
    int countRange(int l, int r, int rval) const {
        if(rval == 0) return 0;
        int ans = 0;
        for(int d=logS-1; d>=0; d--){
            if(rval & (1<<d)){
                ans += getLeftPointer(d,r) - getLeftPointer(d,l);
                l = getRightPointer(d,l);
                r = getRightPointer(d,r);
            } else{
                l = getLeftPointer(d,l);
                r = getLeftPointer(d,r);
            }
        }
        return ans;
    }
    int count(int l, int r, int lval, int rval) const {
        return countRange(l, r, rval) - countRange(l, r, lval);
    }
    int getKthSmallest(int l, int r, int k) const {
        int res = 0;
        for(int d=logS-1; d>=0; d--){
            res *= 2;
            int zerocnt = r - l;
            zerocnt -= getLevelRank(d,r);
            zerocnt += getLevelRank(d,l);
            if(k < zerocnt){
                l = getLeftPointer(d,l);
                r = getLeftPointer(d,r);
            }
            else{
                res += 1;
                k -= zerocnt;
                l = getRightPointer(d,l);
                r = getRightPointer(d,r);
            }
        }
        return res;
    }
    int getMaxNoGreaterThanRec(int l, int r, int k, int d) const {
        if(l >= r) return -1;
        if(d < 0) return 0;
        if(!(k & (1 << d))){
            return getMaxNoGreaterThanRec(getLeftPointer(d,l), getLeftPointer(d,r), k, d-1);
        } else {
            int q = getMaxNoGreaterThanRec(getRightPointer(d,l), getRightPointer(d,r), k-(1<<d), d-1);
            if(q != -1) return q + (1 << d);
            return getMaxNoGreaterThanRec(getLeftPointer(d,l), getLeftPointer(d,r), (1<<d)-1, d-1);
        }
    }
    int getMaxNoGreaterThan(int l, int r, int k) const {
        return getMaxNoGreaterThanRec(l, r, k, logS-1);
    }
};

}
