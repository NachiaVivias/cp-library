
template<unsigned int MOD>
class AffineModStrict;
template<unsigned int MOD>
AffineModStrict<MOD> operator+(AffineModStrict<MOD> l, AffineModStrict<MOD> r);

template<unsigned int MOD>
class AffineModStrict {
private:
    unsigned int a;
    unsigned int b;

    friend AffineModStrict<MOD> operator+<MOD>(AffineModStrict<MOD> l, AffineModStrict<MOD> r);
public:
    
    AffineModStrict(unsigned int x, unsigned int y) : a(x), b(y) {}

    static AffineModStrict Identity(){ return AffineModStrict(1,0); }

    unsigned int eval(unsigned int x) const {
        return ((unsigned long long)x * a + b) % MOD;
    }
};

template<unsigned int MOD>
AffineModStrict<MOD> operator+(AffineModStrict<MOD> l, AffineModStrict<MOD> r){
    auto res = AffineModStrict<MOD>(0,0);
    res.a = (unsigned long long)l.a * r.a % MOD;
    res.b = ((unsigned long long)l.b * r.a + r.b) % MOD;
    return res;
}
