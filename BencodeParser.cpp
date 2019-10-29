#include "BencodeParser.hpp"

bool BencodeParser::parseDecimal(std::string str, BencodeNumber& out) {
    bool negative = (str[0] == '-');
    bool startsWithZero;

    if (negative && (str.length() == 1 || (str.length() > 1 && str[1] == '0')))
        return false;
    else
        startsWithZero = (str[0] == '0');

    if (startsWithZero) out = 0;

    for (int i = startsWithZero || negative; i < str.length(); i++)
        if (startsWithZero)
            return false;
        else if (str[i] >= '0' && str[i] <= '9')
            out = (out * 10) + (str[i] - '0');
        else
            return false;

    if (negative) out = -out;

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

template<>
bool BencodeParser::parse(BencodeString& out) {
    std::string lengthString;

    while (str[pos] != ':')
        lengthString += str[pos++];

    int length = 0;

    if (!parseDecimal(lengthString, length))
        return (valid = false);

    if (length < 0)
        return (valid = false);

    for (int i = 0; i < length; i++)
        if (pos < str.length())
            out += str[++pos];
        else
            return (valid = false);

    return true;
}

// TODO: implement list, and dictionary parsing.

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
