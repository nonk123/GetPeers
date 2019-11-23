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

void print(const BencodeDynamic& dynamic);

void print(const BencodeNumber& num) {
    std::cout << num;
}

void print(const BencodeString& str) {
    std::cout << "\"" << str << "\"";
}

void print(const BencodeList& list) {
    std::cout << "{ ";

    int index = 0;
    for (const auto& e : list) {
        print(e);

        if (++index != list.size())
            std::cout << ", ";
    }

    std::cout << " }";
}

void print(const BencodeDictionary& dict) {
    std::cout << "{ ";

    int index = 0;
    for (const auto& p : dict) {
        print(p.first);
        std::cout << ": ";
        print(p.second);

        if (++index != dict.size())
            std::cout << ", ";
    }

    std::cout << " }";
}

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
        "d3:hey3:youe",
        "d3:hey6:no you7:yes youi1000ee",
        "l3:hey3:nou4:yesu7:reversee",
        "d2:nollli10eeei20ee3:yesllleeee"
    }) {
        BencodeDynamic d;
        BencodeParser(e) >> d;
        std::cout << e << " = ";
        print(d);
        std::cout << std::endl;
    }

    return 0;
}

int main(int argc, char** argv) {
    return getPeers();
}
