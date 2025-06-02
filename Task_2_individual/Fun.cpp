#include "Fun.h"

BaseString::BaseString(const string& id, const string& val) : id(id), value(val) {}
BaseString::~BaseString() {}
const string& BaseString::getId() const { return id; }
const string& BaseString::getValue() const { return value; }
void BaseString::show() const {
    cout << "ID: " << id << ", Value: " << value << endl;
}
void BaseString::showInFormat(int format) const {
    show(); // По умолчанию просто вызываем обычный show
}

SymbString::SymbString(const string& id, const string& val) : BaseString(id, val) {}
void SymbString::toUpperCase() {
    transform(value.begin(), value.end(), value.begin(), ::toupper);
}
void SymbString::toLowerCase() {
    transform(value.begin(), value.end(), value.begin(), ::tolower);
}
void SymbString::showInFormat(int format) const {
    show(); // Для SymbString формат не имеет значения
}

BinString::BinString(const string& id, const string& val) : BaseString(id, val) {
    if (!isBinary(val)) {
        throw invalid_argument("Invalid binary string");
    }
}
bool BinString::isBinary(const string& s) const {
    return all_of(s.begin(), s.end(), [](char c) {
        return c == '0' || c == '1';
        });
}
long BinString::toDecimal() const {
    long dec = 0;
    for (char c : value) {
        dec = dec * 2 + (c - '0');
    }
    return dec;
}
void BinString::showOct() const {
    cout << "Octal: " << oct << toDecimal() << dec << endl;
}
void BinString::showDec() const {
    cout << "Decimal: " << toDecimal() << endl;
}
void BinString::showHex() const {
    cout << "Hexadecimal: " << hex << toDecimal() << dec << endl;
}
void BinString::show() const {
    BaseString::show();
    showDec();
    showOct();
    showHex();
}
void BinString::showInFormat(int format) const {
    BaseString::show();
    switch (format) {
    case 1: showOct(); break;
    case 2: showDec(); break;
    case 3: showHex(); break;
    default:
        showDec();
        showOct();
        showHex();
    }
}

Factory::~Factory() { clear(); }
BaseString* Factory::createSymbString(const string& id, const string& val) {
    SymbString* obj = new SymbString(id, val);
    objects.push_back(obj);
    return obj;
}
BaseString* Factory::createBinString(const string& id, const string& val) {
    try {
        BinString* obj = new BinString(id, val);
        objects.push_back(obj);
        return obj;
    }
    catch (const invalid_argument& e) {
        cerr << "Error: " << e.what() << endl;
        return nullptr;
    }
}
void Factory::deleteObject(const string& id) {
    auto it = find_if(objects.begin(), objects.end(),
        [&id](BaseString* obj) { return obj->getId() == id; });

    if (it != objects.end()) {
        delete* it;
        objects.erase(it);
        cout << "Object with ID " << id << " deleted." << endl;
    }
    else {
        cerr << "Error: Object with ID " << id << " not found." << endl;
    }
}
void Factory::showObjectById(const string& id) const {
    auto it = find_if(objects.begin(), objects.end(),
        [&id](BaseString* obj) { return obj->getId() == id; });

    if (it != objects.end()) {
        BinString* binObj = dynamic_cast<BinString*>(*it);
        if (binObj != nullptr) {
            showFormatMenu();
            int format;
            cin >> format;
            cin.ignore();
            binObj->showInFormat(format);
        }
        else {
            (*it)->show();
        }
    }
    else {
        cerr << "Error: Object with ID " << id << " not found." << endl;
    }
}
void Factory::clear() {
    for (auto obj : objects) {
        delete obj;
    }
    objects.clear();
}

void showMenu() {
    cout << "\n======== String Objects Manager ========" << endl;
    cout << "1. Create Symbol String (T1)" << endl;
    cout << "2. Create Binary String (T2)" << endl;
    cout << "3. Delete Object" << endl;
    cout << "4. Show Object by ID" << endl;
    cout << "5. Exit" << endl;
    cout << "=====================================" << endl;
    cout << "Enter your choice: ";
}

void showFormatMenu() {
    cout << "\nSelect output format for binary string:" << endl;
    cout << "1. Octal" << endl;
    cout << "2. Decimal" << endl;
    cout << "3. Hexadecimal" << endl;
    cout << "4. All formats (default)" << endl;
    cout << "Enter your choice: ";
}