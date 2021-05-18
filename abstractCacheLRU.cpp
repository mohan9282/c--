Abstract Classes - Polymorphism
Abstract base classes in C++ can only be used as base classes. Thus, they are allowed to have virtual member functions without definitions.
A cache is a component that stores data so future requests for that data can be served faster. The data stored in a cache might be the results of an earlier computation, or the duplicates of data stored elsewhere. A cache hit occurs when the requested data can be found in a cache, while a cache miss occurs when it cannot. Cache hits are served by reading data from the cache which is faster than recomputing a result or reading from a slower data store. Thus, the more requests that can be served from the cache, the faster the system performs. One of the popular cache replacement policies is: "least recently used" (LRU). It discards the least recently used items first.

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <set>
#include <cassert>
using namespace std;

struct Node{
   Node* next;
   Node* prev;
   int value;
   int key;
   Node(Node* p, Node* n, int k, int val):prev(p),next(n),key(k),value(val){};
   Node(int k, int val):prev(NULL),next(NULL),key(k),value(val){};
};

class Cache{
   
   protected: 
   map<int,Node*> mp; //map the key to the node in the linked list
   int cp;  //capacity
   Node* tail; // double linked list tail pointer
   Node* head; // double linked list head pointer
   virtual void set(int, int) = 0; //set function
   virtual int get(int) = 0; //get function

};
#include <iostream>
#include <list>
#define key first
#define val second
class LRUCache {
    int cp;
    map<int, list<pair<int, int> >::iterator> mp;
    list<pair<int, int> > lru;
public:
    LRUCache(int capacity) : cp(capacity){}
    void set(int key, int val) {
        if(mp.find(key) != mp.end()) {
            mp[key]->key = key;
            mp[key]->val = val;
        }
        else {
            lru.push_front({key, val});
            mp[key] = lru.begin();
            if(lru.size() > cp) {
                mp.erase(lru.back().key);
                lru.pop_back();
            }
        }
    }
    int get(int key) {
        if(mp.find(key) != mp.end()) {
            lru.push_front(*mp[key]);
            lru.erase(mp[key]);
            mp[key] = lru.begin();
            return mp[key]->val;
        }
        else
            return -1;
    }
};
int main() {
   int n, capacity,i;
   cin >> n >> capacity;
   LRUCache l(capacity);
   for(i=0;i<n;i++) {
      string command;
      cin >> command;
      if(command == "get") {
         int key;
         cin >> key;
         cout << l.get(key) << endl;
      } 
      else if(command == "set") {
         int key, value;
         cin >> key >> value;
         l.set(key,value);
      }
   }
   return 0;
}
-------------------------------------------------
class LRUCache : public Cache {
public:
    LRUCache(size_t capacity)
    {
        cp = capacity;
        tail = 0;
        head = 0;
    }
    
    ~LRUCache() {
        while(tail) {
            auto node = tail;
            tail = tail->prev;
            delete node;
        }
    }
    
    // Set/insert the value off the key, if present, otherwise
    // add the key as the most recently used key. If the cache
    // has reached its capacity, it should replace the least
    // recently used key with a new key.
    void set(int key, int value) {
        Node* node;
        auto it = mp.find(key);
        if(mp.end() == it) {
            if(mp.size() < cp) {
                node = new Node(key, value);
                if(tail) {
                    tail->next = node;
                    node->prev = tail;
                } else {
                    tail = node;
                    head = node;
                }
            } else {
                node = tail;
                mp.erase(tail->value);
            }
            mp.insert(make_pair(key, node));
        } else {
            node = it->second;
        }
        node->key = key;
        node->value = value;
        set_mru(node);
    }
    
    // Get the value (will always be positive) of the key
    // if the key exists in the cache and then make that key
    // as the most recently used key; otherwise, return -1.
    int get(int key) {
        auto it = mp.find(key);
        if(mp.end() == it)
            return -1;

        auto node = it->second;
        set_mru(node);
        return node->value;
    }

private:
    void set_mru(Node* node) {
        if(node->next) {
            node->next->prev = node->prev;
        }
        if(node->prev) {
            node->prev->next = node->next;
        }
        if(tail == node)
            tail = node->prev;
        node->prev = 0;
        node->next = head;
        head = node;
    }
};