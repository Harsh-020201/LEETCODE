class Solution {
public:
    long long countCommas(long long n) {
        long long total = 0;
        long long start = 1;   // smallest number with `digits` digits
        int digits = 1;

        while (start <= n) {
            long long end = start * 10 - 1;      // largest number with this many digits
            long long hi = min(end, n);
            long long count = hi - start + 1;    // how many numbers in this digit-length band
            int commas = (digits - 1) / 3;       // commas per number of this length
            total += count * commas;

            start *= 10;
            digits++;
        }

        return total;
    }
};