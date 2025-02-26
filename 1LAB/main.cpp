//LSP - 2413982
//El.pastas - dominykas.pavlavicius@mif.stud.vu.lt
//Uzduotis - 1. Klasė 

#include <iostream>
#include <string>
#include <cassert>
#include <vector>
#include <regex>
#include <unordered_set>
#include <sstream>

using namespace std;

class Subscription {
    private:
        static int nextId;
        static int objCount;
        int id;
        string firstName;
        string lastName;
        string planType;   // Basic, Premium, ...
        string expiration; // Format: YYYY-MM-DD
        double price;

    bool isValidDate(const string &date) {
        regex datePattern(R"(\d{4}-\d{2}-\d{2})");
        return regex_match(date, datePattern);
    }

    bool isValidPrice(double price) {
        return price > 0;
    }

    bool isValidName(const string &name) {
        regex namePattern(R"([A-Za-z]+)");
        return regex_match(name, namePattern);
    }

    bool isValidPlanType(const string &planType) {
        static const unordered_set<string> validPlanTypes = {"Basic", "Premium", "Gold"};
        return validPlanTypes.find(planType) != validPlanTypes.end();
    }

    public:
        Subscription() : id(nextId++) {
            cout << "Constructor called" << endl;
            objCount++;
        }
        ~Subscription() {
            cout << "Destructor called" << endl;
            objCount--;
        }

        int getId() const { return id; }
        string getFirstName() const { return firstName; }
        string getLastName() const { return lastName; }
        string getPlanType() const { return planType; }
        string getExpiration() const { return expiration; }
        double getPrice() const { return price; }

        void setFirstName(const string &firstName) {
            if(isValidName(firstName)) {
                this->firstName = firstName;
            } else {
                cout << "Invalid first name format" << endl;
            }
        }

        void setLastName(const string &lastName) {
            if(isValidName(lastName)) {
                this->lastName = lastName;
            } else {
                cout << "Invalid last name format" << endl;
            }
        }

        void setPlanType(const string &planType) {
            if(isValidPlanType(planType)) {
                this->planType = planType;
            } else {
                cout << "Invalid plan type" << endl;
            }
        }

        void setExpiration(const string &expiration) {
            if(isValidDate(expiration)) {
                this->expiration = expiration;
            } else {
                cout << "Invalid date format" << endl;
            }
        }

        void setPrice(double price) {
            if(isValidPrice(price)) {
                this->price = price;
            } else {
                cout << "Invalid price" << endl;
            }
        }

        static int getObjectCount() {
            return objCount;
        }

        string toString() const {
            ostringstream oss;
            oss << "Subscription ID: " << id << "\n"
                << "First Name: " << firstName << "\n"
                << "Last Name: " << lastName << "\n"
                << "Plan Type: " << planType << "\n"
                << "Expiration: " << expiration << "\n"
                << "Price: " << price << "\n";
            return oss.str();
        }
};

int Subscription::nextId = 0;
int Subscription::objCount = 0;

int main(int argc, char *argv[]) {
    vector<Subscription*> subscriptions;

    assert(Subscription::getObjectCount() == 0);

    Subscription *sub[5];

    sub[0] = new Subscription();
    sub[0]->setFirstName("John");
    sub[0]->setLastName("Doe");
    sub[0]->setPlanType("Basic");
    sub[0]->setExpiration("2025-01-01");
    sub[0]->setPrice(99.99);
    subscriptions.push_back(sub[0]);

    sub[1] = new Subscription();
    sub[1]->setFirstName("Tony");
    sub[1]->setLastName("Stark");
    sub[1]->setPlanType("Premium");
    sub[1]->setExpiration("2035-03-05");
    sub[1]->setPrice(199.99);
    subscriptions.push_back(sub[1]);

    subscriptions.pop_back();
    delete sub[1];

    assert(Subscription::getObjectCount() == 1);

    sub[2] = new Subscription();
    sub[2]->setFirstName("Jonas");
    sub[2]->setLastName("Jonaitis");
    sub[2]->setPlanType("Basic");
    sub[2]->setExpiration("2025-02-27");
    sub[2]->setPrice(0.99);
    subscriptions.push_back(sub[2]);

    sub[3] = new Subscription();
    sub[3]->setFirstName("Petras");
    sub[3]->setLastName("Petraitis");
    sub[3]->setPlanType("Premium");
    sub[3]->setExpiration("2028-02-28");
    sub[3]->setPrice(60);
    subscriptions.push_back(sub[3]);

    assert(sub[3]->getId() == 3);
    assert(sub[3]->toString() == "Subscription ID: 3\n"
                                "First Name: Petras\n"
                                "Last Name: Petraitis\n"
                                "Plan Type: Premium\n"
                                "Expiration: 2028-02-28\n"
                                "Price: 60\n");

    sub[4] = new Subscription();
    sub[4]->setFirstName("Goose");
    sub[4]->setLastName("Fridge");
    sub[4]->setPlanType("Premium");
    sub[4]->setExpiration("2099-09-09");
    sub[4]->setPrice(1284.99);
    subscriptions.push_back(sub[4]);

    // Assert values
    assert(sub[0]->getId() == 0);
    assert(sub[0]->getFirstName() == "John");
    assert(sub[0]->getLastName() == "Doe");
    assert(sub[0]->getPlanType() == "Basic");
    assert(sub[0]->getExpiration() == "2025-01-01");
    assert(sub[0]->getPrice() == 99.99);

    assert(sub[2]->getFirstName() == "Jonas");
    assert(sub[2]->getLastName() == "Jonaitis");
    assert(sub[2]->getPlanType() == "Basic");
    assert(sub[2]->getExpiration() == "2025-02-27");
    assert(sub[2]->getPrice() == 0.99);

    assert(sub[3]->getFirstName() == "Petras");
    assert(sub[3]->getLastName() == "Petraitis");
    assert(sub[3]->getPlanType() == "Premium");
    assert(sub[3]->getExpiration() == "2028-02-28");
    assert(sub[3]->getPrice() == 60);

    assert(sub[4]->getFirstName() == "Goose");
    assert(sub[4]->getLastName() == "Fridge");
    assert(sub[4]->getPlanType() == "Premium");
    assert(sub[4]->getExpiration() == "2099-09-09");
    assert(sub[4]->getPrice() == 1284.99);

    for(auto sub : subscriptions) {
        delete sub;
    }

    assert(Subscription::getObjectCount() == 0);

    cout << "All tests passed" << endl;
    
    return 0;
}