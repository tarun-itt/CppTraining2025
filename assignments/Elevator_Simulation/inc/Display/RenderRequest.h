#ifndef RENDER_REQUEST_H
#define RENDER_REQUEST_H

#include <string>

class IPrintable;

enum class RenderOperation { None, Display, Clear, Remove };

struct RenderRequest {
    RenderOperation operationType;
    IPrintable *object = nullptr;
    std::string printableId;

    RenderRequest(): operationType(RenderOperation::None), object(nullptr), printableId("") {}
    RenderRequest(RenderOperation operationType, IPrintable *object, std::string printableId): operationType(operationType), object(object), printableId(printableId) {}

    explicit operator bool() const noexcept {
        return operationType != RenderOperation::None;
    }
};

#endif