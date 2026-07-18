#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int reverse(int x) {
        long int rev_num=0;
        long int last_dig;
        while(x!=0){
            last_dig=x%10;
            if( rev_num > INT_MAX /10 ||(rev_num == INT_MAX /10 && last_dig >7)){
                return 0;
            }
            if( rev_num < INT_MIN /10 ||(rev_num == INT_MIN /10 && last_dig <-8)){
                return 0;
            }
            rev_num=(rev_num*10)+last_dig;
            x=x/10;
        }
        return rev_num;
    }
};
