class Solution {
public:
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

private:
    std::map<char, char> match = {
        {'(', ')'},
        {'{', '}'},
        {'[', ']'}
    };
};
