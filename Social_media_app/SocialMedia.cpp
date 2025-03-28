#include "SocialMedia.h"
#include "User.h"
#include "Post.h"

void SocialMedia::addUser(int userId, string name) {
    users[userId] = make_shared<User>(userId, name);
    cout << "User " << name << " added to the system.\n";
}



void SocialMedia::deleteUser(int userId) {
    // Using shared_ptr, once we remove references (from
    // the user map ), the object is freed automatically. 
    // deleting his posts
    if (users.count(userId)) {
        
        //Method 1:
        //removing all posts of the user
        auto userPosts = users[userId]->getPosts();
        for(auto post : userPosts) {
            deletePost(userId,post->getId());
        }
        //removing user from the system
        users.erase(userId); 
        
        // // Method 2:
        // // remove all posts of the user
        // auto userPosts = users[userId]->getPosts();
        // for(auto post : userPosts) {
        //     posts.erase(post->getId());
        // }
        // users[userId]->deleteAllPosts();
        // //removing user from the system
        // users.erase(userId); 
    } else {
        cout << "User with ID " << userId << " does not exist.\n";
    }
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
    // Using shared_ptr, once we remove all references (from
    // the posts map and the user's posts vector), the object
    // is freed automatically.
    if (posts.count(postId) && users.count(userId)) {
        users[userId]->deletePost(postId); //remove reference from user post list
        posts.erase(postId); //remove reference from posts map
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