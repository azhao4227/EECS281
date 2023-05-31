// Project Identifier: 1CAEF3A0FEDD0DEC26BA9808C69D4D22A9962768


#include <iostream>
#include <deque>
#include <stack>
#include <iostream>
using namespace std;

bool balanced(){
        
    char character;
    
    deque<char> chars;

    while(cin >> character){

        if(character == '(' || character == '{' || character == '['){
            chars.push_back(character);
        }

        if(character == ')' || character == '}' || character == ']'){

            if(chars.empty()){
                return false;
            } else {

                if(character == ')'){
                    if(chars.back() != '('){
                        return false;
                    }
                } else if (character == ']'){
                    if(chars.back() != '['){
                        return false;
                    }
                } else {
                    if(chars.back() != '{'){
                        return false;
                    }
                }

                chars.pop_back();
            }
            

        }


    }

    if(chars.empty()){
        return true;
    } else {
        return false;
    }

}

int main() {

    if(balanced()){
        cout << "Balanced" << endl;
    }else{
        cout << "Not balanced" <<  endl;
    }

    return 0;
}
