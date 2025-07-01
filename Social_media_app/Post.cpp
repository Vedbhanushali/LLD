#include "Post.h"

Post::Post(int postId, string postContent, shared_ptr<User> postOwner)
    : id(postId), content(postContent), timestamp(time(0)), owner(postOwner) {}

int Post::getId() const { return id; }
string Post::getContent() const { return content; }
time_t Post::getTimestamp() const { return timestamp; }
shared_ptr<User> Post::getOwner() const { return owner; }

void Post::displayPost() const {
    cout << "[Post ID: " << id << "] " << content << " - By: " << owner->getName() << " at " << ctime(&timestamp);
}
