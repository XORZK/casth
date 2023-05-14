#include "lexer.cpp"

std::string read_file(const std::string fn) {
    std::string contents = "", line;
    std::ifstream input(fn);

    while (std::getline(input, line)) { contents += line; }

    input.close();

    return contents;
}

int main(int argc, char* argv[]) {
    if (argc >= 2) {
        Lexer lexer(read_file(argv[1]));
        Token token = lexer.next();
        while (token.is_not(TokenType::END_OF_FILE) && token.is_not(TokenType::UNEXPECTED)) {
            std::cout << token.type() << " | " << token.value() << " |\n";
            token = lexer.next();
        }
    } else {
        printf("Usage: %s file\n", argv[0]);
    }
}