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
    std::optional<BencodeNumber> num;
    std::optional<BencodeString> str;
    std::optional<BencodeList> list;
    std::optional<BencodeDictionary> dict;

    BencodeDynamic() {
    }

    BencodeDynamic(BencodeNumber num) : num(num) {
    }

    BencodeDynamic(BencodeString str) : str(str) {
    }

    BencodeDynamic(BencodeList list) : list(list) {
    }

    BencodeDynamic(BencodeDictionary dict) : dict(dict) {
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

    BencodeParser& operator>>(BencodeDynamic& out);
    BencodeParser& operator>>(BencodeNumber& out);
    BencodeParser& operator>>(BencodeString& out);
    BencodeParser& operator>>(BencodeList& out);
    BencodeParser& operator>>(BencodeDictionary& out);
};

#endif
