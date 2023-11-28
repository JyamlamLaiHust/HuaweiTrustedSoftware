#include "PriceCalculator.h"
#include "Discount.h"
#include <memory>


namespace PriceCalc
{
PriceCalculator* PriceCalculator::instance = nullptr;

double PriceCalculator::AcceptCash(const DiscountType discountType, const double money) noexcept
{
    // static std::unordered_map <DiscountType, std::unique_ptr<Discount>> discountMap;
    // std::unordered_map <DiscountType, std::function<double(const double)>> discountMap;
    // if (discountMap.empty())
    // {
    //     discountMap.emplace(DiscountType::CASH_NORMAL, std::make_unique<Normal>());
    //     discountMap.emplace(DiscountType::CASH_PERCENTOFF_10, std::make_unique<CASH_PERCENT_OFF>(0.9));
    //     discountMap.emplace(DiscountType::CASH_PERCENTOFF_20, std::make_unique<CASH_PERCENT_OFF>(0.8));
    //     discountMap.emplace(DiscountType::CASH_PERCENTOFF_30, std::make_unique<CASH_PERCENT_OFF>(0.7));
    //     discountMap.emplace(DiscountType::CASH_BACK, std::make_unique<CashBack>());
    // }


    if (discountMap.empty()) {
        discountMap.emplace(DiscountType::CASH_NORMAL, [](double money) noexcept { return money; });
        discountMap.emplace(DiscountType::CASH_PERCENTOFF_10, [](const double money) noexcept { return money * 0.9; });
        discountMap.emplace(DiscountType::CASH_PERCENTOFF_20, [](const double money) noexcept { return money * 0.8; });
        discountMap.emplace(DiscountType::CASH_PERCENTOFF_30, [](const double money) noexcept { return money * 0.7; });
        discountMap.emplace(DiscountType::CASH_BACK, [](const double money) noexcept {
            const double threshold = 100.0;
            const double cashback = 20.0;
            return money - std::floor(money / threshold) * cashback;
        });
    }

    return discountMap[discountType](money);

    // return discountMap.find(discountType)->second->AcceptCash(money);
}  // namespace PriceCalc
};