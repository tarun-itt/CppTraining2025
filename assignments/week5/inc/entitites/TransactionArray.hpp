#ifndef TRANSACTIONARRAY_HPP
#define TRANSACTIONARRAY_HPP

#include "Transaction.hpp"

class TransactionArray {
    private:
        Transaction** data;
        uint32_t size;
        int capacity;

        void resize(int newCapacity);

    public:
        explicit TransactionArray(int capacity = 10);
        ~TransactionArray();

        void add(Transaction* t);
        Transaction* operator[](int index) const;
        int getSize() const;
        TransactionArray getSubArray(const TransactionArray& source, int startIndex, int count);
};

#endif
