#include <iostream>
#include<stack>
#include<string>
#include<cctype>
using namespace std;

bool isOperator(char c){
return c == '+' || c == '-' || c=='*'||c=='/'||c=='%';
}

int precedence (char c){
if(c=='*'||c=='/'||c=='%'){
  return 2;
}else if(c=='+'||c=='-'){
    return 1;
  }else{
return -1;
  }
}

string infixToPostfix(const string& infix){
stack<string> stack;
  string postfix;
  bool expectOperand = true;

for (size_t i=0; i < infix.length(); ++i){
  char ch = infix[i];

  if(isspace(ch)) continue;
  if(isdigit(ch)){
     while (i < infix.length() && isdigit(infix[i])){
           postfix += infix [i++];
     }
    postfix += " ";
    --i;
    expectOperand = false;
  }else if(ch =='-' && (expectOperand || infix[i-1]=='(')){
     postfix += "-1";
     stack.push("*");
     expectOperand = true;
  }else if(ch=='('){
      stack.push(string(1,ch));
      expectOperand = true;
  }else if(ch==')'){
      while(!stack.empty() && stack.top() != "("){
          postfix += stack.top() + " ";
          stack.pop();
      }
      if(!stack.empty() && stack.top() =="("){
          stack.pop();
      }
      expectOperand = false;
  }else if(isOperator(ch)){
    while(!stack.empty() && precedence(ch) <= precedence (stack.top()[0])){
        postfix += stack.top() + " ";
      stack.pop();
    }
    stack.push(string(1,ch));
    expectOperand;
  }
}
return postfix;
}

int main(){
  string infix_exp;
  getline(cin, infix_exp);
  string postfix_exp = infixToPostfix(infix_exp);
  cout<<postfix_exp<<endl;

  return 0;
}
