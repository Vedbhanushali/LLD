#ifndef USER_H
#define USER_H

#include <iostream>
#include <vector>
#include <memory>
#include "Poll.h"


using namespace std;
class Poll;
class User {
    private :
        int id;
        string name;
        vector<shared_ptr<Poll>> polls;
    public:
    User(int userId,string userName);
    const int& getId() const;
    const string& getName() const;
    const vector<shared_ptr<Poll>>& getPolls() const;
    void addPoll(shared_ptr<Poll> poll);
    void removePoll(int pollId);
    void updatePoll(int pollId,string question,vector<string> options);
};

#endif