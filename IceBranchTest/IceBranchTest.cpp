#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
// 定义链表节点类
class LinkNode
{
public:
    /************************************************************************/
    /* 在链表后面插入数据                                                        */
    /************************************************************************/
    void insertNode(int val)
    {
        // 创建新节点
        LinkNode* newNode = new LinkNode{ val,nullptr };

        // 找到链表的末尾
        LinkNode* pCurrent = this;
        while (pCurrent->next != nullptr)
        {
            pCurrent = pCurrent->next;
        }

        // 将新节点插入到链表末尾
        pCurrent->next = newNode;
    }
    /************************************************************************/
    /* 在某个值前面插入节点                                                    */
    /************************************************************************/
    void insertNode(int oldval, int newval)
    {
        //创建两个新的临时节点
        LinkNode* pPrve = this;
        LinkNode* pCurrent = this->next;// 找到链表的末尾

        while (pCurrent != nullptr)
        {
            if (pCurrent->num == oldval)
            {
                break;
            }
            //如果没找到对应的位置,辅助指针往后移动
            pPrve = pCurrent;
            pCurrent = pCurrent->next;
        }

        // 创建新节点
        LinkNode* newNode = new LinkNode{ newval,nullptr };

        //建立关系
        newNode->next = pCurrent;
        pPrve->next = newNode;
    }
    /************************************************************************/
    /* 在特定位置插入节点,最后一个参数不知道填啥，反正现在用不上，随便写个数吧！        */
    /************************************************************************/
    void insertNode(int val, int pos, int x)
    {
        // 创建新节点
        LinkNode* newNode = new LinkNode{ val,nullptr };

        // 找到要插入的位置
        LinkNode* pCurrent = this;
        for (int i = 0; i < pos && pCurrent->next != nullptr; i++)
        {
            pCurrent = pCurrent->next;
        }
        // 将新节点插入到链表中
        newNode->next = pCurrent->next;
        pCurrent->next = newNode;
    }
    /************************************************************************/
    /* 删除所有值为val的节点                                                    */
    /************************************************************************/
    void deleteNodeAllVal(int val)
    {
        LinkNode* pCurrent = this;
        while (pCurrent->next != nullptr)
        {
            if (pCurrent->next->num == val)
            {
                // 找到要删除的节点
                LinkNode* pDelete = pCurrent->next;
                // 更改指针指向
                pCurrent->next = pDelete->next;
                // 删除节点
                delete pDelete;
            }
            else
            {
                pCurrent = pCurrent->next;
            }
        }
    }
    /************************************************************************/
    /* 删除第一个值为val的节点                                                 */
    /************************************************************************/
    void deleteNode(int val)
    {
        LinkNode* pCurrent = this;
        while (pCurrent->next != nullptr)
        {
            if (pCurrent->next->num == val)
            {
                // 找到要删除的节点
                LinkNode* pDelete = pCurrent->next;
                // 更改指针指向
                pCurrent->next = pDelete->next;
                // 删除节点
                delete pDelete;
                break;
            }
            else
            {
                pCurrent = pCurrent->next;
            }
        }
    }
    /************************************************************************/
    /* 使其删除链表中特定位置的节点.                                            */
    /*这个函数遍历链表，找到要删除的位置。然后，它更改指针指向，将该节点从链表中删除，  */
    /*并释放该节点所占用的内存。 注意，如果给定的位置超出了链表长度，则不会进行任何操作。*/
    /************************************************************************/
    void deleteNodePos(int pos)
    {
        LinkNode* pCurrent = this;
        for (int i = 0; i < pos && pCurrent->next != nullptr; i++)
        {
            pCurrent = pCurrent->next;
        }

        if (pCurrent->next != nullptr)
        {
            // 找到要删除的节点
            LinkNode* pDelete = pCurrent->next;
            // 更改指针指向
            pCurrent->next = pDelete->next;
            // 删除节点
            delete pDelete;
        }
    }
    /************************************************************************/
    /* 搜索第一个值为 val 的节点的位置                                            */
    /************************************************************************/
    int searchNode(int val)
    {
        int pos = 0;
        LinkNode* pCurrent = this->next;
        while (pCurrent != nullptr)
        {
            if (pCurrent->num == val)
            {
                return pos;
            }
            else
            {
                pos++;
                pCurrent = pCurrent->next;
            }
        }

        // 没有找到
        return -1;
    }
    /************************************************************************/
    /* 返回链表中所有值为 val 的节点的位置,返回类型是std::vector                  */
    /************************************************************************/
    std::vector<int> searchNodeAll(int val)
    {
        std::vector<int> positions;
        int pos = 0;
        LinkNode* pCurrent = this->next;
        while (pCurrent != nullptr)
        {
            if (pCurrent->num == val)
            {
                positions.push_back(pos);
            }
            pos++;
            pCurrent = pCurrent->next;
        }

        return positions;

    }
    /************************************************************************/
    /* 清空链表的操作，不删除链表                                               */
    /************************************************************************/
    void clearLinkList()
    {
        LinkNode* pCurrent = this->next;
        while (pCurrent != nullptr)
        {
            //先保存下一个节点的位置
            LinkNode* newNode = pCurrent->next;
            //释放内存
            delete pCurrent;
            //将pCurrent指向下一个节点
            pCurrent = newNode;

        }
        this->next = nullptr;
    }
    /************************************************************************/
    /* 销毁链表                                                              */
    /************************************************************************/
    void destroyLinklist()
    {
        //先清空链表
        clearLinkList();
        delete this;
    }
public:
    int num; // 数据域
    class LinkNode* next; // 指针域，指向下一个节点
};
LinkNode* initLinkList()
{
    //创建头节点
    LinkNode* pHeader = new LinkNode;
    if (pHeader == nullptr)
    {
        return nullptr;
    }
    //初始化头节点
    pHeader->num = -1; //头节点不维护数据，这句可不写
    //记录尾结点的位置
    LinkNode* pTail = pHeader;
    pHeader->next = nullptr;
    int val = -1;
    while (1)
    {
        cin >> val;
        if (val == -1)
        {
            break;
        }
        //如何输入不是负一，插入到链表
        // 创建1个链表节点
        LinkNode* node1 = new LinkNode{ val,nullptr };

        //更改指针指向
        pTail->next = node1;
        //更新尾结点的指向
        pTail = node1;
    }
    return pHeader;
}
void foreachLinklist(LinkNode* pHeader)
{
    if (pHeader == nullptr)
    {
        return;
    }
    LinkNode* pCurrent = pHeader->next;
    while (pCurrent != nullptr)
    {
        cout << pCurrent->num << endl;
        pCurrent = pCurrent->next;
    }
}
void test01()
{
    //LinkNode* pHeader = initLinkList();
    LinkNode* pHeader = new LinkNode{ -1,nullptr };

    pHeader->insertNode(10);
    pHeader->insertNode(10);
    pHeader->insertNode(10);
    pHeader->insertNode(20);
    pHeader->insertNode(30);

    cout << "插入重载后" << endl;
    pHeader->insertNode(100, 1, 11);


    //pHeader->deleteNode(3000);
    //pHeader->deleteNodeAllVal(10);

    foreachLinklist(pHeader);

    cout << "第一个值为30的位置：" << pHeader->searchNode(30) << endl;

    cout << "返回所有值为10的节点位置：" << endl;
    std::vector<int> positions = pHeader->searchNodeAll(10);
    for (int pos : positions)
    {
        cout << pos << endl;
    }

    cout << "清空链表：" << endl;
    pHeader->clearLinkList();

    cout << "销毁链表：" << endl;
    pHeader->destroyLinklist();
    pHeader = nullptr;
    //pHeader->insertNode(10);//再操作就会报错

    //// 删除链表
    //LinkNode* pCurrent = pHeader;
    //while (pCurrent != nullptr)
    //{
    //    LinkNode* pNext = pCurrent->next;
    //    delete pCurrent;
    //    pCurrent = pNext;
    //}
}

int main()
{
    test01(); // 调用 test01 函数
}