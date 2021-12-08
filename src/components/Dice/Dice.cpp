#include "../../components/Dice/Dice.hpp"
#include <cmath>

namespace Catan {
    /************************** Constructor and Destructor **************************/

    Dice::Dice(/* args */) {}

    Dice::~Dice() {}

    int Dice::roll() {
        return (((rand()*(unsigned)std::chrono::system_clock::now().time_since_epoch().count())%6)+1);
    }
}