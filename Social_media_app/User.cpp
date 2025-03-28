#include "User.h"
#include "Post.h"

User::User(int userId, string userName) : id(userId), name(userName) {}

int User::getId() const { return id; }
string User::getName() const { return name; }

void User::follow(int userId) {
    if (following.find(userId) == following.end()) {
        //if does not exist, add to following
        following.insert(userId);
        cout << name << " followed user " << userId << endl;
    }
}

void User::unfollow(int userId) {
    if (following.find(userId) != following.end()) {
        //if exists, remove from following
        following.erase(userId);
        cout << name << " unfollowed user " << userId << endl;
    }
}

const unordered_set<int>& User::getFollowing() const { return following; }

void User::addPost(shared_ptr<Post> post) {
    posts.push_back(post);
    cout << name << " created a post: " << post->getContent() << endl;
}

void User::deletePost(int postId) {
   for (size_t i = 0; i < posts.size(); i++) {
        if (posts[i]->getId() == postId) {
            posts.erase(posts.begin() + i);
            cout << "Post ID " << postId << " deleted by " << name << endl;
            break;  
        }
    }
}

void User::deleteAllPosts() {
    posts.clear();
}

const vector<shared_ptr<Post>>& User::getPosts() const { return posts; }
