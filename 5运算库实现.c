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
