#ifndef POLL_H
#define POLL_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <ctime>
#include <memory>
using namespace std;

class User; // Forward declaration
class Poll {
    private:
        int id;
        string question;
        vector<string> options;
        time_t timestamp;
        shared_ptr<User> owner; 
        unordered_map<int, string> votes; // userId -> option
    public:
    Poll(int _id,string _question,vector<string> _options);
    const int& getId() const;
    const string& getQuestion() const;
    const vector<string>& getOptions() const;
    const time_t& getTimestamp() const;
    void updatePoll(string _question,vector<string> _options);
    void castVote(int userId,string option);
    void DisplayResult();
};   

#endif