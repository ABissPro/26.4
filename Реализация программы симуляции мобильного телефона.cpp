#include <iostream>
#include <string>
#include <vector>

class PhoneNumber {
public:
    // Конструктор по умолчанию создает невалидный номер
    PhoneNumber() : isValid_(false) {}

    // Попытка создать номер из строки
    bool createFromString(const std::string& number) {
        std::string cleaned;
        for (char c : number) {
            if (c >= '0' && c <= '9') {
                cleaned += c;
            }
            else if (c == '+' && cleaned.empty()) {
                cleaned += c;
            }
        }

        if (cleaned.size() == 11 && cleaned[0] == '7') {
            number_ = "+7" + cleaned.substr(1);
            isValid_ = true;
        }
        else if (cleaned.size() == 11 && cleaned[0] == '8') {
            number_ = "+7" + cleaned.substr(1);
            isValid_ = true;
        }
        else if (cleaned.size() == 10) {
            number_ = "+7" + cleaned;
            isValid_ = true;
        }
        else if (cleaned.size() == 12 && cleaned.substr(0, 2) == "+7") {
            number_ = cleaned;
            isValid_ = true;
        }
        else {
            number_ = "";
            isValid_ = false;
        }

        return isValid_;
    }

    std::string getNumber() const {
        return number_;
    }

    bool isValid() const {
        return isValid_;
    }

private:
    std::string number_;
    bool isValid_;
};

class Contact {
public:
    Contact(const std::string& name, const PhoneNumber& number)
        : name_(name), number_(number) {
    }

    std::string getName() const {
        return name_;
    }

    PhoneNumber getNumber() const {
        return number_;
    }

private:
    std::string name_;
    PhoneNumber number_;
};

class MobilePhone {
public:
    bool addContact(const std::string& name, const PhoneNumber& number) {
        if (!number.isValid()) {
            std::cout << "Wrong format of phonenumber" << std::endl;
            return false;
        }

        if (name.empty()) {
            std::cout << "Name of contact cannot be empty" << std::endl;
            return false;
        }

        contacts_.emplace_back(name, number);
        return true;
    }

    bool call(const std::string& input) const {
        // Поиск по имени
        for (size_t i = 0; i < contacts_.size(); ++i) {
            if (contacts_[i].getName() == input) {
                std::cout << "CALL " << contacts_[i].getNumber().getNumber() << std::endl;
                return true;
            }
        }

        // Если не найдено по имени, пробуем как номер
        PhoneNumber num;
        if (num.createFromString(input) && num.isValid()) {
            std::cout << "CALL " << num.getNumber() << std::endl;
            return true;
        }

        std::cout << "Contack not found" << std::endl;
        return false;
    }

    bool sms(const std::string& input, const std::string& message) const {
        // Поиск по имени
        for (size_t i = 0; i < contacts_.size(); ++i) {
            if (contacts_[i].getName() == input) {
                std::cout << "SMS to " << contacts_[i].getNumber().getNumber() << ": " << message << std::endl;
                return true;
            }
        }

        // Если не найдено по имени, пробуем как номер
        PhoneNumber num;
        if (num.createFromString(input) && num.isValid()) {
            std::cout << "SMS to " << num.getNumber() << ": " << message << std::endl;
            return true;
        }

        std::cout << "Contact not found" << std::endl;
        return false;
    }

private:
    std::vector<Contact> contacts_;
};

int main() {
    MobilePhone phone;
    std::string command;

    while (true) {
        std::cout << "Enter command (add, call, sms, exit): ";
        std::cin >> command;

        if (command == "add") {
            std::string name, numberStr;
            std::cout << "Name: ";
            std::cin >> name;
            std::cout << "Phone number: ";
            std::cin >> numberStr;

            PhoneNumber number;
            if (number.createFromString(numberStr)) {
                if (phone.addContact(name, number)) {
                    std::cout << "Successfuly added" << std::endl;
                }
            }
            else {
                std::cout << "wrong format of phone number" << std::endl;
            }

        }
        else if (command == "call") {
            std::string input;
            std::cout << "Enter name or phone number: ";
            std::cin >> input;
            phone.call(input);

        }
        else if (command == "sms") {
            std::string input, message;
            std::cout << "Enter name or phone number: ";
            std::cin >> input;
            std::cout << "Enter message: ";
            std::cin.ignore();
            std::getline(std::cin, message);
            phone.sms(input, message);

        }
        else if (command == "exit") {
            break;

        }
        else {
            std::cout << "Unknown command." << std::endl;
        }
    }

    return 0;
}