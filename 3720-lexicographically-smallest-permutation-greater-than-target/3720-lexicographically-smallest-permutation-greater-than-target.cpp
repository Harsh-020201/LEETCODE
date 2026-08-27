class Solution {
public:
    string lexGreaterPermutation(string s, string target) {
        int n = s.size();

        int cnt[26] = {};
        for (char c : s) {
            cnt[c - 'a']++;
        }

        string prefix;

        // Try to match target as much as possible
        for (int i = 0; i < n; i++) {

            int x = target[i] - 'a';

            // We can keep the prefix equal to target
            if (cnt[x] > 0) {
                prefix += target[i];
                cnt[x]--;
                continue;
            }

            // target[i] is unavailable.
            // Try to put the smallest character > target[i].
            for (int c = x + 1; c < 26; c++) {
                if (cnt[c] > 0) {
                    string ans = prefix;

                    ans += char('a' + c);
                    cnt[c]--;

                    // Put remaining characters in sorted order
                    for (int k = 0; k < 26; k++) {
                        while (cnt[k] > 0) {
                            ans += char('a' + k);
                            cnt[k]--;
                        }
                    }

                    return ans;
                }
            }

            // No larger character here.
            // We must backtrack.
            break;
        }

        /*
         * Backtracking:
         *
         * prefix currently contains the longest prefix
         * that was equal to target.
         *
         * Try changing the rightmost position to a
         * character greater than target[pos].
         */

        for (int pos = (int)prefix.size() - 1; pos >= 0; pos--) {

            // Restore the character used at prefix[pos]
            cnt[prefix[pos] - 'a']++;

            int targetChar = target[pos] - 'a';

            // Find the smallest available character
            // greater than target[pos]
            for (int c = targetChar + 1; c < 26; c++) {

                if (cnt[c] > 0) {

                    string ans = target.substr(0, pos);

                    ans += char('a' + c);
                    cnt[c]--;

                    // Smallest possible suffix
                    for (int k = 0; k < 26; k++) {
                        while (cnt[k] > 0) {
                            ans += char('a' + k);
                            cnt[k]--;
                        }
                    }

                    return ans;
                }
            }
        }

        return "";
    }
};