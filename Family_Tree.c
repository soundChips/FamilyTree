#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//结构体
typedef struct CSLinklist {
    char name[50];
    char birthdate[20];
    char occupation[50];
    struct CSLinklist *firstchild, *nextsibling;
} CSLinklist, *CSTree;
//函数声明
CSTree createFamilyTree();
void displayFamilyTree(CSTree root, int level);
CSTree findMember(CSTree root, const char *name);
CSTree insertMember(CSTree root, const char *parentName, const char *newMemberName, const char *birthdate, const char *occupation);
CSTree modifyMember(CSTree root, const char *oldName, const char *newName, const char *birthdate, const char *occupation);
void printMenu() {
    printf("\n家谱树管理系统\n");
    printf("1. 显示家谱树\n");
    printf("2. 查找成员\n");
    printf("3. 添加成员\n");
    printf("4. 修改成员信息\n");
    printf("0. 退出\n");
    printf("请选择操作: ");
}
//主函数
int main() {
    CSTree familyTree = createFamilyTree();
    int choice;
//do-while至少执行一次
    do {
        printMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("家谱树：\n");
                displayFamilyTree(familyTree, 0);
                break;
            case 2:
                printf("请输入要查找的成员姓名: ");
                char searchName[50];
                scanf("%s", searchName);
                CSTree foundMember = findMember(familyTree, searchName);
                if (foundMember != NULL) {
                    printf("\n%s 在家谱中找到。\n", searchName);
                } else {
                    printf("\n%s 在家谱中未找到。\n", searchName);
                }
                break;
            case 3:
                printf("请输入父亲姓名: ");
                char parentName[50], newMemberName[50], birthdate[20], occupation[50];
                scanf("%s", parentName);
                printf("请输入新成员姓名: ");
                scanf("%s", newMemberName);
                printf("请输入新成员出生日期: ");
                scanf("%s", birthdate);
                printf("请输入新成员职业: ");
                scanf("%s", occupation);
                familyTree = insertMember(familyTree, parentName, newMemberName, birthdate, occupation);
                break;
            case 4:
                printf("请输入要修改的成员姓名: ");
                char oldName[50], newName[50], newBirthdate[20], newOccupation[50];
                scanf("%s", oldName);
                printf("请输入新的姓名: ");
                scanf("%s", newName);
                printf("请输入新的出生日期: ");
                scanf("%s", newBirthdate);
                printf("请输入新的职业: ");
                scanf("%s", newOccupation);
                familyTree = modifyMember(familyTree, oldName, newName, newBirthdate, newOccupation);
                break;
            case 0:
                printf("程序已退出。\n");
                break;
            default:
                printf("无效的选择，请重新输入。\n");
        }
    } while (choice != 0);        //输入非0且不可用重新开始循环

    return 0;
}
//创建初始家谱图
CSTree createFamilyTree() {
    CSTree root = (CSTree)malloc(sizeof(CSLinklist));
    strcpy(root->name, "Adam");
    strcpy(root->birthdate, "1950-01-01");
    strcpy(root->occupation, "Founder");
    root->firstchild = root->nextsibling = NULL;

    CSTree child1 = (CSTree)malloc(sizeof(CSLinklist));
    strcpy(child1->name, "David");
    strcpy(child1->birthdate, "1975-03-12");
    strcpy(child1->occupation, "Engineer");
    child1->firstchild = child1->nextsibling = NULL;

    CSTree child2 = (CSTree)malloc(sizeof(CSLinklist));
    strcpy(child2->name, "John");
    strcpy(child2->birthdate, "1980-07-25");
    strcpy(child2->occupation, "Teacher");
    child2->firstchild = child2->nextsibling = NULL;

    CSTree child3 = (CSTree)malloc(sizeof(CSLinklist));
    strcpy(child3->name, "Eve");
    strcpy(child3->birthdate, "1978-11-30");
    strcpy(child3->occupation, "Artist");
    child3->firstchild = child3->nextsibling = NULL;

    CSTree grandChild1 = (CSTree)malloc(sizeof(CSLinklist));
    strcpy(grandChild1->name, "Alice");
    strcpy(grandChild1->birthdate, "1995-02-10");
    strcpy(grandChild1->occupation, "Student");
    grandChild1->firstchild = grandChild1->nextsibling = NULL;

//根据孩子兄弟表示法构造
    root->firstchild = child1;        //这里rootnextsibling并不需要设定值
    child1->nextsibling = child2;
    child2->firstchild = grandChild1;
    child2->nextsibling = child3;

    return root;
}
//打印家谱图
//因为没学过前端所以ui用的是终端
void displayFamilyTree(CSTree root, int level){
    if (root == NULL) return ;
    
    // 使用两个空格表示每一级的缩进
    for(int i = 0; i < level * 2; i++){
        printf(" ");
    }

    // 打印节点信息
    printf("|-- %s (%s, %s)\n", root->name, root->birthdate, root->occupation);

    // 递归显示子节点和兄弟节点
    if(root->firstchild != NULL || root->nextsibling != NULL){
        displayFamilyTree(root->firstchild, level + 1);
        if(root->nextsibling != NULL){
            displayFamilyTree(root->nextsibling, level);
        }
    }
}
//核心内容
//先序遍历
CSTree findMember(CSTree root, const char *name) {
    if (root == NULL) return NULL;
    
    if (strcmp(root->name, name) == 0) {
        return root;
    }

    CSTree foundInChildren = findMember(root->firstchild, name);//递归，指针移动到左孩子
    if (foundInChildren != NULL) {
        return foundInChildren;
    }

    return findMember(root->nextsibling, name);      //root->nextsibling指向root兄弟节点
}
//加入新成员
CSTree insertMember(CSTree root, const char *parentName, const char *newMemberName, const char *birthdate, const char *occupation) {
    if (root == NULL) return NULL;
    //先找到新成员的父亲节点
    CSTree parent = findMember(root, parentName);
    if (parent != NULL) {
        //为新成员分配空间
        CSTree newMember = (CSTree)malloc(sizeof(CSLinklist));
        strcpy(newMember->name, newMemberName);
        strcpy(newMember->birthdate, birthdate);
        strcpy(newMember->occupation, occupation);
        newMember->firstchild = newMember->nextsibling = NULL;
        //如果父亲节点的左孩子为空，就把新成员分配给左孩子
        if (parent->firstchild == NULL) {
            parent->firstchild = newMember;
        } 
        else {
            CSTree sibling = parent->firstchild;
            //如果左孩子的nextsibling不为空，说明有兄弟存在，这时指针要移动到兄弟节点，一直循环到parent最后一个孩子
            while (sibling->nextsibling != NULL) {
                sibling = sibling->nextsibling;
            }
            //此时把sibling的nextsibling指针指向newMember
            sibling->nextsibling = newMember;
        }
    }

    return root;
}
//修改成员
CSTree modifyMember(CSTree root, const char *oldName, const char *newName, const char *birthdate, const char *occupation) {
    if (root == NULL) return NULL;
    //创建一个指针指向需要修改的节点
    CSTree toModify = findMember(root, oldName);
    if (toModify != NULL) {
        strcpy(toModify->name, newName);
        strcpy(toModify->birthdate, birthdate);
        strcpy(toModify->occupation, occupation);
    }

    return root;
}
