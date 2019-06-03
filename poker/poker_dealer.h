#ifndef POKER_DEALER_H
#define POKER_DEALER_H

class PokerDealer
{
public: 
    PokerDealer();
    ~PokerDealer();

    static void ProcessArgs(int argc, char* argv[]);

private:    
    size_t numPlayers;

};

#endif //POKER_DEALER_H