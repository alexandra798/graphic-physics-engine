#pragma once
#include "SupportADessin.h"
#include <iostream>

//只有dessine这一个方法

class TextViewer : public SupportADessin {
private:
    std::ostream& sortie;  // 引用到输出流
    
public:

    // 构造函数
    TextViewer(std::ostream& out = std::cout) : sortie(out) {}
    
    // 析构函数
    virtual ~TextViewer() = default;
    
    // 实现绘制方法
    virtual void dessine(const PointMateriel& point) override;
    virtual void dessine(const Systeme& systeme) override;
    virtual void dessine(const ChargeElectrique& charge) override;
};