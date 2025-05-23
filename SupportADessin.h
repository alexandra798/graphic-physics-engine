#pragma once
#include <iostream>

// 前向声明
class PointMateriel;
class Systeme;
class Bloc;
class Moucheron;
class Dervish;
class ChargeElectrique;

class SupportADessin {
public:
    // 构造函数和析构函数
    SupportADessin() = default;
    virtual ~SupportADessin() = default;
    
    // 用于绘制不同类型对象的纯虚函数
    virtual void dessine(const PointMateriel&) = 0;
    virtual void dessine(const Systeme&) = 0;
    virtual void dessine(const Bloc&) = 0;
    virtual void dessine(const Moucheron&) = 0;
    virtual void dessine(const Dervish&) = 0;
    virtual void dessine(const ChargeElectrique&) = 0;
    
private:
    // 禁止拷贝
    SupportADessin(SupportADessin const&) = delete;
    SupportADessin& operator=(SupportADessin const&) = delete;
};