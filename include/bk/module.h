#pragma once

#include <bk/token.h>

#include <vector>
#include <string>

namespace bk {

struct Module {
public:
    Module(const std::string&, std::vector<bk::Token>&);
    ~Module(){}
    std::string filename();
    std::vector<bk::Token> tokens();

private:
    std::string mFilename;
    std::vector<bk::Token> mTokens;

    friend std::ostream& operator<<(std::ostream&, const bk::Module&);
};

}
