// Trie Binaria
//

const int tam = 6e6 + 5, MAXL = 30; // deve ser qtd de numeros * qtd maxima de bits
// cuidado que MAXL deve ser exatamente o maior bit que pode estar aceso
// mudar pra ll se precisar

int at = 0, trie[tam][2], qtd[tam];

void insert(int x, int add) {
    int node = 0;
    for (int i = MAXL; i >= 0; i--) {
        int &a = trie[node][!!(x & (1 << i))];
        if (!a) {
            a = ++at;
        }
        node = a;
        qtd[node] += add;
    }
}

int maxTrie(int x) {
    // devolve max(x ^ y) para todo y na trie
	int node = 0, resp = 0;
	for (int i = MAXL; i >= 0; i--) {
        int bit = !!(x & (1 << i));
		if (qtd[trie[node][!bit]]) {
			resp += (1<<i);
			node = trie[node][!bit];
		}
		else {
			node = trie[node][bit];
		}
	}
	return resp;
}

int minTrie(int x) {
    // devolve min(x ^ y) para todo y na trie
    int node = 0, resp = 0;
	for (int i = MAXL; i >= 0; i--) {
        int bit = !!(x & (1 << i));
		if (qtd[trie[node][bit]]) {
			node = trie[node][bit];
		}
		else {
			resp += (1<<i);
			node = trie[node][!bit];
		}
	}
	return resp;
}