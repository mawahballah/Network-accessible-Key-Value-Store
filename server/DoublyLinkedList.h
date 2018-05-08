#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H
#include"Node.h"
class DoublyLinkedList {
	Node *front, *rear;
	bool isEmpty();
public:
	DoublyLinkedList();
	Node* add_page_to_head(string key, string value);
	void move_page_to_head(Node *page);
	void remove_node(Node*page);
	void remove_rear_page();
	Node* get_rear_page();
};
#endif