/**
 * @author: Al Motasem Bellah Arisheh
 * 
 **/
#ifndef TRENDCARD_HEADER
#define TRENDCARD_HEADER

#include "../../../types/TrendCardType.hpp"

class TrendCard {
protected:
    /* data */
    TrendCardType type;
public:
    TrendCard(TrendCardType type);
    ~TrendCard();
    TrendCardType getTrendCardType();
    void setTrendCardType(TrendCardType type);
};

#endif