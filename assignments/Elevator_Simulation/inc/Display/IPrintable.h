#ifndef IPRINTABLE_H
#define IPRINTABLE_H

#include <string>

struct DisplayProperties;

class IPrintable {
public:
    virtual ~IPrintable() = default;
    virtual std::string getContent() const = 0;
    virtual DisplayProperties getDisplayProperties() const = 0;
};

#endif