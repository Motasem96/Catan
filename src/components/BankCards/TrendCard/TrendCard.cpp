#include "../../../types/TrendCardType.hpp"
#include "../../../components/BankCards/TrendCard/TrendCard.hpp"

TrendCard::TrendCard(TrendCardType type) {
    this->type = type;
}

TrendCard::~TrendCard() {}

TrendCardType TrendCard::getTrendCardType() {
    return this->type;
}

void TrendCard::setTrendCardType(TrendCardType type){
    this->type = type;
}