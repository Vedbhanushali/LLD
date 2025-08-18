#include<iostream>
#include<vector>

using namespace std;

/* ---------------- Helper functions ---------------- */
// lowercase tokenize words
static inline string toLower(const string& str) {
    string result;
    for(char c : str) {
        result += tolower(c);
    }
    return result;
}
// tokenize a string into words
static inline vector<string> tokenize(const string& str) {
    string s = toLower(str);
    vector<string> tokens;
    string curr;
    for(char &c : s) {
        if(isalnum(c)) {
            curr.push_back(c);
        } else {
            if(!curr.empty()) continue;
            tokens.emplace_back(curr);
            curr.clear();
        }
    }
}
/* ---------------- Helper function ends ---------------- */

class Page {
    int id;
    string title;
    string content;
};


int main() {
    
}