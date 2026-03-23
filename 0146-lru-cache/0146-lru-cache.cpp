#include <unordered_map>
#include <list>

class LRUCache {
private:
    int cap;
    // list stores {key, value} pairs
    std::list<std::pair<int, int>> cacheList;
    // map stores key -> iterator to the node in cacheList
    std::unordered_map<int, std::list<std::pair<int, int>>::iterator> cacheMap;

public:
    LRUCache(int capacity) {
        cap = capacity;
    }
    
    int get(int key) {
        if (cacheMap.find(key) == cacheMap.end()) {
            return -1;
        }
        
        // Move the accessed node to the front (most recently used)
        // splice() moves the element from one position to another in O(1)
        cacheList.splice(cacheList.begin(), cacheList, cacheMap[key]);
        
        return cacheMap[key]->second;
    }
    
    void put(int key, int value) {
        // If key already exists
        if (cacheMap.find(key) != cacheMap.end()) {
            // Update the value
            cacheMap[key]->second = value;
            // Move to front
            cacheList.splice(cacheList.begin(), cacheList, cacheMap[key]);
            return;
        }
        
        // If at capacity, evict the least recently used (tail of the list)
        if (cacheList.size() == cap) {
            int lastKey = cacheList.back().first;
            cacheMap.erase(lastKey);
            cacheList.pop_back();
        }
        
        // Insert new pair at the front
        cacheList.push_front({key, value});
        cacheMap[key] = cacheList.begin();
    }
};