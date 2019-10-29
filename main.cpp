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

int getPeers() {
    // Test data.
    std::vector<std::string> strings {
        "3:hey", "2:ja", "1:o", "0:", "10:abcdefghijkl", "1:abc", "-1:a"
    };

    std::cout << std::boolalpha;
    for (const auto& s : strings) {
        BencodeString str;
        bool b = BencodeParser(s).next(str);
        std::cout << s << "\t= " << str << " (" << b << ")" << std::endl;
    }

    return 0;
}

int main(int argc, char** argv) {
    return getPeers();
}
