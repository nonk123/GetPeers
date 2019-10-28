#include "BencodeParser.hpp"

bool BencodeParser::parseDecimal(std::string str, BencodeNumber& out) {
    bool startsWithZero = (str[0] == '0');

    if (startsWithZero) out = 0;

    for (int i = startsWithZero; i < str.length(); i++)
        if (startsWithZero)
            return false;
        else if (str[i] >= '0' && str[i] <= '9')
            out = (out * 10) + (str[i] - '0');
        else
            return false;

    return true;
}

template<>
bool BencodeParser::parse(BencodeNumber& out) {
    if (str[pos++] != 'i')
        return (valid = false);

    std::string toParse;

    while (str[pos] != 'e')
        toParse += str[pos++];

    return (valid = parseDecimal(toParse, out));
}

// TODO: implement string, list, and dictionary parsing.

template<>
bool BencodeParser::next(BencodeString& out) {
    if (str[pos] >= '0' && str[pos] <= '9')
        return parse<BencodeString>(out);
    else
        return (valid = false);
}

template<>
bool BencodeParser::next(BencodeNumber& out) {
    if (str[pos] == 'i')
        return parse<BencodeNumber>(out);
    else
        return (valid = false);
}

template<>
bool BencodeParser::next(BencodeList& out) {
    if (str[pos] == 'l')
        return parse<BencodeList>(out);
    else
        return (valid = false);
}

template<>
bool BencodeParser::next(BencodeDictionary& out) {
    if (str[pos] == 'd')
        return parse<BencodeDictionary>(out);
    else
        return (valid = false);
}
