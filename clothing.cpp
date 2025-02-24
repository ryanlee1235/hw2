#include <sstream>
#include <iomanip>
#include "clothing.h"
#include "util.h"

using namespace std;

Clothing::Clothing(const std::string name, double price, int qty, const std::string size, const std::string brand) :
    Product("clothing", name, price, qty), size_(size), brand_(brand)
{
}

std::set<std::string> Clothing::keywords() const
{
    std::set<std::string> keywordsSet;
    keywordsSet = parseStringToWords(name_ + " " + brand_);
    keywordsSet.insert(convToLower(size_));
    //keywordsSet.insert(brand_);
    
    return keywordsSet;
}

std::string Clothing::displayString() const
{
    std::string display = name_ + "\nSize: " + size_ + " Brand: " + brand_ + "\n" + std::to_string(price_) + " " + std::to_string(qty_) + " left.";
    return display;
}

void Clothing::dump(std::ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << size_ << "\n" << brand_ << endl;
}

std::string Clothing::getSize() const
{
    return size_;
}

std::string Clothing::getBrand() const
{
    return brand_;
}