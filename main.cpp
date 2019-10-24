#include <iostream>
#include <vector>
#include <string>
#include <memory>

#include "HTTPRequest.hpp"

static std::vector<std::string> trackers {
    #include "trackers.def"
};

int main() {
    for (const auto& tracker : trackers)
        std::cout << tracker << "\n";
}
