// __int128_t
//
// nao pode ler nem printar
// pra ler use a to128
// pra printar use a tostring

__int128_t to128(string s) {
    __int128_t a = 0;
    __int128_t pot = 1;
    int n = s.size();
    for (int i = n - 1; i >= 0; i--, pot *= 10) {
        a += (s[i] - '0') * pot;
    }
    return a;
}
string tostring(__int128_t a) {
    string s;
    while (a) {
        s += (a % 10) + '0';
        a /= 10;
    }
    reverse(s.begin(), s.end());
    return (s.empty() ? "0" : s);
}