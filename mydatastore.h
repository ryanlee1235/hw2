#include "datastore.h"
#include "product.h"
#include "user.h"
#include <iostream>
#include <map>
#include <deque>

class MyDataStore : public DataStore {
public:
    // MyDataStore();

    ~MyDataStore();

    /**
     * Adds a product to the data store
     */
    void addProduct(Product* p);

    /**
     * Adds a user to the data store
     */
    void addUser(User* u);

    /**
     * Performs a search of products whose keywords match the given "terms"
     *  type 0 = AND search (intersection of results for each term) while
     *  type 1 = OR search (union of results for each term)
     */
    std::vector<Product*> search(std::vector<std::string>& terms, int type);

    /**
     * Reproduce the database file from the current Products and User values
     */
    void dump(std::ostream& ofile);

    // Add item to cart
    void addCart(int userInd, Product* prod);

    // view contents of cart
    std::deque<Product*> viewCart(int userInd);

    // buy items in user's cart
    void buyCart(int userInd);

    // check if username is valid
    int checkUser(std::string username);

private:
    std::map<std::string, std::set<Product*>> searchMap;
    std::vector<Product*> products;
    std::vector<User*> users;
    std::map<User*, std::deque<Product*>> cart;
};