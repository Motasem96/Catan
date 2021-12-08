/**
 * @author: Al Motasem Bellah Arisheh
 * This Class represents a Dice, which could be rolled by a player to get a random number from 1 to 6.
 **/

#ifndef DICE_HEADER
#define DICE_HEADER
#include <chrono>
#include <random>

namespace Catan {
    class Dice {

    protected:
        /* data */
    public:
        Dice(/* args */);
        ~Dice();
        int roll();
    };
}
#endif