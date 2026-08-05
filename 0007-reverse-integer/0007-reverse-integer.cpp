#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
int reverse(int n){
    long int revNum=0;
    long int lastDigit;
    while(n !=0){
        lastDigit=n%10;
        if( revNum > INT_MAX /10 ||(revNum == INT_MAX /10 && lastDigit >7)){
                return 0;
            }
            if( revNum < INT_MIN /10 ||(revNum == INT_MIN /10 && lastDigit <-8)){
                return 0;
            }
        revNum = (revNum*10) + lastDigit;
        n=n/10;
    }
     return revNum;
}
 
};
