#include "System.h"

System::System() : pollCounter(0) {}

void System::createUser(int id, string name) {
    shared_ptr<User> user = make_shared<User>(id, name);
    users[id] = user;
}

int System::createPoll(int userId, string questions, vector<string> options) {
    shared_ptr<Poll> poll = make_shared<Poll>(pollCounter++, questions, options);
    polls[poll->getId()] = poll;
    users[userId]->addPoll(poll);
    return poll->getId();
}

void System::userPosts(int userId) {
    if (users.count(userId)) {
        vector<shared_ptr<Poll>> polls = users[userId]->getPolls();
        for (const auto& poll : polls) {
            cout << "Poll ID: " << poll->getId() << ", Question: " << poll->getQuestion() << endl;
        }
    } else {
        cout << "User not found." << endl;
    }
}

void System::updatePoll(int userId, int pollId, string questions, vector<string> options) {
    // if (users.count(userId)) {
    //     users[userId]->updatePoll(pollId, questions, options);
    // } else {
    //     cout << "User not found." << endl;
    // }

    //Method 2
    if (polls.count(pollId)) {
        polls[pollId]->updatePoll(questions, options);
    } else {
        cout << "Poll not found." << endl;
    }
}

void System::deletePoll(int userId,int pollId) {
    if(!users.count(userId)){
        cout<<"User not found"<<endl;
        return;
    }
    if(!polls.count(pollId)){
        cout<<"Poll not found"<<endl;
        return;
    }
    //remvoing all references of poll from global and user's poll list
    users[userId]->removePoll(pollId);
    if (polls.count(pollId)) {
        polls.erase(pollId);
    } 
}

void System::voteInPoll(int userId,int pollId) {
    if(!polls.count(pollId)){
        cout<<"Poll not found"<<endl;
        return;
    }
    cout<<polls[pollId]->getQuestion()<<endl;
    cout<<"Enter options to vote"<<endl;
    vector<string> options = polls[pollId]->getOptions();
    for(int i=0;i<options.size();i++){
        cout<<i+1<<". "<<options[i]<<endl;
    }
    string option;
    cin>>option;
    polls[pollId]->castVote(userId, option);
}

void System::viewPollresult(int pollId) {
    if(!polls.count(pollId)){
        cout<<"Poll not found";
        return;
    }
    polls[pollId]->DisplayResult();
}

