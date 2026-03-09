// customer.h（客户结构体定义）
// #ifndef CUSTOMER_H
// #define CUSTOMER_H
// // 客户结构体：包含客户ID和兴趣分值（核心排序依据）
// typedef struct {
//     int id;             // 客户唯一标识
//     float interest;     // 兴趣分值（越高越优先推荐）
// } Customer;
// #endif

// array_ops.h（数组接口声明）
// #ifndef ARRAY_OPS_H
// #define ARRAY_OPS_H

// #include <stddef.h>
// #include "customer.h"

// /* 说明：所有操作以 id 为键；无序：尾插O(1摊还)/线性查找O(n)/左移删除O(n)；有序(按id升序)：二分查找O(log n)/插入与删除O(n)。 */

// /* 统计信息（可选，传NULL不统计） */
// typedef struct {
//     long long compares;   // 比较次数
//     long long moves;      // 移动次数（一次结构体拷贝计1）
// } Metrics;

// #define INTEREST_NOT_FOUND (-1.0f)

// /* ================= 无序数组 ================= */
// /* 线性查找（返回interest或INTEREST_NOT_FOUND） */
// // 参数：customers-客户数组，n-数组长度，id-目标id，m-统计指针
// float uaFindInterestById(const Customer customers[], int n, int id, Metrics *m);
// /* 尾部插入（成功返回新n，失败返回-1） */
// // 参数：customers-客户数组，n-当前元素个数，capacity-最大容量，c-新客户，m-统计指针
// int uaInsertBack(Customer customers[], int n, int capacity, Customer c, Metrics *m);
// /* 按id删除（成功返回新n，未找到返回-1） */
// // 参数：customers-客户数组，n-当前元素个数，id-目标id，m-统计指针
// int uaDeleteById(Customer customers[], int n, int id, Metrics *m);


// /* ================= 有序数组（按id升序） ================= */
// /* 二分查找（返回interest或INTEREST_NOT_FOUND） */
// // 参数：customers-有序数组，n-数组长度，id-目标id，m-统计指针
// float oaFindInterestById(const Customer customers[], int n, int id, Metrics *m);
// /* 保序插入（成功返回新n，失败返回-1） */
// // 参数：customers-有序数组，n-当前元素个数，capacity-最大容量，c-新客户，m-统计指针
// int oaInsertKeepOrder(Customer customers[], int n, int capacity, Customer c, Metrics *m);

// /* 按id删除（成功返回新n，未找到返回-1） */
// // 参数：customers-有序数组，n-当前元素个数，id-目标id，m-统计指针
// int oaDeleteById(Customer customers[], int n, int id, Metrics *m);

// #endif /* ARRAY_OPS_H */