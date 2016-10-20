#ifndef HASHTABLE_HASH_H
#define HASHTABLE_HASH_H

#include <malloc.h>
#include <assert.h>
#include <utility>
#include <string>

typedef std::string Key;

struct Value {
    unsigned age;
    unsigned weight;
};

struct Items {
    Key key;
    Value value;
    Items * next;
};

class HashTable
{
private:
    Items ** H_Table;
    const int H_Size = 512;
    //Мы же вычислять его должны уметь, в конце-концов
    int getHash(const Key & key) const;
public:
    HashTable();

    ~HashTable();

    //Конструктор копирования
    HashTable(const HashTable& b);


    // Обменивает значения двух хэш-таблиц.
    // Подумайте, зачем нужен этот метод, при наличии стандартной функции
    // std::swap. - - - Не нужен.
    void swap(HashTable& b);

    HashTable& operator=(const HashTable& b);


    // Очищает контейнер.
    void clear();
    // Удаляет элемент по заданному ключу.
    bool erase(const Key& k);
    // Вставка в контейнер. Возвращаемое значение - успешность вставки.
    bool insert(const Key& k, const Value& v);

    // Проверка наличия значения по заданному ключу.
    bool contains(const Key& k) const;

    // Возвращает значение по ключу. Небезопасный метод.
    // В случае отсутствия ключа в контейнереа следует вставить в контейнер
    // значение, созданное конструктором по умолчанию и вернуть ссылку на него.
    Value& operator[](const Key& k);

    // Возвращает значение по ключу. Бросает исключение при неудаче.
    Value& at(const Key& k);
    const Value& at(const Key& k) const;

    size_t size() const;
    bool empty() const;

    bool operator==(const HashTable & other) const;
    bool operator!=(const HashTable & other) const;
};



#endif //HASHTABLE_HASH_H
