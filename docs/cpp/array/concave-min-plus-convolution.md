# 片方の列が凹である場合の min-plus 畳み込み

[C++ 用ライブラリ一覧に戻る](../index.md)

## ソースコード

[nachia/array/concave-min-plus-convolution.hpp](https://github.com/NachiaVivias/cp-library/blob/main/Cpp/Include/nachia/array/concave-min-plus-convolution.hpp)

## 主な機能

$A[i] + A[i] \leq A[i-1] + A[i+1]$ を満たす数列と任意の数列 $B$ について、

$$C[i] = \min _ {a+b=i} (A[a] + B[b])$$

の値およびこの最小値を達成する $a$ の値を求める。

## 関数

### MinPlusConvolution\_AIsConcave

```c++
template<class Elem>
std::vector<std::pair<Elem, int>> MinPlusConvolution_AIsConcave(
    const std::vector<Elem>& A,
    const std::vector<Elem>& B,
    Elem Inf
);
```

* $1 \leq |A| \leq 10^8$
* $1 \leq |B| \leq 10^8$
* $A[i] + A[i] \leq A[i-1] + A[i+1]$ ($1 \leq i \leq |A|-1$)
* $\texttt{Inf}$ は、どの $A[i]+B[j]$ よりも大きい値である
* $N=|A|+|B|$ として $O(N\log N)$ 時間

返り値は $|A|+|B|-1$ 要素の配列である。 $i$ 番目の要素は、 $C[i] = \min _ {a+b=i} (A[a] + B[b])$ の値と、 $C[i] = A[a] + B[i-a]$ を満たす $a$ の組である。

---

[TOP PAGE](https://nachiavivias.github.io/cp-library/)


<script type="text/x-mathjax-config">MathJax.Hub.Config({tex2jax:{inlineMath:[['\$','\$']],processEscapes:true},CommonHTML: {matchFontHeight:false}});</script>
<script type="text/javascript" async src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.1/MathJax.js?config=TeX-MML-AM_CHTML"></script>
