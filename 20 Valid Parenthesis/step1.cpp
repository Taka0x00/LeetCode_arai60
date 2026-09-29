class Solution {
public:
    bool isValid(string s) {
        stack<char> st;

        for(char c : s) {
            if(c == '(' || c == '{' || c == '[')
            {
                st.push(c);
            }
            else if (c == ')' || c == '}' || c == ']')
            {
                if(st.empty()){
                    return false;
                }

                char top = st.top();
                if(c == ')' && top != '(') return false;
                if(c == '}' && top != '{') return false;
                if(c == ']' && top != '[') return false;

                st.pop();
            }

        }

        if(st.empty()) return true;
        else return false;
        
    }
};
