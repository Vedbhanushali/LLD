#include "User.h"
#include "Poll.h"

User::User(int userId,string userName):id(userId),name(userName) {}
const int& User::getId() const { return id; }
const string& User::getName() const {return name;}
const vector<shared_ptr<Poll>>& User::getPolls() const { return polls; }

void User::createPoll(shared_ptr<Poll> poll) {
    polls.push_back(poll);
}

void User::deletePoll(int pollId) {
    for(int i=0;i<polls.size();i++){
        if(pollId == polls[i]->getId()) {
            // delete polls[i];
            polls.erase(polls.begin()+i);
        }
    }
}

void User::updatePoll(int pollId,string question,vector<string> options) {
     for(int i=0;i<polls.size();i++){
        if(pollId == polls[i]->getId()) {
            polls[i]->updatePoll(question,options);
        }
    }
}
