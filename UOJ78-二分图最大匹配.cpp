#include "cstdio"
#include "vector"
#include "iostream"
#include "cstring"
#include "queue"
#include "algorithm"
#include "set"
#include "map"

using namespace std;
typedef long long LL;
const int N = 1e5 + 7;
vector<vector<int> > G;
vector<int> pa, pb;
vector<int> vis;

//每次从左边的未盖点出发，寻找右边的一个未盖点。若没找到，则先右面一个对面一个已盖点，再从它对应的左边的已盖点出发找未盖点。
//由于算法的本质在于在所有可能的左边的点中找一个对应右面的未盖点，因此没一个左边的点的复杂度是O(m)。
//寻找到新的增广路，并不会更改原来的点是已改点或者未盖点的事实
bool dfs(int u) {
    vis[u] = true;
    for (int v : G[u]) {
        //右边的点是未盖点
        if (pb[v] == -1) {
            pb[v] = u;
            pa[u] = v;
            return true;
        }
    }

    //相连的右边没有未盖点
    for (int v : G[u]) {
        int next_u = pb[v];
        if (vis[next_u] != -1)
            continue;
        if (dfs(next_u)) {
            pb[v] = u;
            pa[u] = v;
            return true;
        }
    }
    return false;
}

void solve() {
    int na, nb, m;
    scanf("%d%d%d", &na, &nb, &m);
    G.resize(na);
    pa = vector<int>(na, -1);
    pb = vector<int>(nb, -1);
    vis = vector<int>(na, -1);
    for (int i = 0; i < m; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        x--;
        y--;
        G[x].push_back(y);
    }

    int cnt = 0;
    for (int i = 0; i < na; i++) {
        vis = vector<int>(na, -1);
        if (dfs(i))
            cnt++;
    }

    printf("%d\n", cnt);
    for (int i = 0; i < na; i++) {
        printf("%d%c", pa[i] + 1, i == (na - 1) ? '\n' : ' ');
    }
}

int main() {
#ifdef LOCAL
    freopen("in", "r", stdin);
#endif
    solve();

}