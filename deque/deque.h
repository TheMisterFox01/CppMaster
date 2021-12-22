#pragma once
#include "MemoryHeapStrategy.h"
#include <string>
#include <exception>

template <class ValueType, class MemoryStrategyType = MemoryHeapStrategy >
class Deque
{
private:

    struct DequeElement
    {
        ValueType value;
        DequeElement* next;
        DequeElement* prev;
    };

    DequeElement* head;
    DequeElement* tail;

    MemoryStrategyType alloc;

public:

    class DequeIterator
    {
    public:

        DequeIterator() : CurrentNode(Head)
        {
        }

        DequeIterator(DequeElement* Node) : CurrentNode(Node)
        {
        }

        DequeIterator& operator=(DequeElement* Node)
        {
            this->CurrentNode = Node;
            return *this;
        }

        DequeIterator& operator++()
        {
            if (CurrentNode)
                CurrentNode = CurrentNode->Next;
            return *this;
        }

        DequeIterator operator ++(int)
        {
            DequeIterator iterator = *this;
            ++* this;
            return iterator;
        }

        bool operator !=(const DequeIterator& iterator)
        {
            return CurrentNode != iterator.CurrentNode;
        }

        ValueType& operator *()
        {
            return CurrentNode->Value;
        }
    private:
        DequeElement* CurrentNode;
    };


    class ConstDequeIterator
    {
    public:

        ConstDequeIterator() : CurrentNode(Head)
        {
        }

        ConstDequeIterator(const DequeElement* Node) : CurrentNode(Node)
        {
        }

        ConstDequeIterator& operator=(DequeElement* Node)
        {
            this->CurrentNode = Node;
            return *this;
        }

        ConstDequeIterator& operator ++()
        {
            if (CurrentNode)
                CurrentNode = CurrentNode->Next;
            return *this;
        }

        ConstDequeIterator operator ++(int)
        {
            ConstDequeIterator iterator = *this;
            ++* this;
            return iterator;
        }

        bool operator !=(const ConstDequeIterator& iterator)
        {
            return CurrentNode != iterator.CurrentNode;
        }

        const ValueType& operator*()
        {
            return CurrentNode->Value;
        }
    private:
        const DequeElement* CurrentNode;
    };

    DequeIterator begin()
    {
        return DequeIterator(Head);
    }

    DequeIterator end()
    {
        return DequeIterator(nullptr);
    }

    ConstDequeIterator begin() const
    {
        return ConstDequeIterator(Head);
    }

    ConstDequeIterator end() const
    {
        return ConstDequeIterator(nullptr);
    }


    Deque() : Head(nullptr), Tail(nullptr)
    {
    }


    Deque(std::initializer_list < ValueType > List) : Head(nullptr), Tail(nullptr)
    {
        for (auto& i : List)
            PushTail(i);
    }

    Deque(Deque const& Other) : Head(nullptr), Tail(nullptr)
    {
        for (auto& i : Other)
            PushTail(i);
    }

    Deque(Deque&& Other) : Head(nullptr), Tail(nullptr)
    {
        this->Head = Other.Head;
        this->Tail = Other.Tail;
        Other.Head = nullptr;
        Other.Tail = nullptr;
    }

    Deque& operator=(Deque const& Other)
    {
        for (auto& i : Other)
            PushTail(*i);
        return *this;
    }

    Deque& operator=(Deque&& Other)
    {
        Clear();
        this->Head = Other.Head;
        this->Tail = Other.Tail;
        Other.Head = nullptr;
        Other.Tail = nullptr;
        return *this;
    }

   ~Deque()
    {
        Clear();
    }

    ValueType const& PeekHead(void) const
    {
        return Head->Value;
    }

    ValueType const& PeekTail(void) const
    {
        return Tail->Value;
    }

    ValueType& GetHead(void)
    {
        return Head->Value;
    }

 ValueType& GetTail(void)
    {
        return Tail->Value;
    }

    void PushHead(ValueType const& Element)
    {
        DequeElement* tmp = (DequeElement*)Allocator.alloc(sizeof(DequeElement));
        tmp->Value = Element;
        tmp->Next = Head;
        tmp->Prev = nullptr;

        if (Head != nullptr)
            Head->Prev = tmp;

        Head = tmp;

        if (Tail == nullptr)
            Tail = Head;
    }

    void PushTail(ValueType const& Element)
    {
        DequeElement* tmp = (DequeElement*)Allocator.alloc(sizeof(DequeElement));
        tmp->Value = Element;
        tmp->Next = nullptr;
        tmp->Prev = Tail;

        if (Tail != nullptr)
            Tail->Next = tmp;

        Tail = tmp;

        if (Head == nullptr)
            Head = Tail;
    }

    void PushHead(ValueType&& Element)
    {
        DequeElement* tmp = (DequeElement*)Allocator.alloc(sizeof(DequeElement));
        tmp->Value = std::move(Element);
        tmp->Next = Head;
        tmp->Prev = nullptr;

        if (Head != nullptr)
            Head->Prev = tmp;

        Head = tmp;

        if (Tail == nullptr)
            Tail = Head;
    }

    void PushTail(ValueType&& Element)
    {
        DequeElement* tmp = (DequeElement*)Allocator.alloc(sizeof(DequeElement));
        tmp->Value = std::move(Element);
        tmp->Next = nullptr;
        tmp->Prev = Tail;

        if (Tail != nullptr)
            Tail->Next = tmp;

        Tail = tmp;

        if (Head == nullptr)
            Head = Tail;
    }

    void PopHead(void)
    {

        DequeElement* tmp = Head;
        Head = Head->Next;
        Allocator.dealloc((byte*)tmp);

        if (Head == nullptr)
            Tail = nullptr;
        else
            Head->Prev = nullptr;
    }

    void PopTail(void)
    {

        DequeElement* tmp = Tail;
        Tail = Tail->Prev;
        Allocator.dealloc((byte*)tmp);

        if (Tail == nullptr)
            Head = nullptr;
        else
            Tail->Next = nullptr;
    }

    Deque& Concatinate(Deque&& Other)
    {
        if (Tail == nullptr)
        {
            this->Head = Other.Head;
            this->Tail = Other.Tail;
            Other.Head = nullptr;
            Other.Tail = nullptr;
        }
        else
        {
            this->Tail->Next = Other.Head;
            Other.Head->Prev = this->Tail;

            this->Tail = Other.Tail;

            Other.Head = nullptr;
            Other.Tail = nullptr;
        }
        return *this;
    }

    Deque& Concatinate(const Deque& Other)
    {
        for (auto& i : Other)
            PushTail(i);
        return *this;
    }

    void Clear(void)
    {
        if (Head == nullptr)
            return;

        while (Head != nullptr)
            PopHead();
    }

    bool IsEmpty(void)
    {
        return Head == nullptr;
    }
};
