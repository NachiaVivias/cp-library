#pragma once
#include <vector>
#include <algorithm>
#include <string>
#include <cassert>

namespace nachia{

namespace nachia_internal{

using u32 = unsigned int;

struct Elem{
    unsigned long long b[4] = {};
    static constexpr u32 Cap = 32;
    void operator<<=(u32 x) noexcept {
        if(x & 128){ b[3] = b[1]; b[2] = b[0]; b[2] = b[1] = 0; }
        if(x & 64){ b[3] = b[2]; b[2] = b[1]; b[1] = b[0]; b[0] = 0; }
        x %= 64;
        if(x == 0) return;
        u32 y = 64 - x;
        b[3] = b[3] << x | b[2] >> y;
        b[2] = b[2] << x | b[1] >> y;
        b[1] = b[1] << x | b[0] >> y;
        b[0] = b[0] << x;
    }
    void operator>>=(u32 x) noexcept {
        if(x & 128){ b[0] = b[2]; b[1] = b[3]; b[2] = b[3] = 0; }
        if(x & 64){ b[0] = b[1]; b[1] = b[2]; b[2] = b[3]; b[3] = 0; }
        x %= 64;
        if(x == 0) return;
        u32 y = 64 - x;
        b[0] = b[0] >> x | b[1] << y;
        b[1] = b[1] >> x | b[2] << y;
        b[2] = b[2] >> x | b[3] << y;
        b[3] = b[3] >> x;
    }
    void operator|=(const Elem& x) noexcept {
        b[0] |= x.b[0]; b[1] |= x.b[1]; b[2] |= x.b[2]; b[3] |= x.b[3];
    }
    void operator&=(u32 h) noexcept {
        int d = 0;
        while(h >= 64){ d++; h--; }
        if(d < 4) b[d++] &= ~(~0ull << h);
        for(; d<4; d++) b[d++] = 0;
    }
    static Elem merge(Elem l, Elem r, u32 lz) noexcept { lz <<= 3; r <<= lz; r |= l; return r; }
    static std::pair<Elem, Elem> split(Elem l, u32 lz) noexcept { lz <<= 3; auto r = l; r >>= lz; l &= lz; return std::make_pair(l, r); }
    void append(u32 p, char c) noexcept { b[p>>3] |= (unsigned long long)c << ((p&7)<<3); }
    char access(u32 p) const noexcept { return (char)((b[p>>3] >> ((p&7)<<3)) & 255); }
};

struct Node;
struct LeafNode;
struct MidNode;
struct SharedPtrNodeObj;

struct Np{
    Node *p;
    void release();
    Np() : p(nullptr) {}
    Np(const MidNode& src);
    Np(const LeafNode& src);
    Np(const Np& new_l, const Np& new_r);
    Np(const Np& src);
    Np(Np&& src) noexcept : p(src.p){ src.p = nullptr; }
    ~Np(){ release(); }
    Node& operator*(){ return *p; }
    const Node* operator->() const noexcept { return p; }
    Node* operator->() noexcept { return p; }
    operator bool() const noexcept { return p; }
    bool operator!() const noexcept { return !p; }
    Np& operator=(const Np& src);
    Np& operator=(Np&& src);
    MidNode* mid() const noexcept { return (MidNode*)p; }
    LeafNode* leaf() const noexcept { return (LeafNode*)p; }
};

struct Node{
    static constexpr const int RANK_SH = 0;
    u32 state;
    u32 refcnt;
    size_t size;
    u32 rank() const noexcept { return state>>RANK_SH; }
    bool isLeaf() const noexcept { return state == 0; }
    Node(u32 new_state, size_t new_size) : state(new_state), refcnt(1), size(new_size) {}
    ~Node(){}
    void dump(std::string& o) const;
};

struct MidNode : public Node {
    Np l;
    Np r;
    MidNode(const MidNode& src) : Node(src), l(src.l) , r(src.r){}
    MidNode(const Np& new_l, const Np& new_r)
        : Node((std::max(new_l->rank(), new_r->rank()) + 1) << RANK_SH, new_l->size + new_r->size)
        , l(new_l)
        , r(new_r) {}
    ~MidNode(){}
};

struct LeafNode : public Node {
    Elem a;
    LeafNode(Elem elem, size_t sz) : Node(0, sz), a(elem) {}
    ~LeafNode(){}
};

void Node::dump(std::string& o) const {
    if(isLeaf()){ for(size_t j=0; j<size; j++) o.push_back(((LeafNode*)this)->a.access(j)); }
    else{ ((MidNode*)this)->l->dump(o); ((MidNode*)this)->r->dump(o); }
}


void Np::release(){
    if(!p) return;
    if(!--p->refcnt){ if(p->isLeaf()) delete((LeafNode*)p); else delete((MidNode*)p); }
    p = nullptr;
}
Np::Np(const MidNode& src) : p(new MidNode(src)) {}
Np::Np(const LeafNode& src) : p(new LeafNode(src)) {}
Np::Np(const Np& new_l, const Np& new_r) : p(new MidNode(new_l, new_r)) {}
Np::Np(const Np& src) : p(src.p){ if(p){ p->refcnt++; } }
Np& Np::operator=(const Np& src){ release(); p = src.p; if(p){ p->refcnt++; } return *this; }
Np& Np::operator=(Np&& src){ release(); p = src.p; src.p = nullptr; return *this; }

struct BST{
static Np mergeDirect(const Np& l, const Np& r);
static Np merge(const Np& l, const Np& r);
static Np mergeOnL(const Np& l, const Np& r);
static Np mergeOnR(const Np& l, const Np& r);
static std::pair<Np, Np> split(const Np& c, size_t where);
static Np splitL(const Np& c, size_t where);
static Np splitR(const Np& c, size_t where);
static Np subarray(const Np& c, size_t l, size_t r){ return (bool)c ? splitR(splitL(c, r), l) : Np(); }
static Np construct(const std::string& s);
static Np leafmerge(const Np& l, const Np& r);
};

Np BST::mergeDirect(const Np& l, const Np& r){
    if(l->rank() > r->rank() + 1){
        auto ll = l.mid()->l;
        auto lr = l.mid()->r;
        if(ll->rank() < lr->rank()) return Np(Np(ll, lr.mid()->l), Np(lr.mid()->r, r));
        return Np(ll, Np(lr, r));
    }
    if(l->rank() + 1 < r->rank()){
        auto rl = r.mid()->l;
        auto rr = r.mid()->r;
        if(rl->rank() > rr->rank()) return Np(Np(l, rl.mid()->l), Np(rl.mid()->r, rr));
        return Np(Np(l, rl), rr);
    }
    return Np(l, r);
}

Np BST::leafmerge(const Np& l, const Np& r){
    size_t sumsz = l->size + r->size;
    Elem la = l.leaf()->a, ra = r.leaf()->a;
    if(sumsz <= Elem::Cap) return Np(LeafNode(Elem::merge(la, ra, l->size), sumsz));
    if(r->size > l->size){
        auto [rla, rra] = Elem::split(ra, r->size - sumsz/2);
        return Np(
            Np(LeafNode(Elem::merge(la, rla, l->size), (sumsz+1)/2)),
            Np(LeafNode(rra, sumsz/2))
        );
    }
    auto [lla, lra] = Elem::split(la, sumsz/2);
    return Np(
        Np(LeafNode(lla, sumsz/2)),
        Np(LeafNode(Elem::merge(lra, ra, l->size - sumsz/2), (sumsz+1)/2))
    );
}

Np BST::mergeOnL(const Np& l, const Np& r){
    if(l->rank() <= r->rank() + 1) return Np(l, r);
    Np r2 = mergeOnL(l.mid()->r, r);
    Np l2 = l.mid()->l;
    return mergeDirect(l2, r2);
}

Np BST::mergeOnR(const Np& l, const Np& r){
    if(l->rank() + 1 >= r->rank()) return Np(l, r);
    Np l2 = mergeOnR(l, r.mid()->l);
    Np r2 = r.mid()->r;
    return mergeDirect(l2, r2);
}

Np BST::merge(const Np& l, const Np& r){
    if(!r) return l;
    if(!l) return r;
    if(l->rank() == r->rank()) return Np(l, r);
    if(l->rank() > r->rank()) return mergeOnL(l, r);
    return mergeOnR(l, r);
}

std::pair<Np, Np> BST::split(const Np& c, size_t where){
    if(where == 0) return std::make_pair(Np(), c);
    if(c->size <= where) return std::make_pair(c, Np());
    if(c->isLeaf()){
        auto [l, r] = Elem::split(c.leaf()->a, where);
        return std::make_pair(Np(LeafNode(l, where)), Np(LeafNode(r, c->size - where)));
    }
    if(c.mid()->l->size == where) return std::make_pair(c.mid()->l, c.mid()->r);
    if(where < c.mid()->l->size){
        auto [ll, lr] = split(c.mid()->l, where);
        return std::make_pair(std::move(ll), merge(lr, c.mid()->r));
    }
    auto [rl, rr] = split(c.mid()->r, where - c.mid()->l->size);
    return std::make_pair(merge(c.mid()->l, rl), std::move(rr));
}

Np BST::splitL(const Np& c, size_t where){
    if(where == 0) return Np();
    if(c->size <= where) return c;
    if(c->isLeaf()) return Np(LeafNode(Elem::split(c.leaf()->a, where).first, where));
    if(c.mid()->l->size == where) return c.mid()->l;
    if(where < c.mid()->l->size) return splitL(c.mid()->l, where);
    return merge(c.mid()->l, splitL(c.mid()->r, where - c.mid()->l->size));
}

Np BST::splitR(const Np& c, size_t where){
    if(where == 0) return c;
    if(c->size <= where) return Np();
    if(c->isLeaf()) return Np(LeafNode(Elem::split(c.leaf()->a, where).second, c->size - where));
    if(c.mid()->l->size == where) return c.mid()->r;
    if(where < c.mid()->l->size) return merge(splitR(c.mid()->l, where), c.mid()->r);
    return splitR(c.mid()->r, where - c.mid()->l->size);
}

Np BST::construct(const std::string& s){
    if(s.empty()) return Np();
    auto dfs = [&](auto& dfs, size_t l, size_t r) -> Np {
        if(l + Elem::Cap >= r){
            Elem q;
            for(size_t j=0; j<r-l; j++) q.append(j, s[l+j]);
            return Np(LeafNode(q, r-l));
        }
        size_t m = (l+r) / 2;
        return BST::merge(dfs(dfs, l, m), dfs(dfs, m, r));
    };
    return dfs(dfs, 0, s.size());
}

}

struct PersistentString{
private:
    using Me = PersistentString;
    using I = nachia_internal::BST;
    nachia_internal::Np p;
    PersistentString(nachia_internal::Np newp) : p(newp) {}
public:
    using MyType = PersistentString;
    static constexpr size_t MaxSize(){ return (size_t)1 << 60; }
    PersistentString(const std::string& s = "") : p(I::construct(s)) {}
    PersistentString(const char* s) : PersistentString(std::string(s)) {}
    MyType substr(size_t pos, size_t len) const { assert(pos <= size()); len = std::min(len, size() - pos); return Me(I::subarray(p, pos, pos+len)); }
    MyType operator+(MyType rh) const { assert(MaxSize() - size() >= rh.size()); return Me(I::merge(p, rh.p)); }
    MyType& operator+=(MyType rh){ p = I::merge(p, rh.p); return *this; }
    MyType inserted(MyType other, size_t pos) const {
        assert(pos <= size()); assert(MaxSize() - size() >= other.size());
        auto q = I::split(p, pos);
        return Me(I::merge(I::merge(q.first, other.p), q.second));
    }
    void insert(MyType other, size_t pos){ (*this) = inserted(other, pos); }
    std::string to_string() const { std::string buf; if(!empty()){ buf.reserve(size()); p->dump(buf); } return buf; }
    bool empty() const noexcept { return !p; }
    size_t size() const noexcept { return empty() ? 0 : p->size; }
    // char operator[](size_t pos) const ;
    
    MyType operator*(size_t z) const {
        if(z == 0 || empty()) return Me();
        if(z == 1) return *this;
        assert(MaxSize() / z >= size());
        auto q = (*this) * (z/2);
        return (z%2) ? (*this)+q+q : (q+q);
    }
    MyType& operator*=(size_t z){ return (*this) = operator*(z); }
};

} // namespace nachia
