#ifndef POST_H
#define POST_H

#include <iostream>
#include <ctime>
#include <memory>
#include "User.h"

using namespace std;

// Forward declaration
class User;

class Post {
    private:
        int id;
        string content;
        time_t timestamp;
        shared_ptr<User> owner;

    public:
        Post(int postId, string postContent, shared_ptr<User> postOwner);
        int getId() const;
        string getContent() const;
        time_t getTimestamp() const;
        shared_ptr<User> getOwner() const;
        void displayPost() const;
};

#endif // POST_H
