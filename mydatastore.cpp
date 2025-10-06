#include "mydatastore.h"
#include "util.h"
#include <iostream>

using namespace std;

MyDataStore::MyDataStore(){
//constructor
}

MyDataStore::~MyDataStore(){
//deconstructor
}

void MyDataStore::addProduct(Product* p){
    products_.push_back(p);
    set<string> keys = p->keywords();
    for(set<string>::iterator it = keys.begin(); it != keys.end(); ++it){
        keywordToProducts_[*it].insert(p);
    }
}

void MyDataStore::addUser(User* u){
    users_.push_back(u);
    string uname = convToLower(u->getName());
    if(carts_.find(uname) == carts_.end()){
        carts_[uname] = vector<Product*>();
    }
}

vector<Product*> MyDataStore::search(vector<string>& terms, int type){
    vector<Product*> results;
    if(terms.size() == 0){
        return results;
    }
    set<Product*> resultSet;
    if(keywordToProducts_.find(terms[0]) != keywordToProducts_.end()){
        resultSet = keywordToProducts_[terms[0]];
    }
    for(unsigned int i = 1; i < terms.size(); i++){
        set<Product*> nextSet;
        if(keywordToProducts_.find(terms[i]) != keywordToProducts_.end()){
            nextSet = keywordToProducts_[terms[i]];
        }

        if(type == 0){
            resultSet = setIntersection(resultSet, nextSet);
        }
        else{
            resultSet = setUnion(resultSet, nextSet);
        }
    }

    for(set<Product*>::iterator it = resultSet.begin(); it != resultSet.end(); ++it){
        results.push_back(*it);
    }
    return results;
}

void MyDataStore::addToCart(const string& username, const vector<Product*>&hits, int hit_index){
    string uname = convToLower(username);
    //check if user exists and hit_index is valid
    if(carts_.find(uname) == carts_.end() || hit_index < 0 || hit_index >= (int)hits.size()){
        cout << "Invalid addToCart in mydatastore.cpp" << endl;
        return;
    }

    //add product to users cart
    carts_[uname].push_back(hits[hit_index]);
}

void MyDataStore::viewCart(const string& username){
    string uname = convToLower(username);
    if(carts_.find(uname) == carts_.end()){
        cout << "Invalid viewcart for mydatastore.cpp" << endl;
        return;
    }

    vector<Product*>& cart = carts_[uname];
    for(unsigned int i = 0; i < cart.size(); i++){
        cout << "Item " << (i+1) << endl;
        cout << cart[i]->displayString() << endl;
        cout << endl;
    }
}

void MyDataStore::buyCart(const string& username){
    string uname = convToLower(username);
    if(carts_.find(uname) == carts_.end()){
        cout << "Invalid username buy cart" << endl;
        return; 
    }

    //find user object
    User* user = NULL;
    for(unsigned int i = 0; i < users_.size(); i++){
        if(convToLower(users_[i]->getName()) == uname){
            user = users_[i];
            break;
        }
    }

    if(user == NULL){
            cout << "Invalid username after find user object" << endl;
            return;
        }

        vector<Product*>& cart = carts_[uname];
        vector<Product*> newCart;
        for(unsigned int i = 0; i < cart.size(); i++){
            if(cart[i]->getQty() > 0 && user->getBalance() >= cart[i]->getPrice()){
                cart[i]->subtractQty(1);
                user->deductAmount(cart[i]->getPrice());
            }
            else{
                newCart.push_back(cart[i]);
            }
        }
        cart = newCart;

}


void MyDataStore::dump(ostream& ofile){
    ofile << "<products>" << endl;
    for(unsigned int i = 0; i < products_.size(); i++){
        products_[i]->dump(ofile);
    }
    ofile << "</products>" << endl;
    ofile << "<users>" << endl;
    for(unsigned int i = 0; i < users_.size(); i++){
        users_[i]->dump(ofile);
    }
    ofile << "</users>" << endl;
}

