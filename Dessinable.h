#pragma once
#include <iostream>
#include <stdexcept>
// 前向声明
class SupportADessin;
//其实不应该前向声明而应该用include


class Dessinable {
public:
    // 构造函数
    Dessinable() = default;
    
    // 析构函数
    virtual ~Dessinable() = default;
    
    // 纯虚函数，在派生类中实现
    virtual void dessine_sur(SupportADessin& support) = 0;
    

};