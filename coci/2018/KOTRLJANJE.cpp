#include <bits/stdc++.h>
using namespace std;

#define oo 0x3f3f3f3f
#define mp make_pair
#define fi first
#define se second
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#define FO(i,a,b) for (int i=(a);i<=(b);++i)
#define FD(i,a,b) for (int i=(a);i>=(b);--i)
#define FE(i,G,x) for(int i=(G).h[x];~i;i=(G).v[i].nxt)
typedef long long LL;
typedef pair<int, int> PII;

template <class T> inline bool chkmin(T& x, T y) { return x > y ? x = y, true : false; }
template <class T> inline bool chkmax(T& x, T y) { return x < y ? x = y, true : false; }

inline LL read(void) {
    LL x, f = 1; char ch = getchar();
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = -1;
    for (x = 0; isdigit(ch); ch = getchar()) x = x * 10 + ch - '0';
    return x * f;
}

int c, d, b, m;
vector<int> A[50100];

int get(LL x) {
    int r = 0;
    while (x) r += x % b, x /= b;
    return r;
}

int main(void) {
    c = read(), d = read(), b = read(), m = read();
    FO(i, 1, 1e9){
        int pp = get(1ll * c * (b - 1) * i + d) / (b - 1);
        A[pp].push_back(i);
        if (A[pp].size() == m){
            for (auto x: A[pp]) printf("%lld ",1ll * x * (b - 1));
            return 0;
        }
    }
    return 0;
}
