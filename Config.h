#ifndef CONFIG_H
#define CONFIG_H
#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
namespace xmorph {
    struct Config {
        std::string suffixFilePath;
        std::string dictionaryFilePath;
        std::string nounPairsPath;
        static void load(const std::string& path,Config& conf);
    };
    const Config DEFAULT_CONFIG = {"dicts/suffixes.json","dicts/bindict","dicts/binpairs"};

}
#endif //CROSSMORPHY_CONFIG_H
