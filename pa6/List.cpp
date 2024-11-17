/*
Phil Liu
phzliu
2024 Fall CSE101 PA6
List.cpp
Implements List ADT and its operations
*/

#include <iostream>
#include <stdexcept>
#include "List.h"

// Private Constructors

List::Node::Node(ListElement x) {
    data = x;
    next = nullptr;
    prev = nullptr;
}

// Class constructors & Destructors

List::List() {
    frontDummy = new Node(-2147483648);
    backDummy = new Node(2147483647);
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    pos_cursor = 0;
    num_elements = 0;
}

List::List(const List& L) {
    frontDummy = new Node(-2147483648);
    backDummy = new Node(2147483647);
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    pos_cursor = 0;
    num_elements = 0;

    Node *N = L.frontDummy->next;
    while (N != L.backDummy) {
        insertBefore(N->data);
        N = N->next;
    }
    moveFront();
}

List::~List() {
    clear();
    delete frontDummy;
    delete backDummy;
}

// access funcs

int List::length() const {
    return num_elements;
}

ListElement List::front() const {
    if (length() <= 0) {
        throw std::length_error("List: calling front() on empty List");
    }

    return frontDummy->next->data;
}

ListElement List::back() const {
    if (length() <= 0) {
        throw std::length_error("List: calling back() on empty List");
    }

    return backDummy->prev->data;
}

int List::position() const {
    return pos_cursor;
}

ListElement List::peekNext() const {
    if (position() >= length()) {
        throw std::range_error("List: calling peekNext() with position() >= length()");
    }

    return afterCursor->data;
}

ListElement List::peekPrev() const {
    if (position() <= 0) {
        throw std::range_error("List: calling peekPrev() with position() < 0");
    }

    return beforeCursor->data;
}

// Manipulation procedures

void List::clear() {
    moveFront();
    while (length() > 0) {
        eraseAfter();
    }
}

void List::moveFront() {
    beforeCursor = frontDummy;
    afterCursor = frontDummy->next;
    pos_cursor = 0;
}

void List::moveBack() {
    beforeCursor = backDummy->prev;
    afterCursor = backDummy;
    pos_cursor = length();
}

ListElement List::moveNext() {
    if (position() >= length()) {
        throw std::range_error("List: calling moveNext() with position() >= length()");
    }

    ListElement passed_over = afterCursor->data;
    beforeCursor = afterCursor;
    afterCursor = afterCursor->next;
    pos_cursor++;
    return passed_over;
}

ListElement List::movePrev() {
    if (position() <= 0) {
        throw std::range_error("List: calling movePrev() with position() <= 0");
    }

    ListElement passed_over = beforeCursor->data;
    afterCursor = beforeCursor;
    beforeCursor = beforeCursor->prev;
    pos_cursor--;
    return passed_over;
}

void List::insertAfter(ListElement x) {
    Node *new_node = new Node(x);
    afterCursor->prev = new_node;
    beforeCursor->next = new_node;
    new_node->prev = beforeCursor;
    new_node->next = afterCursor;
    afterCursor = new_node;
    num_elements++;
}

void List::insertBefore(ListElement x) {
    Node *new_node = new Node(x);
    afterCursor->prev = new_node;
    beforeCursor->next = new_node;
    new_node->prev = beforeCursor;
    new_node->next = afterCursor;
    beforeCursor = new_node;
    num_elements++;
    pos_cursor++;
}

void List::setAfter(ListElement x) {
    if (position() >= length()) {
        throw std::range_error("List: calling setAfter() with position() >= length()");
    }

    afterCursor->data = x;
}

void List::setBefore(ListElement x) {
    if (position() <= 0) {
        throw std::range_error("List: calling setBefore() with position() <= 0");
    }

    beforeCursor->data = x;
}

void List::eraseAfter() {
    if (position() >= length()) {
        throw std::range_error("List: Calling eraseAfter() with position() >= length()");
    }

    Node *temp = afterCursor;
    afterCursor = afterCursor->next;
    afterCursor->prev = beforeCursor;
    beforeCursor->next = afterCursor;
    delete temp;
    num_elements--;
}

void List::eraseBefore() {
    if (position() <= 0) {
        throw std::range_error("List: calling eraseBefore() with position() <= 0");
    }

    Node *temp = beforeCursor;
    beforeCursor = beforeCursor->prev;
    beforeCursor->next = afterCursor;
    afterCursor->prev = beforeCursor;
    delete temp;
    num_elements--;
    pos_cursor--;
}

// other functions

int List::findNext(ListElement x) {
    while (position() < length()) {
        if (moveNext() == x) {
            return position();
        }
    }

    return -1;
}

int List::findPrev(ListElement x) {
    while (position() > 0) {
        if (movePrev() == x) { 
            return position();
        }
    }

    return -1;
}

void List::cleanup() {
    Node *N = beforeCursor;
    moveFront();
    List seen;
    while (this->position() < this->length()) {
        seen.moveFront();
        if (seen.findNext(this->moveNext()) != -1) {
            if (N == beforeCursor) {
                N = N->prev;
            }
            this->eraseBefore();
        }
        else {
            seen.insertBefore(this->peekPrev());
        }
    }

    moveFront();
    if (N != frontDummy) {
        findNext(N->data);
    }
}

List List::concat(const List&L) const {
    List temp;
    Node *curr1 = this->frontDummy->next;
    Node *curr2 = L.frontDummy->next;
    while (curr1 != this->backDummy) {
        temp.insertBefore(curr1->data);
        curr1 = curr1->next;
    }
    while (curr2 != L.backDummy) {
        temp.insertBefore(curr2->data);
        curr2 = curr2->next;
    }
    temp.moveFront();
    return temp;
}

std::string List::to_string() const {
    Node *curr = frontDummy->next;
    std::string s = "(";
    while (curr != backDummy) {
        s += std::to_string(curr->data);
        if (curr != backDummy->prev) {
            s += ", ";
        }
        curr = curr->next;
    }
    s += ")";
    return s;
}

bool List::equals(const List& R) const {
    if (this->length() != R.length()) {
        return false;
    }

    Node *curr1 = this->frontDummy->next;
    Node *curr2 = R.frontDummy->next;
    while (curr1 != this->backDummy) {
        if (curr1->data != curr2->data) {
            return false;
        }
        curr1 = curr1->next;
        curr2 = curr2->next;
    }

    return true;
}

// overriden operators

std::ostream& operator<<( std::ostream& stream, const List& L ) {
    return stream << L.List::to_string();
}

bool operator==( const List& A, const List& B ) {
    return A.List::equals(B);
}

List& List::operator=( const List& L ) {
    if (this != &L) {
        List temp = L;
        std::swap(frontDummy, temp.frontDummy);
        std::swap(backDummy, temp.backDummy);
        std::swap(num_elements, temp.num_elements);
        std::swap(beforeCursor, temp.beforeCursor);
        std::swap(afterCursor, temp.afterCursor);
        std::swap(pos_cursor, temp.pos_cursor);
    }
    return *this;
}