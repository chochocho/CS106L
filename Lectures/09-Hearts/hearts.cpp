#include <ctime>
#include <string>
#include <vector>
#include <deque>
#include <utility>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <iostream>
#include <iomanip>

using namespace std;

// The CardSuit enum lists all of the possible suits that a card can have.
enum CardSuit {
  HEARTS,
  DIAMONDS,
  CLUBS,
  SPADES
};

// The CardValue enum lists all of the possible values that a card can have, in
// increasing order.
enum CardValue {
  TWO, THREE, FOUR, FIVE, SIX,
  SEVEN, EIGHT, NINE, TEN,
  JACK, QUEEN, KING, ACE
};

// A Card simply consists of a suit and a value.
struct Card {
  CardSuit suit;
  CardValue value;
};

// We devise this data structure to hold a bunch of cards. It'll be used for the
// entire deck, as well as the cards in a player's hand and the cards in the
// current trick.
typedef deque<Card> Deck;

// A Player has a name, a hand, and some number of points.
struct Player {
  string name;
  Deck hand;
  int points;
};

// These constants control the number of cards, tricks, players, and score limit
// for the game of hearts.
const int kNumCardsPerPlayer = 13;
const int kNumPlayers = 4;
const int kPointsToLose = 100;

// Our card players!
const string kPlayerNames[kNumPlayers] = {
  "John Lennon",
  "Paul McCartney",
  "George Harrison",
  "The Drummer Guy"
};

#include "hearts.h"

void ShuffleDeck(Deck& deck) {
  random_shuffle(deck.begin(), deck.end());
}

bool CompareTwoCards(Card lhs, Card rhs) {
  if (lhs.suit != rhs.suit)
    return lhs.suit < rhs.suit;
  return lhs.value < rhs.value;
}

void DealCards(Deck& deck, vector<Player>& players) {
  for (size_t p = 0; p < players.size(); ++p) {
    players[p].hand.resize(kNumCardsPerPlayer);
    copy(deck.begin() + kNumCardsPerPlayer * p,
         deck.begin() + kNumCardsPerPlayer * (p + 1),
         players[p].hand.begin());
    
    sort(players[p].hand.begin(), players[p].hand.end(), CompareTwoCards);
  }
}

bool CompareByValue(Card lhs, Card rhs) {
  return lhs.value < rhs.value;
}

bool CompareBySuit(Card lhs, Card rhs) {
  return lhs.suit < rhs.suit;
}

void PlayFirstCard(Deck& trick, Player& player) {
  Deck::iterator toPlay = min_element(player.hand.begin(), player.hand.end(), CompareByValue);
  
  trick.push_back(*toPlay);
  player.hand.erase(toPlay);
}

void PlayFollowingCard(Deck& trick, Player& player) {
  pair<Deck::iterator, Deck::iterator> allOfSuit =
    equal_range(player.hand.begin(), player.hand.end(), trick.front(), CompareBySuit);
  
  
  Deck::iterator toPlay;
  if (allOfSuit.first == allOfSuit.second) {
    toPlay = max_element(player.hand.begin(), player.hand.end(), CompareByValue);
  } else {
    toPlay = min_element(allOfSuit.first, allOfSuit.second, CompareByValue);
  }
  
  trick.push_back(*toPlay);
  player.hand.erase(toPlay);
}

void PlayRound(vector<Player>& players) {
  for (int i = 0; i < kNumCardsPerPlayer; ++i) {
    Deck trick;
    for (size_t p = 0; p < players.size(); ++p) {
      if (p == 0) {
        PlayFirstCard(trick, players[p]);
      } else {
        PlayFollowingCard(trick, players[p]);
      }
      
      cout << players[p].name << ": ";
      PrintCard(trick.back());
      cout << endl;
    }
    
    size_t winningPlayer = GetTrickWinner(trick);
    cout << players[winningPlayer].name << " takes the trick." << endl << endl;
    players[winningPlayer].points += GetPoints(trick);
    
    rotate(players.begin(), players.begin() + winningPlayer, players.end());
  }
}

bool HasTooManyPoints(Player& player) {
  return player.points >= kPointsToLose;
}

bool IsGameOver(vector<Player>& players) {
  vector<Player>::iterator itr = find_if(players.begin(), players.end(), HasTooManyPoints);
  return itr != players.end();
}

int main() {
  srand(time(NULL));
  Deck deck;
  FillDeck(deck);
  vector<Player> players = InitializePlayers();
  
  while (!IsGameOver(players)) {
    ShuffleDeck(deck);
    DealCards(deck, players);
    PrintAllHands(players);
    WaitForEnter();
    
    PlayRound(players);
    PrintScores(players);
    WaitForEnter();
  }
  
  return 0;
}

