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
    string description;
    public:
    Expense(int id,string title,string description): id(id),title(title), description(description){}
    void addUserBalance(int userId,shared_ptr<Amount> amount){
        userBalances[userId] = amount;
    }
    void settleExpense() {

    }
    void print() const {
        cout << "Expense Title: " << title << endl;
        cout << "Description: " << description << endl;
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
    vector<shared_ptr<User>> members;
    vector<shared_ptr<Expense>> expenses;

    public:
    Group(int groupId,string name, string description):groupId(groupId), name(name), description(description) {}
    int getId() const {
        return groupId;
    }
    string getName() const {
        return name;
    }
    const vector<shared_ptr<User>>& getMembers() const {
        return members;
    }
    void addMember(shared_ptr<User> user) {
        members.emplace_back(user);
    }
    void addExpense() {
        int id;
        string title,desc;
        cout<<"Enter id:"; cin>>id;
        cout<<"Enter title:"; cin>>title;
        cout<<"Enter description"; cin>>desc;
        expenses.emplace_back(make_shared<Expense>(id,title,desc));
    }
    void editExpense(int expenseId) {

    }
};

class Splitwise {
    unordered_map<int,shared_ptr<Group>> Groups;
    public:
    Splitwise(){}
    void addGroups(int id,string name,string desc) {
        if(Groups.find(id)==Groups.end())
            Groups[id] = make_shared<Group>(id,name,desc);
        else
            cout<<"Group alread exist"<<endl;
    }
    void addGroupExpense(int groupId) {
        cout<<"Creating Expense of group"<<endl;
        Groups[groupId]->addExpense();
    }
    void editExpense(int groupId,int expenseId) {
        cout<<"Editing Expense of Group "<<Groups[groupId]->getName();
        Groups[groupId]->editExpense(expenseId);
    }
    void settleExpenses(int groupId,int expenseId) {

    }
    void settleGroupExpense() {

    }
};

int main() {
    cout<<"Welcome to Splitwise"<<endl;
    Splitwise sw = Splitwise();
    sw.addGroups(1,"Goa Trip","trip expense");
    sw.addGroups(2,"Daily expense","day to day share");
    return 0;
}
