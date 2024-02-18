# オイラー路の構築

[C++ 用ライブラリ一覧に戻る](../index.md)

## ソースコード

[nachia/graph/eulerian-trail.hpp](https://github.com/NachiaVivias/cp-library/blob/main/Cpp/Include/nachia/graph/eulerian-trail.hpp)

## 主な機能

グラフの辺をすべてちょうど $1$ 回ずつ通る walk があれば、構築する。

## 関数 EulerianTrail

### テンプレート引数

```c++
auto EulerianTrail(const Graph& graph);
```

* 頂点数 : $1\leq n\leq 10^8$
* 辺数 : $0\leq m\leq 10^8$
* グラフの設定が有向か無向かによって動作が適切に変化する。

返り値の型は次の通り。

```c++
struct Result {
    int length;
    int start;
    std::vector<int> edges;
};
```

返り値として、

* $m=0$ ならば、 $(0,0,())$ として返す。
* オイラー路が存在しなければ `length == -1` として返す。
* オイラー路が存在すれば、
    * 辺の個数を `length` 、
    * 始点を `start` 、
    * 通る辺を順番に `edges` に格納して返す。

---

[TOP PAGE](https://nachiavivias.github.io/cp-library/)


<script type="text/x-mathjax-config">MathJax.Hub.Config({tex2jax:{inlineMath:[['\$','\$']],processEscapes:true},CommonHTML: {matchFontHeight:false}});</script>
<script type="text/javascript" async src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.1/MathJax.js?config=TeX-MML-AM_CHTML"></script>
