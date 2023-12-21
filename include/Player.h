#ifndef PLAYER_H
#define PLAYER_H

class Player {
    protected:
        int balance;
        int position;

    public:
        Player(void) {};
        void print(void) {};
        int getBalance(void) const { return this->balance; };
};

#endif