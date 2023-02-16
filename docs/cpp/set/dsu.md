# Disjoint Set Union

[C++ 用ライブラリ一覧に戻る](../index.md)

## ソースコード

[nachia/set/dsu.hpp](https://github.com/NachiaVivias/cp-library/blob/main/Cpp/Include/nachia/set/dsu.hpp)

## 主な機能

互いに素な $n$ 個の集合 $\lbrace 0\rbrace , \lbrace 1\rbrace \ldots \lbrace n-1\rbrace$ から始めて、次の操作を繰り返すことができる。

- $w=$ merge( $u$ , $v$ , $w$ ) : 整数 $u$ が含まれる集合と整数 $v$ が含まれる集合を見て、それが異なる集合なら併合する。（併合される前の集合は破棄する。）その集合に整数 $w$ のラベルをつける。
- $w=$ label( $u$ ) : 整数 $u$ が含まれる集合についているラベル $w$ を求める。

初期状態では、 $u$ が含まれる集合にラベル $u$ がついているとする。

各操作の計算量が償却 $O(\alpha (n))$ （ $\alpha$ はアッカーマン関数の逆関数と呼ばれてる関数を表す。）、最悪 $O(\log n)$ にできることが証明されている。

現バージョンでは、 path halving と union by size の組み合わせを採用している。

## struct nachia::Dsu

### コンストラクタ

```c++
    Dsu();      // (#)
    Dsu(int n); // (1)
```

- $O(n)$ 空間

`(#)` ダミーを生成する。このコンストラクタで生成したインスタンスでクエリを呼んではいけない。

`(1)` $n$ 要素でデータ構造を初期化する。

### leader

```c++
int leader(int u);
```

- $0\leq u \lt n$
- 償却 $O(\alpha (n))$ 時間 , 最悪 $O(\log (n))$ 時間

整数 $u$ が含まれる集合について、代表元を返す。集合が変更されない限り、その集合の代表元は変更されない。

### append

```c++
int append();
```

- 償却 $O(1)$ 時間

$n$ を $1$ だけ増やす。つまり、要素を $1$ つ増やし、それ $1$ つだけからなる集合を追加する。追加された整数を返す。

### label

```c++
int label(int u);
int operator[](int u);
```

- $0\leq u \lt n$
- 償却 $O(\alpha (n))$ 時間 , 最悪 $O(\log (n))$ 時間

整数 $u$ が含まれる集合についているラベルを返す。添字演算子 `[]` でもアクセスできる。

### merge

```c++
int merge(int u, int v);
int merge(int u, int v, int newLabel);
```

- $0\leq u \lt n$
- $0\leq v \lt n$
- 償却 $O(\alpha (n))$ 時間 , 最悪 $O(\log (n))$ 時間

整数 $u$ が含まれる集合と整数 $v$ が含まれる集合を併合する。併合されたかどうかにかかわらず、その集合のラベルを `newLabel` で上書きする。 `newLabel` を返す。

### count

```c++
int count();
```

管理している集合の個数を返す。

### size

```c++
int size(int u);
```

- $0\leq u \lt n$
- 償却 $O(\alpha (n))$ 時間 , 最悪 $O(\log (n))$ 時間

整数 $u$ が含まれている集合の要素数を返す。

### same

```c++
bool same(int u, int v);
```

- $0\leq u \lt n$
- $0\leq v \lt n$
- 償却 $O(\alpha (n))$ 時間 , 最悪 $O(\log (n))$ 時間

整数 $u$ と整数 $v$ が同じ集合に属しているときに `true` を返す。

## 参考


---

[TOP PAGE](https://nachiavivias.github.io/cp-library/)


<script type="text/x-mathjax-config">MathJax.Hub.Config({tex2jax:{inlineMath:[['\$','\$']],processEscapes:true},CommonHTML: {matchFontHeight:false}});</script>
<script type="text/javascript" async src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.1/MathJax.js?config=TeX-MML-AM_CHTML"></script>


