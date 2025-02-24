#include "mydatastore.h"
#include "util.h"
#include <sstream>
#include <iomanip>
#include <cstring>

//MyDataStore::MyDataStore() { }

MyDataStore::~MyDataStore() 
{
    for(int i = 0; i < (int)products.size(); i++)
    {
        delete products[i];
    }
    for(int i = 0; i < (int)users.size(); i++)
    {
        delete users[i];
    }
}

/**
 * Adds a product to the data store
 */
void MyDataStore::addProduct(Product* p)
{
    std::set<std::string> keywordSet = p->keywords();
    for(std::set<std::string>::iterator it=keywordSet.begin(); it != keywordSet.end(); ++it)
    {
        std::map<std::string, std::set<Product*>>::iterator it2 = searchMap.find(*it);
        if (it2 != searchMap.end()) // we found the element
        {
            it2->second.insert(p);
        }
        else 
        {
            std::set<Product*> s;
            s.insert(p);
            searchMap.insert(std::make_pair(*it, s));
        }
    }
    products.push_back(p);
}

/**
 * Adds a user to the data store
 */
void MyDataStore::addUser(User* u)
{
    users.push_back(u);
    std::deque<Product*> q;
    cart.insert(std::make_pair(u, q));
}

/**
 * Performs a search of products whose keywords match the given "terms"
 *  type 0 = AND search (intersection of results for each term) while
 *  type 1 = OR search (union of results for each term)
 */
std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type)
{
    std::vector<Product*> v; //(setOut.begin(), setOut.end());
    if((int)terms.size() <1)
    {
        return v;
    }
    std::set<Product*> setOut;
    //if(type == 0) {setOut = searchMap[terms[0]];}
    int count = 0;
    for(int i = 0; i < (int)terms.size(); i++)
    {
        std::map<std::string, std::set<Product*>>::iterator it = searchMap.find(terms[i]);
        if(it != searchMap.end())
        {
            if(type == 0)
            {
                if(count == 0)
                {
                    setOut = it->second;
                }
                setOut = setIntersection(setOut, it->second);
                count++;
            }
            else
            {
                setOut = setUnion(setOut, it->second);
            }
        }
    }
    for(Product* p : setOut)
    {
        v.push_back(p);
    }
    return v;
}

/**
 * Reproduce the database file from the current Products and User values
 */
void MyDataStore::dump(std::ostream& ofile)
{
    ofile << "<products>" << std::endl;
    for(int i = 0; i < (int)products.size(); i++)
    {
        products[i]->dump(ofile);
    }
    ofile << "</products>\n<users>" << std::endl;
    for(int i = 0; i < (int)users.size(); i++)
    {
        users[i]->dump(ofile);
    }    
    ofile << "</users>" << std::endl;
}

// Add item to cart
void MyDataStore::addCart(int userInd, Product* prod)
{
    User* u = users[userInd];
    std::map<User*, std::deque<Product*>>::iterator it = cart.find(u);
    if(it != cart.end())
    {
        it->second.push_back(prod);
    }
}

// view contents of cart
std::deque<Product*> MyDataStore::viewCart(int userInd)
{
    User* u = users[userInd];
    std::map<User*, std::deque<Product*>>::iterator it = cart.find(u);
    if(it != cart.end())
    {
        return it->second;
    }
}

// buy items in user's cart
void MyDataStore::buyCart(int userInd)
{
    User* u = users[userInd];
    std::map<User*, std::deque<Product*>>::iterator it = cart.find(u);
    if(it != cart.end())
    {
        int noBuy = 0;
        std::deque<Product*> d = it->second;
        while((int)d.size() > noBuy)
        {
            if(d.front()->getQty() > 0)
            {
                if(u->getBalance() >= d.front()->getPrice())
                {
                    d.front()->subtractQty(1);
                    u->deductAmount(d.front()->getPrice());
                    d.pop_front();
                    continue;
                }
            }
            d.push_back(d.front());
            d.pop_front();
            noBuy++;
        }
        it->second = d;
    }
}

// check if username is valid
int MyDataStore::checkUser(std::string username)
{
    for(int i = 0; i < (int)users.size(); i++)
    {
        if(convToLower(users[i]->getName()) == convToLower(username))
        {
            return i;
        }
    }
    return -1;
}
