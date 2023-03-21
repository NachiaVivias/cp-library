#pragma once
#include <vector>

namespace nachia{

template<class Val>
struct DequeOperateAggregation{
private:

    std::vector<Val> A[2];
    std::vector<Val> Prod[2];

    void recalcProd(){
        Prod[0].resize(A[0].size() + 1);
        for(size_t i=0; i<A[0].size(); i++) Prod[0][i+1] = A[0][i] + Prod[0][i];
        Prod[1].resize(A[1].size() + 1);
        for(size_t i=0; i<A[1].size(); i++) Prod[1][i+1] = Prod[1][i] + A[1][i];
    }
public:

    DequeOperateAggregation(){
        recalcProd();
    }
    void pushFront(Val v){
        A[0].push_back(std::move(v));
        Prod[0].push_back(A[0].back() + Prod[0].back());
    }
    void pushBack(Val v){
        A[1].push_back(std::move(v));
        Prod[1].push_back(Prod[1].back() + A[1].back());
    }
    void popFront(){
        if(A[0].empty()){
            int lessHalf = A[1].size() / 2;
            A[0] = std::vector<Val>(A[1].rbegin() + lessHalf, A[1].rend());
            A[1] = std::vector<Val>(A[1].end() - lessHalf, A[1].end());
            recalcProd();
        }
        A[0].pop_back();
        Prod[0].pop_back();
    }
    void popBack(){
        if(A[1].empty()){
            int lessHalf = A[0].size() / 2;
            A[1] = std::vector<Val>(A[0].rbegin() + lessHalf, A[0].rend());
            A[0] = std::vector<Val>(A[0].end() - lessHalf, A[0].end());
            recalcProd();
        }
        A[1].pop_back();
        Prod[1].pop_back();
    }
    Val allProd(){ return Prod[0].back() + Prod[1].back(); }
};

} // namespace nachia
