class Solution {
public:
    int maxActiveSectionsAfterTrade(string s) {

        int n = s.length();

        int totalOnes = 0;
        int prevZeroBlock = INT_MIN;
        int maxMerge = 0;

        int i = 0;

        while (i < n) {

            int j = i;

            while (j < n && s[j] == s[i])
                j++;

            int len = j - i;

            if (s[i] == '1') {
                totalOnes += len;
            } 
            else {
                maxMerge = max(maxMerge, prevZeroBlock + len);
                prevZeroBlock = len;
            }

            i = j;
        }

        return totalOnes + maxMerge;
    }
};