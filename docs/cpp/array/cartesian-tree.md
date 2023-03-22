# Cartesian tree

[C++ 用ライブラリ一覧に戻る](../index.md)

## ソースコード

[nachia/array/cartesian-tree.hpp](https://github.com/NachiaVivias/cp-library/blob/main/Cpp/Include/nachia/array/cartesian-tree.hpp)

## 主な機能

長さ $n$ の要素列を最小値があるところ（タイブレークは先頭に近いほうを選ぶ）から 2 つに分割すると、分割過程を表す、ノード数 $n$ の二分木を考えられるので、その木の辺のリストを計算する。

この木は Cartesian tree と呼ばれる。

## 関数

### CartesianTree

```c++
template<class T>
nachia::Graph CartesianTree(const std::vector<T>& A);
```

- $n = $ `A.size()`
- $1 \leq n \leq 10^9$ （その他 Graph の制約にも注意）
- `T` 同士で比較 `<` ができる
- $O(n)$ 時間

Cartesian tree の辺のリストを返す。ただし、

- すべての辺は親から子の方向を向いており、
- Graph の設定は有向グラフになっている。

---

[TOP PAGE](https://nachiavivias.github.io/cp-library/)


<script type="text/x-mathjax-config">MathJax.Hub.Config({tex2jax:{inlineMath:[['\$','\$']],processEscapes:true},CommonHTML: {matchFontHeight:false}});</script>
<script type="text/javascript" async src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.1/MathJax.js?config=TeX-MML-AM_CHTML"></script>
