#ifndef SYSTEM_H
#define SYSTEM_H

#include <iostream>
#include <unordered_map>
#include <memory>
#include <vector>
using namespace std;

class User;
class Poll;
class System {
    private :
        unordered_map<int,shared_ptr<User>> users;
        unordered_map<int,shared_ptr<Poll>> polls; //pollid - poll
        int pollCounter;
    public : 
        System();
        void createUser(int id,string name);  
        int createPoll(int userId,string questions,vector<string> options);
        void userPosts(int userId);
        void updatePoll(int userId,int pollId,string questions,vector<string> options);
        void deletePoll(int userId,int pollId);
        void voteInPoll(int userId,int pollId);
        void viewPollresult(int pollId);
};

#endif