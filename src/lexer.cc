#include "bk/lexer.h"
#include "bk/token.h"

#include <filesystem>
#include <sstream>
#include <fstream>

namespace bk {

Lexer::Lexer(const std::string& path) :
    mLineNum(0),
    mAcceptExtension(".md") {
    mRoot = path;
}

Lexer::~Lexer() {}

void Lexer::process() {
    namespace fs = std::filesystem;

    for (auto& el : fs::recursive_directory_iterator(mRoot))
        if (el.path().extension() == mAcceptExtension)
            mFiles.push_back(el.path());

    for (auto& path : mFiles)
        tokenizeFile(path);
}

void Lexer::tokenizeFile(const std::string& filename) {
    std::ifstream file(filename, std::ifstream::in);
    std::stringstream ss;
    std::vector<bk::Token> tokens;
    std::size_t linecount = 0;
    char c;

    while(file >> c) {
        if (c == ' ' || c == '\n' || c == '\r') {
            if (c == '\n') linecount++;
            bk::Token tok(ss.str(), linecount);
            tokens.push_back(tok);
            ss.clear();
            continue;
        }

        ss << c;
    }

    bk::Module mod(filename, tokens);
    mModules.push_back(mod);
}

std::ostream& operator<<(std::ostream &stream, const Lexer& lex) {
    for (auto& el : lex.mModules)
        stream << el << std::endl;

    return stream;
}

} // namespace bk
