#include "System.h"

int main() {
    cout<<"Welcome to Poll Management System"<<endl;
    System sys;
    sys.createUser(1,"Ved");
    sys.createUser(2,"Vansh");
    sys.createUser(3,"Dhruv");

    sys.createPoll(1,"what is your age",{"1","2","3","4"}); //0
    sys.createPoll(1,"what is your fav sport",{"cricket","football","hockey","tennis"});//1
    sys.createPoll(2,"what is your fav color",{"red","green","blue","yellow"}); //2
    sys.createPoll(2,"what is your fav car",{"sedan","suv","hatchback","convertible"}); //3
    sys.createPoll(3,"what is your fav food",{"pizza","burger","pasta","samosa"}); //4

    sys.userPosts(1);
    sys.updatePoll(1,0,"what is your age?",{"1","2","3","4","5"});
    sys.userPosts(1);
    sys.userPosts(2);
    cout<<"Deleting polls of user 2"<<endl;
    sys.deletePoll(2,2);
    sys.userPosts(2);
    cout<<"Voting in polls"<<endl;
    sys.voteInPoll(1,0);
    sys.voteInPoll(2,0);
    sys.voteInPoll(1,1);
    sys.voteInPoll(1,2);
    sys.voteInPoll(1,3);
    sys.viewPollresult(0);
    sys.deletePoll(1,0);
    sys.viewPollresult(0);
    return 0;
}