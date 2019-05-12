#include "bk/module.h"

#include <iostream>

namespace bk {
Module::Module(const std::string& filename, std::vector<bk::Token>& tokens) {
    mFilename = filename;
    mTokens = tokens;
}

std::ostream& operator<<(std::ostream& stream, const Module& module) {
    stream << module.mFilename << std::endl << "   ";

    for (auto& el : module.mTokens)
        stream << el << " ";

    return stream;
}

} // namespace bk
