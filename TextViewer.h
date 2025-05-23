#pragma once
#include "SupportADessin.h"
#include <iostream>
#include "PointMateriel.h"
#include "ChargeElectrique.h"
#include "Systeme.h"

/**
 * @class TextViewer
 * @brief 文本模式的显示器
 * 
 * 继承自SupportADessin，实现文本模式的显示功能
 */
class TextViewer : public SupportADessin {
private:
    std::ostream& flot;  // 输出流的引用

public:
    // 构造函数，接受一个输出流的引用
    explicit TextViewer(std::ostream& os = std::cout) : flot(os) {}
    
    // 实现各种对象的绘制方法
    void dessine(const PointMateriel& pm) override;
    void dessine(const ChargeElectrique& ce) override;
    void dessine(const Systeme& sys) override;
};