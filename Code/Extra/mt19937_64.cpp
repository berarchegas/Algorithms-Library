// mt19937_64
//
// Random generator for long long

mt19937 rng((int) chrono::steady_clock::now().time_since_epoch().count());
ll rand = rng();