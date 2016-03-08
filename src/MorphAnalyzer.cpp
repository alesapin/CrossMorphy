#include "MorphAnalyzer.h"
namespace xmorph{
     void MorphAnalyzer::load(MorphAnalyzer& ma,const Config& conf = DEFAULT_CONFIG){
         analyze::SufProcessor proc;
         analyze::SufProcessor::loadSufProcessor(conf.suffixFilePath,proc);
         dawg::Dictionary<analyze::NounSuffix>* ns = new dawg::Dictionary<analyze::NounSuffix>();
         std::ifstream npStream(conf.nounPairsPath,std::ifstream::binary);
         if(!ns->deserialize(npStream)){
             throw
         }
         analyze::NounPairs np(ns);
     }

}