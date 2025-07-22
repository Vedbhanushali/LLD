#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <memory>

using namespace std;

// Represents an item in the system
class Item {
public:
    string itemId;
    string name;

    Item(string id, string name) : itemId(id), name(name) {}
};

// Holds inventory data for an item
class InventoryRecord {
public:
    shared_ptr<Item> item;
    int quantity;
    string location;  // e.g., "Zone A - Shelf 3"
    InventoryRecord(shared_ptr<Item> item, int qty, string loc) 
        : item(item), quantity(qty), location(loc) {}
};

// Service to manage warehouse inventory
class InventoryService {
private:
    unordered_map<string, shared_ptr<InventoryRecord>> inventoryMap; // itemId -> InventoryRecord

public:
    void addItem(shared_ptr<Item> item, int qty, string location) {
        if (inventoryMap.count(item->itemId)) {
            cout<<"found"<<endl;
            inventoryMap[item->itemId]->quantity += qty;
        } else {
            cout<<"not found"<<endl;
            inventoryMap[item->itemId] = make_shared<InventoryRecord>(item, qty, location);
        }
        cout << "Added " << qty << " units of " << item->name << " to " << location << endl;
    }

    bool removeItem(string itemId, int qty) {
        if (inventoryMap.count(itemId) && inventoryMap[itemId]->quantity >= qty) {
            inventoryMap[itemId]->quantity -= qty;
            return true;
        }
        return false;
    }

    void viewInventory() {
        cout << "\n--- Current Inventory ---\n";
        for (auto& i: inventoryMap) {
            cout << "Item: " << i.second->item->name
                 << " | Qty: " << i.second->quantity
                 << " | Location: " << i.second->location << endl;
        }
    }

    bool hasSufficientStock(const string& itemId, int qty) {
        return inventoryMap.count(itemId) && inventoryMap[itemId]->quantity >= qty;
    }

    shared_ptr<Item> getItem(const string& itemId) {
        return inventoryMap[itemId]->item;
    }
};

// Represents a customer order
class Order {
public:
    string orderId;
    unordered_map<string, int> itemQuantities;  // itemId -> quantity requested

    Order(string id) : orderId(id) {}

    void addItem(string itemId, int qty) {
        itemQuantities[itemId] += qty;
    }
};

// Service to manage order fulfillment
class OrderService {
private:
    shared_ptr<InventoryService> inventory;

public:
    OrderService(shared_ptr<InventoryService> inv) : inventory(move(inv)) {}

    void processOrder(shared_ptr<Order> order) {
        
        cout << "\nProcessing Order ID: " << order->orderId << endl;

        // Check stock availability
        for (auto& iq : order->itemQuantities) {
            if (!inventory->hasSufficientStock(iq.first, iq.second)) {
                cout << "Order failed: Not enough stock for item " << iq.first << endl;
                return;
            }
        }

        // Deduct stock
        for (auto& iq : order->itemQuantities) {
            inventory->removeItem(iq.first, iq.second);
            // cout << "Fulfilled: " << iq.second << " units of Item " << iq.first << endl;
            cout << "Fulfilled: " << iq.second << " units of Item " << inventory->getItem(iq.first)->name << endl;
        }

        cout << "Order " << order->orderId << " processed successfully!\n";
    }
};

// Entry point
int main() {
    cout<<"Hello Starting program"<<endl;
    shared_ptr<InventoryService> inventory = make_shared<InventoryService>();
    unique_ptr<OrderService> orderService = make_unique<OrderService>(inventory);

    cout<<"Adding stock"<<endl;
    inventory->addItem(make_shared<Item>("101", "Paneer"), 100, "Zone A");
    inventory->addItem(make_shared<Item>("102", "Tomatoes"), 200, "Zone B");
    inventory->addItem(make_shared<Item>("103", "Chilies"), 50, "Zone C");
    
    cout<<"Inventory ->"<<endl;
    inventory->viewInventory();

    // Create an order
    // Order order1("ORD001");
    shared_ptr<Order> o1 = make_shared<Order>("ORD001");
    o1->addItem("101", 10);  // 10 Paneer
    o1->addItem("102", 25);  // 25 Tomatoes

    orderService->processOrder(o1);
    inventory->viewInventory();

    return 0;
}
