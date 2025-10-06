#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include "datastore.h"
#include <vector>
#include <string>
#include <set>
#include <map>

class MyDataStore : public DataStore{
public:
    MyDataStore();
    ~MyDataStore();

    void addProduct(Product* p) override;
    void addUser(User* u) override;
    std::vector<Product*> search(std::vector<std::string>& terms, int type) override;
    //create functions for add, view, buy
    void addToCart(const std::string& username, const std::vector<Product*>&hits, int hit_index);
    void viewCart(const std::string& username);
    void buyCart(const std::string& username);
    void dump(std::ostream& ofile) override;

private:
    std::vector<Product*> products_;
    std::vector<User*> users_;
    std::map<std::string, std::set<Product*> >keywordToProducts_; //for more efficient search
    std::map<std::string, std::vector<Product*> > carts_; //FIFO
    
};

//self note: this phrase "const std::string&" is the string type and saying it passed by reference (not a copy).
//self note: std::vector<Type> name;
//"Type" is what the vector will hold. in this case Product* (pointers to any Product object)
//self note: a map is a container that associates keys with values. every key is unique and you can look up a value by its key
//the syntax for a map is "std::map<KeyType, ValueType> myMap"
//keywordToProducts_ maps keywords ot products. this would be used like: keywordToProducts_["couches"] = 20 would make 20 the key to couches
#endif