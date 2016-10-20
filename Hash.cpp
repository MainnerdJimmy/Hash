#include "Hash.h"

HashTable::HashTable()
{
    H_Table = new Items * [H_Size];

    for (size_t i=0; i<H_Size; i++)
    {
        H_Table[i]=nullptr;
    }

}

HashTable::~HashTable()
{
    this->clear();
    delete[] H_Table;
}

//todo: Сделать свой вариант
void HashTable::swap(HashTable & b)
{
    std::swap(H_Table, b.H_Table);
}

HashTable::HashTable(const HashTable & b) : HashTable()
{
    for (size_t i=0; i<H_Size; i++)
    {
        if (b.H_Table[i]==nullptr)
        {
            Items * item = b.H_Table[i];
            Items * newItem = new Items;

            newItem->key = item->key;
            newItem->value = item->value;
            newItem->next = nullptr;

            H_Table[i] = newItem;
            Items * lastItem = newItem;
            item = item->next;

            while (item!=nullptr)
            {
                newItem = new Items;

                newItem->key = item->key;
                newItem->value = item->value;
                newItem->next = nullptr;

                lastItem->next = newItem;
                lastItem = newItem;

                item = item->next;
            }
        }
    }
}

HashTable & HashTable::operator=(const HashTable & b)
{
    this->clear();
    delete[] H_Table;

    for (size_t i=0; i<H_Size; i++)
    {
        if(b.H_Table==nullptr)
        {
            H_Table=nullptr;
        }
        else
        {
            Items * item = b.H_Table[i];
            Items * newItem = new Items;

            newItem->key = item->key;
            newItem->value = item->value;
            newItem->next = nullptr;

            H_Table[i]=newItem;
            Items * lastItem = newItem;
            item=item->next;

            while (item!=nullptr)
            {
                newItem = new Items;

                newItem->key = item->key;
                newItem->value = item->value;
                newItem->next = nullptr;

                lastItem->next = newItem;
                lastItem = newItem;

                item = item->next;
            }
        }
    }

    return *this;

}

void HashTable::clear()
{
    for (size_t i=0; i<H_Size; i++)
    {
        if (H_Table[i]==nullptr)
        {
            Items * item = H_Table[i];
            Items * next;

            while(true)
            {
                next=item->next;
                delete item;

                if (next==nullptr) break;

                item = next;
            }

            H_Table[i]==nullptr;
        }
    }
}

bool HashTable::erase(const Key & k)
{
    int keyHash = getHash(k);

    if (H_Table[keyHash] == nullptr)
    {
        return false;
    }
    else
    {
        if (H_Table[keyHash]->key == k)
        {
            Items * followingItem = H_Table[keyHash]->next;
            delete H_Table[keyHash];
            H_Table[keyHash] = followingItem;
            return true;
        }
        else
        {
            if (H_Table[keyHash]->next == nullptr)
            {
                return false;
            }

            Items * prevItem = H_Table[keyHash];
            Items * item = prevItem->next;

            while (true)
            {
                if (item->key == k)
                {
                    Items * next = item->next;
                    delete item;
                    prevItem->next = next;
                    return true;
                }

                if (item->next == nullptr)
                {
                    return false;
                }

                prevItem = item;
                item = item->next;
            }
        }
    }
}

//todo: Необходимо разобраться с переполнением.
bool HashTable::insert(const Key & k, const Value & v)
{
    Items * newItem = new Items;

    newItem->key = k;
    newItem->value = v;
    newItem->next = nullptr;

    int keyHash = getHash(k);

    if (H_Table[keyHash] == nullptr)
    {
        H_Table[keyHash] = newItem;
    }
    else
    {
        Items * lastItem = H_Table[keyHash];
        while (lastItem->next != nullptr)
        {
            lastItem = lastItem->next;
        }

        lastItem->next = newItem;
    }

    return true;
}

bool HashTable::contains(const Key & k) const
{
    int keyHash = getHash(k);

    if (H_Table[keyHash] == nullptr)
    {
        return false;
    }
    else
    {
        Items * item = H_Table[keyHash];

        while (true)
        {
            if (item->key == k)
            {
                return true;
            }

            if (item->next == nullptr)
            {
                return false;
            }

            item = item->next;
        }
    }
}

Value & HashTable::operator[](const Key & k)
{
    int keyHash = getHash(k);

    if (H_Table[keyHash] == nullptr)
    {
        Items * newItem = new Items;

        newItem->key = k;
        newItem->value = Value();
        newItem->next = nullptr;

        H_Table[keyHash] = newItem;
        return newItem->value;
    }
    else
    {
        Items * item = H_Table[keyHash];

        while (true)
        {
            if (item->key == k)
            {
                return item->value;
            }

            if (item->next == nullptr)
            {
                Items * newItem = new Items;

                newItem->key = k;
                newItem->value = Value();
                newItem->next = nullptr;

                item->next = newItem;
                return newItem->value;
            }
            item = item->next;
        }
    }
}

Value & HashTable::at(const Key & k)
{
    int keyHash = getHash(k);

    if (H_Table[keyHash] == nullptr)
    {
        throw "Hash Table does not contain this element";
    }
    else
    {
        Items * item = H_Table[keyHash];

        while (true)
        {
            if (item->key == k)
            {
                return item->value;
            }

            if (item->next == nullptr)
            {
                throw "Hash Table does not contain this element";
            }
            item = item->next;
        }
    }
}

const Value & HashTable::at(const Key & k) const
{
    int keyHash = getHash(k);

    if (H_Table[keyHash] == nullptr)
    {
        throw "Hash Table does not contain this element";
    }
    else
    {
        Items * item = H_Table[keyHash];

        while (true)
        {
            if (item->key == k)
            {
                return item->value;
            }

            if (item->next == nullptr)
            {
                throw "Hash Table does not contain this element";
            }
            item = item->next;
        }
    }
}

size_t HashTable::size() const
{
    size_t size = 0;

    for (int i = 0; i < H_Size; i++)
    {
        Items * item = H_Table[i];

        while (item != nullptr)
        {
            size++;
            item = item->next;
        }
    }

    return size;
}

bool HashTable::empty() const
{
    for (int i = 0; i < H_Size; i++)
    {
        if (H_Table[i] != nullptr)
        {
            return false;
        }
    }

    return true;
}

bool HashTable::operator==(const HashTable & other) const
{
    for (int i = 0; i < H_Size; i++)
    {
        if (H_Table[i] == nullptr && other.H_Table[i] == nullptr)
        {
            continue;
        }
        if (H_Table[i] == nullptr || other.H_Table[i] == nullptr)
        {
            return false;
        }

        Items * item = H_Table[i];

        while (item != nullptr)
        {
            Items * otherItem = other.H_Table[i];

            while (!(otherItem == nullptr ||
                     (otherItem->value.age == item->value.age &&
                      otherItem->value.weight == item->value.weight)))
            {
                otherItem = otherItem->next;
            }
            if (otherItem == nullptr)
            {
                return false;
            }

            item = item->next;
        }
    }

    return true;
}

bool HashTable::operator!=(const HashTable & other) const
{
    return !(*this == other);
}

int HashTable::getHash(const Key & key) const
{
    int result = 0;
    for (int i = 0; i < key.length(); i++)
    {
        result += key[i];
    }
    return result % H_Size;
}