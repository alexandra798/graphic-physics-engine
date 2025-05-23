#include "ForceCentrale.h"
#include "ObjetPhysique.h"
#include <stdexcept>

// 构造函数
ForceCentrale::ForceCentrale(std::shared_ptr<ObjetPhysique> centre)
    : centre(centre) {
    if (!centre) {
        throw std::runtime_error("中心物体不能为空");
    }
}

// 计算平方反比力矢量
Vecteur ForceCentrale::quadratique_inverse(const ObjetPhysique& objet) const {
    // 获取中心物体和目标物体的位置
    Vecteur pos_centre = centre->position();
    Vecteur pos_objet = objet.position();
    
    // 计算两物体间的位置差向量
    Vecteur diff = pos_centre - pos_objet;
    
    // 计算距离的平方
    double dist2 = diff.norme2();
    
    // 如果距离太小，返回零向量以避免数值问题
    if (dist2 < 1e-10) {
        return Vecteur(diff.memeDimension(pos_objet) ? pos_objet.memeDimension(Vecteur()) : 3);
    }
    
    // 计算单位向量（方向从目标物体指向中心物体）
    Vecteur unit_vector = diff * (1.0 / sqrt(dist2));
    
    // 计算平方反比力大小
    double magnitude = 1.0 / dist2;
    
    // 返回平方反比力向量
    return unit_vector * magnitude;
} 