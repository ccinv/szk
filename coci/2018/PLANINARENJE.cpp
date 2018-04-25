#include <bits/stdc++.h>
using namespace std;

#define oo 0x3f3f3f3f
#define mp make_pair
#define fi first
#define se second
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#define FO(i,a,b) for (int i=(a);i<=(b);++i)
#define FD(i,a,b) for (int i=(a);i>=(b);--i)
#define FE(i,G,x) for(int i=G.h[x];~i;i=G.v[i].nxt)
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

#define N 5005
struct Graph {
    enum { maxn = N, maxm = N };
    struct { int to, nxt; } v[maxm];
    int h[maxn], cnt;
    Graph() { memset(h, -1, sizeof(h)); }
    void clear() { cnt = 0; memset(h, -1, sizeof(h)); }
    void add(int x, int y) { v[cnt].nxt = h[x]; v[cnt].to = y; h[x] = cnt++; }
} G;

int plorais;
int n, m, x, y, v[N], ori[N];

bool dfs(int x) {
    v[x] = 1;
    FE(i, G, x) {
        int to = G.v[i].to;
        if (ori[to] == -1 || !v[ori[to]] && dfs(ori[to])) {
            ori[to] = x;
            return 1;
        }
    }
    return 0;
}
void hungary() {
    fill_n(ori + 1, n, -1);
    FO(i, 1, n) {
        fill_n(v + 1, n, 0);
        if (dfs(i)) plorais++;
    }
}

int main(void) {
    n = read(); m = read();
    FO(i, 1, m) {
        x = read(); y = read();
        G.add(y, x);
    }
    hungary();
    FO(i, 1, n) {
        fill_n(v + 1, n, 0);
        if (ori[i] == -1 || dfs(ori[i])) puts("Mirko"), ori[i] = -1;
        else puts("Slavko");
    }
    return 0;
}
