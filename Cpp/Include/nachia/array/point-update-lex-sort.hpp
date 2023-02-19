#include "../misc/sorting.hpp"
#include "../array/csr-array.hpp"
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <cassert>

namespace nachia {

template<class T>
struct PointUpdateLexSort{
public:
    using MyType = PointUpdateLexSort;
private:
    int k = 0;
    std::vector<T> valbuf;
    std::vector<int> mutpos;
    std::vector<int> sPos;
    int xsPos = 0;
    struct DfsNode{
        std::vector<int> TBuf, TList, TPos, VBuf;
        PointUpdateLexSort *p;
        static void ToInt(std::vector<int>::iterator dest, std::vector<std::pair<int,int>> pairs, int z1, int z2){
            int n = pairs.size();
            std::vector<int> I = nachia::BucketSortPermutation(pairs.begin(), pairs.end(), [&](std::pair<int,int>& x){ return x.second; }, z2-1);
            I = nachia::BucketSort(std::move(I), [&](int i){ return pairs[i].first; }, z1-1);
            dest[I[0]] = 0;
            for(int i=1; i<n; i++) dest[I[i]] = dest[I[i-1]] + (pairs[I[i-1]] < pairs[I[i]] ? 1 : 0);
        }
        void MakeTBuf(PointUpdateLexSort* pc){
            p = pc;
            int n = p->valbuf.size();
            TBuf.resize(n);
            TList.resize(n);
            TPos.resize(p->k + 2, 1);
            VBuf.resize(n);
            TPos[0] = TPos[1] = 0;
            for(auto& m : p->mutpos) TPos[m+2]++;
            for(int i=0; i<=p->k; i++) TPos[i+1] += TPos[i];
            for(int i=0; i<p->k; i++) TList[TPos[i+1]++] = i;
            for(int i=p->k; i<n; i++) TList[TPos[p->mutpos[i-p->k]+1]++] = i;
        }
        void dfs(int l, int r){
            if(l+1 == r){
                auto I = TBuf.begin();
                int sz = TPos[r] - TPos[l];
                for(int i=0; i<sz; i++) I[i] = i + TPos[l];
                std::sort(I, I + sz, [&](int l, int r){ return p->valbuf[TList[l]] < p->valbuf[TList[r]]; });
                int sp = VBuf[I[0]] = 0;
                for(int i=1; i<sz; i++){
                    VBuf[I[i]] = sp += (p->valbuf[TList[I[i-1]]] < p->valbuf[TList[I[i]]] ? 1 : 0);
                }
                return;
            }
            int m = (l+r)/2;
            dfs(l, m); dfs(m, r);
            int pql = TPos[l], pqr = TPos[m];
            int pqlz = TPos[l+1], pqrz = TPos[m+1];
            int bufi = TPos[l];
            std::vector<std::pair<int, int>> tmp;
            TBuf[bufi++] = TList[pqr];
            tmp.emplace_back(VBuf[pql++], VBuf[pqr++]);
            while(pql < pqlz || pqr < pqrz){
                bool choosel = true;
                if(pql == pqlz) choosel = false;
                else if(pqr == pqrz) choosel = true;
                else choosel = TList[pql] < TList[pqr];
                if(choosel){
                    TBuf[bufi] = TList[pql];
                    tmp.emplace_back(VBuf[pql], tmp.back().second);
                    pql++;
                }
                else{
                    TBuf[bufi] = TList[pqr];
                    tmp.emplace_back(tmp.back().first, VBuf[pqr]);
                    pqr++;
                }
                bufi++;
            }
            ToInt(VBuf.begin() + TPos[l], std::move(tmp), pqlz-TPos[l], pqrz-TPos[m]);
            TPos[l+1] = bufi;
            for(int i=TPos[l]; i<bufi; i++) TList[i] = TBuf[i];
        }
    };
public:
    struct Iter {
        const MyType *p;
        int i;
        int operator*() const { return p->sPos[i]; }
    };
    PointUpdateLexSort(){}
    PointUpdateLexSort(std::vector<T> A){
        k = A.size();
        valbuf = std::move(A);
    }
    Iter mutate(int pos, T val){
        assert(0 <= pos); assert(pos < k);
        valbuf.push_back(std::move(val));
        mutpos.emplace_back(pos);
        return Iter{ this, (int)mutpos.size() };
    }
    int count() const { return (int)mutpos.size() + 1; }
    int maxSortedPos() const { return xsPos; }
    Iter last() const { return Iter{ this, count()-1 }; }
    void proc(){
        auto v = DfsNode();
        v.MakeTBuf(this);
        v.dfs(0, k);
        v.VBuf.resize(count());
        sPos = std::move(v.VBuf);
        xsPos = *std::max_element(sPos.begin(), sPos.end());
    }
};

} // namespace nachia
