#include <stdio.h>
#include <stdint.h>

// 函数声明
uint32_t endian_swap(uint32_t value);
void print_bytes(uint32_t value);
int is_little_endian(void);

int main() {
    uint32_t num = 0x12253647;
    
    // 检测本机字节序
    if (is_little_endian()) {
        printf("本机为小端模式\n");
    } else {
        printf("本机为大端模式\n");
    }
    
    // 打印原始数字
    printf("\n原始数字: 0x%08X\n", num);
    printf("本机字节序下的字节表示: ");
    print_bytes(num);
    
    // 转换字节序
    uint32_t swapped_num = endian_swap(num);
    
    // 打印不同模式下的表示
    printf("\n小端模式下的字节表示: ");
    if (is_little_endian()) {
        print_bytes(num);  // 本机就是小端，直接打印
    } else {
        print_bytes(swapped_num);  // 大端机需要转换
    }
    
    printf("大端模式下的字节表示: ");
    if (!is_little_endian()) {
        print_bytes(num);  // 本机就是大端，直接打印
    } else {
        print_bytes(swapped_num);  // 小端机需要转换
    }
    
    return 0;
}

/**
 * 大小端转换函数
 * 将32位整数的字节序进行反转
 */
uint32_t endian_swap(uint32_t value) {
    return ((value & 0x000000FF) << 24) |  // 低字节移到高字节
           ((value & 0x0000FF00) << 8)  |  // 次低字节移到次高字节
           ((value & 0x00FF0000) >> 8)  |  // 次高字节移到次低字节
           ((value & 0xFF000000) >> 24);   // 高字节移到低字节
}

/**
 * 以十六进制形式打印32位整数的四个字节
 */
void print_bytes(uint32_t value) {
    uint8_t *bytes = (uint8_t *)&value;
    printf("0x%02X 0x%02X 0x%02X 0x%02X\n", 
           bytes[0], bytes[1], bytes[2], bytes[3]);
}

/**
 * 检测本机是否为小端模式
 * 返回1表示小端，0表示大端
 */
int is_little_endian(void) {
    uint32_t test = 0x00000001;
    uint8_t *byte = (uint8_t *)&test;
    return (*byte == 1);  // 小端模式下第一个字节是0x01
}
