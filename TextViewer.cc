#include "TextViewer.h"
#include "PointMateriel.h"
#include "Systeme.h"
#include "ChargeElectrique.h"


// 绘制PointMateriel对象
void TextViewer::dessine(const PointMateriel& point) {
    sortie << point;
}

// 绘制Systeme对象
void TextViewer::dessine(const Systeme& systeme) {
    sortie << systeme;
}



// 绘制ChargeElectrique对象
void TextViewer::dessine(const ChargeElectrique& charge) {
    sortie << "Charge Electrique: " << charge << std::endl;
}