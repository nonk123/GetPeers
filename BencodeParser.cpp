#include <exception>

#include "BencodeParser.hpp"

bool parseDecimal(std::string str, BencodeNumber& out) {
    out = 0;

    bool negative = (str[0] == '-');

    if (negative && (str.length() == 1 || (str.length() > 1 && str[1] == '0')))
        return false;

    bool startsWithZero = (str[0] == '0');

    for (std::size_t i = startsWithZero || negative; i < str.length(); i++)
        if (startsWithZero)
            return false;
        else if (str[i] >= '0' && str[i] <= '9')
            out = (out * 10) + (str[i] - '0');
        else
            return false;

    if (negative) out = -out;

    return true;
}

BencodeParser& BencodeParser::operator>>(BencodeNumber& out) {
    if (str[pos] != 'i')
        throw std::runtime_error("Not a number");

    std::string toParse;

    while (str[++pos] != 'e')
        toParse += str[pos];

    if (parseDecimal(toParse, out))
        return *this;
    else
        throw std::runtime_error("Can't parse number: " + toParse);
}

BencodeParser& BencodeParser::operator>>(BencodeString& out) {
    if (str[pos] < '0' || str[pos] > '9')
        throw std::runtime_error("Not a string");

    std::string lengthString;

    while (str[pos] != ':')
        lengthString += str[pos++];

    int length = 0;

    if (!parseDecimal(lengthString, length))
        throw std::runtime_error("Can't parse string length: " + lengthString);

    if (length < 0)
        throw std::runtime_error("Negative string length: "
                                 + std::to_string(length));

    if (pos + length > str.length())
        throw std::length_error("String is longer than input");

    for (int i = 0; i < length; i++)
        out += str[++pos];

    return *this;
}

BencodeParser& BencodeParser::operator>>(BencodeList& out) {
    if (str[pos] != 'l')
        throw std::runtime_error("Not a list");

    while (str[++pos] != 'e') {
        BencodeDynamic e;
        *this >> e;
        out.push_back(e);
    }

    return *this;
}

BencodeParser& BencodeParser::operator>>(BencodeDictionary& out) {
    if (str[pos] != 'd')
        throw std::runtime_error("Not a dictionary");

    char keyOrder = 0;
    while (str[++pos] != 'e') {
        BencodeString key;
        *this >> key;

        if (key.empty())
            throw std::runtime_error("Key is empty");

        if (key[0] < keyOrder)
            throw std::runtime_error("Key is out of order: " + key);

        keyOrder = key[0];
        pos++;

        BencodeDynamic value;
        *this >> value;
        out.insert({key, value});
    }

    return *this;
}

BencodeParser& BencodeParser::operator>>(BencodeDynamic& out) {
    if (str[pos] == 'i') {
        BencodeNumber num;
        *this >> num;
        out = num;
    } else if (str[pos] >= '0' && str[pos] <= '9') {
        BencodeString str;
        *this >> str;
        out = str;
    } else if (str[pos] == 'l') {
        BencodeList list;
        *this >> list;
        out = list;
    } else if (str[pos] == 'd') {
        BencodeDictionary dict;
        *this >> dict;
        out = dict;
    } else {
        throw std::runtime_error("Nothing left to parse");
    }

    return *this;
}
