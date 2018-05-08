#ifndef NODE_H
#define NODE_H
#include <iostream>
#include<string>
#include<string.h>
#include<unordered_map>
#include <algorithm>
using namespace std;
class Node {
public:
	string key, value;
	Node *prev, *next;
	Node(string k, string v);
};
#endif