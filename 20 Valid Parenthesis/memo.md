## step 1
頭の中の方針

特定の開き括弧が入力されたら、対応する閉じ括弧をスタックに積む。
閉じ括弧が入力されたときにスタックの一番上と異なる(か、スタックが空)なら``false``を返す
最終的にスタックが空であれば``true``を返す

実装
```cpp
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
```

頭の中で実装したのとプログラムが異なっていたので、再実装。こちら側だと実行速度が少し遅かった
```cpp
class Solution {
public:
    bool isValid(string s) {
        stack<char> st;

        for(char c : s) {
            if(c == '(' || c == '{' || c == '['){
                if(c == '(') st.push(')');
                if(c == '{') st.push('}');
                if(c == '[') st.push(']');
            }
            else if (c == ')' || c == '}' || c == ']')
            {
                if(st.empty() || c != st.top()){
                    return false;
                }

                st.pop();
            }

        }
        
        return st.empty();
    }
};
```

## step 2
プッシュダウンオートマトンという知らない単語が出てきた。

### 他の人の解法

スタックを用いる解法という意味で大差はなかったが、括弧の対応規則が人によって違っていたのが面白かった。自分はif文を三個作って無理やり通るプログラムを作ってしまった。

- https://github.com/SuperHotDogCat/coding-interview/pull/6
この人は対応規則をデータで持っていた(良さそう、好き)

- https://github.com/colorbox/leetcode/pull/4
この人は対応規則を定めるbool関数を作っていた(そのような実装方法があるのかと感心した)

実装(かなりすっきりしているが、括弧以外の文字が入ったときには想定と異なる動きをしてしまう。)
```cpp
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
```
