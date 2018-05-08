#include "DoublyLinkedList.h"

bool DoublyLinkedList::isEmpty() {
	return rear == NULL;
}

DoublyLinkedList::DoublyLinkedList() : front(NULL), rear(NULL) {}
Node* DoublyLinkedList::add_page_to_head(string key, string value) {
	Node *page = new Node(key, value);
	if (!front && !rear) {
		front = rear = page;
	}
	else {
		page->next = front;
		front->prev = page;
		front = page;
	}
	return page;
}
void DoublyLinkedList::move_page_to_head(Node *page) {
	if (page == front) {
		return;
	}
	if (page == rear) {
		rear = rear->prev;
		rear->next = NULL;
	}
	else {
		page->prev->next = page->next;
		page->next->prev = page->prev;
	}

	page->next = front;
	page->prev = NULL;
	front->prev = page;
	front = page;
}
void DoublyLinkedList::remove_node(Node*page)
{
	if (page == rear)
	{
		rear = rear->prev;
		if(rear)
			rear->next = NULL;
		delete page;
		return;
	}
	if (page == front)
	{
		front = front->next;
		if (front)
			front->prev = NULL;
		delete page;
		return;
	}
	page->prev->next = page->next;
	page->next->prev = page->prev;
	delete page;
}
void DoublyLinkedList::remove_rear_page() {
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
Node* DoublyLinkedList::get_rear_page() {
	return rear;
}