# 一点更新列で得られる配列の辞書順比較

[C++ 用ライブラリ一覧に戻る](../index.md)

## ソースコード

[nachia/array/point-update-lex-sort.hpp](https://github.com/NachiaVivias/cp-library/blob/main/Cpp/Include/nachia/array/point-update-lex-sort.hpp)

## 主な機能

ユーザーは、先ず長さ $n$ の配列を与える。次に、次の形式の変更を $q$ 回入力する。

- 配列のうち $1$ つの要素を任意に変更する。

変更の過程で $q+1$ 個の配列が得られるので、このライブラリではこれを高速に辞書順でソート、座標圧縮する。

## struct PointUpdateLexSort<K>::Iter

計算結果にアクセスするためのアイテムである。

```c++
    int operator*() const;
```

単項 `*` 演算子で座標圧縮結果にアクセスする。

## struct PointUpdateLexSort

### コンストラクタ

```c++
PointUpdateLexSort<K>(); // dummy
PointUpdateLexSort<K>(std::vector<K> A); // (1)
```

- 要素数 $n$ : $1\leq n\leq 5\times 10^5$
- $K$ は演算子 `<` で比較できる
- $O(n)$ 時間

(0) ダミーのインスタンスを作成する。いかなる操作も呼び出してはいけない。

(1) ユーザーは最初の配列を与える。

### mutate

```c++
Iter mutate(int pos, T val);
```

- $0\leq \text{pos} \lt n$
- 呼び出す回数 $q$ : $q\leq 5\times 10^5$

配列の変更の情報を受け取る。変化後の配列に対応するアイテムを返す。配列の変更は次の代入で表される。

```c++
A[pos] = std::move(val);
```

### count, last

```c++
int count() const; // (1)
Iter last() const; // (2)
```

- $O(1)$ 時間

(1) 生成された配列の個数を取得する。

(2) 現在の配列の状態にアクセスするためのアイテムを取得する。

### proc

```c++
int proc();
```

- $O(q\log q + n\log n)$ 時間

メインの計算を行う。計算結果に関する出力は、最後に呼ばれた `proc` の計算結果に基づく。

### maxSortedPos

```c++
int maxSortedPos();
```

- $O(1)$ 時間

座標圧縮後に現れる値の最大値を返す。座標圧縮後の要素は $0$ 以上この値以下である。

## 参考

- ハッシュが嫌いな人の数列一点更新ソート $\vert$ Mathenachia [link](https://www.mathenachia.blog/sortseqs/)

---

[TOP PAGE](https://nachiavivias.github.io/cp-library/)


<script type="text/x-mathjax-config">MathJax.Hub.Config({tex2jax:{inlineMath:[['\$','\$']],processEscapes:true},CommonHTML: {matchFontHeight:false}});</script>
<script type="text/javascript" async src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.1/MathJax.js?config=TeX-MML-AM_CHTML"></script>
