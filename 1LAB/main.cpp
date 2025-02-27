//LSP - 2413982
//El.pastas - dominykas.pavlavicius@mif.stud.vu.lt
//Uzduotis - 1. Klasė 

#include <iostream>
#include <string>
#include <cassert>
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

    public:
        Subscription() : id(nextId++) {
            firstName = "Unknown";
            lastName = "Unknown";
            planType = "Basic";
            expiration = "0000-00-00";
            price = 0.0;
            objCount++;
        }

        Subscription(string fN, string lN, string pT, string exp, double pr) : id(nextId++) {
            firstName = fN;
            lastName = lN;
            planType = pT;
            expiration = exp;
            if(isValidPrice(pr)) {
                price = pr;
            } else {
                cout << "Invalid price" << endl;
            }
            objCount++;
        }

        ~Subscription() {
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
            stringstream ss;
            ss << "Subscription ID: " << id << "\n"
                << "First Name: " << firstName << "\n"
                << "Last Name: " << lastName << "\n"
                << "Plan Type: " << planType << "\n"
                << "Expiration: " << expiration << "\n"
                << "Price: " << price << "\n";
            return ss.str();
        }

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
};

int Subscription::nextId = 0;
int Subscription::objCount = 0;

int main(int argc, char *argv[]) {
    Subscription *sub[5];

    assert(Subscription::getObjectCount() == 0);

    sub[0] = new Subscription("John", "Doe", "Basic", "2025-01-01", 99.99);

    sub[1] = new Subscription("Tony", "Stark", "Premium", "2035-03-05", 199.99);

    delete sub[1];
    sub[1] = nullptr;

    assert(Subscription::getObjectCount() == 1);

    sub[2] = new Subscription("Jonas", "Jonaitis", "Basic", "2025-02-27", 0.99);

    sub[3] = new Subscription("Petras", "Petraitis", "Premium", "2028-02-28", 60);

    assert(sub[3]->getId() == 3);
    assert(sub[3]->toString() == "Subscription ID: 3\n"
                                "First Name: Petras\n"
                                "Last Name: Petraitis\n"
                                "Plan Type: Premium\n"
                                "Expiration: 2028-02-28\n"
                                "Price: 60\n");

    sub[4] = new Subscription("Goose", "Fridge", "Premium", "2099-09-09", 1284.99);

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

    assert(sub[4]->getFirstName() == "Goose");
    assert(sub[4]->getLastName() == "Fridge");
    assert(sub[4]->getPlanType() == "Premium");
    assert(sub[4]->getExpiration() == "2099-09-09");
    assert(sub[4]->getPrice() == 1284.99);

    assert(sub[0]->isValidDate("2025-01-01") == true);
    assert(sub[0]->isValidDate("2025/12/01") == false);
    assert(sub[0]->isValidPrice(99.99) == true);
    assert(sub[0]->isValidPrice(-1) == false);
    assert(sub[2]->isValidName("Jonas") == true);
    assert(sub[2]->isValidName("Jonas2") == false);
    assert(sub[3]->isValidPlanType("Premium") == true);
    assert(sub[3]->isValidPlanType("Not Premium") == false);

    for(int i = 0; i < 5; ++i) {
        if(sub[i] != nullptr) {
            delete sub[i];
        }
    }

    assert(Subscription::getObjectCount() == 0);

    cout << "All tests passed" << endl;
    
    return 0;
}
