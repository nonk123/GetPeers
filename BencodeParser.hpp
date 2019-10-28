#ifndef BENCODE_PARSER_HPP
#define BENCODE_PARSER_HPP

#include <string>
#include <vector>
#include <map>
#include <any>

typedef std::any BencodeDynamic;
typedef std::string BencodeString;
typedef int BencodeNumber;
typedef std::vector<BencodeDynamic> BencodeList;
typedef std::map<BencodeString, BencodeDynamic> BencodeDictionary;

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

  private:
    bool parseDecimal(std::string str, BencodeNumber& out);

    template<typename T>
    bool parse(T& out) {
        return false;
    }
};

#endif
