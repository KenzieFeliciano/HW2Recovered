#include "clothing.h"
#include "util.h"
#include <sstream>
#include <set>
using namespace std;


Clothing::Clothing(const std::string& name, double price, int qty, const std::string& brand_, const std::string& size_)
    : Product(name, price, qty), brand_(brand_), size_(size_)
{
    //constructor
}

set<string> Clothing::keywords() const
{
    set<string> keys = parseStringToWords(convToLower(name_));
    set<string> brandWrds = parseStringToWords(convToLower(brand_));
    keys.insert(brandWrds.begin(), brandWrds.end());
    return keys;
}

string Clothing::displayString() const
{
    ostringstream oss;
    oss << name_ << "\n";
    oss << "Brand: " << brand_ << " Size: " << size_ << "\n";
    oss << price_ << " " << qty_ << " left.";
    return oss.str();
}

void Clothing::dump(ostream& os) const
{
    os << "clothing" << endl;
    os << name_ << endl;
    os << price_ << endl;
    os << qty_ << endl;
    os << brand_ << endl;
    os << size_ << endl;
}