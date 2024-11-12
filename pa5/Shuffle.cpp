/*
Phil Liu
phzliu
2024 Fall CSE101 PA5
List.h
Header file for List ADT
*/

#include<string>
#include"List.h"

using namespace std;

void shuffle(List& deck) {
int deckSize = deck.length();

List firstHalf;
List secondHalf;
deck.moveFront();

while (deck.position() < deck.length()) {
    if (deck.position() < deckSize / 2) {
        firstHalf.insertBefore(deck.moveNext());
    }
    else {
        secondHalf.insertBefore(deck.moveNext());
    }
}

deck.clear();
firstHalf.moveFront();
secondHalf.moveFront();
for (int i = 1; i <= deckSize; i += 1) {
    if (i % 2 == 0) {
        deck.insertBefore(firstHalf.moveNext());
    } else {
        deck.insertBefore(secondHalf.moveNext());
    }
}
}


int main(int argc, char* argv[]) {
    if( argc != 2 ){
        cerr << "Usage: " << argv[0] << " <deck size>" << endl;
        return(EXIT_FAILURE);
    }

    int deck_size = atoi(argv[1]);
    if (deck_size <= 0) {
        cerr << "Deck size must be a positive integer" << endl;
        return(EXIT_FAILURE);
    }

    cout << "deck size\t\tshuffle count\n------------------------------" << endl;

    for (int i = 1; i <= deck_size; i++) {
        List deck;
        for (int j = 1; j <= i; j++) {
            deck.insertBefore(j);
        }

        List deck_inorder = deck;
        int count = 0;
        while (true) {
            shuffle(deck);
            count++;
            if (deck.equals(deck_inorder)) {
                break;
            }
        }
        cout << i << "\t\t\t\t" << count << endl;
    }

    return 0;
}