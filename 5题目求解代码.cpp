#ifndef VECTOR3F_H
#define VECTOR3F_H

// 三维向量结构体定义
typedef struct {
    float x;
    float y;
    float z;
} vector3f;

// 向量加法：v3 = v1 + v2
vector3f vector3f_add(const vector3f v1, const vector3f v2);

// 向量减法：v3 = v1 - v2
vector3f vector3f_sub(const vector3f v1, const vector3f v2);

// 点乘运算：返回 v1 · v2 = x1*x2 + y1*y2 + z1*z2
float vector3f_dot(const vector3f v1, const vector3f v2);

// 叉乘运算：返回 v1 × v2 = (y1*z2 - z1*y2, z1*x2 - x1*z2, x1*y2 - y1*x2)
vector3f vector3f_cross(const vector3f v1, const vector3f v2);

// 求向量模长：返回 |v| = √(x² + y² + z²)
float vector3f_magnitude(const vector3f v);

// 单位化向量：返回 v 的单位向量（模长为1），若模长为0则返回零向量
vector3f vector3f_normalize(const vector3f v);

// 向量数乘：v = scalar * v
vector3f vector3f_scale(const vector3f v, float scalar);

// 打印向量内容（调试用）
void vector3f_print(const vector3f v);

#endif // VECTOR3F_H

#include "vector3f.h"
#include <math.h>
#include <stdio.h>

// 向量加法
vector3f vector3f_add(const vector3f v1, const vector3f v2) {
    return (vector3f){v1.x + v2.x, v1.y + v2.y, v1.z + v2.z};
}

// 向量减法
vector3f vector3f_sub(const vector3f v1, const vector3f v2) {
    return (vector3f){v1.x - v2.x, v1.y - v2.y, v1.z - v2.z};
}

// 点乘运算
float vector3f_dot(const vector3f v1, const vector3f v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

// 叉乘运算
vector3f vector3f_cross(const vector3f v1, const vector3f v2) {
    return (vector3f){
        v1.y * v2.z - v1.z * v2.y,
        v1.z * v2.x - v1.x * v2.z,
        v1.x * v2.y - v1.y * v2.x
    };
}

// 求模长
float vector3f_magnitude(const vector3f v) {
    return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}

// 单位化向量
vector3f vector3f_normalize(const vector3f v) {
    float mag = vector3f_magnitude(v);
    if (mag == 0) { // 避免除以0
        return (vector3f){0, 0, 0};
    }
    return (vector3f){v.x / mag, v.y / mag, v.z / mag};
}

// 向量数乘
vector3f vector3f_scale(const vector3f v, float scalar) {
    return (vector3f){v.x * scalar, v.y * scalar, v.z * scalar};
}

// 打印向量
void vector3f_print(const vector3f v) {
    printf("(%.2f, %.2f, %.2f)\n", v.x, v.y, v.z);
}

#include "vector3f.h"
#include <math.h>
#include <stdio.h>

// 计算点到直线的距离：
// 公式：|(P2 - P1) × (P0 - P1)| / |P2 - P1|
// P0: 点坐标, P1/P2: 直线上两点
float point_to_line_distance(
    const vector3f P0, 
    const vector3f P1, 
    const vector3f P2
) {
    vector3f P1P2 = vector3f_sub(P2, P1); // P2 - P1
    vector3f P1P0 = vector3f_sub(P0, P1); // P0 - P1
    vector3f cross = vector3f_cross(P1P2, P1P0); // 叉乘
    return vector3f_magnitude(cross) / vector3f_magnitude(P1P2);
}

// 计算直线到平面的距离（直线平行于平面时，取直线上一点到平面的距离）
// 平面方程：Ax + By + Cz + D = 0，可由平面内三点求法向量
// 步骤：
// 1. 求平面法向量 n = (A,B,C)
// 2. 若直线方向向量与法向量点乘为0（直线平行平面），则计算直线上一点到平面的距离
float line_to_plane_distance(
    const vector3f line_dir,    // 直线方向向量
    const vector3f plane_point, // 平面内一点
    const vector3f plane_norm,  // 平面法向量（单位化）
    const vector3f line_point   // 直线上一点
) {
    // 检查直线是否平行平面：方向向量 · 法向量 == 0
    float dot = vector3f_dot(line_dir, plane_norm);
    if (fabs(dot) > 1e-6) { // 不平行则距离为0（直线与平面相交）
        return 0;
    }
    // 计算直线上一点到平面的距离：|(line_point - plane_point) · plane_norm|
    vector3f diff = vector3f_sub(line_point, plane_point);
    return fabs(vector3f_dot(diff, plane_norm));
}

int main() {
    // 正方体顶点坐标（棱长为1，设 A(0,0,0), B(1,0,0), C(1,1,0), D(0,1,0)
    // A1(0,0,1), B1(1,0,1), C1(1,1,1), D1(0,1,1)
    vector3f A  = {0, 0, 0};
    vector3f B  = {1, 0, 0};
    vector3f C  = {1, 1, 0};
    vector3f A1 = {0, 0, 1};
    vector3f C1 = {1, 1, 1};
    vector3f E  = {0.5, 0, 1}; // E是A1B1中点（A1(0,0,1), B1(1,0,1)）
    vector3f F  = {0.5, 0, 0}; // F是AB中点（A(0,0,0), B(1,0,0)）

    // -------------------------
    // (1) 点B到直线AC1的距离
    // 直线AC1：A(0,0,0) → C1(1,1,1)
    vector3f P0 = B;   // 点B
    vector3f P1 = A;   // 直线上点A
    vector3f P2 = C1;  // 直线上点C1
    float dist1 = point_to_line_distance(P0, P1, P2);
    printf("(1) 点B到直线AC1的距离：%.4f\n", dist1);

    // -------------------------
    // (2) 直线FC到平面AEC1的距离
    // 步骤1：求平面AEC1的法向量
    vector3f AE = vector3f_sub(E, A);   // A→E: (0.5,0,1)-(0,0,0) = (0.5,0,1)
    vector3f AC1 = vector3f_sub(C1, A); // A→C1: (1,1,1)-(0,0,0) = (1,1,1)
    vector3f plane_norm = vector3f_cross(AE, AC1); // 平面法向量
    plane_norm = vector3f_normalize(plane_norm);   // 单位化

    // 步骤2：直线FC的方向向量
    vector3f F_point = F;    // 直线上点F
    vector3f C_point = C;    // 直线上点C
    vector3f line_dir = vector3f_sub(C_point, F_point); // FC方向向量

    // 步骤3：平面AEC1内一点（如A）
    vector3f plane_point = A;

    // 步骤4：直线上一点（如F）到平面的距离（直线平行平面时有效）
    float dist2 = line_to_plane_distance(
        line_dir,    // 直线方向向量
        plane_point, // 平面内点A
        plane_norm,  // 平面单位法向量
        F_point      // 直线上点F
    );
    printf("(2) 直线FC到平面AEC1的距离：%.4f\n", dist2);

    return 0;
}