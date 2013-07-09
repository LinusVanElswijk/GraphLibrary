#ifndef EXPIREDVERTEXEXCEPTION_H
#define EXPIREDVERTEXEXCEPTION_H

#include <stdexcept>

class ExpiredVertexException: public std::runtime_error
{
    public:
        explicit ExpiredVertexException (const std::string& what_arg)
        :std::runtime_error(what_arg)
        { }

        explicit ExpiredVertexException (const char* what_arg)
        :std::runtime_error(what_arg)
        { }
};

#endif // EXPIREDVERTEXEXCEPTION_H
