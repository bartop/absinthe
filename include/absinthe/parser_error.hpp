#pragma once

#include <string>

namespace absinthe
{

class parser_error {
public:
    parser_error(std::string error) : error_(std::move(error)) {}

    std::string message() const {
        return error_;
    }

private:
    std::string error_;   
};

}
