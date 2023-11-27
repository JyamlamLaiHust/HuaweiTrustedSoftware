#include "PriceCalculator.h"
#include "Discount.h"
#include <memory>
#include <cmath>
#include <unordered_map>

namespace PriceCalc
{
PriceCalculator* PriceCalculator::instance = nullptr;

double PriceCalculator::AcceptCash(const DiscountType discountType, const double money) const noexcept
{
    std::unordered_map <DiscountType, std::unique_ptr<Discount>> discountMap;
    // std::unordered_map <DiscountType, std::function<double(const double)>> discountMap;
    discountMap.emplace(DiscountType::CASH_NORMAL, std::make_unique<Normal>());
    // 
    discountMap.emplace(DiscountType::CASH_PERCENTOFF_10, std::make_unique<CASH_PERCENT_OFF>(0.9));
    discountMap.emplace(DiscountType::CASH_PERCENTOFF_20, std::make_unique<CASH_PERCENT_OFF>(0.8));
    discountMap.emplace(DiscountType::CASH_PERCENTOFF_30, std::make_unique<CASH_PERCENT_OFF>(0.7));
    discountMap.emplace(DiscountType::CASH_BACK, std::make_unique<CashBack>());

    return discountMap.find(discountType)->second->AcceptCash(money);
}  // namespace PriceCalc
};