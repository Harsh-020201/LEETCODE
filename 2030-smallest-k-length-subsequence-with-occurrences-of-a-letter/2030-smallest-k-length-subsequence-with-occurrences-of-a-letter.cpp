class Solution {
public:
#define ll int
#define pb push_back
#define st string
    string smallestSubsequence(string s, int k, char c, int r) {
        ll n = s.size();
        vector<ll> a(n, 0);
        ll x = 0;

        //  special char suffix counting
        for (ll i = n - 1; i >= 0; i--) {
            if (s[i] == c) {
                x++;
            }
            a[i] = x;
        }

        // special char demand is atleast  y=r and total demand is k
        ll y = r;

        stack<char> q;

        for (ll i = 0; i < n; i++) {
            char d = s[i];
            // from this place special char suffix counting
            ll u = a[i];

            // total remaining char
            ll v = (n - i);

            while (!q.empty()) {
                char e = q.top();

                // If bigger char, it has no power to eleminate other char
                if (d >= e) {
                    break;
                }

                if (e == c) {
                    // If it is special char then check is the remaining part of
                    // string satisfy the necessity
                    if (u >= (y + 1) && v >= (k + 1)) {
                        q.pop();
                        y++;
                        k++;
                    } else {
                        break;
                    }
                } else {
                    // If it is not special char then also check is the
                    // remaining part of string satisfy the necessity
                    if (u >= y && v >= (k + 1)) {
                        q.pop();
                        k++;
                    } else {
                        break;
                    }
                }
            }

            // push in the stack
            if (k > 0) {
                if (d == c) {
                    // If still there is demand and char is special char then
                    // definately push it
                    k--;
                    y--;
                    q.push(d);
                } else {
                    // If not a special char then check due to this the least
                    // count of special char should not be hampered
                    if (k - 1 >= y) {
                        q.push(d);
                        k--;
                    }
                }
            }
        }

        st ans = "";

        // pop the stack characters and reverse them to form the string
        while (!q.empty()) {
            char d = q.top();
            q.pop();
            ans.pb(d);
        }

        reverse(ans.begin(), ans.end());

        return ans;
    }
};