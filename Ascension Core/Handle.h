//
// Created by Hindrik Stegenga on 7/20/2016.
//

#ifndef ASCENSION_CORE_HANDLE_H
#define ASCENSION_CORE_HANDLE_H

template<typename T>
class Handle {
public:
	Handle();
    Handle(int index);
    int GetIndex() const;
    void SetIndex(int index);
private:
    int Index;
};

template<typename T>
int Handle<T>::GetIndex() const
{
    return Index;
}

template<typename T>
void Handle<T>::SetIndex(int index)
{
    Index = index;
}

template<typename T>
Handle<T>::Handle(int index) : Index(index)
{

}

template<typename T>
Handle<T>::Handle() : Index(-1)
{
}

#endif //ASCENSION_CORE_HANDLE_H
