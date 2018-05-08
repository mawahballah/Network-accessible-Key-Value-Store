#include"LRUCache.h"

LRUCache::LRUCache(int capacity, CapacityType type) {
	switch (type) {
	case CapacityType::BYTES:
		this->capacity = capacity;
		break;
	case CapacityType::KB:
		this->capacity = capacity * 1024;
		break;
	case CapacityType::MB:
		this->capacity = capacity * 1024 * 1024;
		break;
	default:
		this->capacity = 10 * 1024 * 1024;
		break;
	}
	this->capacity = capacity;
	size = 0;
	KVList = new DoublyLinkedList();
	KeyNodeMap = unordered_map<string, Node*>();
	remove("file.txt");
}

string LRUCache::get(string key) {
	if (KeyNodeMap.find(key) != KeyNodeMap.end()) {
		string val = KeyNodeMap[key]->value;
		// move the node to front
		KVList->move_node_to_front(KeyNodeMap[key]);
		return val;
	}
	else
	{
		string entryinfile = getfromfile(key);
		if (entryinfile != "")
		{
			size_t pos = entryinfile.find(' ');
			put(key, entryinfile.substr(pos + 1, entryinfile.size()));
			return entryinfile.substr(pos + 1, entryinfile.size());
		}
		else
			return "not found";
	}
}

string LRUCache::getfromfile(string key)
{
	infile.open("file.txt");
	string entry;
	string result = "";
	ofstream out("outfile.txt");
	while (getline(infile, entry))
	{
		size_t pos = entry.find(' ');
		string deletekey = entry.substr(0, pos);
		if (deletekey != key)
		{
			out << entry << endl;
		}
		else
		{
			result = entry;
		}
	}
	infile.close();
	out.close();
	remove("file.txt");
	rename("outfile.txt", "file.txt");
	return result;
}

void LRUCache::put(string key, string value) {
	deleteentry(key);
	//if(capacity >  key.size() + value.size())
	while ((capacity < size + key.size() + value.size())) {
		// remove rear page
		string k = KVList->get_rear_node()->key;
		string v = KeyNodeMap[k]->value;
		string entry = k + ' ' + v;
		outfile.open("file.txt", std::ios_base::app);
		outfile << entry << endl;
		outfile.close();
		KeyNodeMap.erase(k);
		KVList->remove_rear_node();
		size -= (k.size() + v.size());
		//size--;
	}
	// add new page to head to Queue
	Node *page = KVList->add_node_to_front(key, value);
	size += key.size() + value.size();
	KeyNodeMap[key] = page;
}

void LRUCache::deleteentry(string key) {
	auto it = KeyNodeMap.find(key);
	if (it != KeyNodeMap.end()) {
		// if key already present, update value and move page to head
		size -= (it->second->value.size() + key.size());
		KVList->remove_node(it->second);
		KeyNodeMap.erase(it);
		return;
	}
	infile.open("file.txt");
	ofstream out("outfile.txt");
	string entry;
	while (getline(infile, entry))
	{
		size_t pos = entry.find(' ');
		string deletekey = entry.substr(0, pos);
		string deletevalue = entry.substr(pos + 1, entry.size());
		if (deletekey != key)
		{
			out << deletekey << ' ' << deletevalue << endl;
		}
	}
	infile.close();
	out.close();
	remove("file.txt");
	rename("outfile.txt", "file.txt");
}
LRUCache::~LRUCache() {
	auto i1 = KeyNodeMap.begin();
	for (; i1 != KeyNodeMap.end(); i1++) {
		delete i1->second;
	}
	delete KVList;
}
