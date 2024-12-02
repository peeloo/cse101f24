/*
Phil Liu
phzliu
2024 Fall CSE101 PA8
Dictionary.cpp
Implementation File for Dictionary ADT
*/

#include <iostream>
#include <stdexcept>
#include <string>
#include "Dictionary.h"

#define RED 0
#define BLACK 1

//Constructors & Destructors ----------------------------------------

Dictionary::Node::Node(keyType k, valType v) {
    key = k;
    val = v;
    parent = nullptr;
    left = nullptr;
    right = nullptr;
    color = RED;
}

Dictionary::Dictionary() {
    nil = new Node("nil", -1);
    nil->color = BLACK;
    root = nil;
    current = nil;
    num_pairs = 0;
}

Dictionary::Dictionary(const Dictionary& D) {
    nil = new Node("nil", -1);
    nil->color = BLACK;
    root = nil;
    current = nil;
    num_pairs = 0;

    preOrderCopy(D.root, D.nil);
}

Dictionary::~Dictionary() {
    clear();
    delete nil;
}

// helper functions
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
    s += R->key + (R->color == RED ? " (RED)" : "") + "\n";
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

// rbt helper functions

void Dictionary::LeftRotate(Node* N) {
    Node* y = N->right;
    N->right = y->left;
    if (y->left != nil) {
        y->left->parent = N;
    }
    y->parent = N->parent;
    if (N->parent == nil) {
        root = y;
    }
    else {
        if (N == N->parent->left) {
            N->parent->left = y;
        }
        else {
            N->parent->right = y;
        }
    }
    y->left = N;
    N->parent = y;
}

void Dictionary::RightRotate(Node* N) {
    Node* y = N->left;
    N->left = y->right;
    if (y->right != nil) {
        y->right->parent = N;
    }
    y->parent = N->parent;
    if (N->parent == nil) {
        root = y;
    }
    else {
        if (N == N->parent->right) {
            N->parent->right = y;
        }
        else {
            N->parent->left = y;
        }
    }
    y->right = N;
    N->parent = y;
}

void Dictionary::RB_InsertFixUp(Node* N) {
    while (N->parent->color == RED) {
        if (N->parent == N->parent->parent->left) {
            Node* y = N->parent->parent->right;
            if (y->color == RED) {
                N->parent->color = BLACK;
                y->color = BLACK;
                N->parent->parent->color = RED;
                N = N->parent->parent;
            }
            else {
                if (N == N->parent->right) {
                    N = N->parent;
                    LeftRotate(N);
                }
                N->parent->color = BLACK;
                N->parent->parent->color = RED;
                RightRotate(N->parent->parent);
            }
        }
        else {
            Node* y = N->parent->parent->left;
            if (y->color == RED) {
                N->parent->color = BLACK;
                y->color = BLACK;
                N->parent->parent->color = RED;
                N = N->parent->parent;
            }
            else {
                if (N == N->parent->left) {
                    N = N->parent;
                    RightRotate(N);
                }
                N->parent->color = BLACK;
                N->parent->parent->color = RED;
                LeftRotate(N->parent->parent);
            }
        }
    }
    root->color = BLACK;
}

void Dictionary::RB_Transplant(Node* u, Node* v) {
    if (u->parent == nil) {
        root = v;
    }
    else if (u == u->parent->left) {
        u->parent->left = v;
    }
    else {
        u->parent->right = v;
    }
    v->parent = u->parent;
}

void Dictionary::RB_DeleteFixUp(Node* N) {
    while (N != root && N->color == BLACK) {
        if (N == N->parent->left) {
            Node* w = N->parent->right;
            if (w->color == RED) {
                w->color = BLACK;
                N->parent->color = RED;
                LeftRotate(N->parent);
                w = N->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                N = N->parent;
            }
            else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    RightRotate(w);
                    w = N->parent->right;
                }
                w->color = N->parent->color;
                N->parent->color = BLACK;
                w->right->color = BLACK;
                LeftRotate(N->parent);
                N = root;
            }
        }
        else {
            Node* w = N->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                N->parent->color = RED;
                RightRotate(N->parent);
                w = N->parent->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;
                N = N->parent;
            }
            else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    LeftRotate(w);
                    w = N->parent->left;
                }
                w->color = N->parent->color;
                N->parent->color = BLACK;
                w->left->color = BLACK;
                RightRotate(N->parent);
                N = root;
            }
        }
    }
    N->color = BLACK;
}

void Dictionary::RB_Delete(Node* N) {
    Node* x;
    Node* y = N;
    int orig_color = y->color;
    if (N->left == nil) {
        x = N->right;
        RB_Transplant(N, N->right);
    }
    else if (N->right == nil) {
        x = N->left;
        RB_Transplant(N, N->left);
    }
    else {
        y = findMin(N->right);
        orig_color = y->color;
        x = y->right;
        if (y->parent == N) {
            x->parent = y;
        }
        else {
            RB_Transplant(y, y->right);
            y->right = N->right;
            y->right->parent = y;
        }
        RB_Transplant(N, y);
        y->left = N->left;
        y->left->parent = y;
        y->color = N->color;
    }
    if (orig_color == BLACK) {
        RB_DeleteFixUp(x);
    }
    delete N;
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

// Manipulation procedures -------------------------------------------------
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
    z->left = nil;
    z->right = nil;
    z->color = RED;
    RB_InsertFixUp(z);
}

void Dictionary::remove(keyType k) {
    if (!contains(k)) {
        throw std::logic_error("Dictionary: remove(): Dictionary does not contain key");
    }

    Node* x = search(root, k);
    if (x == current) {
        current = nil;
    }
    RB_Delete(x);
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
