#pragma once
#include <algorithm>
#include <utility>
#include <cassert>
#include <vector>

namespace nachia{

struct BbstListVoidPayload {
    static BbstListVoidPayload identity(){ return {}; }
    BbstListVoidPayload operator+(BbstListVoidPayload) const { return {}; }
};

struct BbstListVoidKey {
    bool operator<(BbstListVoidKey) const { return false; }
};

template<class Key, class Payload>
struct BbstList {
public:

struct FNode;
struct Node;

struct FNode {
    struct Node *p;
    unsigned int z;
    FNode(unsigned int _z) : p(nullptr), z(_z) {}
    struct Node *re(){ return (Node*)this; }
};

struct Iterator {
    using Item = typename Node::Item;
    FNode* p = nullptr;
    bool isEnd() const { return p->z == 0; }
    unsigned int index() const { return p->z ? p->re()->index() : p->p->z; }
    const Item& operator*() const { return p->re()->kv; }
    const Item* operator->() const { return &p->re()->kv; }
    Item getOr(Item ifEnd) const { return isEnd() ? ifEnd : (* *this); }
    bool operator==(Iterator r) const { return p == r.p; }
    bool operator!=(Iterator r) const { return p != r.p; }
    bool operator<(Iterator r) const { return index() < r.index(); }
    bool operator>(Iterator r) const { return index() > r.index(); }
    bool operator<=(Iterator r) const { return index() <= r.index(); }
    bool operator>=(Iterator r) const { return index() >= r.index(); }
    Iterator& operator++(){ p = p->re()->next(); return *this; }
    Iterator& operator--(){ p = (isEnd() ? p->p->back() : p->re()->prev()); return *this; }
    Iterator operator++(int) { auto res = *this; ++*this; return res; }
    Iterator operator--(int) { auto res = *this; --*this; return res; }
};

struct Node : public FNode {
    static inline Node* NIL;
    unsigned int h;
    struct Item { Key key; Payload val; } kv;
    Payload sum;
    Node *l = nullptr;
    Node *r = nullptr;
    Node()
        : FNode(0), h(0)
        , kv({Key(),Payload::identity()})
        , sum(Payload::identity()) {}
    Node(Key _key, Payload p)
        : FNode(1), h(1)
        , kv({std::move(_key),p})
        , sum(p) {}
    static Node* GetNil(){
        if(!NIL){
            NIL = new Node();
            NIL->l = NIL->r = NIL->p = NIL;
        }
        return NIL;
    }
    static Node* NewNode(Key key, Payload val){
        GetNil();
        Node *res = new Node(key, val);
        res->l = res->r = res->p = NIL;
        res->z = 1;
        return res;
    }
    static Node* Construct(std::vector<std::pair<Key, Payload>> val){
        for(size_t i=0; i+1<val.size(); i++) assert(!(val[i+1].first < val[i].first));
        auto s = [&](auto& s, int l, int r) -> Node* {
            if(l == r) return GetNil();
            int m = (l + r) / 2;
            auto buf = NewNode(std::move(val[m].first), std::move(val[m].second));
            buf->setChildren(s(s,l,m), s(s,m+1,r));
            return buf;
        };
        return s(s, 0, (int)val.size());
    }
    void aggregate(){
        sum = kv.val;
        h = 1; this->z = 1;
        sum = l->sum + sum; this->z += l->z; h = std::max(h, l->h + 1);
        sum = sum + r->sum; this->z += r->z; h = std::max(h, r->h + 1);
    }
    void setChildren(Node* lc, Node* rc){
        l = lc; if(lc != NIL) lc->p = this;
        r = rc; if(rc != NIL) rc->p = this;
        aggregate();
    }
    // if the 2 children have unbalanced height, fix them
    Node* rebalance(){
        auto c = this;
        auto cl = c->l;
        auto cr = c->r;
        if(cl->h + 1 < cr->h){
            auto crl = cr->l;
            auto crr = cr->r;
            if(crl->h <= crr->h){
                cr->p = c->p;
                c->setChildren(cl, crl);
                cr->setChildren(c, crr);
                return cr;
            } else{
                crl->p = c->p;
                c->setChildren(cl, crl->l);
                cr->setChildren(crl->r, crr);
                crl->setChildren(c, cr);
                return crl;
            }
        }
        else if(cl->h > cr->h + 1){
            auto cll = cl->l;
            auto clr = cl->r;
            if(clr->h <= cll->h){
                cl->p = c->p;
                c->setChildren(clr, cr);
                cl->setChildren(cll, c);
                return cl;
            } else{
                clr->p = c->p;
                c->setChildren(clr->r, cr);
                cl->setChildren(cll, clr->l);
                clr->setChildren(cl, c);
                return clr;
            }
        }
        aggregate();
        return this;
    }
    // call rebalance from this node to the root
    Node* rebalanceToRoot(){
        auto c = this;
        while(c->p != NIL){
            auto cp = c->p;
            (cp->l == c ? cp->l : cp->r) = c->rebalance();
            c = cp;
        }
        return c->rebalance();
    }
    Node* next(){
        auto c = this;
        if(c->r != NIL){
            c = c->r;
            while(c->l != NIL) c = c->l;
            return c;
        }
        while(c->p->r == c) c = c->p;
        return c->p;
    }
    Node* prev(){
        auto c = this;
        if(c->l != NIL){
            c = c->l;
            while(c->r != NIL) c = c->r;
            return c;
        }
        while(c->p->l == c) c = c->p;
        return c->p;
    }
    unsigned int index(){
        auto c = this;
        if(c == NIL) return ~0u;
        unsigned int res = c->l->z;
        while(c->p != NIL){
            auto cp = c->p;
            if(cp->r == c) res += cp->l->z + 1;
            c = cp;
        }
        return res;
    }
    // kth node under this, returns alt if not exist
    Node* kth(unsigned int idx, Node* alt){
        if(idx >= this->z) return alt;
        auto c = this;
        while(true){
            if(c->l->z > idx) c = c->l;
            else if(c->l->z == idx) break;
            else{ idx -= c->l->z + 1; c = c->r; }
        }
        return c;
    }
    // most left no-less-than k under this, and the next
    std::pair<Node*, Node*> lBound(Key k){
        Node *ql = NIL;
        Node *qr = NIL;
        auto c = this;
        while(c != NIL){
            if(c->kv.key < k){ ql = c; c = c->r; }
            else{ qr = c; c = c->l; }
        }
        return std::make_pair(ql, qr);
    }
    // most left grater-than k under this, and the next
    std::pair<Node*, Node*> uBound(Key k){
        Node *ql = NIL;
        Node *qr = NIL;
        auto c = this;
        while(c != NIL){
            if(k < c->kv.key){ qr = c; c = c->l; }
            else{ ql = c; c = c->r; }
        }
        return std::make_pair(ql, qr);
    }
    // update the payload and aggregate upto root
    void set(Payload val){
        kv.val = std::move(val);
        auto c = this;
        while(c != NIL){ c->aggregate(); c = c->p; }
    }
    static Node* rootOf(Node* p){
        while(p->p != NIL) p = p->p;
        return p;
    }
    static Payload rangeSumR(Node* l){
        assert(l != NIL);
        Payload res = l->kv.val + l->r->sum;
        auto lp = l->p;
        while(lp != NIL){
            if(lp->l == l) res = res + lp->kv.val + lp->r->sum;
            l = lp; lp = l->p;
        }
        return res;
    }
    static Payload rangeSum(Node* l, Node* r){
        assert(l != NIL);
        assert(r != NIL);
        assert(l != r);
        assert(rootOf(l) == rootOf(r));
        assert(l->index() <= r->index());
        r = r->prev();
        if(l == r) return l->kv.val;
        Payload lsum = l->kv.val;
        Payload rsum = r->kv.val;
        while(l != r){
            if(l->h < r->h){
                Node* lp = l->p;
                lsum = lsum + l->r->sum;
                while(lp->l != l){ l = lp; lp = l->p; }
                if(lp == r) return lsum + rsum;
                lsum = lsum + lp->kv.val;
                l = lp;
            } else {
                Node* rp = r->p;
                rsum = r->l->sum + rsum;
                while(rp->r != r){ r = rp; rp = r->p; }
                if(rp == l) return lsum + rsum;
                rsum = rp->kv.val + rsum;
                r = rp;
            }
        }
        return lsum + rsum;
    }
    template<class Pred>
    static Node* maxRight(Node* l, Pred& pred){
        Payload q = l->kv.val;
        if(!pred(q)) return l;
        while(true){
            Payload q2 = q + l->r->sum;
            if(!pred(q2)) break;
            l = l->p;
            if(l == NIL) return NIL;
            q = q2 + l->kv.val;
            if(!pred(q)) return l;
        }
        auto c = l->r;
        while(c != NIL){
            Payload q2 = q + c->l->sum;
            if(!pred(q2)){ c = c->l; continue; }
            q = q2 + c->kv.val;
            if(!pred(q)) return c;
            c = c->r;
        }
        return NIL;
    }
    void clear(){
        if(this == NIL) return;
        l->clear(); if(l != NIL) delete(l);
        r->clear(); if(r != NIL) delete(r);
    }
    Node* insert(Node* x){
        if(this == NIL) return x;
        auto q = lBound(x->kv.key);
        if(q.first != NIL && q.first->r == NIL){
            q.first->setChildren(q.first->l, x);
            return q.first->rebalanceToRoot();
        }
        q.second->setChildren(x, q.second->r);
        return q.second->rebalanceToRoot();
    }
    Node* erase(Node* ql, Node* qr){
        auto qlp = ql->p;
        Node* res = NIL;
        if(ql->r == NIL){
            auto qll = ql->l;
            if(qll != NIL) qll->p = qlp;
            if(qlp != NIL) (qlp->l == ql ? qlp->l : qlp->r) = qll;
            res = (qlp == NIL ? qll : qlp->rebalanceToRoot());
        } else {
            assert(qr != NIL);
            assert(qr->l == NIL);
            auto qrp = qr->p;
            auto qrr = qr->r;
            if(qlp != NIL) (qlp->l == ql ? qlp->l : qlp->r) = qr;
            qr->p = qlp;
            qr->l = ql->l;
            if(qr->l != NIL) qr->l->p = qr;
            if(ql->r == qr){
                qr->aggregate();
                res = qr->rebalanceToRoot();
            } else {
                (qrp->l == qr ? qrp->l : qrp->r) = qrr;
                if(qrr != NIL) qrr->p = qrp;
                qr->r = ql->r;
                qr->r->p = qr;
                qr->aggregate();
                res = qrp->rebalanceToRoot();
            }
        }
        ql->l = ql->r = ql->p = NIL;
        ql->aggregate();
        return res;
    }
    Node* back(){
        auto c = this;
        while(c->r != NIL) c = c->r;
        return c;
    }
};

