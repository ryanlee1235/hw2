#include <sstream>
#include <iomanip>
#include "movie.h"
#include "util.h"

using namespace std;

Movie::Movie(const std::string name, double price, int qty, const std::string genre, const std::string rating) :
    Product("movie", name, price, qty), genre_(genre), rating_(rating)
{
}

std::set<std::string> Movie::keywords() const
{
    std::set<std::string> keywordsSet;
    keywordsSet = parseStringToWords(name_);
    keywordsSet.insert(convToLower(genre_));
    keywordsSet.insert(convToLower(rating_));
    
    return keywordsSet;
}

std::string Movie::displayString() const
{
    std::string display = name_ + "\nGenre: " + genre_ + " Rating: " + rating_ + "\n" + std::to_string(price_) + " " + std::to_string(qty_) + " left.";
    return display;
}

void Movie::dump(std::ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << genre_ << "\n" << rating_ << endl;
}

std::string Movie::getGenre() const
{
    return genre_;
}

std::string Movie::getRating() const
{
    return rating_;
}