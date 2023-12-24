# subset sum problem

[C++ 用ライブラリ一覧に戻る](../index.md)

## ソースコード

[nachia/set/subset-sum.hpp](https://github.com/NachiaVivias/cp-library/blob/main/Cpp/Include/nachia/set/subset-sum.hpp)

## 主な機能

部分和問題の競プロ向け解法である。

> **部分和問題**
>
> $n$ 個の整数 $A _ 0,A _ 1,\ldots ,A _ n$ のうち $0$ 要素以上を選んで総和を $X$ にすることができるか？ あるいは、総和が $X$ になるような選び方を $1$ つ求めよ。

* 半分全列挙

## 関数

### SubsetSumHalfBruteforce

```c++
std::vector<int> SubsetSumHalfBruteforce(long long X, std::vector<long long> A);
```

- $n\leq 60$
- 任意の部分和 $s$ について、 $|s| \leq 2\times 10^{18}$
- $O(2^{n/2})$ 時間。

半分全列挙による解法。

部分和を $X$ とできない場合、 `{-1}` を返す。

部分和を $X$ とできる場合、 $0$ と $1$ からなる長さ $n$ の配列 `R` を返す。この配列は $\displaystyle \sum _ {i=0}^{n-1}R _ iA _ i=X$ を満たす。

---

[TOP PAGE](https://nachiavivias.github.io/cp-library/)


<script type="text/x-mathjax-config">MathJax.Hub.Config({tex2jax:{inlineMath:[['\$','\$']],processEscapes:true},CommonHTML: {matchFontHeight:false}});</script>
<script type="text/javascript" async src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.1/MathJax.js?config=TeX-MML-AM_CHTML"></script>


