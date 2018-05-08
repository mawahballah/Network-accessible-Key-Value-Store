#include "DoublyLinkedList.h"

bool DoublyLinkedList::isEmpty() {
	return rear == NULL;
}

DoublyLinkedList::DoublyLinkedList() : front(NULL), rear(NULL) {}
Node* DoublyLinkedList::add_node_to_front(string key, string value) {
	Node *entry = new Node(key, value);
	if (!front && !rear) {
		front = rear = entry;
	}
	else {
		entry->next = front;
		front->prev = entry;
		front = entry;
	}
	return entry;
}
void DoublyLinkedList::move_node_to_front(Node *entry) {
	if (entry == front) {
		return;
	}
	if (entry == rear) {
		rear = rear->prev;
		rear->next = NULL;
	}
	else {
		entry->prev->next = entry->next;
		entry->next->prev = entry->prev;
	}

	entry->next = front;
	entry->prev = NULL;
	front->prev = entry;
	front = entry;
}
void DoublyLinkedList::remove_node(Node*entry)
{
	if (entry == rear)
	{
		rear = rear->prev;
		if(rear)
			rear->next = NULL;
		delete entry;
		return;
	}
	if (entry == front)
	{
		front = front->next;
		if (front)
			front->prev = NULL;
		delete entry;
		return;
	}
	entry->prev->next = entry->next;
	entry->next->prev = entry->prev;
	delete entry;
}
void DoublyLinkedList::remove_rear_node() {
	if (isEmpty()) {
		return;
	}
	if (front == rear) {
		delete rear;
		front = rear = NULL;
	}
	else {
		Node *temp = rear;
		rear = rear->prev;
		rear->next = NULL;
		delete temp;
	}
}
Node* DoublyLinkedList::get_rear_node() {
	return rear;
}