#include "Config.h"
namespace xmorph{
     void Config::load(const std::string& path,Config& conf){
        boost::property_tree::ptree pt;
        boost::property_tree::ini_parser::read_ini(path, pt);
        conf.suffixFilePath = pt.get<std::string>("DictsPaths.SuffPath");
        conf.dictionaryFilePath = pt.get<std::string>("DictsPath.MainDictPath");
        conf.nounPairsPath = pt.get<std::string>("DictsPath.NounPairsPath");
    }

}

