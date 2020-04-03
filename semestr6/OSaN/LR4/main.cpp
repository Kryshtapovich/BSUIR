#include <iostream>
#include <map>
#include <string>

using namespace std;

const map<char, string> dict = {
        {'a', ".-"},
        {'b', "-..."},
        {'c', "-.-."},
        {'d', "-.."},
        {'e', "."},
        {'f', "..-."},
        {'g', "--."},
        {'h', "...."},
        {'i', ".."},
        {'j', ".---"},
        {'k', "-.-"},
        {'l', ".-.."},
        {'m', "--"},
        {'n', "-."},
        {'o', "---"},
        {'p', ".--."},
        {'q', "--.-"},
        {'r', ".-."},
        {'s', "..."},
        {'t', "-"},
        {'u', "..-"},
        {'v', "...-"},
        {'w', ".--"},
        {'x', "-..-"},
        {'y', "-.--"},
         {'z', "--.."}
};

string to_morse(string s){
    string ans;
    for (int i = 0; i < s.size(); i++){
        if ((s[i] >= 'A' && s[i] <= 'Z') || (s[i]>='a' && s[i]<='z')){
            ans += dict.at(tolower(s[i])) + '/';
        }
        else ans += s[i];
    }
    return ans;
}

int main() {
    string s;
    cout << "Enter string: ";
    cin >> s;
    cout << "Morse string: " << to_morse(s) << endl;
    return 0;
}
