class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> ans;

        for (int i = 0; i < (1 << (2 * n)); i++) {
            string s;

            for (int j = 0; j < 2*n; j++) {
                if (i & (1 << j)) {
                    s += ')';
                }
                else {
                    s += '(';
                }
            }

            if (isValid(s)) {
                ans.push_back(s);
            }
        }
        
        return ans;
    }

private:
    bool isValid(string s) {
        stack<char> st;

        for(char c : s) {
            if(match.contains(c)) {
                st.push(match[c]);
            }
            else {
                if( st.empty() || c != st.top() )
                    return false;

                st.pop();
            }
        }
        
        return st.empty();
    }

    std::map<char, char> match = {
        {'(', ')'},
        {'{', '}'},
        {'[', ']'}
    };
};
