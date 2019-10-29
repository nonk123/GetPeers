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
    std::vector<std::string> ints {
        "i-3e", "i3e", "i--3e",
        "i0e", "i-0e",
        "i10e", "i-10e",
        "i03e", "i03e", "i-03e", "i003e",
        "i10000e", "i103e"
    };

    std::cout << std::boolalpha;
    for (const auto& i : ints) {
        BencodeNumber j = 0;
        bool b = BencodeParser(i).next<BencodeNumber>(j);
        std::cout << i << "\t= " << j << " (" << b << ")"  << std::endl;
    }

    return 0;
}

int main(int argc, char** argv) {
    return getPeers();
}
