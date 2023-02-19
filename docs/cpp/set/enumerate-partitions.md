# 分割の列挙

[C++ 用ライブラリ一覧に戻る](../index.md)

## ソースコード

[nachia/set/enumerate-partitions.hpp](https://github.com/NachiaVivias/cp-library/blob/main/Cpp/Include/nachia/set/enumerate-partitions.hpp)

## 主な機能

非負整数 $n$ に対して $n$ の分割とは、正整数からなる多重集合であって、要素の総和が $n$ であるものである。 $n$ を与えると、これを全列挙する。

## 関数

### EnumeratePartitions

```c++
std::vector<CsrArray<int>> EnumeratePartitions(int n)
```

[nachia::CsrArray とは？](../array/csr-array.md)

- $0\leq n$

$n$ 以下の非負整数 $m$ それぞれについて、 $m$ の分割を列挙する。

返り値を `A` とすると、 `A[m]` は $m$ の分割をすべて列挙したものである。 `A[m][i]` は $m$ の分割であるような多重集合を表す。各多重集合は、要素を昇順に並べた列で表現されている。

## 参考


---

[TOP PAGE](https://nachiavivias.github.io/cp-library/)


<script type="text/x-mathjax-config">MathJax.Hub.Config({tex2jax:{inlineMath:[['\$','\$']],processEscapes:true},CommonHTML: {matchFontHeight:false}});</script>
<script type="text/javascript" async src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.1/MathJax.js?config=TeX-MML-AM_CHTML"></script>


