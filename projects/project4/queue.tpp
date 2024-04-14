#include "queue.hpp"

template <typename T, typename L>
void Queue<T, L>::enqueue(const T &item)
{
    internal_list.insert(0, item);
}

template <typename T, typename L>
void Queue<T, L>::dequeue()
{
    size_t position = internal_list.getLength() - 1;
    internal_list.remove(position);
}

template <typename T, typename L>
T Queue<T, L>::peekFront()
{
    size_t position = internal_list.getLength() - 1;
    return internal_list.getEntry(position);
}

template <typename T, typename L>
bool Queue<T, L>::isEmpty() const
{
    return internal_list.isEmpty();
}
