//
// Created by Hindrik Stegenga on 7/19/2016.
//

#ifndef ASCENSION_CORE_POOLITEM_H
#define ASCENSION_CORE_POOLITEM_H

template<typename T>
class PoolItem {
public:
    PoolItem();
	~PoolItem();

    union Data
    {
        Data(){};
        ~Data(){};

        T Object;
        int NextItemIndex;
    } CurrentState;
    bool IsUsed = false;
	void CleanUp();

	template<typename... ResetArgs>
    void Reset(ResetArgs... arguments);
};

template<typename T>
PoolItem<T>::PoolItem()
{
}

template<typename T>
inline PoolItem<T>::~PoolItem()
{
	if (IsUsed)
	{
		CleanUp();
	}
}

template<typename T>
inline void PoolItem<T>::CleanUp()
{
	CurrentState.Object.~T();
}

template<typename T>
template<typename... ResetArgs>
void PoolItem<T>::Reset(ResetArgs... arguments)
{
	void* tVoid = &CurrentState;
	new (tVoid) T(arguments...);
}


#endif //ASCENSION_CORE_POOLITEM_H
