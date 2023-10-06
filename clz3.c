#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>  // 用于 malloc 函数

// 定义链表节点结构
typedef struct Node {
    uint32_t data; // 修改为32位整数
    struct Node* next;
} Node;

// 计算一个 32 位整数的前导零数量
uint16_t count_leading_zeros(uint32_t x)
{
    x |= (x >> 1);
    x |= (x >> 2);
    x |= (x >> 4);
    x |= (x >> 8);
    x |= (x >> 16);

    /* count ones (population count) */
    x -= ((x >> 1) & 0x55555555);
    x = ((x >> 2) & 0x33333333) + (x & 0x33333333);
    x = ((x >> 4) + x) & 0x0f0f0f0f;
    x += (x >> 8);
    x += (x >> 16);

    return (32 - (x & 0x1f)); // 32位整数前导零的位数
}

// 计算链表中所有节点数据的前导零数量之和
uint64_t sum_of_leading_zeros(Node* head)
{
    uint64_t sum = 0;

    while (head != NULL) {
        uint16_t leadingZeros = count_leading_zeros(head->data);
        sum += leadingZeros;
        head = head->next;
    }

    return sum;
}

int main()
{
    // 创建一个简单的链表
    Node* head = NULL;
    Node* node1 = malloc(sizeof(Node));
    node1->data = 23;
    node1->next = NULL;
    head = node1;

    Node* node2 = malloc(sizeof(Node));
    node2->data = 15;
    node2->next = NULL;
    node1->next = node2;

    Node* node3 = malloc(sizeof(Node));
    node3->data = 8;
    node3->next = NULL;
    node2->next = node3;

    // 计算链表中所有节点数据的前导零数量之和
    uint64_t totalLeadingZeros = sum_of_leading_zeros(head);
    printf("Sum of Leading Zeros: %llu\n", totalLeadingZeros);

    // 释放链表节点内存
    while (head != NULL) {
        Node* temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}
