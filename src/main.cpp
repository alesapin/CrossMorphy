#include <iostream>
#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <vector>
#include <string>
using namespace std;
#include <iomanip>
#include "Analyze/SufProcessor.h"
#include "DAWG/Dictionary.h"
#include "Base/MorphChars.h"
#include "Base/MorphClass.h"
int main(int argc, char *argv[])
{
  analyze::SufProcessor proc;
  analyze::SufProcessor::loadSufProcessor("dicts/suffixes.json",proc);
  base::MorphClass cls(base::SpeechPart::ADJ,0);
  // cls.setShortAdjPos(2);
  // using boost::property_tree::ptree;
  // ptree pt;
  // read_json("dicts/suffixes.json", pt);
  // std::vector<std::vector<string>> result;
  // for(auto all : pt.get_child("Noun")){
  //   result.push_back(std::vector<string>());
  //   for(auto val : all.second) {
  //     result.back().push_back(val.second.get_value<std::string>());
  //   }
  // }
  // std::cerr<<result.size()<<"\n";
  std::vector<analyze::WordForm> wordForms = proc.getAllFormsByDictForm("беж",cls);
  std::cerr<<"Размер:"<<wordForms.size()<<"\n";
  for(int i = 0;i<wordForms.size();++i){
    std::cerr<<wordForms[i].getForm()<<"\n";
  }
  return 0;
}
