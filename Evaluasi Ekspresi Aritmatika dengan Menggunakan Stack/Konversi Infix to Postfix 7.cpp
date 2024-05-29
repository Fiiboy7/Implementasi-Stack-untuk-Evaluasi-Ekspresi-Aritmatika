#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <cctype>
#include <unordered_map>

using namespace std;

bool isOperator(char c){
    return c == '+' || c == '-' || c == '*' || c == '/';
}

bool isParenthesis(char c){
    return c == '(' || c == ')';
}

int precedence (char op){
    if(op == '+' || op == '-'){
        return 1;
    } else if (op == '*' || op == '/' || op == '%'){
        return 2;
    }
    return 0;
}

bool isHigherPrecedence(char op1, char op2){
    return precedence(op1) > precedence(op2);
}

vector<string> tokenize(const string& expr){
    vector<string> tokens;
    string num = "";
    
    for(size_t i = 0;i < expr.length(); ++i){
        char c = expr[i];
        
        if(isspace(c)){
            continue;
        }
        
        if(isdigit(c)){
            num += c;
        } else {
            if(!num.empty()){
                tokens.push_back(num);
                num.clear();
            }
            
            if(isOperator(c) || isParenthesis(c)){
                if(c == '-'){
                    if(i == 0 || isOperator(expr[i - 1]) || expr[i - 1] == '('){
                        tokens.push_back("-1");
                        tokens.push_back("*");
                        continue;
                    }
                }
                tokens.push_back(string(1, c));
            } else {
                num += c;
            }
        }
    }
    
    if(!num.empty()){
        tokens.push_back(num);
    }
    return tokens;
}

vector<string> infixToPostfix(const vector<string>&tokens){
    vector<string> output;
    stack<string> opStack;
    unordered_map<string, int> precedence = {{"+", 1}, {"-", 1}, {"*", 2}, {"/", 2}, {"%", 2}};
    
    for(const string&token : tokens){
        if(isdigit(token[0]) || (token[0] == '-' && token.size() > 1 && isdigit(token[1]))){
            output.push_back(token);
        } else if(isOperator(token[0])){
            while(!opStack.empty() && opStack.top() != "("&& precedence[opStack.top()] >= precedence[token]){
                output.push_back(opStack.top());
                opStack.pop();
            }
        opStack.push(token);
        } else if(token == "("){
            opStack.push(token);
        } else if(token == ")"){
            while (!opStack.empty() && opStack.top() != "("){
               output.push_back(opStack.top());
               opStack.pop();
            }
            opStack.pop();
      }
    }
    while (!opStack.empty()){
        output.push_back(opStack.top());
        opStack.pop();
    }
    return output;
}

void printPostfix(const vector<string>&postfix){
    for(size_t i = 0;i < postfix.size(); ++i){
        cout << postfix[i];
        if(i != postfix.size() - 1){
            cout << " ";
        }
    }
    cout << endl;
}

int main(){
    string input;
    getline(cin, input);
    
    vector<string> tokens = tokenize(input);
    vector<string> postfix = infixToPostfix(tokens);
    printPostfix(postfix);
    
    return 0;
}
