//
// Created by Hindrik Stegenga on 7/19/2016.
//

#ifndef ASCENSION_CORE_POOL_H
#define ASCENSION_CORE_POOL_H

#include "Handle.h"
#include <array>
#include "PoolItem.h"

using std::array;

#define MIN_SIZE 1
#define  MAX_SIZE 2000000

template<typename T, int SIZE>
class Pool {
    static_assert(SIZE <= MAX_SIZE && SIZE >= MIN_SIZE, "You must use a size between (and including) MIN_SIZE and (including) MAX_SIZE!");

public:
    Pool();

    //not movable or copy-able
    Pool(const Pool& pool) = delete;
    Pool(const Pool&& pool) = delete;
    Pool& operator= (const Pool& pool) = delete;

    inline T& operator[] (const size_t index);
	inline T& At(const size_t index);

	template<typename... ResetArgs>
    Handle<T> GetNewItem(ResetArgs... args);

	inline const array<PoolItem<T>, SIZE>& GetStorageRef() const;

    void RemoveItem(Handle<T> item);

	inline int GetItemInUseCount();
    inline size_t size();

	inline const int GetFirstFreeIndex() const;
private:
	int InUseCounter = 0;
    int FirstFreeIndex = 0;
    int Max_Size = SIZE;
    array<PoolItem<T>, SIZE> storage;
};


template<typename T, int SIZE>
inline int Pool<T, SIZE>::GetItemInUseCount()
{
	return InUseCounter;
}

template<typename T, int SIZE>
inline size_t Pool<T, SIZE>::size()
{
    return static_cast<size_t>(Max_Size);
}

template<typename T, int SIZE>
inline const int Pool<T, SIZE>::GetFirstFreeIndex() const
{
	return FirstFreeIndex;
}

template<typename T, int SIZE>
inline Pool<T,SIZE>::Pool()
{
    for(size_t i = 0; i < size(); ++i)
    {
        if(i != size() - 1)
            storage[static_cast<int>(i)].CurrentState.NextItemIndex = (static_cast<int>(i) + 1);
        else
            storage[static_cast<int>(i)].CurrentState.NextItemIndex = -1;
    }
}

template<typename T, int SIZE>
template<typename... ResetArgs>
Handle<T> Pool<T, SIZE>::GetNewItem(ResetArgs... args) {

    if(FirstFreeIndex == -1)
        throw "No free item left in the pool!";
    int TempIndex = FirstFreeIndex;
    FirstFreeIndex = storage[FirstFreeIndex].CurrentState.NextItemIndex;
    storage[TempIndex].IsUsed = true;
	storage[TempIndex].Reset(args...);
	InUseCounter++;
    return Handle<T>(TempIndex);
}

template<typename T, int SIZE>
inline const array<PoolItem<T>, SIZE>& Pool<T, SIZE>::GetStorageRef() const
{
	return storage;
}

template<typename T, int SIZE>
void Pool<T, SIZE>::RemoveItem(Handle<T> item)
{
    if(item.GetIndex() < 0 || item.GetIndex() > static_cast<int>(size()))
        throw "Out of range exception!";

    storage[item.GetIndex()].CurrentState.NextItemIndex = FirstFreeIndex;
    FirstFreeIndex = item.GetIndex();
    storage[item.GetIndex()].IsUsed = false;
	storage[item.GetIndex()].CleanUp();
	InUseCounter--;
}

template<typename T, int SIZE>
inline T& Pool<T,SIZE>::operator[](const size_t index)
{
    return storage[index].CurrentState.Object;
}

template<typename T, int SIZE>
inline T& Pool<T,SIZE>::At(const size_t index)
{
    if(index > 0 && index < size())
        return storage[index];
    throw "Out of range exception!";
};


#endif //ASCENSION_CORE_POOL_H