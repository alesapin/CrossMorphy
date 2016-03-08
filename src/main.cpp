#include <iostream>
#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <vector>
#include <string>
#include <sstream>
#include <boost/regex/icu.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/program_options.hpp>
#include <boost/regex.hpp>
#include "MorphAnalyzer.h"
using namespace boost::locale;
namespace po=boost::program_options;
using namespace std;
void removeNonAlpha(std::string &str,std::locale& loc){
    for(int i = 0;i<str.size();++i){
        if(!std::isalpha(str[i],loc) && str[i] != ' '){
            str[i] = ' ';
        }
    }
}

int main(int argc, char *argv[]) {
    generator gen;
    locale loc = gen("ru_RU.UTF8");
    locale::global(loc);
    xmorph::MorphAnalyzer m;
    xmorph::MorphAnalyzer::load(m);
    po::options_description desc("General options");
    std::string files;
    desc.add_options()
            ("help,h", "Show help")
            ("input,I", po::value<std::string>(), "Input plain text file")
            ("output,O", po::value<std::string>(), "Output parsed file")
            ("err,E",po::value<std::string>(), "Error output file");
            ("word,w", po::value<std::string>(), "Parse single word");
    po::variables_map vm;
    boost::u32regex seqSpace = boost::make_u32regex("[ ]{2,}");
    boost::u32regex nonAlpha = boost::make_u32regex("[^\\w\\-]|[0-9]");
    try {
        po::parsed_options parsed = po::command_line_parser(argc, argv).options(desc).run();
        po::store(parsed, vm);
        po::notify(vm);
        if(vm.find("input") != vm.end()) {
            std::ostream* output = &std::cout;
            std::ostream* err = &std::cerr;
            std::string input_file = vm["input"].as<std::string>();
            std::ifstream ifs(input_file);
            if(vm.find("output") != vm.end()){
                output = new std::ofstream(vm["output"].as<std::string>());
            }
            if(vm.find("err") != vm.end()) {
                err = new std::ofstream(vm["err"].as<std::string>());
            }
            std::string line;
            while(std::getline(ifs,line)){
                if(line[0] == '\n') continue;
                line = boost::locale::normalize(line,boost::locale::norm_default,loc);
                line = boost::u32regex_replace(line, nonAlpha, " ");
                line = boost::u32regex_replace(line,seqSpace, " ");
                if(line.find_first_not_of(' ') == std::string::npos) continue;
                std::vector<std::string> words;
                boost::split(words,line,boost::is_any_of(" "));
                for (int i = 0;i < words.size(); ++i) {
                    if(words[i][0] == 0) continue;
                    std::vector<analyze::Parsed> res = m.analyze(words[i]);
                    if(res.empty()) {
                        *(err) << words[i] <<" unrecognized\n";
                    }else {
                        for(int i = 0;i<res.size();++i){
                            (*output) << res[i]<<"\n";
                        }
                    }
                }
            }
            if(output != & std::cout){
                delete output;
            }
            if(err != &std::cerr){
                delete err;
            }
        } else if(vm.find("word")!= vm.end()){
            std::vector<analyze::Parsed> res = m.analyze(vm["word"].as<std::string>());
            for(int i = 0;i<res.size();++i){
                std::cout << res[i]<<"\n";
            }
        }
    }  catch(std::exception& ex) {
        std::cout << desc << std::endl;
    }
    return 0;
}
