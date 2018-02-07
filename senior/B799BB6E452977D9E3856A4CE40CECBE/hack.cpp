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

#define min(a,b) ((a)<(b)?(a):(b))

unordered_map<unsigned, string> M[10];
string ans[16];
int l, p1, p2, q;
unsigned pw[10], H[16], p;
char str[16][10];

void dfs1(int len, unsigned h, string raw) {
    auto x = M[len].find(h);
    if (x == M[len].end()) M[len][h] = raw;
    else M[len][h] = min(x->se, raw);
    if (len == p1) return ;
    FO(i, 'A', 'Z') dfs1(len + 1, h * p + (unsigned)i, raw + (char)i);
}
void dfs2(int len, unsigned h, string now) {
    FO(i, 0, p1) {
        FO(j, 0, q - 1) {
            if (ans[j] != "" && now > ans[j]) continue;
            auto x = M[i].find(H[j] - pw[i] * h);
            if (x != M[i].end() && now + x->se != string(str[j]))
                (ans[j] == "") ? ((ans[j] = now + x->se), 1) : chkmin(ans[j], now + x->se);
        }
    }
    if (len == p2) return ;
    FO(i, 'A', 'Z') dfs2(len + 1, h * p + (unsigned)i, now + (char)i);
}

int main(void) {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    p = read(); l = read(); q = read();
    pw[0] = 1; FO(i, 1, l) pw[i] = pw[i - 1] * p;
    p1 = l / 2; p2 = l - p1; if (p1 < p2) swap(p1, p2);
    dfs1(0, 0, "");
    FO(i, 0, q - 1) {
        scanf("%s", str[i]);
        unsigned cur = 0; int n = strlen(str[i]);
        FO(j, 0, n - 1) cur = cur * p + str[i][j];
        H[i] = cur;
    }
    dfs2(0, 0, "");
    FO(i, 0, q - 1) printf("%s\n", ans[i] != "" ? ans[i].c_str() : "-1");
    return 0;
}
