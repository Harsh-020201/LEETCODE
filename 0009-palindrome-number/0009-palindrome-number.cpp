class Solution {
public:
    bool isPalindrome(int x) {
        long int rev_num=0;
        long int last_dig;
        long int dup=x;
        if(x<0){
           return false;
        }
        while(x!=0){
            last_dig=x%10;
            rev_num=(rev_num*10)+last_dig;
            x/=10;
            
        }
       if(dup==rev_num){
                return true;
            }
            else{
                return false;
            }
    }
};