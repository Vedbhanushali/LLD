#include "SocialMedia.h"
#include "User.h"
#include "Post.h"

void SocialMedia::addUser(int userId, string name) {
    users[userId] = make_shared<User>(userId, name);
    cout << "User " << name << " added to the system.\n";
}

void SocialMedia::follow(int followerId, int followeeId) {
    if (users.count(followerId) && users.count(followeeId)) {
        // checking if both follower and followee user exist
        users[followerId]->follow(followeeId);
    }
}

void SocialMedia::unfollow(int followerId, int followeeId) {
    if (users.count(followerId) && users.count(followeeId)) {
        users[followerId]->unfollow(followeeId);
    }
}

void SocialMedia::createPost(int userId, string content) {
    if (users.count(userId)) {
        shared_ptr<Post> newPost = make_shared<Post>(postIdCounter++, content, users[userId]);
        users[userId]->addPost(newPost);
        posts[newPost->getId()] = newPost;
    }
}

void SocialMedia::deletePost(int userId, int postId) {
    if (posts.count(postId) && users.count(userId)) {
        users[userId]->deletePost(postId);
        posts.erase(postId);
    }
}

void SocialMedia::getFeeds(int userId, int N) {
    if (!users.count(userId)) return; //user does not exist

    vector<shared_ptr<Post>> feed;
    const auto& followingList = users[userId]->getFollowing();

    // Collect own posts
    feed.insert(feed.end(), users[userId]->getPosts().begin(), users[userId]->getPosts().end());

    // Collect followed users' posts
    for (int followedId : followingList) {
        feed.insert(feed.end(), users[followedId]->getPosts().begin(), users[followedId]->getPosts().end());
    }

    // Sort feed by timestamp (latest first)
    sort(feed.begin(), feed.end(), [](shared_ptr<Post> a, shared_ptr<Post> b) {
        return a->getTimestamp() > b->getTimestamp();
    });

    cout << "\nFeed for user " << users[userId]->getName() << ":\n";
    for (int i = 0; i < min(N, (int)feed.size()); i++) {
        feed[i]->displayPost();
    }
    cout << endl;
}

void SocialMedia::browseFeeds(int N) {
    //get all post
    vector<shared_ptr<Post>> allPosts;
    for(auto it = posts.begin(); it != posts.end(); it++) {
        allPosts.push_back(it->second);
    }
    sort(allPosts.begin(), allPosts.end(), [](shared_ptr<Post> a, shared_ptr<Post> b) {
        return a->getTimestamp() > b->getTimestamp();
    });
    for(int i=0;i<min(N,(int)allPosts.size());i++) {
        allPosts[i]->displayPost();
    }
    cout << endl;
}