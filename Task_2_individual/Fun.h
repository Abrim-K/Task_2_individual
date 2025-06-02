#ifndef STRINGS_H
#define STRINGS_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <climits>
#include <stdexcept>
using namespace std;

class BaseString {
protected:
    string id;
    string value;
public:
    BaseString(const string& id, const string& val);
    virtual ~BaseString();

    const string& getId() const;
    const string& getValue() const;

    virtual void show() const;
    virtual void showInFormat(int format = 0) const;
};

class SymbString : public BaseString {
public:
    SymbString(const string& id, const string& val);
    void toUpperCase();
    void toLowerCase();
    void showInFormat(int format = 0) const override;
};

class BinString : public BaseString {
public:
    BinString(const string& id, const string& val);
    bool isBinary(const string& s) const;
    long toDecimal() const;
    void showOct() const;
    void showDec() const;
    void showHex() const;
    void show() const override;
    void showInFormat(int format) const override;
};

class Factory {
private:
    vector<BaseString*> objects;
public:
    ~Factory();
    BaseString* createSymbString(const string& id, const string& val);
    BaseString* createBinString(const string& id, const string& val);
    void deleteObject(const string& id);
    void showObjectById(const string& id) const;
    void clear();
};

void showMenu();
void showFormatMenu();

#endif // STRINGS_H