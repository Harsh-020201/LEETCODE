class Solution {
public:
    string smallestSubsequence(string s) {
        vector<int> last(256);
        for(int i=0;i<s.size();i++){
            last[s[i]]=i;
        }
        vector<bool> vis(256,false);
        stack<char> st;
        for(int i=0;i<s.size();i++){
            char ch=s[i];
            if(vis[ch]){
                continue;
            }
            while(!st.empty() && st.top()>ch && last[st.top()]>i){
                vis[st.top()]=false;
                st.pop();
            } 
            st.push(ch);
            vis[ch]=true;

        }
        string ans="";
        while(!st.empty()){
            ans +=st.top();
            st.pop();
        }
        reverse(ans.begin(),ans.end());
         return ans; 
    }
};