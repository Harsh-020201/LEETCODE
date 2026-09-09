class Solution {
public:
    long long countCommas(long long n) {
        long long total = 0;
        long long x = 1000;                 // first threshold where commas start
        while (x <= n) {
            total += n - x + 1;             // every number >= x picks up one MORE comma
            x *= 1000;                      // move to next threshold (10^6, 10^9, ...)
        }
        return total;
    }
};