#pragma once

// 前向声明
class SupportADessin;

/**
 * @class Dessinable
 * @brief 抽象类，表示可以被"绘制"（显示）的对象
 * 
 * 所有需要在系统中被观察或显示的对象都应该继承这个类
 */
class Dessinable {
public:
    // 虚析构函数
    virtual ~Dessinable() = default;
    
    // 纯虚函数，必须在每个子类中实现
    // 注意：根据作业要求，这个方法必须在每个子类中重新定义，
    // 而不是在基类中定义然后被继承
    virtual void dessine_sur(SupportADessin& support) = 0;
};