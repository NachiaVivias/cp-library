# $N$ 以下の素数の個数

[C++ 用ライブラリ一覧に戻る](../index.md)

## 主な機能

$N$ 以下の素数の個数を求める。

## 関数

### CountingPrimes

```c++
long long CountingPrimes(long long maxval);
```

- $n = \text{maxval}$
- $0 \leq n \leq 10^{11}$
- $O(n^{3/4} / \log n)$ 時間

$n$ 以下の素数の個数を返す。

## 参考

えびちゃんの日記 \| 眠れない夜は素数の個数でも数えましょう [https://rsk0315.hatenablog.com/entry/2021/05/18/015511](https://rsk0315.hatenablog.com/entry/2021/05/18/015511)

---

[TOP PAGE](https://nachiavivias.github.io/cp-library/)


<script type="text/x-mathjax-config">MathJax.Hub.Config({tex2jax:{inlineMath:[['\$','\$']],processEscapes:true},CommonHTML: {matchFontHeight:false}});</script>
<script type="text/javascript" async src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.1/MathJax.js?config=TeX-MML-AM_CHTML"></script>
