#include <stdio.h>
#include <string.h>
#include <math.h>
#include <haizei/test.h>
#include <haizei/linklist.h>
#include <stdlib.h>

// int func_cnt = 0;
// Function func_arr[100];
Function func_head, *func_tail = &func_head; // 虚拟头节点，尾指针
struct FunctionInfo haizei_test_info; // 计算成功率

// GREEN RED 宏在test.h中实现
int RUN_ALL_TESTS() {
    // for (int i = 0; i < func_cnt; i++) {
    for (struct LinkNode *p = func_head.p.next; p; p = p->next) {
        Function *func = Head(p, Function, p);
        printf(GREEN("[====RUN====] ") RED_HL("%s\n"), func->str);
        haizei_test_info.total = 0, haizei_test_info.success = 0;
        func->func();
        double rate = 1.0 * haizei_test_info.success / haizei_test_info.total; // *100.0 可能溢出
        rate *= 100.0;
        printf(PURPLE("[  "));
        if (fabs(rate - 100.0) < 1e-6) {
            printf(BLUE_HL("%6.2lf%%"), rate); // 算上%占6位
        } else {
            printf(RED_HL("%6.2lf%%"), rate);
        }
        printf(PURPLE("  ]") " total : %d    success : %d\n",
            haizei_test_info.total,
            haizei_test_info.success
        );
    }
    return 0;
}

void add_function(TestFuncT func, const char *str) {
    // func_arr[func_cnt].func = func;
    // func_arr[func_cnt].str = strdup(str);
    // func_cnt++;
    Function *temp = (Function *)calloc(1, sizeof(Function));
    temp->func = func;
    temp->str = strdup(str);
    func_tail->p.next = &(temp->p);
    func_tail = temp;
    return ;
}
