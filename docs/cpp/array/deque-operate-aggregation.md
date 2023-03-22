# 集約値取得可能な deque

[C++ 用ライブラリ一覧に戻る](../index.md)

## ソースコード

[nachia/array/deque-operate-aggregation.hpp](https://github.com/NachiaVivias/cp-library/blob/main/Cpp/Include/nachia/array/deque-operate-aggregation.hpp)

## 主な機能

モノイドの要素列に対して、以下の操作を行う。

- 列の末尾に要素を追加
- 列の先頭に要素を追加
- 列の末尾の要素を削除
- 列の先頭の要素を削除
- 二項演算 `+` によって全体を集約した値を取得

モノイドの操作を定数時間とすると、各操作は償却定数時間である。

最悪は要素数に対して線形時間かかりうる。

## 構造体テンプレート DequeOperateAggregation

### テンプレート引数

```c++
template<class Val>
struct DequeOperateAggregation;
```

- `Val` どうしの二項演算 `+` を正しく処理しなければならない。

### コンストラクタ

```c++
DequeOperateAggregation(Val e);
```

$e+a=a$ の性質をもつ $e$ を渡さなければ構築できない。

### pushFront, pushBack

```c++
void pushFront(Val v);
void pushBack(Val v);
```

要素を追加する。

### popFront, popBack

```c++
void popFront();
void popBack();
```

要素を削除する。

### sum

```c++
Val sum();
```

集約値を返す。


---

[TOP PAGE](https://nachiavivias.github.io/cp-library/)


<script type="text/x-mathjax-config">MathJax.Hub.Config({tex2jax:{inlineMath:[['\$','\$']],processEscapes:true},CommonHTML: {matchFontHeight:false}});</script>
<script type="text/javascript" async src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.1/MathJax.js?config=TeX-MML-AM_CHTML"></script>
