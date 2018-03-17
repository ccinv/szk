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

#define N 1000005
inline int ran() {
    static int x = 23333;
    return x ^= x << 13, x ^= x>>17, x ^= x << 5;
}

int n, q, op, l, r;
struct Node {
    int l, r, pri, x, sz;
    void init(int p) { x = p; sz = 1; l = r = 0; pri = ran(); }
    void upd();
} A[N * 40]; int cnt;
struct Seg { int rot, lz; } T[N * 4];
inline void Node::upd() { sz = A[l].sz + A[r].sz + 1; }

int merge(int x, int y) {
    if (!x || !y) return x + y;
    int X = ++cnt;
    if (A[x].pri < A[y].pri) { A[X] = A[x]; return A[X].r = merge(A[X].r, y), A[X].upd(), X; }
    else { A[X] = A[y]; return A[X].l = merge(x, A[X].l), A[X].upd(), X; }
}
PII split(int x, int s) {
    if (!x) return mp(0, 0);
    int cmp = A[A[x].l].sz; PII ret;
    int X = ++cnt; A[X] = A[x];
    if (s <= cmp) {
        ret = split(A[x].l, s);
        A[X].l = ret.se; ret.se = X;
    } else {
        ret = split(A[x].r, s - cmp - 1);
        A[X].r = ret.fi; ret.fi = X;
    }
    return A[X].upd(), ret;
}
inline int ins(int x, int z) {
    int y = ++cnt; A[y].init(z);
    return merge(x, y);
}

#define LS x<<1
#define RS x<<1|1
#define MID (l+r>>1)
inline void quesig(int x, int d) {
    int r = T[x].rot;
    if (A[r].sz < d) { puts("Error"); return ; }
    PII p = split(r, A[r].sz - d);
    PII q = split(p.se, 1);
    printf("%d\n", A[q.fi].x);
}
inline void delsig(int x, int k) {
    int& r = T[x].rot;
    int nd = min(A[r].sz, k);
    T[x].lz += k - nd; r = split(r, A[r].sz - nd).fi;
}

void pushdown(int x) {
    if (T[x].lz) {
        delsig(LS, T[x].lz), delsig(RS, T[x].lz);
        T[x].lz = 0;
    }
    if (T[x].rot) {
        T[LS].rot = merge(T[LS].rot, T[x].rot);
        T[RS].rot = merge(T[RS].rot, T[x].rot);
        T[x].rot = 0;
    }
}
void del(int x, int l, int r, int ll, int rr) {
    if (l > rr || r < ll) return ;
    if (l >= ll && r <= rr) { delsig(x, 1); return ; }
    pushdown(x);
    del(LS, l, MID, ll, rr); del(RS, MID + 1, r, ll, rr);
}
void insert(int x, int l, int r, int ll, int rr, int v) {
    if (l > rr || r < ll) return ;
    if (l >= ll && r <= rr) { T[x].rot = ins(T[x].rot, v); return ; }
    pushdown(x);
    insert(LS, l, MID, ll, rr, v); insert(RS, MID + 1, r, ll, rr, v);
}
void query(int x, int l, int r, int pos, int v) {
    if (l == r) return quesig(x, v);
    pushdown(x);
    if (pos <= MID) query(LS, l, MID, pos, v);
    else query(RS, MID + 1, r, pos, v);
}

int main(void) {
    freopen("stack.in", "r", stdin);
    freopen("stack.out", "w", stdout);
    n = read(); q = read();
    while (q--) {
        op = read(); l = read(); r = read();
        if (op == 0) insert(1, 1, n, l, r, read());
        if (op == 1) del(1, 1, n, l, r);
        if (op == 2) query(1, 1, n, l, r);
    }
    return 0;
}
