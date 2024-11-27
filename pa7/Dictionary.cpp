/*
Phil Liu
phzliu
2024 Fall CSE101 PA7
Dictionary.cpp
Implementation File for Dictionary ADT
*/

#include <iostream>
#include <stdexcept>
#include <string>
#include "Dictionary.h"

// class constructors / destructors

Dictionary::Node::Node(keyType k, valType v) {
    key = k;
    val = v;
    parent = nullptr;
    left = nullptr;
    right = nullptr;
}

Dictionary::Dictionary() {
    nil = nullptr;
    root = nullptr;
    current = nullptr;
    num_pairs = 0;
}

Dictionary::Dictionary(const Dictionary& D) {
    nil = nullptr;
    root = nullptr;
    current = nullptr;
    num_pairs = 0;
    preOrderCopy(D.root, nil);
}

Dictionary::~Dictionary() {
    clear();
    delete nil;
}

void Dictionary::inOrderString(std::string& s, Node* R) const {
    if (R == nil) {
        return;
    }
    inOrderString(s, R->left);
    s.append(R->key).append(" : ").append(std::to_string(R->val)).append("\n");
    inOrderString(s, R->right);
}

void Dictionary::preOrderString(std::string& s, Node* R) const {
    if (R == nil) {
        return;
    }
    s.append(R->key).append("\n");
    preOrderString(s, R->left);
    preOrderString(s, R->right);
}

void Dictionary::preOrderCopy(Node* R, Node* N) {
    if (R == N) {
        return;
    }
    setValue(R->key, R->val);
    preOrderCopy(R->left, N);
    preOrderCopy(R->right, N);
}

void Dictionary::postOrderDelete(Node *R) {
    if (R == nil) {
        return;
    }
    postOrderDelete(R->left);
    postOrderDelete(R->right);
    delete R;
}

Dictionary::Node* Dictionary::search(Node* R, keyType k) const {
    if (R == nil) {
        return R;
    }

    if (R->key > k) {
        return search(R->left, k);
    }
    else if (R->key < k) {
        return search(R->right, k);
    }
    return R;
}

Dictionary::Node* Dictionary::findMin(Node* R) {
    while (R->left != nil) {
        R = R->left;
    }
    return R;
}
Dictionary::Node* Dictionary::findMax(Node* R) {
    while (R->right != nil) {
        R = R->right;
    }
    return R;
}

Dictionary::Node* Dictionary::findNext(Node* N) {
    // case 1
    if (N->right != nil) {
        return findMin(N->right);
    }

    // case 2
    Node* P = N->parent;
    while (P != nil && P->right == N) {
        N = P;
        P = P->parent;
    }
    return P;
}

Dictionary::Node* Dictionary::findPrev(Node* N) {
    if (N->left != nil) {
        return findMax(N->left);
    }

    Node* P = N->parent;
    while (P != nil && P->left == N) {
        N = P;
        P = P->parent;
    }
    return P;
}

// access functions

int Dictionary::size() const {
    return num_pairs;
}

bool Dictionary::contains(keyType k) const {
    return (search(root, k) != nil);
}

valType& Dictionary::getValue(keyType k) const {
    if (!contains(k)) {
        throw std::logic_error("Dictionary: getValue(): Dictionary does not contain key");
    }
    Node* temp = search(root, k);
    return temp->val;
}

bool Dictionary::hasCurrent() const {
    return (current != nil);
}

keyType Dictionary::currentKey() const {
    if (!hasCurrent()) {
        throw std::logic_error("Dictionary: currentKey(): Current is nil");
    }
    return current->key; 
}

valType& Dictionary::currentVal() const {
    if (!hasCurrent()) {
        throw std::logic_error("Dictionary: currentVal(): Current is nil");
    }
    return current->val;
}

// manipulation procedures

void Dictionary::clear() {
    postOrderDelete(root);
    root = nil;
    current = nil;
    num_pairs = 0;
}

void Dictionary::setValue(keyType k, valType v) {
    Node* x = root;
    Node* y = nil;
    Node* z = new Node(k, v);
    while (x != nil) {
        y = x;
        if (z->key < x->key) {
            x = x->left;
        }
        else if (z->key > x->key) {
            x = x->right;
        }
        else {  // key already exists
            x->val = v;
            delete z;
            return;
        }
    }
    z->parent = y;
    if (y == nil) {
        root = z;
    }
    else if (z->key < y->key) {
        y->left = z;
    }
    else {
        y->right = z;
    }
    num_pairs++;
}

void Dictionary::remove(keyType k) {
    if (!contains(k)) {
        throw std::logic_error("Dictionary: remove(): Dictionary does not contain key");
    }

    Node* x = search(root, k);
    if (x == current) {
        current = nil;
    }

    // Lambda function for transplant
    auto transplant = [this](Node* u, Node* v) {
        if (u->parent == nil) {
            root = v;
        } else if (u == u->parent->left) {
            u->parent->left = v;
        } else {
            u->parent->right = v;
        }
        if (v != nil) {
            v->parent = u->parent;
        }
    };

    if (x->left == nil) {
        transplant(x, x->right);
        delete x;
    }
    else if (x->right == nil) {
        transplant(x, x->left);
        delete x;
    }
    else {
        Node* y = findMin(x->right);
        if (y->parent != x) {
            transplant(y, y->right);
            y->right = x->right;
            y->right->parent = y;
        }
        transplant(x, y);
        y->left = x->left;
        y->left->parent = y;
        delete x;
    }
    num_pairs--;
}

void Dictionary::begin() {
    if (root == nil) {
        return;
    }
    current = findMin(root);
}

void Dictionary::end() {
    if (root == nil) {
        return;
    }
    current = findMax(root);
}

void Dictionary::next() {
    if (!hasCurrent()) {
        throw std::logic_error("Dictionary: next(): current pointer not initialized");
    }
    current = findNext(current);
}

void Dictionary::prev() {
    if (!hasCurrent()) {
        throw std::logic_error("Dictionary: prev(): current pointer not initialized");
    }
    current = findPrev(current);
}

// other functions

std::string Dictionary::to_string() const {
    std::string s;
    inOrderString(s, root);
    return s;
}

std::string Dictionary::pre_string() const {
    std::string s;
    preOrderString(s, root);
    return s;
}

bool Dictionary::equals(const Dictionary& D) const {
    if (this->num_pairs != D.num_pairs) {
        return false;
    }
    return (to_string() == D.to_string());
}

// overloaded operators

std::ostream& operator<<(std::ostream& stream, Dictionary& D) {
    stream << D.to_string();
    return stream;
}

bool operator==(const Dictionary& A, const Dictionary& B) {
    return A.equals(B);
}

Dictionary& Dictionary::operator=(const Dictionary& D) {
    if (this != &D) {
        Dictionary temp = D;
        std::swap(nil, temp.nil);
        std::swap(root, temp.root);
        std::swap(current, temp.current);
        std::swap(num_pairs, temp.num_pairs);
    }
    return *this;
}