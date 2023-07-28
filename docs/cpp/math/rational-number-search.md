# 有理数の二分探索

[C++ 用ライブラリ一覧に戻る](../index.md)

## ソースコード

[nachia/math/rational-number-search.hpp](https://github.com/NachiaVivias/cp-library/blob/main/Cpp/Include/nachia/math/rational-number-search.hpp)

## 主な機能

$0$ より大きく、分母分子が $n$ 以下である分数全体を二分探索する。

## クラス RationalNumberSearch

```c++
namespace nachia{

    class RationalNumberSearch;

}
```

### コンストラクタ

```c++
RationalNumberSearch(long long maxVal);
```

- $n = \text{maxval}$
- $0 \leq n \lt 2^{63}$

### 二分探索

```c++
struct Rational {
    long long num;
    long long den;
};

bool hasNext() const;
Rational getNext() const;
void give(bool toRight);
```

例えば、仮に目的の値を `answer` とすると、次の手順で探索できる。

```c++
int main(){
    double answer;
    cin >> answer;

    auto rns = RationalNumberSearch(1000);
    RationalNumberSearch::Rational smaller_than_answer = {0,1};

    while(rns.hasNext()){
        auto x = rns.getNext();
        bool x_is_small = (double)x.num / x.den < answer;
        if(x_is_small) smaller_than_answer = x;
        rns.give(x_is_small);
    }

    cout << smaller_than_answer.num << "/" << smaller_than_answer.den << endl;
    return 0;
}
```

---

[TOP PAGE](https://nachiavivias.github.io/cp-library/)


<script type="text/x-mathjax-config">MathJax.Hub.Config({tex2jax:{inlineMath:[['\$','\$']],processEscapes:true},CommonHTML: {matchFontHeight:false}});</script>
<script type="text/javascript" async src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.1/MathJax.js?config=TeX-MML-AM_CHTML"></script>
