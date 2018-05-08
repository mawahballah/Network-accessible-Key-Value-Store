#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H
#include"Node.h"
class DoublyLinkedList {
	Node *front, *rear;
	bool isEmpty();
public:
	DoublyLinkedList();
	Node* add_node_to_front(string key, string value);
	void move_node_to_front(Node *entry);
	void remove_node(Node*entry);
	void remove_rear_node();
	Node* get_rear_node();
};
#endif