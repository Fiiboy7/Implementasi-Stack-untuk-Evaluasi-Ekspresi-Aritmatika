#include <iostream>
#include <vector>
#include <string>

using namespace std;

bool isOperator(auto c){
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '%';
}

bool isDigit(auto c){
    return c >= '0' && c <= '9';
}

void parseInfix(const string& infix, vector<string>& result, int len){
    string num;
    for(int i = 0; i < len; i++){
        char c = infix[i];

        if (c == ' '){
            continue;
        }

        if (isDigit(c)){
            num += c;
            if (i == len - 1 || !isdigit(infix[i + 1])){
                result.push_back(num);
                num = "";
            }
        } else if (isOperator(c) || c == '(' || c == ')'){
            if (!num.empty()){
                result.push_back(num);
                num = "";
            }
            if (c == '-'){
                if (i == 0 || infix[i - 1] == '(' || isOperator(infix[i - 1])){
                    if (i + 1 < len && isDigit(infix[i + 1]) && !isOperator(infix[i - 1])){
                        num += c;
                        continue;
                    } else {
                        result.push_back("-1");
                        result.push_back("*");
                        continue;
                    }
                }
            }
            result.push_back(string(1, c));
        }
    }
    if (!num.empty()){
        result.push_back(num);
    }
}

void printResult(const vector<string>& result){
    for (const auto& str : result){
        cout << str << " ";
    }
    cout << endl;
}

int main(){
    string infix;
    getline(cin, infix);
    int len = infix.length();
    vector<string> result;
    parseInfix(infix, result, len);
    printResult(result);

    return 0;
}
