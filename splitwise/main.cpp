#include <iostream>
#include <memory>
#include <unordered_map>
#include <vector>

using namespace std;

/* ------------ Currency Enum --------------- */

enum Currency {
    USD,
    EUR,
    GBP,
    INR,
    JPY
};

/* ------------ Amount --------------- */

class Amount {
    Currency currency;
    double value;

    public:
        Amount(Currency currency, double value) : currency(currency), value(value) {}
        void add(const shared_ptr<Amount> amount){ //will add amount to current Amount
            if (this->currency != amount->getCurrency()) {
                throw invalid_argument("Cannot add amounts with different currencies");
            }
            this->value += amount->getValue();  
        } 
        Currency getCurrency() const {
            return this->currency;
        }
        double getValue() const{
            return this->value;
        }
        string print() const {
            string currencyStr;
            switch (this->currency) {
                case USD: currencyStr = "USD"; break;
                case EUR: currencyStr = "EUR"; break;
                case GBP: currencyStr = "GBP"; break;
                case INR: currencyStr = "INR"; break;
                case JPY: currencyStr = "JPY"; break;
            }
            return to_string(this->value) + " " + currencyStr;
        }
};

/* ---------------- User ------------------------ */

class User {
    int id;
    string name;
    string bio;
    string imageUrl;
    public:
    User(int id, string name, string bio, string imageUrl):id(id),name(name),bio(bio),imageUrl(imageUrl) {}
    int getId() const {
        return id;
    }
    string getName() const {
        return name;
    }
};


/*----------------- Expense --------------------- */

class Expense { //expense of a user
    int id;
    unordered_map<int,shared_ptr<Amount>> userBalances; // userId -> amount
    string title;
    string imageUrl;
    string description;
    public:
    Expense(int id,string title,string imageUrl, string description): id(id),title(title), imageUrl(imageUrl), description(description){}
    void addUserBalance(int userId,shared_ptr<Amount> amount){
        userBalances[userId] = amount;
    }
    void print() const {
        cout << "Expense Title: " << title << endl;
        cout << "Description: " << description << endl;
        cout << "Image URL: " << imageUrl << endl;
        cout << "User Balances:" << endl;
        for(const auto& entry : userBalances) {
            const auto userId = entry.first;
            const auto amount = entry.second;
            //TODO
            // cout << "User: " << user->getName() << ", Balance: " << amount->print() << endl;
        }
    }
};

/* --------- Group ---------------- */
class Group {
    int groupId;
    string name;
    string description;
    string imageUrl;
    vector<shared_ptr<User>> members;
    vector<shared_ptr<Expense>> expenses;

    public:
    Group(int groupId,string name, string description, string imageUrl):groupId(groupId), name(name), description(description), imageUrl(imageUrl) {}
    int getId() const {
        return groupId;
    }
    const vector<shared_ptr<User>>& getMembers() const {
        return members;
    }
    void addMember(shared_ptr<User> user) {
        members.emplace_back(user);
    }
    void addGroupExpense(shared_ptr<Expense> expense) {
        expenses.emplace_back(expense);
    }
};

class Splitwise {
    unordered_map<int,shared_ptr<Group>> Groups;
    public:
    Splitwise(){}
    void addExpense(int expenseId) {

    }
    void editExpense(int expenseId) {

    }
    void settleExpenses(int groupId) {

    }
    void addGroupExpense(int groupId) {

    }
    void settleGroupExpense() {

    }
};

int main() {
    cout<<"Welcome to Splitwise"<<endl;
    Splitwise sw = Splitwise();
    return 0;
}
