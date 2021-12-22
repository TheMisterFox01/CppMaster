#include <iostream>
#include "deque.h"

template <class ValueType>
void printDeque(Deque < ValueType > d)
{
    for (auto& i : d)
        std::cout << i << " ";

    std::cout << std::endl;
}

int main()
{

    Deque<int> deque1;
    printDeque(deque1);

    Deque<int> deque2({ 1, 2, 3, 4, 5 });
    printDeque(deque2);

    Deque<int> deque3(deque2);
    printDeque(deque3);

    Deque<int> deque4(Deque<int>({ 1, 2, 3, 4, 5 }));
    printDeque(deque4);

    Deque<int> deque5 = deque2;
    printDeque(deque5);

    Deque<int> deque6 = Deque<int>({ 1, 2, 3, 4, 5 });
    printDeque(deque6);

    std::cout << deque2.PeekHead() << std::endl;

    std::cout << deque6.PeekTail() << std::endl;

    deque3.PushHead(30);
    printDeque(deque3);

    deque4.PushTail(47);
    printDeque(deque4);

    int a = 30;
    deque3.PushHead(a);
    printDeque(deque3);

    deque4.PushTail(a);
    printDeque(deque4);

    deque2.PopHead();
    printDeque(deque2);

    deque5.PopTail();
    printDeque(deque5);

    printDeque(Deque<int>({ 1, 2, 3, 4, 5 }).Concatinate({ 6, 7, 8, 9, 10 }));

    printDeque(Deque<int>({ 1, 2, 3, 4, 5 }).Concatinate(deque2));

    std::cout << deque2.IsEmpty() << std::endl;
    deque2.Clear();
    std::cout << deque2.IsEmpty() << std::endl;
    return 0;
}
