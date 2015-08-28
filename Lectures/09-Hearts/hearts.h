#ifndef HEARTS_HEADER
#define HEARTS_HEADER

// WaitForEnter, from lecture 1, waits for the user to type something in at the
// console and returns the input as a string.
string WaitForEnter() {
  string result;
  getline(cin, result);
  return result;
}

// PrintCard handily prints the suit and value of a card using unicode for the
// suit symbols.
void PrintCard(Card card) {
  switch (card.value) {
    case JACK:
      cout << " J";
      break;
    case QUEEN:
      cout << " Q";
      break;
    case KING:
      cout << " K";
      break;
    case ACE:
      cout << " A";
      break;
    default:
      cout << setw(2) << (card.value + 2);
  }
  
  switch (card.suit) {
    case HEARTS:
      cout << "\u2665 ";
      break;
    case DIAMONDS:
      cout << "\u2666 ";
      break;
    case CLUBS:
      cout << "\u2663 ";
      break;
    case SPADES:
      cout << "\u2660 ";
      break;
  }
}

// InitializePlayers sets up the players vector. It is assumed that the players
// vector starts off at the appropriate size.
vector<Player> InitializePlayers() {
  vector<Player> players(kNumPlayers);
  for (size_t i = 0; i < players.size(); ++i) {
    players[i].name = kPlayerNames[i];
    players[i].points = 0;
  }
  
  return players;
}

// FillDeck populates the given deck of cards (assumed to be empty) with each
// of the 52 cards in a standard deck.
void FillDeck(Deck& deck) {
  for (CardSuit suit = HEARTS; suit <= SPADES; suit = CardSuit(suit + 1)) {
    for (CardValue value = TWO; value <= ACE; value = CardValue(value + 1)) {
      Card card = { suit, value };
      deck.push_back(card);
    }
  }
}

// GetTrickWinner loops through the cards played in a trick and
// determines which one wins.
size_t GetTrickWinner(Deck& trick) {
  // Assume the first player is the winning player:
  size_t winningIndex = 0;
  CardValue winningValue = trick.front().value;
  CardSuit toFollow = trick.front().suit;
  
  // Check the other players:
  for (size_t i = 1; i < trick.size(); ++i) {
    if (trick[i].suit == toFollow && trick[i].value > winningValue) {
      winningIndex = i;
      winningValue = trick[i].value;
    }
  }
  
  return winningIndex;
}

// GetPoints tallies the total worth of the trick based on how many hearts it
// contains, and whether the queen of spades appears.
int GetPoints(Deck& trick) {
  int total = 0;
  for (size_t i = 0; i < trick.size(); ++i) {
    if (trick[i].suit == HEARTS)
      ++total;
    if (trick[i].suit == SPADES && trick[i].value == QUEEN)
      total += 13;
  }
  
  return total;
}

// PrintAllHands prints out the cards held in each player's hand.
void PrintAllHands(vector<Player>& players) {
  for (size_t i = 0; i < players.size(); ++i) {
    cout << players[i].name << " has:" << endl;
    for (size_t j = 0; j < players[i].hand.size(); ++j)
      PrintCard(players[i].hand[j]);
    
    cout << endl;
  }
}

// PrintScores prints out each player's score.
void PrintScores(vector<Player>& players) {
  for(size_t i = 0; i < players.size(); ++i)
    cout << players[i].name << " has " << players[i].points << " points." << endl;
}

/** starter code ends here **/
#endif
