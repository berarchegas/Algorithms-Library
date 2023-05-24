// Satanic Panic
//
// Given n points with no three collinear
// Counts the number of k-sided convex polygons
// O(k * n^3)

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct vetor {
    int ini, fim;
    complex<double> pt;
    vetor(int _ini = 0, int _fim = 0, complex<double> _pt = complex<double>()) {
        ini = _ini;
        fim = _fim;
        pt = _pt;
    }
};

const int k = 5;
const int MAXN = 305;

ll dp[MAXN][MAXN][k + 1];
vector<vetor> linhas;
vector<complex<double>> pontos;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        pontos.push_back(complex<double>(a, b));
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            linhas.push_back(vetor(i, j, pontos[j] - pontos[i]));
        }
    }
    sort(linhas.begin(), linhas.end(), [&] (vetor a, vetor b) {
        return arg(a.pt) < arg(b.pt);
    });
    for (int i = 0; i < n; i++) dp[i][i][0] = 1;
    for (vetor x : linhas) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < k; j++) {
                dp[i][x.fim][j + 1] += dp[i][x.ini][j];
            }
        }
    }
    ll ans = 0;
    for (int i = 0; i < n; i++) ans += dp[i][i][5];
    cout << ans << '\n';
    return 0;
}