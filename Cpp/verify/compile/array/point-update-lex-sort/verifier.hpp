#include "../../../../Include/nachia/array/point-update-lex-sort.hpp"

#include <algorithm>

class Verify{
public:
    struct K {
        int e;
        explicit K(int k) : e(k) {}
        bool operator<(const K& r){ return e<r.e; }
    };
    using DS = nachia::PointUpdateLexSort<K>;
    using Iter = DS::Iter;
    std::vector<int> init;
    std::vector<int> mutpos;
    std::vector<int> mutval;
    std::vector<int> ans;
    Verify& push(int v){
        init.push_back(v);
        return *this;
    }
    Verify& mut(int i, int j){
        mutpos.push_back(i);
        mutval.push_back(j);
        return *this;
    }
    bool verify(){
        DS ds;
        std::vector<K> initK;
        for(int i : init) initK.emplace_back(i);
        ds = DS(std::move(initK));
        std::vector<int> real = init;
        std::vector<std::vector<int>> vecs;
        std::vector<Iter> iters;
        vecs.push_back(real);
        iters.push_back(ds.last());
        for(std::size_t i=0; i<mutpos.size(); i++){
            real[mutpos[i]] = mutval[i];
            vecs.push_back(real);
            iters.push_back(ds.mutate(mutpos[i], K(mutval[i])));
        }
        ds.proc();
        if(ds.count() != (int)vecs.size()) return false;
        int cnt = ds.count();
        int cntpos = ds.maxSortedPos() + 1;
        std::vector<int> tmp(cntpos, -1);

        for(int i=0; i<cnt; i++){
            int t = *iters[i];
            // range?
            if(t < 0 || ds.maxSortedPos() < t) return false;
            // same?
            if(tmp[t] >= 0 && vecs[tmp[t]] != vecs[i]) return false;
            tmp[t] = i;
        }

        // if compressed
        for(int i=0; i<cntpos; i++) if(tmp[i] < 0) return false;

        // if sorted
        for(int i=0; i<cntpos-1; i++) if(!(vecs[tmp[i]] < vecs[tmp[i+1]])) return false;
        return true;
    }
};
