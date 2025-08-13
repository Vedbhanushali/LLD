#include <iostream>
#include <memory>
#include <unordered_map>
#include <vector>
#include <queue>
#include <math.h>

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
    Expense() = default; // Default constructor
    Expense(vector<shared_ptr<User>>& users) {
        for(const auto& user : users) {
            shared_ptr<Amount> amount = make_shared<Amount>(INR, 0);
            userBalances[user] = amount;
        }
    }
    Expense(int id,string title,string description): id(id),title(title), description(description){
        cout << "Expense created with ID: " << id << ", Title: " << title << endl;
    }
    int getId() const {
        return id;
    }
    const unordered_map<shared_ptr<User>, shared_ptr<Amount>>& getUserBalances() const {
        return userBalances;
    }
    void editExpense() {
        string title, desc;
        cout << "Enter new title: "; cin >> title;
        cout << "Enter new description: "; cin >> desc;
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
    void addUserBalance(const unordered_map<shared_ptr<User>,shared_ptr<Amount>>& balance){
        for(const auto& entry : balance) {
            const auto user = entry.first;
            const auto amount = entry.second;
            userBalances[user]->add(amount);
        }
    }
    void settleExpense() {
        if(userBalances.empty()) {
            cout << "No users to settle expense." << endl;
            return;
        }
        cout << "Settling expense: " << title << endl;
        int sum = 0;
        for(const auto& entry : userBalances) {
            const auto user = entry.first;
            const auto amount = entry.second;
            cout << "User: " << user->getName() << ", Amount: " << amount->print() << endl;
            sum += amount->getValue();
        }
        if(sum!=0) {
            cout<<"Wrong Expense, sum of all user balances is not zero."<<endl;
            return;
        }
        priority_queue<pair<double, shared_ptr<User>>, vector<pair<double, shared_ptr<User>>>, greater<pair<double, shared_ptr<User>>>> minHeap;
        priority_queue<pair<double, shared_ptr<User>>, vector<pair<double, shared_ptr<User>>>, less<pair<double, shared_ptr<User>>>> maxHeap;
        for(const auto& entry : userBalances) {
            const auto user = entry.first;
            const auto amount = entry.second;
            if(amount->getValue() == 0) {
                cout << "User " << user->getName() << " has no balance to settle." << endl;
            } else if(amount->getValue() < 0) {
                minHeap.push(make_pair(amount->getValue(), user)); 
            } else {
                maxHeap.push(make_pair(amount->getValue(), user)); 
            }
        }
        userBalances.clear(); // Clear user balances after processing
        while(!minHeap.empty() && !maxHeap.empty()) {
            auto minEntry = minHeap.top();
            auto maxEntry = maxHeap.top();
            minHeap.pop();
            maxHeap.pop();
            double minAmount = minEntry.first;
            double maxAmount = maxEntry.first;
            shared_ptr<User> minUser = minEntry.second;
            shared_ptr<User> maxUser = maxEntry.second;
            int sum = minAmount + maxAmount;
            if(sum == 0) {
                cout<< "Settling " << minUser->getName() << " owes " << maxAmount << " to " << maxUser->getName() << endl;
            } else if(sum < 0) {
                cout<< "Settling " << minUser->getName() << " owes " << maxAmount << " to " << maxUser->getName() << endl;
                minHeap.push(make_pair(sum, minUser)); 
            } else {
                cout<< "Settling " << minUser->getName() << " owes " << abs(minAmount) << " to " << maxUser->getName() << endl;
                maxHeap.push(make_pair(sum, maxUser));
            }
        }
        cout << "Expense settled successfully." << endl;
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
            string userName, userBio="temp", userImageUrl="temp";
            cout << "Enter User ID: "; cin >> userId;
            cout << "Enter User Name: "; cin >> userName;
            // cout << "Enter User Bio: "; cin >> userBio;
            // cout << "Enter User Image URL: "; cin >> userImageUrl;
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
        cout<<"Enter id: "; cin>>id;
        cout<<"Enter title: "; cin>>title;
        cout<<"Enter description: "; cin>>desc;
        shared_ptr<Expense> expense = make_shared<Expense>(id, title, desc);
        expense->addUsersBalance(members);
        expenses[id] = expense;
    }
    void editExpense(int expenseId) {
        if(expenses.find(expenseId) == expenses.end()) {
            cout << "Expense with ID " << expenseId << " not found." << endl;
            return;
        }
        cout << "Editing Expense with ID: " << expenseId << endl;
        expenses[expenseId]->editExpense();
    }
    void settleExpense(int expenseId) {
        if(expenses.find(expenseId) == expenses.end()) {
            cout << "Expense with ID " << expenseId << " not found." << endl;
            return;
        }
        expenses[expenseId]->settleExpense();
        expenses.erase(expenseId);
        cout << "Expense settled successfully." << endl;
    }
    void settleAllExpenses() {
        cout << "Settling all expenses for group: " << name << endl;
        shared_ptr<Expense> AllExpense = make_shared<Expense>(members);
        for(const auto& entry : expenses) {
            auto expense = entry.second;
            AllExpense->addUserBalance(expense->getUserBalances());    
        }
        AllExpense->settleExpense();
        expenses.clear(); 
        cout << "All expenses settled successfully." << endl;
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
    // sw.addGroups(2,"Daily expense","day to day share");
    sw.addGroupExpense(1);
    sw.addGroupExpense(1);
    sw.addGroupExpense(1);
    // sw.settleExpenses(1, 1);
    sw.settleGroupExpense(1);
    // sw.addGroupExpense(1);
    // sw.addGroupExpense(2);
    return 0;
}
