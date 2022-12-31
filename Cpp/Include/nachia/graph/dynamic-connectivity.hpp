#pragma once



#include <vector>
#include <algorithm>
#include <cassert>


namespace nachia{

namespace dycon_internal{

template<
    class S,
    class Key,
    S op(S l, S r),
    S e()
>
struct SplayTreeByIdx{
    static SplayTreeByIdx *NIL;

    using MyType = SplayTreeByIdx;

    MyType *l = nullptr;
    MyType *r = nullptr;
    MyType *p = nullptr;
    S a = e();
    S mprod = e();
    Key key;

    SplayTreeByIdx(){
    }

    void prepareUp(){
        mprod = op(op(l->mprod, a), r->mprod);
    }
    MyType*& parentchild(){
        if(p == NIL) return NIL;
        if(p->l == this) return p->l;
        else return p->r;
    }
    void rotL(){
        auto t = p;
        if(t->p != NIL) t->parentchild() = this;
        p = t->p;
        t->p = this;
        if(l != NIL) l->p = t;
        t->r = l;
        l = t;
    }
    void rotR(){
        auto t = p;
        if(t->p != NIL) t->parentchild() = this;
        p = t->p;
        t->p = this;
        if(r != NIL) r->p = t;
        t->l = r;
        r = t;
    }
    void splay(){
        while(p != NIL){
            auto pc = p;
            auto ppc = pc->p;
            if(pc->l == this){
                if(ppc == NIL){ rotR(); }
                else if(ppc->l == pc){ pc->rotR(); rotR(); }
                else if(ppc->r == pc){ rotR(); rotL(); }
            }
            else{
                if(ppc == NIL){ rotL(); }
                else if(ppc->r == pc){ pc->rotL(); rotL(); }
                else if(ppc->l == pc){ rotL(); rotR(); }
            }
            if(ppc != NIL) ppc->prepareUp();
            if(pc != NIL) pc->prepareUp();
        }
        prepareUp();
    }
    static MyType* get_new_node(S a, Key key){
        MyType* nx = new MyType(*get_nil());
        nx->a = nx->mprod = a;
        nx->key = key;
        return nx;
    }
    S prod(){
        if(!is_root()) splay();
        return mprod;
    }

    static MyType* get_nil(){
        if(NIL) return NIL;
        NIL = new MyType();
        NIL->l = NIL->r = NIL->p = NIL;
        return NIL;
    }

    bool is_nil(){ return this == NIL; }
    bool is_root(){ return p->is_nil(); }

    MyType* front(){
        auto c = this;
        if(!c->is_root()) c->splay();
        while(!c->l->is_nil()){
            c = c->l;
        }
        c->splay();
        return c;
    }

    static MyType* merge(MyType* R1, MyType* R2){
        if(!R1->is_root()) R1->splay();
        if(!R2->is_root()) R2->splay();
        if(R1 == NIL) return R2;
        if(R2 == NIL) return R1;
        R2 = R2->front();
        R2->l = R1;
        R1->p = R2;
        R2->prepareUp();
        return R2;
    }
    static std::pair<MyType*, MyType*> split_l(MyType *R){
        if(!R->is_root()) R->splay();
        MyType* Rl = R->l;
        Rl->p = NIL;
        R->l = NIL;
        R->prepareUp();
        return std::make_pair(Rl, R);
    }
    static std::pair<MyType*, MyType*> split_r(MyType *R){
        if(!R->is_root()) R->splay();
        MyType* Rr = R->r;
        Rr->p = NIL;
        R->r = NIL;
        R->prepareUp();
        return std::make_pair(R, Rr);
    }

    MyType* search_flag(unsigned int mask){
        auto v = this;
        if((v->prod().flags & mask) == 0) return get_nil();
        while(true){
            if(v->a.flags & mask) break;
            if(v->l->mprod.flags & mask) v = v->l;
            else v = v->r;
        }
        v->splay();
        return v;
    }
};

template<
    class S,
    class Key,
    S op(S l, S r),
    S e()
>
    SplayTreeByIdx<S,Key,op,e> *
    SplayTreeByIdx<S,Key,op,e>
    ::NIL
    = get_nil();

} // namespace dycon_internal

} // namespace nachia

#include <unordered_map>

namespace nachia {

namespace dycon_internal {

template<
    class S,
    S op(S l, S r),
    S e(),
    S newnode()
>
struct EulerTourTree{
    struct new_Key {
        std::pair<int, int> edgeidx;
    };
    
    using SplayNode = SplayTreeByIdx<S, new_Key, op, e>;
    std::vector<SplayNode*> nodes;
    
