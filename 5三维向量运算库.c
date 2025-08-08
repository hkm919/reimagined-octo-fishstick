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
