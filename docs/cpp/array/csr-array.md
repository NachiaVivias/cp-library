# グラフの辺リスト

[C++ 用ライブラリ一覧に戻る](../index.md)

## ソースコード

[nachia/array/csr-array.hpp](https://github.com/NachiaVivias/cp-library/blob/main/Cpp/Include/nachia/array/csr-array.hpp)

## 主な機能

`const std::vector<std::vector<Elem>>` を `std::vector` の入れ子を用いずに表現する。特に、グラフの隣接リスト表現に使うときに便利である。

## テンプレート CsrArray

```c++
template<class Elem>
class CsrArray
```

`const std::vector<std::vector<Elem>>` の代替。

### 構築用メンバ

```c++
CsrArray();
static CsrArray Construct(int n, const std::vector<std::pair<int, Elem>>& items); // (1)
static CsrArray FromRaw(std::vector<Elem> list, std::vector<int> pos); // (2)
```

コンストラクタで要素をもたないリストを構築できるが、要素をもつものは別の `static` メンバ関数で構築する。

(1)

```c++
std::vector<std::vector<Elem>> Construct(int n, const std::vector<std::pair<int, Elem>>& items){
    std::vector<std::vector<Elem>> res(n);
    for(auto item : items) res[item.first].push_back(item.second);
    return res;
}
```

(2)

```c++
std::vector<std::vector<Elem>> FromRaw(std::vector<Elem> list, std::vector<int> pos){
    std::vector<std::vector<Elem>> res(pos.size()-1);
    for(int i=0; i<(int)res.size(); i++) res[i] = std::vector<Elem>(
        list.begin() + pos[i],
        list.begin() + pos[i+1]
    );
    return res;
}
```

### アクセス

```c++
ListRange operator[](int u);
ConstListRange operator[](int u) const;
int size() const;
```

- `ListRange` や `ConstListRange` は `(const) std::vector<int>&` を部分的に代替するためのインターフェースをもつ。

### fullSize

```c++
int fullSize() const;
```

全体の要素数を取得する。

---

[TOP PAGE](https://nachiavivias.github.io/cp-library/)


<script type="text/x-mathjax-config">MathJax.Hub.Config({tex2jax:{inlineMath:[['\$','\$']],processEscapes:true},CommonHTML: {matchFontHeight:false}});</script>
<script type="text/javascript" async src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.1/MathJax.js?config=TeX-MML-AM_CHTML"></script>
