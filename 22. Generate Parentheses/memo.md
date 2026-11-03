## 1st
初めは帰納法でうまく回すのだろうな、と思ったが、どのような処理を回すのかという言語化がうまくできなかった。

最終的には、0から2^2nまで回して、正しい括弧の並びとなるものを配列に挿入する方法をとった。

括弧の並びが正しいかどうかの判定には、20番の問題で書いたプログラムを流用することにした。
```cpp
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
```
## 2nd
プログラムを書き終わった後に、わざわざforループで回す変数を括弧の並びに変換する必要はないのではないかと思い、直接数字で判定する方針に書き換えた。それに伴って、括弧の並びの判定関数も、直接数字で判定するように書き換えた。実行速度とメモリ使用量が大幅に改善された。
```cpp
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

        for(int bit_position = 2 * n - 1; bit_position >= 0; bit_position--) {
            if(bit_pattern & (1 << bit_position)) {
                parentheses += '(';            
            }
            else {
                parentheses += ')';            
            }

        }

        return parentheses;
    }
};
```
