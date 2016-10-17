#include "MorphAnalyzer.h"
namespace xmorph{
    void MorphAnalyzer::load(MorphAnalyzer& ma,const Config& conf) {
        analyze::SufProcessor proc;
        analyze::SufProcessor::loadSufProcessor(conf.suffixFilePath,proc);
        dawg::Dictionary<analyze::NounSuffix>* ns = new dawg::Dictionary<analyze::NounSuffix>();
        std::ifstream npStream(conf.nounPairsPath,std::ifstream::binary);
        if(!ns->deserialize(npStream)) {
            throw BinaryFileException(conf.nounPairsPath);
        }
        std::shared_ptr<dawg::Dictionary<analyze::NounSuffix>> sns(ns);
        analyze::NounPairs np(sns);
        dawg::Dictionary<base::MorphClassContainer>* odict = new dawg::Dictionary<base::MorphClassContainer>();
        std::ifstream dictStream(conf.dictionaryFilePath,std::ifstream::binary);
        if(!odict->deserialize(dictStream)){
            throw BinaryFileException(conf.dictionaryFilePath);
        }
        std::shared_ptr<dawg::Dictionary<base::MorphClassContainer>> dictPtr(odict);
        analyze::DictAnalyzer* anl = new analyze::DictAnalyzer(dictPtr,np,proc);
        std::shared_ptr<analyze::DictAnalyzer> dictAnalyzer(anl);
        ma.analyzers.push_back(dictAnalyzer);
    }

    std::vector<Parsed> MorphAnalyzer::analyze(const std::string& w) const {
        std::string word = prepareWord(w);
        std::vector<Parsed> result;
        for(std::size_t i = 0;i<analyzers.size();++i){
            std::vector<Parsed> anResult = analyzers[i]->analyze(word);
            if(!anResult.empty()){
                result.insert(result.end(),anResult.begin(),anResult.end());
                break;
            }
        }
        return result;
    }
    std::string MorphAnalyzer::prepareWord(const std::string word) const {
        std::string res = boost::locale::to_lower(word,ruUtf8Locale);
        boost::replace_all(res,"ё","е");
        return res;

    }

}