#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

enum class TokenType {
    NUMBER,
    FLOAT,
    STRING,
    ADDITION,
    SUBTRACTION,
    MULTIPLICATION,
    DIVISION,
    MODULO,
    GREATER_THAN,
    LESS_THAN,
    EQUAL,
    LEFT_CURLY,
    RIGHT_CURLY,
    LEFT_PAREN,
    RIGHT_PAREN,
    LEFT_SQUARE,
    RIGHT_SQUARE,
    KEYWORD,
    IDENTIFIER,
    COMMENT,
    END_OF_FILE,
    COLON,
    SEMICOLON,
    COMMA,
    DOT,
    DOUBLE_QUOTE,
    UNEXPECTED,
};

bool is_digit(char c) { return (c >= '0' && c <= '9'); }
bool is_alpha(char c) { return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (is_digit(c))); }
bool is_space(char c) { return (c == ' ' || c == '\t' || c == '\r' || c == '\n'); }
bool is_separator(char c) { return ((c == '(' || c == ')') || (c == '{' || c == '}') || (c == '[' || c == ']') || c == ';'); }
bool is_identifier(char c) { return (c == '_' || is_alpha(c)); }

struct Token {
    private:
        TokenType t_type{};
        std::string t_value{};
    public:
        Token(TokenType t) : t_type(t), t_value("") {}
        Token(TokenType t, const char v) : t_type(t), t_value(std::string(1, v)) {}
        Token(TokenType t, std::string v) : t_type(t), t_value(v) {}
        Token(TokenType t, const char* v) : t_type(t), t_value(v) {}
        TokenType type() { return this->t_type; }
        void type(TokenType t) { this->t_type = t; }
        bool is(TokenType t) { return (this->t_type == t); }
        bool is_not(TokenType t) { return (this->t_type != t); }
        std::string value() { return this->t_value; }
};

struct Lexer {
    private:
        size_t index = 0;
        std::string contents;

    public:
        Lexer(std::string c) : contents(c) {}
        Lexer(const char* c) : contents(c) {}

        Token comment() {
            this->index++;
            std::string comment = "";
            while (this->contents.substr(this->index, 2) != "*/") {
                comment += this->contents[this->index++];
            }
            this->index++;
            return inc_token(TokenType::COMMENT, comment);
        }

        Token string() {
            this->index++;
            std::string s = "";
            while (this->contents[this->index] != '"') {
                s += this->contents[this->index++];
            }
            return inc_token(TokenType::STRING, s);
        }

        Token integral_type() {
            bool fp = false;
            std::string i = "";
            while (is_digit(this->contents[this->index]) || this->contents[this->index] == '.') {
                if (!fp) fp = (this->contents[this->index] == '.');
                i += this->contents[this->index++];
            }
            return inc_token(fp ? TokenType::FLOAT : TokenType::NUMBER, i);
        }

        Token identifier() {
            std::string identifier = "";
            while (is_identifier(this->contents[this->index])) {
                identifier += this->contents[this->index++];
            }
            return inc_token(TokenType::IDENTIFIER, identifier);
        }

        Token forward_slash() {
            return (this->contents[this->index] == '*' ? this->comment() : Token(TokenType::DIVISION, '/'));
        }

        Token inc_token(TokenType t, std::string s) { this->index++; return Token(t, s); }
        Token inc_token(TokenType t, char c) { this->index++; return Token(t, c); }

        Token next() {
            while (is_space(this->contents[this->index])) {
                this->index++;
            }

            char curr = this->contents[this->index];

            switch (curr) {
                case ('\0'): return inc_token(TokenType::END_OF_FILE, curr);
                case ('='): return inc_token(TokenType::EQUAL, curr);
                case ('>'): return inc_token(TokenType::GREATER_THAN, curr);
                case ('<'): return inc_token(TokenType::LESS_THAN, curr);
                case ('/'): { this->index++; return this->forward_slash(); }
                case ('*'): return inc_token(TokenType::MULTIPLICATION, curr);
                case ('%'): return inc_token(TokenType::MODULO, curr);
                case ('+'): return inc_token(TokenType::ADDITION, curr);
                case ('-'): return inc_token(TokenType::SUBTRACTION, curr);
                case ('{'): return inc_token(TokenType::LEFT_CURLY, curr);
                case ('}'): return inc_token(TokenType::RIGHT_CURLY, curr);
                case ('('): return inc_token(TokenType::LEFT_PAREN, curr);
                case (')'): return inc_token(TokenType::RIGHT_PAREN, curr);
                case ('['): return inc_token(TokenType::LEFT_SQUARE, curr);
                case (']'): return inc_token(TokenType::RIGHT_SQUARE, curr);
                case (';'): return inc_token(TokenType::SEMICOLON, curr);
                case (':'): return inc_token(TokenType::COLON, curr);
                case (','): return inc_token(TokenType::COMMA, curr);
                case ('.'): return inc_token(TokenType::DOT, curr);
                case ('"'): return this->string();
                default: {
                    if (is_digit(curr)) {
                        return this->integral_type();
                    } else if (is_identifier(curr)) {
                        return this->identifier();
                    }
                    break;
                }
            }

            return Token(TokenType::UNEXPECTED);
        }
};


std::ostream& operator<<(std::ostream& os, const TokenType type) {
    const char* tokens[] = {
    "NUMBER",
    "FLOAT",
    "STRING",
    "ADDITION",
    "SUBTRACTION",
    "MULTIPLICATION",
    "DIVISION",
    "MODULO",
    "GREATER_THAN",
    "LESS_THAN",
    "EQUAL",
    "LEFT_CURLY",
    "RIGHT_CURLY",
    "LEFT_PAREN",
    "RIGHT_PAREN",
    "LEFT_SQUARE",
    "RIGHT_SQUARE",
    "KEYWORD",
    "IDENTIFIER",
    "COMMENT",
    "END_OF_FILE",
    "COLON",
    "SEMICOLON",
    "COMMA",
    "DOT",
    "DOUBLE_QUOTE",
    "UNEXPECTED",
    };

    return os << tokens[static_cast<int>(type)];
}