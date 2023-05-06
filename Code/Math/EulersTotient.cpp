// Euler's Totient Function
//
// O(sqrt(n))

// be careful with overflow
int totient(int n){
	int ret = n;

	for (int i = 2; i*i <= n; i++) if (n % i == 0) {
		while (n % i == 0) n /= i;
		ret -= ret / i;
	}
	if (n > 1) ret -= ret / n;

	return ret;
}