    BbstList() : rt(0) { rt.p = Node::GetNil(); }
    BbstList(std::vector<std::pair<Key, Payload>> init) : rt(0) { rt.p = Node::Construct(std::move(init)); }
    Iterator end(){ return {&rt}; }
    Iterator begin(){
        FNode *p = rt.p->z ? rt.p->kth(0,nullptr) : &rt;
        return {p};
    }
    void clear(){
        if(rt.p != Node::GetNil()){
            rt.p->clear();
            delete(rt.p);
            rt.p = Node::NIL;
        }
    }
    ~BbstList(){ clear(); }
    int size() const { return rt.p->z; }
    bool empty() const { return rt.p == Node::NIL; }
    Payload sum(Iterator l, Iterator r, Payload ifnull){
        if(l == r) return ifnull;
        if(r == end()) return Node::rangeSumR(l.p->re());
        return Node::rangeSum(l.p->re(), r.p->re());
    }
    Iterator kth(unsigned int idx){
        auto p = root()->kth(idx, nullptr);
        return p ? Iterator{p} : end();
    }
    Iterator lBound(Key key){
        auto p = root()->lBound(std::move(key)).second;
        return p == Node::NIL ? end() : Iterator{p};
    }
    Iterator uBound(Key key){
        auto p = root()->uBound(std::move(key)).second;
        return p == Node::NIL ? end() : Iterator{p};
    }
    Iterator lBoundL(Key key){
        auto p = root()->lBound(std::move(key)).first;
        return p == Node::NIL ? end() : Iterator{p};
    }
    Iterator uBoundL(Key key){
        auto p = root()->uBound(std::move(key)).first;
        return p == Node::NIL ? end() : Iterator{p};
    }
    Iterator find(Key key){
        auto p = lBound(key);
        return (p.isEnd() || key < p->key) ? end() : p;
    }
    Iterator insert(Key k, Payload v){
        auto x = Node::NewNode(std::move(k), std::move(v));
        rt.p = root()->insert(x);
        return Iterator{ x };
    }
    Iterator erase(Iterator i){
        if(i == end()) return i;
        auto nx = i; ++nx;
        auto nxv = nx == end() ? Node::NIL : nx.p->re();
        rt.p = root()->erase(i.p->re(), nxv);
        delete(i.p->re());
        return nx;
    }
    Iterator changeKey(Iterator i, Key k){
        if(i == end()) return i;
        auto nx = i; ++nx;
        auto ptr = i.p->re();
        auto nxv = nx == end() ? Node::NIL : nx.p->re();
        rt.p = root()->erase(i.p->re(), nxv);
        ptr->kv.key = std::move(k);
        rt.p = root()->insert(i.p->re());
        return i;
    }
    void set(Iterator pos, Payload val){ pos.p->re()->set(val); }
    void output(){ root()->output(); }
    
private:
    FNode rt;
    Node* root(){ return rt.p->re(); }
};

} // namespace nachia
