#include <iostream>
#include <vector>
#include <string>
#include <memory>

#include "HTTPRequest.hpp"
#include "cxxopts.hpp"

#include "BencodeParser.hpp"

static std::vector<std::string> trackers {
    #include "trackers.def"
};

bool checkTracker(std::string tracker) {
    // TODO: implement.
    return true;
}

std::string parseTorrentFile(std::string path) {
    // TODO: implement.
    return std::string();
}

template<typename T>
void print(const T& t) {
}

template<>
void print(const BencodeDynamic& t);

template<>
void print(const BencodeNumber& t) {
    std::cout << t;
}

template<>
void print(const BencodeString& t) {
    std::cout << t;
}

template<>
void print(const BencodeList& t) {
    for (const auto& e : t) {
        print(e);
        std::cout << " ";
    }
}

template<>
void print(const BencodeDictionary& t) {
    for (const auto& p : t) {
        std::cout << "\"";
        print(p.first);
        std::cout << "\": \"";
        print(p.second);
        std::cout << "\" ";
    }
}

template<>
void print(const BencodeDynamic& t) {
    if (t.str.has_value())
        print(t.str.value());
    else if (t.num.has_value())
        print(t.num.value());
    else if (t.list.has_value())
        print(t.list.value());
    else if (t.dict.has_value())
        print(t.dict.value());
}

int getPeers() {
    std::cout << std::boolalpha;
    for (const auto& e : std::vector<std::string> {
        "le", "l3:heye", "li1e1:e0:e", "li1ei2ei3ei4ei5ee",
        "li3eli3eee"
    }) {
        BencodeList list;
        bool b = BencodeParser(e).next(list);
        std::cout << e << " = ";
        print(list);
        std::cout << " (" << b << ")" << std::endl;
    }

    return 0;
}

int main(int argc, char** argv) {
    return getPeers();
}
