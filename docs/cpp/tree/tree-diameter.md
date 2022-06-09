# 木の直径

[C++ 用ライブラリ一覧に戻る](../index.md)

## 主な機能

$n$ 頂点の木を `AdjacencyList` で入力すると、木の直径であるパスを $1$ つ求める。

## 関数

### UnitTreeDiameter

```c++
std::vector<int> UnitTreeDiameter(const AdjacencyList& T);
```

- $1 \leq n \leq 10^8$
- $O(n)$ 時間

木の直径のパスを表す頂点列を求める。

---

[TOP PAGE](https://nachiavivias.github.io/cp-library/)


<script type="text/x-mathjax-config">MathJax.Hub.Config({tex2jax:{inlineMath:[['\$','\$']],processEscapes:true},CommonHTML: {matchFontHeight:false}});</script>
<script type="text/javascript" async src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.1/MathJax.js?config=TeX-MML-AM_CHTML"></script>
