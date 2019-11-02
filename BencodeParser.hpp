#ifndef BENCODE_PARSER_HPP
#define BENCODE_PARSER_HPP

#include <string>
#include <vector>
#include <map>
#include <optional>

struct BencodeDynamic;
typedef std::string BencodeString;
typedef int BencodeNumber;
typedef std::vector<BencodeDynamic> BencodeList;
typedef std::map<BencodeString, BencodeDynamic> BencodeDictionary;

struct BencodeDynamic {
    std::optional<BencodeString> str;
    std::optional<BencodeNumber> num;
    std::optional<BencodeList> list;
    std::optional<BencodeDictionary> dict;

    template<typename T>
    BencodeDynamic& operator=(const T& t) {
        return *this;
    }
};

class BencodeParser {
  private:
    std::string str;
    int pos;
  public:
    bool valid;

    BencodeParser(std::string str) : str(str), pos(0), valid(true) {
    }

    template<typename T>
    bool next(T& out) {
        return false;
    }

    template<typename T>
    bool isNext() const {
        return false;
    }

  private:
    bool parseDecimal(std::string str, BencodeNumber& out);

    template<typename T>
    bool parse(T& out) {
        return false;
    }
};

#endif
