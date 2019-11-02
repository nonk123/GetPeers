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
    std::cout << "\"" << t << "\"";
}

template<>
void print(const BencodeList& t) {
    std::cout << "{ ";

    for (const auto& e : t) {
        print(e);
        std::cout << ", ";
    }

    std::cout << "}";
}

template<>
void print(const BencodeDictionary& t) {
    std::cout << "{ ";

    for (const auto& p : t) {
        print(p.first);
        std::cout << ": ";
        print(p.second);
        std::cout << ", ";
    }

    std::cout << "}";
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
        "d3:hey3:youe", "di3ee", "d3:hey6:no you7:yes youi1000ee",
        "l3:hey3:nou4:yesu7:reversee",
        "d2:nollli10eeei20ee3:yesllleeee"
    }) {
        BencodeDynamic d;
        bool b = BencodeParser(e).next(d);
        std::cout << e << " = ";
        print(d);
        std::cout << " (" << b << ")" << std::endl;
    }

    return 0;
}

int main(int argc, char** argv) {
    return getPeers();
}