    std::unordered_map<unsigned long long, SplayNode*> node_searcher;

    static unsigned long long edgeid_compress(int u, int v){
        return ((unsigned long long)u << 32) | v;
    }

    int num_nodes(){ return nodes.size(); }

    void delete_node(int u, int v){
        auto searcher_itr = node_searcher.find(edgeid_compress(u, v));
        delete(searcher_itr->second);
        node_searcher.erase(searcher_itr);
    }

    EulerTourTree(int n = 0){
        nodes.assign(n, SplayNode::get_nil());
    }

    std::pair<SplayNode*, SplayNode*> create_edge(int u, int v, S x){
        auto edgeuv = SplayNode::get_new_node(x, {{u,v}});
        node_searcher.insert_or_assign(edgeid_compress(u, v), edgeuv);
        auto edgevu = SplayNode::get_new_node(x, {{v,u}});
        node_searcher.insert_or_assign(edgeid_compress(v, u), edgevu);
        return std::make_pair(edgeuv, edgevu);
    }

    SplayNode* expose(int v){
        if(nodes[v]->is_nil()){
            nodes[v] = SplayNode::get_new_node(newnode(), {{v,v}});
        }
        nodes[v]->splay();
        return nodes[v];
    }

    SplayNode* evert(int v){
        auto Hv = expose(v);
        auto [l,r] = SplayNode::split_l(Hv);
        Hv = SplayNode::merge(r, l);
        return Hv;
    }
    // u will be the new root
    SplayNode* link(int u, int v, S x){
        auto Hv = evert(v);
        auto Hu = evert(u);
        assert(Hv->is_root());
        auto [Huv, Hvu] = create_edge(u, v, x);
        return SplayNode::merge(SplayNode::merge(Hu, Huv), SplayNode::merge(Hv, Hvu));
    }

    SplayNode* find_ettnode(int u, int v){
        if(u == v) return nodes[u];
        auto i = node_searcher.find(edgeid_compress(u, v));
        if(i == node_searcher.end()) return SplayNode::get_nil();
        return i->second;
    }

    std::pair<SplayNode*, SplayNode*> cut(int u, int v){
        evert(u);
        SplayNode* Hvu = find_ettnode(v, u);
        SplayNode* Huv = find_ettnode(u, v);
        auto [Hu, R2] = SplayNode::split_l(Huv);
        [[maybe_unused]] auto [edgeuv, R3] = SplayNode::split_r(Huv);
        auto [Hv, R4] = SplayNode::split_l(Hvu);
        [[maybe_unused]] auto [edgevu, Hu2] = SplayNode::split_r(Hvu);
        delete_node(u, v);
        delete_node(v, u);
        return std::make_pair(SplayNode::merge(Hu, Hu2), Hv);
    }

    S get(int u){
        return expose(u)->a;
    }
    S get(int u, int v){
        auto Huv = find_ettnode(u, v);
        if(!Huv->is_nil()) Huv->splay();
        return Huv->a;
    }
    void set(int u, S x){
        auto Hu = expose(u);
        Hu->a = x;
        Hu->prepareUp();
    }
    void set(int u, int v, S x){
        auto Huv = find_ettnode(u, v);
        Huv->splay();
        Huv->a = x;
        Huv->prepareUp();
    }

    S component_prod(int u){
        return expose(u)->prod(u);
    }

    bool is_connected(int u, int v){
        if(nodes[u]->is_nil()) return false;
        if(nodes[v]->is_nil()) return false;
        if(u == v) return true;
        auto Hu = expose(u);
        expose(v);
        return !(Hu->is_root());
    }
};

namespace DyConETT{
    using u32 = unsigned int;
    using u64 = unsigned long long;

    static const u32 FLAG_JUSTRANK = 2;
    static const u32 FLAG_EDGEMARK = 1;
    struct S{ u32 flags; u32 z; };
    S op(S l, S r){ return { l.flags | r.flags, l.z + r.z }; }
    S e(){ return { 0, 0 }; }
    S newnode(){ return { 0, 1 }; }
    using ETT = ::nachia::dycon_internal::EulerTourTree<S, op, e, newnode>;
}

} // namespace dycon_internal

} // namespace nachia



#include <unordered_set>
#include <unordered_map>
#include <list>

namespace nachia {

struct OnlineFullyDynamicConnectivityBySplayEtt{
private:

    int n = 0;
    int RanksCount = 0;
    std::vector<dycon_internal::DyConETT::ETT> etts;

