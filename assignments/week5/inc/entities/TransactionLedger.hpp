#ifndef TransactionLedger_HPP
#define TransactionLedger_HPP

#include "Transaction.hpp"

class TransactionLedger {
    private:
        Transaction** data;
        uint32_t size;
        int capacity;

        void resize(int newCapacity);

    public:
        explicit TransactionLedger(int capacity = 10);
        ~TransactionLedger();

        void add(Transaction* t);
        Transaction* operator[](int index) const;
        int getSize() const;
        TransactionLedger getSubArray(const TransactionLedger& source, int startIndex, int count);
};

#endif
