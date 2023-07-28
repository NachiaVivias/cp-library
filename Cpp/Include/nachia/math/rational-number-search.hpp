#pragma once
#include <utility>
#include <cassert>

namespace nachia{

class RationalNumberSearch{
public:
    struct Rational {
        long long num;
        long long den;
    };
    RationalNumberSearch(long long maxVal){
        assert(0 < maxVal);
        mx = maxVal;
    }
    bool hasNext() const { return state >= 0; }
    Rational getNext() const {
        switch(state){
        case 0: return soft(a0+a1, b0+b1);
        case 1: return soft(a0+tr*a1, b0+tr*b1);
        case 2: return soft(a1+tr*a0, b1+tr*b0);
        case 3: return soft(a0+(tl+tr)/2*a1, b0+(tl+tr)/2*b1);
        case 4: return soft(a1+(tl+tr)/2*a0, b1+(tl+tr)/2*b0);
        }
        return {0,0};
    }
    void give(bool toRight){
        int x = toRight ? 1 : 0;
        switch(state){
        case 0:
            tl = 1; tr = 2;
            if(a0 + a1 > mx || b0 + b1 > mx){ state = -1; }
            else{ state = (toRight ? 1 : 2); }
            break;
        case 1: case 2:
            if(x ^ (2-state)){ state += 2; }
            else{ tr *= 2; tl *= 2; }
            break;
        case 3: case 4:
            ((x ^ (4-state)) ? tr : tl) = (tl+tr)/2;
            break;
        }
        while(givecheck());
    }
private:
    using UInt = unsigned long long;
    static Rational soft(UInt a, UInt b){ return { (long long)a, (long long)b }; }
    UInt a0=0, b0=1, a1=1, b1=0, tl=0, tr=0, mx;
    int state = 0;
    bool givecheck(){
        auto st = [this](int x){ state = x; return true; };
        auto trq = [this](UInt x0, UInt x1) -> bool {
            bool f = x0+tr*x1 > mx;
            if(f) tr = (mx-x0)/x1 + 1;
            return f;
        };
        bool f = false;
        switch(state){
        case -1 : break;
        case 0:
            if(a0 + a1 > mx || b0 + b1 > mx){ state = -1; }
            break;
        case 1:
            if(trq(a0,a1)) f = true;
            if(trq(b0,b1)) f = true;
            if(f) return st(3);
            break;
        case 2:
            if(trq(a1,a0)) f = true;
            if(trq(b1,b0)) f = true;
            if(f) return st(4);
            break;
        case 3:
            if(tl + 1 == tr){
                a0 += a1 * tl;
                b0 += b1 * tl;
                return st(0);
            }
            break;
        case 4:
            if(tl + 1 == tr){
                a1 += a0 * tl;
                b1 += b0 * tl;
                return st(0);
            }
            break;
        }
        return false;
    }
};

} // namespace nachia
