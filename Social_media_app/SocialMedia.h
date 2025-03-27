#ifndef SOCIALMEDIA_H
#define SOCIALMEDIA_H

#include <iostream>
#include <memory>
#include <unordered_map>
#include <algorithm>

using namespace std;

class User;
class Post;

class SocialMedia {
private:
    unordered_map<int, shared_ptr<User>> users;
    unordered_map<int, shared_ptr<Post>> posts;
    int postIdCounter = 1;

public:
    void addUser(int userId, string name);
    void follow(int followerId, int followeeId);
    void unfollow(int followerId, int followeeId);
    void createPost(int userId, string content);
    void deletePost(int userId, int postId);
    void getFeeds(int userId, int N = 10);
    void browseFeeds(int N = 10) ;
};

#endif // SOCIALMEDIA_H
