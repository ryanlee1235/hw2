/* Write derived product classes:
 Book, Clothing and Movie implementing 
the keywords() which returns the
appropriate keywords to index the 
product, displayString() [to create
a string that contains the product
info] and dump() [that outputs the
database format of the product info]. 
We recommend trying to compile (NOT test,
just compile) each of these files as you
write them to avoid solving the same compile
issue 3 times for each derived class. 
Remember you can easily compile by using 
the -c flag (e.g. $ g++ -g -Wall -std=c++11 -c book.cpp ).
Each class should be written in its own .h and .cpp files 
(i.e. book.h, book.cpp, clothing.h, etc.) */

#include <sstream>
#include <iomanip>
#include "book.h"
#include "util.h"

using namespace std;

Book::Book(const std::string name, double price, int qty, const std::string isbn, const std::string author) :
    Product("book", name, price, qty), isbn_(isbn), author_(author)
{
}

std::set<std::string> Book::keywords() const
{
    std::set<std::string> keywordsSet;
    keywordsSet = parseStringToWords(name_ + " " + author_);
    keywordsSet.insert(isbn_);
    
    return keywordsSet;
}

std::string Book::displayString() const
{
    std::string display = name_ + "\nAuthor: " + author_ + " ISBN: " + isbn_ + "\n" + std::to_string(price_) + " " + std::to_string(qty_) + " left.";
    return display;
}

void Book::dump(std::ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << isbn_ << "\n" << author_ << endl;
}

std::string Book::getISBN() const
{
    return isbn_;
}

std::string Book::getAuthor() const
{
    return author_;
}