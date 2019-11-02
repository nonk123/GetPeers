#include "BencodeParser.hpp"

template<>
BencodeDynamic& BencodeDynamic::operator=(const BencodeDynamic& t) {
    this->str = t.str;
    this->num = t.num;
    this->list = t.list;
    this->dict = t.dict;
    return *this;
}

template<>
BencodeDynamic& BencodeDynamic::operator=(const BencodeString& t) {
    this->str = t;
    return *this;
}

template<>
BencodeDynamic& BencodeDynamic::operator=(const BencodeNumber& t) {
    this->num = t;
    return *this;
}

template<>
BencodeDynamic& BencodeDynamic::operator=(const BencodeList& t) {
    this->list = t;
    return *this;
}

template<>
BencodeDynamic& BencodeDynamic::operator=(const BencodeDictionary& t) {
    this->dict = t;
    return *this;
}

bool BencodeParser::parseDecimal(std::string str, BencodeNumber& out) {
    bool negative = (str[0] == '-');

    if (negative && (str.length() == 1 || (str.length() > 1 && str[1] == '0')))
        return false;

    bool startsWithZero = (str[0] == '0');

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
bool BencodeParser::isNext<BencodeNumber>() const {
    return str[pos] == 'i';
}

template<>
bool BencodeParser::isNext<BencodeString>() const {
    return str[pos] >= '0' && str[pos] <= '9';
}

template<>
bool BencodeParser::isNext<BencodeList>() const {
    return str[pos] == 'l';
}

template<>
bool BencodeParser::isNext<BencodeDictionary>() const {
    return str[pos] == 'd';
}

template<>
bool BencodeParser::isNext<BencodeDynamic>() const {
    return isNext<BencodeString>() || isNext<BencodeNumber>()
        || isNext<BencodeList>()   || isNext<BencodeDictionary>();
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
bool BencodeParser::next(BencodeNumber& out) {
    if (isNext<BencodeNumber>())
        return parse<BencodeNumber>(out);
    return false;
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

template<>
bool BencodeParser::next(BencodeString& out) {
    if (isNext<BencodeString>())
        return parse<BencodeString>(out);
    return false;
}

template<>
bool BencodeParser::next(BencodeDynamic& out);

template<>
bool BencodeParser::parse(BencodeList& out) {
    if (str[pos] != 'l')
        return (valid = false);

    while (str[++pos] != 'e') {
        BencodeDynamic e;

        if (next(e))
            out.push_back(e);
        else
            return (valid = false);
    }

    return true;
}

template<>
bool BencodeParser::next(BencodeList& out) {
    if (isNext<BencodeList>())
        return parse<BencodeList>(out);
    return false;
}

template<>
bool BencodeParser::parse(BencodeDictionary& out) {
    if (str[pos] != 'd')
        return (valid = false);

    char keyOrder = 0;
    while (str[++pos] != 'e') {
        BencodeString key;

        if (!next(key) || key.empty() || key[0] < keyOrder)
            return (valid = false);

        keyOrder = key[0];
        pos++;

        BencodeDynamic value;

        if (!next(value))
            return (valid = false);

        out.insert({key, value});
    }

    return true;
}

template<>
bool BencodeParser::next(BencodeDictionary& out) {
    if (isNext<BencodeDictionary>())
        return parse<BencodeDictionary>(out);
    return false;
}

template<>
bool BencodeParser::next(BencodeDynamic& out) {
    if (isNext<BencodeString>()) {
        BencodeString str;

        if (!next(str))
            return (valid = false);

        out = str;
    } else if (isNext<BencodeNumber>()) {
        BencodeNumber num = 0;

        if (!next(num))
            return (valid = false);

        out = num;
    } else if (isNext<BencodeList>()) {
        BencodeList list;

        if (!next(list))
            return (valid = false);

        out = list;
    } else if (isNext<BencodeDictionary>()) {
        BencodeDictionary dict;

        if (!next(dict))
            return (valid = false);

        out = dict;
    } else {
        return (valid = false);
    }

    return true;
}
