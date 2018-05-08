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
	pageList = new DoublyLinkedList();
	pageMap = unordered_map<string, Node*>();
	remove("file.txt");
}

string LRUCache::get(string key) {
	if (pageMap.find(key) != pageMap.end()) {
		string val = pageMap[key]->value;
		// move the page to front
		pageList->move_page_to_head(pageMap[key]);
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
		string k = pageList->get_rear_page()->key;
		string v = pageMap[k]->value;
		string entry = k + ' ' + v;
		outfile.open("file.txt", std::ios_base::app);
		outfile << entry << endl;
		outfile.close();
		pageMap.erase(k);
		pageList->remove_rear_page();
		size -= (k.size() + v.size());
		//size--;
	}
	// add new page to head to Queue
	Node *page = pageList->add_page_to_head(key, value);
	size += key.size() + value.size();
	pageMap[key] = page;
}

void LRUCache::deleteentry(string key) {
	auto it = pageMap.find(key);
	if (it != pageMap.end()) {
		// if key already present, update value and move page to head
		size -= (it->second->value.size() + key.size());
		pageList->remove_node(it->second);
		pageMap.erase(it);
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
	auto i1 = pageMap.begin();
	for (; i1 != pageMap.end(); i1++) {
		delete i1->second;
	}
	delete pageList;
}
