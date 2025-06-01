#ifndef USER_H
#define USER_H

#include <iostream>
using namespace std;

class User {
    string id;
    string name;
    string bio;
    string imageUrl;
    public:
    User(string id, string name, string bio, string imageUrl);
};

#endif