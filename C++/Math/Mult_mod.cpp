long long multiply_modulo(long long a, long long b, long long m) {
    long long result = 0;
    a %= m;

    while (b > 0) {
        if (b & 1) {
            result = (result + a) % m;
        }
        a = (2 * a) % m;
        b >>= 1;
    }

    return result;
}
