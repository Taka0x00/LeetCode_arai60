class Solution {
 public:
    std::vector<string> generateParenthesis(int n) {
        std::vector<string> results;
        for (int bit_pattern = 0; bit_pattern < (1 << (2 * n)); bit_pattern++) {
            if (IsValidBitString(bit_pattern, n)) {
                results.push_back(ToParentheses(bit_pattern, n));
            }
        }

        return results;
    }
 private:
    bool IsValidBitString(int bit_pattern, int n) {
        int open_brackets = 0;
        int close_brackets = 0;

        for (int bit_position = 2 * n - 1; bit_position >= 0; bit_position--) {
            if (bit_pattern & (1 << bit_position)) {
                open_brackets++;
            }
            else {
                close_brackets++;
            }

            if (open_brackets < close_brackets) {
                return false;
            }
        }

        return open_brackets == close_brackets;
    }

    string ToParentheses(int bit_pattern, int n) {
        string parentheses;

        for(int i = 2 * n - 1; i >= 0; i--) {
            if(bit_pattern & (1 << i)) {
                parentheses += '(';            
            }
            else {
                parentheses += ')';            
            }

        }

        return parentheses;
    }
};
