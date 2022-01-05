# 2-dimensional rectangle query

[C++ 用ライブラリ一覧に戻る](../../)

## 主な機能

$2$ 次元平面上の与えられた $n$ 点 $(P_0,P_1,P_2, \ldots , P_{n-1})$ について、任意の矩形内クエリを $1$ 次元区間クエリに変形する。性質上、集約関数の可換性を仮定する。

区間クエリ用のデータ構造の必要数は $\log_2 n + O(1)$ で、それぞれが $n$ 点をちょうど $1$ 個ずつ管理する。 $d$ 個目の区間クエリ用のデータ構造の $i$ 番目の位置で管理される点の番号を $A[d][i]$ とする。

## struct nachia::RangeTree

### テンプレート引数

```c++
namespace nachia{

    template<typename Pos>
    struct RangeTree;

}
```

`Pos` は、点を配置する座標のスカラーの型。整数型、浮動小数型、その他全順序が成り立つ比較ができる型を設定できる。

### コンストラクタ

```c++
RangeTree(const std::vector<std::pair<Pos, Pos>>& P);
```

- $P\text{.size()} = n$
- $0 \leq n \leq 10^6$
- $O(n \log n)$ 時間
- $O(n \log n)$ 空間

$P$ を点集合として前処理を行う。 $P$ の各要素は軸 $1$ の座標、 軸 $2$ の座標の組である。

メモリ使用量には注意すべきだ。

### get_segment_count

```c++
int get_segment_count() const;
```

- $O(1)$ 時間

区間クエリを処理するために必要な、区間クエリ用データ構造の個数を返す。

### size

```c++
int size() const;
```

- $O(1)$ 時間

$n$ を返す。

### to_vtx

```c++
int to_vtx(int d, int i) const;
```

- $0 \leq d \lt \text{get\_segment\_count()}$
- $0 \leq i \lt n$
- $O(1)$ 時間

$A[d][i]$ を返す。

### get_update_points

```c++
struct UpdatePoint{ int d, i; };

std::vector<UpdatePoint> get_update_points(int v);
```

- 引数を $v$ として、 $0 \leq v \lt n$
- $O(\log n)$ 時間

$A[d][i]=v$ を満たす組 $(d,i)$ をすべて求め、返す。つまり、区間クエリ用データ構造の添え字で、点 $P_v$ に対応するものを列挙する。

`to_vtx` と逆の関係にある。

### get_ranges, get_ranges_from_idx

```c++
struct Query{ int d,l,r; };

std::vector<Query> get_ranges(Pos xl, Pos xr, Pos yl, Pos yr); // (1)
std::vector<Query> get_ranges_from_idx(int xl, int xr, int yl, int yr) // (2)
```

- $O(\log n)$ 時間

(1) $2$ 次元矩形 $\lbrace (x,y) \vert x_l\leq x \lt x_r , y_l\leq y \lt y_r \rbrace$ に対する集約クエリを、 $O( \log n )$ 個の $1$ 次元区間の集約クエリで表す。

(2) 与えられた点集合 $P$ を各軸で昇順ソートし、それぞれ $P_X,P_Y$ とする。このときのソートは安定ではなく、 $P_X,P_Y$ は複数回の呼び出しの間に変化しない。 $P_X$ の $x_l$ 番目から $x_{r-1}$ 番目からなる集合と、 $P_Y$ の $y_l$ 番目から $y_{r-1}$ 番目からなる集合の共通部分に対する集約を考える。これを、 $O( \log n )$ 個の $1$ 次元区間の集約クエリで表す。

返す配列の要素 $(d,l,r)$ は、 $A[d][l],A[d][l+1], \ldots ,A[d][r-1]$ に対する集約を表す。すべての区間の集約クエリを処理すると、指定した矩形内の点のみちょうど $1$ 回ずつ集約に含まれる。

## 使用例

Library Checker : Point Add Rectangle Sum (https://judge.yosupo.jp/problem/point_add_rectangle_sum)

```c++
#include <iostream>

struct BIT{
    std::vector<long long> A;
    BIT(int n=0){ A.assign(n+1,0); }
    long long sum(int r){
        long long res = 0;
        while(r){ res += A[r]; r -= r & -r; }
        return res;
    }
    void add(int p, long long x){
        p += 1;
        while(p < A.size()){ A[p] += x; p += p & -p; }
    }
};


int main(){
    int N,Q; std::cin >> N >> Q;
    std::vector<std::pair<int,int>> P(N);
    std::vector<int> A(N);
    for(int i=0; i<N; i++){
        std::cin >> P[i].first >> P[i].second;
        std::cin >> A[i];
    }

    std::vector<std::vector<int>> queries;

    // read all queries first
    for(int i=0; i<Q; i++){
        int t; std::cin >> t;
        if(t == 0) /* additional point */ {
            int x, y, w; std::cin >> x >> y >> w;
            queries.push_back({ t, (int)P.size(), w });
            P.push_back({ x, y });
            A.push_back(0);
        }
        if(t == 1) /* query */ {
            int xl, yl, xr, yr; std::cin >> xl >> yl >> xr >> yr;
            queries.push_back({ t, xl, xr, yl, yr });
        }
    }

    // 2-dimensional to 1-dimensional
    nachia::TwoDRectangeQuery<int> two_dim(P);

    // 1-dimensional data structure
    std::vector<BIT> rq(two_dim.get_segment_count());
    for(int d=0; d<two_dim.get_segment_count(); d++){
        rq[d] = BIT(two_dim.size() + 1);
        for(int i=0; i<two_dim.size(); i++) rq[d].add(i, A[two_dim.to_vtx(d, i)]);
    }

    for(auto& q : queries){
        if(q[0] == 0) /* update */ {
            for(auto qq : two_dim.get_update_points(q[1])){
                rq[qq.d].add(qq.i, q[2]);
            }
        }
        if(q[0] == 1) /* query */ {
            long long ans = 0;
            for(auto qq : two_dim.get_ranges(q[1], q[2], q[3], q[4])){
                ans += rq[qq.d].sum(qq.r) - rq[qq.d].sum(qq.l);
            }
            std::cout << ans << "\n";
        }
    }
    
    return 0;
}
```

## 参考

Eating Your Own Cat Food | ウェーブレット行列(wavelet matrix) : https://miti-7.hatenablog.com/entry/2018/04/28/152259


---

[TOP PAGE](https://nachiavivias.github.io/cp-library/)


<script type="text/x-mathjax-config">MathJax.Hub.Config({tex2jax:{inlineMath:[['\$','\$']],processEscapes:true},CommonHTML: {matchFontHeight:false}});</script>
<script type="text/javascript" async src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.1/MathJax.js?config=TeX-MML-AM_CHTML"></script>


