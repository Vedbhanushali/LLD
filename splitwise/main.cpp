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
    unordered_map<shared_ptr<User>,shared_ptr<Amount>> userBalances; // user -> amount
    string title;
    string description;
    public:
    Expense(int id,string title,string description): id(id),title(title), description(description){
        cout << "Expense created with ID: " << id << ", Title: " << title << endl;
    }
    int getId() const {
        return id;
    }
    void editExpense(string title, string description) {
        this->title = title;
        this->description = description;
    }
    void addUsersBalance(vector<shared_ptr<User>>& users) {
        for(const auto& user : users) {
            double amountValue;
            cout << "Enter Balance for User " << user->getName() << ": ";
            cin >> amountValue;
            Currency currency;
            shared_ptr<Amount> amount = make_shared<Amount>(INR, amountValue);
            userBalances[user] = amount;
            cout << "User " << user->getName() << " added with balance: " << amount->print() << endl;
        }
    }
    void settleExpense() {

    }
    void print() const {
        cout << "Expense Title: " << title << endl;
        cout << "Description: " << description << endl;
        cout << "User Balances:" << endl;
        for(const auto& entry : userBalances) {
            const auto user = entry.first;
            const auto amount = entry.second;
            cout << "User: " << user->getName() << ", Balance: " << amount->print() << endl;
        }
    }
};

/* --------- Group ---------------- */
class Group {
    private:
    int groupId;
    string name;
    string description;
    unordered_map<int,shared_ptr<Expense>> expenses; //expenseId -> Expense
    vector<shared_ptr<User>> members; 

    public:
    Group(int groupId,string name, string description):groupId(groupId), name(name), description(description) {
        cout << "Group created with ID: " << groupId << ", Name: " << name << endl;
        cout << "Enter number of users : " << endl;
        int n; cin>>n;
        for(int i=0;i<n;i++) {
            int userId;
            string userName, userBio, userImageUrl;
            cout << "Enter User ID: "; cin >> userId;
            cout << "Enter User Name: "; cin >> userName;
            cout << "Enter User Bio: "; cin >> userBio;
            cout << "Enter User Image URL: "; cin >> userImageUrl;
            shared_ptr<User> user = make_shared<User>(userId, userName, userBio, userImageUrl);
            members.emplace_back(user);
        }
    }
    int getId() const {
        return groupId;
    }
    string getName() const {
        return name;
    }
    void addExpense() {
        int id;
        string title,desc;
        cout<<"Enter id:"; cin>>id;
        cout<<"Enter title:"; cin>>title;
        cout<<"Enter description"; cin>>desc;
        shared_ptr<Expense> expense = make_shared<Expense>(id, title, desc);
        expense->addUsersBalance(members);
        expenses.emplace_back(expense);
    }
    void editExpense(int expenseId) {
        if(expenses.find(expenseId) == expenses.end()) {
            cout << "Expense with ID " << expenseId << " not found." << endl;
            return;
        }
        string title, desc;
        cout << "Editing Expense with ID: " << expenseId << endl;
        cout << "Enter new title: "; cin >> title;
        cout << "Enter new description: "; cin >> desc;
        expenses[expenseId]->editExpense(title, desc);
        
    }
    void settleExpense(int expenseId) {
        if(expenses.find(expenseId) == expenses.end()) {
            cout << "Expense with ID " << expenseId << " not found." << endl;
            return;
        }
        expenses[expenseId]->settleExpense();
        expenses.erase(expenseId);
    }
    void settleAllExpenses() {
        cout << "Settling all expenses for group: " << name << endl;
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
            cout<<"Group already exist"<<endl;
    }
    void addGroupExpense(int groupId) {
        cout<<"Creating Expense of group "<<Groups[groupId]->getName()<<endl;
        Groups[groupId]->addExpense();
    }
    void editExpense(int groupId,int expenseId) {
        cout<<"Editing Expense of Group "<<Groups[groupId]->getName();
        Groups[groupId]->editExpense(expenseId);
    }
    void settleExpenses(int groupId,int expenseId) {
        Groups[groupId]->settleExpense(expenseId);
    }
    void settleGroupExpense(int groupId) {
        Groups[groupId]->settleAllExpenses();
    }
};

int main() {
    cout<<"Welcome to Splitwise"<<endl;
    Splitwise sw = Splitwise();
    sw.addGroups(1,"Goa Trip","trip expense");
    sw.addGroups(2,"Daily expense","day to day share");
    sw.addGroupExpense(1);
    sw.addGroupExpense(1);
    sw.addGroupExpense(1);
    sw.addGroupExpense(2);
    return 0;
}
