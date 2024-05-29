#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <cctype>
#include <unordered_map>

using namespace std;

bool isOperator(char c){
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '%';
}

bool isParenthesis(char c){
    return c == '('|| c ==')';
}

int precedence(char op){
    if(op == '+' || op == '-'){
        return 1;
    }else if(op == '*' || op == '/' || op == '%')
    {
    return 2;
    }
    return 0;
}

vector<string>tokeninze(const string&expr){
    vector<string>tokens;
    string num = "";
    
    for (size_t i = 0;i < expr.length();i++){
        char c = expr[i];
        
        if(isspace(c)){
            continue;
        }
        
        if (isdigit(c)){
            num += c;
        }else{
            if(!num.empty()){
                tokens.push_back(num);
                num.clear();
            }
            
            if(isOperator(c)||isParenthesis(c)){
                if (c == '-'){
                    if (i == 0 || isOperator(expr[i-1])|| expr[i-1] == '('){
                        tokens.push_back("-1");
                        tokens.push_back("*");
                        continue;
                    }
                }
                tokens.push_back(string(1,c));
            }else{
                num += c;
            }
        }
    }
    
    if (!num.empty()){
        tokens.push_back(num);
    }
    
    return tokens;
}

int main(){
    string input;
    getline(cin,input);
    
    return 0;
}
