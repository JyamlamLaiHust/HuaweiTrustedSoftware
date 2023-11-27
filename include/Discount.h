#pragma once
#include <cmath>

namespace PriceCalc
{
class PriceCalculator final
{
public:
    double AcceptCash(const DiscountType discountType, const double money) const noexcept;
    static PriceCalculator* getInstance()
    {
        if(instance == nullptr)
        {
            instance = new PriceCalculator();
        }
        return instance;
    }
private:
    // 静态成员变量，存储单例实例
    static PriceCalculator* instance;
    
    // 将构造函数和析构函数设为私有，防止外部创建和销毁对象
    PriceCalculator(){}
    ~PriceCalculator(){}
    
    class Discount
    {
    public:
        virtual ~Discount() = default;
        virtual double AcceptCash(const double money) const noexcept = 0;
    };

    class Normal final : public Discount 
    {
    public:
        double AcceptCash(const double money) const noexcept
        {
            return money;
        }

        // std::function<double(const double)> acceptCash = [](const double money) noexcept{ return money;};
    };

    class CASH_PERCENT_OFF final :public Discount
    {
    public:
        explicit CASH_PERCENT_OFF(const double rate) : rate(rate)
        {

        }

        double AcceptCash(const double money) const noexcept override
        {
            return money * rate;
           //  std::function<double(const double)> acceptCash = [this](const double money) noexcept{ return money;};
        }

    private:
        const double rate;
    };

    class CashBack final :public Discount 
    {
    public:
        double AcceptCash(const double money) const noexcept override
        {
            const double threshold = 100.0;
            const double cashback = 20.0;
            return money - std::floor(money / threshold) * cashback;
        }

        // std::function<double(const double)> acceptCash = [](const double money) noexcept{ return return money - std::floor(money / threshold) * cashback;};
    };
};
};  // namespace PriceCalc
