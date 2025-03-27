#ifndef USER_H
#define USER_H

#include <iostream>
#include <memory>
#include <unordered_set>
#include <vector>

using namespace std;
class Post;

class User {
private:
    int id;
    string name;
    unordered_set<int> following;
    vector<shared_ptr<Post>> posts;

public:
    User(int userId, string userName);
    int getId() const;
    string getName() const;
    void follow(int userId);
    void unfollow(int userId);
    const unordered_set<int>& getFollowing() const;
    void addPost(shared_ptr<Post> post);
    void deletePost(int postId);
    const vector<shared_ptr<Post>>& getPosts() const;
};

#endif // USER_H
