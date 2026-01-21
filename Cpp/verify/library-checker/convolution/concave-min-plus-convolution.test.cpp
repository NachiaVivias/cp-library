#define PROBLEM "https://judge.yosupo.jp/problem/min_plus_convolution_concave_arbitrary"

#include "../../../Include/nachia/array/concave-min-plus-convolution.hpp"
#include "../../../Include/nachia/misc/fastio.hpp"

int main(){
  using nachia::cin;
  using nachia::cout;
  int N, M; cin >> N >> M;
  std::vector<int> A(N), B(M);
  for(int i=0; i<N; i++) cin >> A[i];
  for(int i=0; i<M; i++) cin >> B[i];
  auto ans = nachia::MinPlusConvolution_AIsConcave<int>(A, B, 2002002002);
  for(int i=0; i<N+M-1; i++){
    if(i) cout << " ";
    cout << ans[i].first;
    if(A[ans[i].second] + B[i-ans[i].second] != ans[i].first) return 1;
  } cout << "\n";
  return 0;
}
