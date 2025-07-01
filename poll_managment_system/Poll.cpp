#include "Poll.h"

Poll::Poll(int id,string question,vector<string> options):id(id), question(question), options(options), timestamp(time(0)) {}
const int& Poll::getId() const { return id;}
const string& Poll::getQuestion() const { return question;}
const vector<string>& Poll::getOptions() const { return options; }
const time_t& Poll::getTimestamp() const { return timestamp;}

void Poll::updatePoll(string _question,vector<string> _options) {
    cout<<"updating poll "<<_question<<endl;
    question = _question;
    options = _options;
}

void Poll::DisplayResult() {
    cout<<"Result of Poll "<<question<<endl;
    unordered_map<string,int> result; //option - count frequency
    for(auto i : votes){
        result[i.second]++;
    }
    for(auto i:result){
        cout<<"Option : "<<i.first<<" votes : "<<i.second<<endl;
    }
}

void Poll::castVote(int userId,string option) {
    cout<<"vote by "<<userId<<" is "<<option<<endl;
    votes[userId] = option;
}