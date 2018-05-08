#ifndef LRUCACHE_H
#define LRUCACHE_H
#include"DoublyLinkedList.h"
#include<fstream>
using namespace std;
enum CapacityType {
	MB,
	KB,
	BYTES
};
class LRUCache {
	int capacity, size;
	DoublyLinkedList *KVList;
	unordered_map<string, Node*> KeyNodeMap;
	ofstream outfile;
	ifstream infile;
public:
	LRUCache(int capacity, CapacityType type);
	string get(string key);
	string getfromfile(string key);
	void put(string key, string value);
	void deleteentry(string key);
	~LRUCache();
	int getCapacity() { return capacity; }
};


#endif