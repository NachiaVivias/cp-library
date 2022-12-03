# Connected Components ( 連結成分 )

[C++ 用ライブラリ一覧に戻る](../index.md)

## ソースコード

[nachia/graph/connected-components.hpp](https://github.com/NachiaVivias/cp-library/blob/main/Cpp/Include/nachia/graph/connected-components.hpp)

## 主な機能

無向グラフを連結成分に分解して、その成分に番号を振る。

再帰の深い関数を使わない。

## struct ConnectedComponents

### コンストラクタ

```c++
ConnectedComponents(const CsrArray<int>& adj);
ConnectedComponents(Graph G = Graph(0, true));
```

- 頂点数： $0 \leq n \leq 1 \times 10^7$
- 辺数： $0 \leq m \leq 1 \times 10^7$
- $G$ は無向グラフ
- $\text{adj}$ は無向グラフの隣接リスト表現
- $O(n + m)$ 時間

メインの計算を行う。

### numComponents

```c++
int numComponents() const;
```

連結成分の個数を返す。

### getMapping

```c++
const std::vector<int>& getMapping() const;
```

各頂点がどの連結成分に属するかを表す、長さ $n$ の配列を取得する。
各要素の値は $0$ 以上 `numComponents()` 未満である。

[`nachia::Graph::induce`](graph.md#induce) と関連している。

---

[TOP PAGE](https://nachiavivias.github.io/cp-library/)


<script type="text/x-mathjax-config">MathJax.Hub.Config({tex2jax:{inlineMath:[['\$','\$']],processEscapes:true},CommonHTML: {matchFontHeight:false}});</script>
<script type="text/javascript" async src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.1/MathJax.js?config=TeX-MML-AM_CHTML"></script>
