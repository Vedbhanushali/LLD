#include<iostream>
#include<algorithm>

using namespace std;

/* -------- Utilities ------------ */
static const string BASE62 = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

string base62Encode(uint64_t n) {
    if (n == 0) return "0";
    string s;
    while (n > 0) {
        s.push_back(BASE62[n % 62]);
        n /= 62;
    }
    reverse(s.begin(), s.end());
    return s;
}

bool isValidUrl(const string& url) {
    // r find last occurence of string 
    // must start with http:// or https://
    return url.rfind("http://", 0) == 0 || url.rfind("https://", 0) == 0;
}

bool isValidAlias(const string& s) {
    if (s.empty() || s.size() > 32) return false;
    for (char c : s) {
        if (!isalnum((unsigned char)c) && c != '-' && c != '_') return false;
    }
    return true;
}

int main() {

    return 0;
}