    std::list<std::unordered_set<int>> edges2;
    using Edges2Iterator = std::list<std::unordered_set<int>>::iterator;
    std::vector<std::unordered_map<int, Edges2Iterator>> edges;
    
    using SplayNode = typename dycon_internal::DyConETT::ETT::SplayNode;

    void add_ranked_edge(int k, int u, int v){
        for(int t=0; t<2; t++){
            auto fu = edges[k].find(u);
            if(fu == edges[k].end()){
                edges2.push_front({});
                fu = edges[k].insert({ u, edges2.begin() }).first;
                etts[k].set(u, { dycon_internal::DyConETT::FLAG_EDGEMARK, 1 });
            }
            fu->second->insert(v);
            std::swap(u,v);
        }
    }
    void erase_ranked_edge(int k, int u, int v){
        for(int t=0; t<2; t++){
            auto fu = edges[k].find(u);
            fu->second->erase(v);
            if(fu->second->empty()){
                etts[k].set(u, { 0, 1 });
                edges2.erase(fu->second);
                edges[k].erase(fu);
            }
            std::swap(u,v);
        }
    }

    bool check_ranked_edge(int k, int u, int v){
        auto fu = edges[k].find(u);
        if(fu == edges[k].end()) return false;
        return fu->second->find(v) != fu->second->end();
    }

    int get_any_edge(int k, int u){
        auto fu = edges[k].find(u);
        if(fu == edges[k].end()) return -1;
        return *(fu->second->begin());
    }

    std::pair<int,int> replace(int k, int u, int v){
        if(k >= RanksCount) return {-1,-1};
        if(!etts[k].is_connected(u, v)) return {-1,-1};
        auto [Hu, Hv] = etts[k].cut(u, v);
        auto [s,t] = replace(k+1,u,v);
        if(s != -1){
            etts[k].link(s, t, { 0, 0 });
            return {s,t};
        }
        if(Hu->prod().z > Hv->prod().z){
            std::swap(u, v);
            std::swap(Hu, Hv);
        }
        while(Hu->prod().flags & dycon_internal::DyConETT::FLAG_JUSTRANK){
            Hu = Hu->search_flag(dycon_internal::DyConETT::FLAG_JUSTRANK);
            auto [eu, ev] = Hu->key.edgeidx;
            etts[k].set(eu, ev, { 0, 0 });
            etts[k].set(ev, eu, { 0, 0 });
            etts[k+1].link(eu, ev, { dycon_internal::DyConETT::FLAG_JUSTRANK, 0 });
            Hu->splay();
        }
        while(Hu->prod().flags & dycon_internal::DyConETT::FLAG_EDGEMARK){
            Hu = Hu->search_flag(dycon_internal::DyConETT::FLAG_EDGEMARK);
            int x = Hu->key.edgeidx.first;
            while(edges[k].count(x)){
                int y = get_any_edge(k, x);
                if(etts[k].is_connected(x, y)){
                    erase_ranked_edge(k, x, y);
                    add_ranked_edge(k+1, x, y);
                    continue;
                }
                erase_ranked_edge(k, x, y);
                etts[k].link(x, y, { dycon_internal::DyConETT::FLAG_JUSTRANK, 0 });
                return {x,y};
            }
            Hu->splay();
        }
        return {-1,-1};
    }
public:

    OnlineFullyDynamicConnectivityBySplayEtt(int new_n){
        n = new_n;
        RanksCount = 0; { int vn = n; while(vn){ RanksCount++; vn /= 2; } }
        etts.resize(RanksCount);
        for(auto& ett : etts){
            ett = dycon_internal::DyConETT::ETT(n);
        }
        edges.resize(RanksCount);
    }

    struct ForestCutQuery{
        std::pair<int, int> forest_cut;
        std::pair<int, int> forest_link;
    };

    std::pair<int, int> link(int u, int v){
        if(etts[0].is_connected(u, v)){
            add_ranked_edge(0, u, v);
            return {-1,-1};
        }
        etts[0].link(u, v, { dycon_internal::DyConETT::FLAG_JUSTRANK, 0 });
        return {u,v};
    }
    
    ForestCutQuery cut(int u, int v){
        if(etts[0].find_ettnode(u, v)->is_nil()){
            for(int k=0; k<RanksCount; k++){
                if(check_ranked_edge(k, u, v)){
                    erase_ranked_edge(k, u, v);
                    break;
                }
            }
            return { {-1,-1}, {-1,-1} };
        }
        return { {u,v}, replace(0, u, v) };
    }

    bool is_connected(int u, int v){
        if(u == v) return true;
        return etts[0].is_connected(u, v);
    }
};


} // namespace nachia

