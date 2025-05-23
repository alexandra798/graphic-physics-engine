#pragma once

// 前向声明
class PointMateriel;
class ChargeElectrique;
class Systeme;

/**
 * @class SupportADessin
 * @brief 抽象类，表示绘制的支持方式（文本、图形等）
 * 
 * 不同的显示方式（文本模式、图形模式等）都继承自这个类
 */
class SupportADessin {
public:
    // 虚析构函数
    virtual ~SupportADessin() = default;
    
    // 删除拷贝和移动操作（根据作业要求）
    SupportADessin(const SupportADessin&) = delete;
    SupportADessin& operator=(const SupportADessin&) = delete;
    SupportADessin(SupportADessin&&) = delete;
    SupportADessin& operator=(SupportADessin&&) = delete;
    
    // 默认构造函数
    SupportADessin() = default;
    
    // 纯虚函数，为每种可绘制对象提供绘制方法
    virtual void dessine(const PointMateriel&) = 0;
    virtual void dessine(const ChargeElectrique&) = 0;
    virtual void dessine(const Systeme&) = 0;
    // 可以根据需要添加更多类型的绘制方法
};