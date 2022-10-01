// SOS DP
//
// SOS DP inversa em h
for (int mask = 0; mask < (1 << n); mask++) {
    if(__builtin_popcount(mask) % 2) {
        h[mask] *= -1;
        add(h[mask], 0);
    }
}
for (int i = 0; i < n; i++) {
    for (int mask = (1 << n) - 1; mask >= 0; mask--) {
        if ((mask & (1 << i)) != 0) {
            add(h[mask], h[mask ^ (1 << i)]);
        }
    }
}
for (int mask = 0; mask < (1 << n); mask++) {
    if (__builtin_popcount(mask) % 2) {
        h[mask] *= -1;
        add(h[mask], 0);
    }
}
// dp1[x] = qtd de submasks de x
// dp2[x] = qtd de supermasks de x
// dp1[ inverso de x ] = qtd de disjuntos de x 
// aqui os valores vao ate 1e6
for (int i = 0; i <= 19; i++) {
    for (int j = (1<<20)-1; j >= 0; j--) {
        if (j & (1<<i)) {
            dp1[j] += dp1[j ^ (1<<i)];
        }
    }
    for (int j = 0; j <= 1e6; j++) {
        if (!(j & (1<<i)) && (j ^ (1<<i)) <= 1e6) {
            dp2[j] += dp2[j ^ (1<<i)];
        }
    }
}