# 対称群の部分群の簡単化

[C++ 用ライブラリ一覧に戻る](../index.md)

## ソースコード

[nachia/permutation/simplify-permitation-subgroup.hpp](https://github.com/NachiaVivias/cp-library/blob/main/Cpp/Include/nachia/permutation/simplify-permitation-subgroup.hpp)

## 主な機能

対称群 $S _ n$ の元の集合 $A$ が与えられたとき、それが生成する部分群 $G=\langle A\rangle$ について、別の集合 $B$ の要素を持つ 2 次元配列 `B` （ただしその要素は順列であるので、実際は 3 次元配列）を求める。ただし、以下の条件を満たすようにする。

* $\langle B\rangle =G$
* $`B[i][j]` は以下の条件を満たす。
    * $i\lt k$ のとき、 `B[i][j][k] == k`
    * `B[i][j][i] < i`
    * $j\neq k$ のとき、 `B[i][j][i] != B[i][k][i]`
* `B[i]` の要素数を $X _ i$ と置くと、 $\prod _{i=0}^{n-1} X _ i$ は $G$ の要素数 $\lvert G \rvert$ に等しい。

## 関数 SimplifyPermutationSubgroup

```c++
// res.size() = n
// res[a][*].size() = (force_size_n ? n : (a+1))
// res[a][*][a] distinct
std::vector<std::vector<std::vector<int>>> SimplifyPermutationSubgroup(
    int n,
    std::vector<std::vector<int>> perm,
    bool force_size_n = true
);
```

* $1 \leq n \leq 100$
* `perm` の各要素は長さ $n$ の配列であり、 $(0,1,\ldots ,n-1)$ の並べ替えである。
* $m$ を `perm` の要素数とする。 $0\leq m\leq 10^8$
* $O(n^6+n^2m)$ 時間
* 返り値 `B` は以下の条件を満たす。
    * $i\lt k$ のとき、 `B[i][j][k] == k`
    * `B[i][j][i] < i`
    * $j\neq k$ のとき、 `B[i][j][i] != B[i][k][i]`

対称群の元を置換で表し、それを順列で表して処理する。仮に各順列を逆順列で置き換えても問題は変わらないため、どちらで捉えてもよい。

`force_size_n` が：

* `true` である場合、すべて要素数 $n$ とする。
* `false` である場合、返り値 `B` について `B[i]` の要素 `B[i][j]` の要素数を $i+1$ とする。

## 参考

* codeforces blog. "Permutation group basis construction (Schreier–Sims algorithm)" by adamant [Link](https://codeforces.com/blog/entry/111290)

---

[TOP PAGE](https://nachiavivias.github.io/cp-library/)


<script type="text/x-mathjax-config">MathJax.Hub.Config({tex2jax:{inlineMath:[['\$','\$']],processEscapes:true},CommonHTML: {matchFontHeight:false}});</script>
<script type="text/javascript" async src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.1/MathJax.js?config=TeX-MML-AM_CHTML"></script>


