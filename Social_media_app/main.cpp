#include "SocialMedia.h"

int main() {
    SocialMedia app;

    app.addUser(1, "Alice");
    app.addUser(2, "Bob");
    app.addUser(3, "Charlie");

    app.follow(1, 2);
    app.follow(1, 3);

    app.createPost(2, "Bob's first post!");
    app.createPost(3, "Charlie's first post!");
    app.createPost(1, "Alice's first post!");
    app.deleteUser(2);
    app.getFeeds(2);
    cout<<"Browse feeds"<<endl;
    app.browseFeeds(4);

    app.getFeeds(1);
    app.deletePost(2, 1);
    app.getFeeds(1);

    return 0;
}
