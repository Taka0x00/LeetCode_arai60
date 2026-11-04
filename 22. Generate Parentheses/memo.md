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
プログラムを書き終わった後に、わざわざforループで回す変数を括弧の並びに変換する必要はないのではないかと思い、直接数字で判定する方針に書き換えた。それに伴って、括弧の並びの判定関数も、直接数字で判定するように書き換えた。余計に探索している範囲が80%ほど存在していたが、今回はひとまず飛ばした。それでも実行速度とメモリ使用量が1stと比べて大幅に改善された。
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
## 3rd
今回の問題ではバックトラッキングという手法が有効らしい。この問題では選択肢が開き括弧と閉じ括弧の二通りのみだったため、2ndのような二進数表記で偶然うまくいったが、もし選択肢が3個以上になるとうまくいかない。選択肢が複数あるときは`BackTrack`の再帰に関連する部分でforループを組み込むと解決するらしい。良い方法かはわからないが、感動した。

有効な括弧列が`(`+`A`+`)`+`B`に限られることを利用する解法もあるらしいが、それで十分なのかを後で判定するのがぱっと見るだけでは難しいのではないかと思い、今回は無し。

最終的には、ほかの人が採用していた、愚直に文字列の最後に`(`と`)`のどちらかを挿入するコードになった。
```cpp
class Solution {
 public:
    vector<string> generateParenthesis(int n) {
        std::string brackets_substring;
        std::vector<std::string> all_parentheses;

        GenerateParen(brackets_substring, n, 0, 0, all_parentheses);

        return all_parentheses;
    }

 private:
    void GenerateParen(
        std::string& brackets_substring,
        int brackets_pair,
        int num_open_brackets,
        int num_close_brackets,
        std::vector<std::string>& all_parentheses) {

        if (brackets_substring.size() == 2 * brackets_pair) {
            all_parentheses.push_back(brackets_substring);
            return;
        }

        if (num_open_brackets < brackets_pair) {
            brackets_substring += '(';
            GenerateParen(
                brackets_substring,
                brackets_pair,
                num_open_brackets + 1,
                num_close_brackets,
                all_parentheses);
            brackets_substring.pop_back();
        }

        if (num_close_brackets < num_open_brackets) {
            brackets_substring += ')';
            GenerateParen(
                brackets_substring,
                brackets_pair,
                num_open_brackets,
                num_close_brackets + 1,
                all_parentheses);
            brackets_substring.pop_back();
        }
    }
};
```
https://github.com/frinfo702/leetcode-arai60/pull/10/changes/a349d8174886d59c7185d7ddd7daeeddac47dea2#r1881386807

コーディングの優先順位は、コードの複雑さ->メモリ使用量->計算量、らしい。

このコードを書いてる途中で、GPTがカタラン数`Cn`と関連していることに言及した。時間計算量は`O(Cn * n)`で、出力する文字列の総量に比例するらしい。他の人のPRでも軽く`Cn`に言及しており、少し合流できた気がしてうれしかった。

まだ、計算量に意識が向いていない。方針を立てるのにも、コーディングするのも、他の人のコードを読むのもすべてに時間がかかって負担がすごい。

参考にさせていただいたPR
- https://github.com/dxxsxsxkx/leetcode/blob/17ee2cb9ad556e9b9623dbcf42382d9b4e220d25/22_generate_parentheses/memo.md

サブルーチンのIsValid関数を採用しない書き方。生成されるのを正しい文字列に限定することで、終了判定を文字列の長さが2nというシンプルな条件にしているのがいい。
- https://github.com/Ryotaro25/leetcode_first60/pull/58/changes#r1997665903

この人のGenerateParenという命名が分かりやすくて、好み。BackTrackは何が返ってくるのかわからないからあまり好きではない命名らしい。
