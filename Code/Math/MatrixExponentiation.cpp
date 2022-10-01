// Exponenciacao de Matriz
//
// Exemplo de como usar em Broken Profile DP + Mat Expo
int tam;
struct mat {
	ll m[tam][tam];
	mat() {
		for (int i = 0; i < tam; i++) {
			for (int j = 0; j < tam; j++) m[i][j] = 0;
		}
	}
	mat operator * (mat x) {
		mat resp;
		for (int i = 0; i < tam; i++) {
			for (int j = 0; j < tam; j++) {
				resp.m[i][j] = 0;
				for (int k = 0; k < tam; k++) {
					resp.m[i][j] += (m[i][k] * x.m[k][j]) % MOD;
					if (resp.m[i][j] >= M) resp.m[i][j] -= MOD;
				}
			}
		}
		return resp;
	}
};
 
mat expo(mat &a, ll e) {
	if (e == 1) return a;
	mat ans = expo(a, e/2);
	ans = ans * ans;
	if (e&1) ans = ans * a;
	return ans;
}