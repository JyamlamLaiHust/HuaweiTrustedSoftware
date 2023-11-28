#pragma once
#include "PriceCalculator.h"

namespace PriceCalc
{
using DiscountFunction = std::function<double(double)>;

class PriceCalculator final
{
public:
    double AcceptCash(const DiscountType discountType, const double money) noexcept;
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
    
    std::unordered_map<DiscountType, DiscountFunction> discountMap;
};
};  // namespace PriceCalc
