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

class Utilities {
    public:
        static bool isValidDate(const string &date) {
            regex datePattern(R"(\d{4}-\d{2}-\d{2})");
            return regex_match(date, datePattern);
        }

        static bool isValidPrice(double price) {
            return price > 0;
        }

        static bool isValidName(const string &name) {
            regex namePattern(R"([A-Za-z]+)");
            return regex_match(name, namePattern);
        }

        static bool isValidPlanType(const string &planType) {
            static const unordered_set<string> validPlanTypes = {"Free", "Basic", "Premium", "Gold"};
            return validPlanTypes.find(planType) != validPlanTypes.end();
        }
};

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
        Subscription(string firstName, string lastName) : id(nextId++) {
            setFirstName(firstName);
            setLastName(lastName);
            this->planType = "Free";
            this->expiration = "Not Set";
            this->price = 0.0;
            objCount++;
        }

        Subscription(string firstName, string lastName, string planType, string expiration, double price) : id(nextId++) {
            setFirstName(firstName);
            setLastName(lastName);
            setPlanType(planType);
            setExpiration(expiration);
            setPrice(price);
            objCount++;
        }

        ~Subscription() {
            objCount--;
        }

        int getId() const {
             return id; 
        }
        string getFirstName() const { 
            return firstName;
        }

        string getLastName() const {
             return lastName;
        }

        string getPlanType() const {
            return planType; 
        }

        string getExpiration() const {
            return expiration;
        }

        double getPrice() const {
            return price; 
        }

        void setFirstName(const string &firstName) {
            if(Utilities::isValidName(firstName)) {
                this->firstName = firstName;
            } else {
                throw invalid_argument("Invalid first name format");
            }
        }

        void setLastName(const string &lastName) {
            if(Utilities::isValidName(lastName)) {
                this->lastName = lastName;
            } else {
                throw invalid_argument("Invalid last name format");
            }
        }

        void setPlanType(const string &planType) {
            if(Utilities::isValidPlanType(planType)) {
                this->planType = planType;
            } else {
            throw invalid_argument("Invalid plan type");
            }
        }

        void setExpiration(const string &expiration) {
            if(Utilities::isValidDate(expiration)) {
                this->expiration = expiration;
            } else {
                throw invalid_argument("Invalid expiration date format");
            }
        }

        void setPrice(double price) {
            if(Utilities::isValidPrice(price)) {
                this->price = price;
            } else {
                throw invalid_argument("Invalid price");
            }
        }

        static int getObjectCount() {
            return objCount;
        }

        string toString() const {
            stringstream ss;
            ss << id << " " << firstName << " " << lastName << " " << planType << " " << expiration << " " << price;
            return ss.str();
        }
};

int Subscription::nextId = 0;
int Subscription::objCount = 0;

int main(int argc, char *argv[]) {
    try {
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
        assert(sub[3]->toString() == "3 Petras Petraitis Premium 2028-02-28 60");

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

        assert(Utilities::isValidDate("2025-01-01") == true);
        assert(Utilities::isValidDate("2025/12/01") == false);
        assert(Utilities::isValidPrice(99.99) == true);
        assert(Utilities::isValidPrice(-1) == false);
        assert(Utilities::isValidName("Jonas") == true);
        assert(Utilities::isValidName("Jonas2") == false);
        assert(Utilities::isValidPlanType("Premium") == true);
        assert(Utilities::isValidPlanType("Not Premium") == false);

        for(int i = 0; i < 5; ++i) {
            if(sub[i] != nullptr) {
                delete sub[i];
                sub[i] = nullptr;
            }
        }

        assert(Subscription::getObjectCount() == 0);

        cout << "All tests passed" << endl;

    } catch(const exception &e) {
        cerr << "Error: " << e.what() << endl;
    }
    
    return 0;
}
