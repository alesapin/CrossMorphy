#include "Analyze/SufProcessor.h"
namespace analyze {
const std::string SufProcessor::NOUN = "NOUN";
const std::string SufProcessor::VERB = "VERB";
const std::string SufProcessor::ADJ = "ADJ";
const std::string SufProcessor::SHRTADJ = "SHRTADJ";
void SufProcessor::loadSufProcessor(const std::string& filepath, SufProcessor& prc){
  using boost::property_tree::ptree;
  ptree pt;
  read_json(filepath, pt);
  for(auto sp = pt.begin(); sp!=pt.end();++sp){
    std::vector<std::vector<std::string>> result;
    if(sp->first != NOUN && sp->first!=VERB &&
      sp->first != ADJ && sp->first != SHRTADJ) {
      throw std::invalid_argument("Wrong file suffix format: " + filepath);
    }
    for(auto all : sp->second){
      result.push_back(std::vector<std::string>());
      for(auto val : all.second) {
        result.back().push_back(val.second.get_value<std::string>());
      }
    }
    SufCollection *collect;
    if(sp->first == SHRTADJ) {
      collect = new ShrtAdjCollection(result);
    } else if(sp->first == ADJ) {
      collect = new AdjCollection(result);
    }else{
      collect = new SufCollection(result);
    }
    prc.suffixes[sp->first] = std::shared_ptr<SufCollection>(collect);
  }
}

std::string SufProcessor::getSuffix(base::SpeechPart sp, std::size_t classNum, std::size_t pos ,
  std::size_t shrtPos ) const {
  switch(sp){
    case base::SpeechPart::NOUN:
      return suffixes.at(NOUN)->getSuffix(base::MorphClass(sp,classNum,pos));
    case base::SpeechPart::VERB:
      return suffixes.at(VERB)->getSuffix(base::MorphClass(sp,classNum,pos));
    case base::SpeechPart::ADJ:
      if(shrtPos != base::MorphClass::UNKNOWN_POS) {
        base::MorphClass mrf(sp,classNum,pos);
        mrf.setShortAdjPos(shrtPos);
        return suffixes.at(SHRTADJ)->getSuffix(mrf);
      } else {
        return suffixes.at(ADJ)->getSuffix(base::MorphClass(sp,classNum,pos));
      }
    default:
      return "";
  }
}

std::string SufProcessor::getSuffix(const base::MorphClass& cls) const {
  return getSuffix(cls.getSpeechPart(),cls.getClassNumber(),cls.getPosition(),cls.getShortAdjPos());
}

std::string SufProcessor::getStemByNormalForm(const std::string& normalForm, const base::MorphClass& cls) const{
  std::string suff;
  if(cls.getPosition() != 0){
    base::MorphClass c(cls);
    c.setPosition(0);
    suff = getSuffix(c);
  }else{
    suff = getSuffix(cls);
  }
  if(suff.length() > normalForm.length()) return "";
  return normalForm.substr(0,normalForm.length() - suff.length());
}

std::string SufProcessor::getStemByForm(const std::string& form, const base::MorphClass& cls) const {
  std::string suff = getSuffix(cls);
  return form.substr(0,form.length() - suff.length());
}

std::vector<std::string> SufProcessor::getAllFormsByStem(const std::string& stem, const base::MorphClass& cls) const {
  std::size_t formsCount;
  if(cls.getSpeechPart() == base::SpeechPart::ADJ){
    formsCount = getNumberOfForms(cls.getSpeechPart(),cls.getClassNumber(),cls.getShortAdjPos());
  } else {
    formsCount = getNumberOfForms(cls.getSpeechPart(),cls.getClassNumber());
  }
  std::vector<std::string> result(formsCount);
  for(std::size_t i = 0; i < formsCount; ++i){
    std::string suf = getSuffix(cls.getSpeechPart(),cls.getClassNumber(),i,cls.getShortAdjPos());
    result[i] = stem+suf;
  }
  return result;
}

std::size_t SufProcessor::getNumberOfForms(base::SpeechPart p,std::size_t clsNum, std::size_t shrtPos) const {
  switch(p){
    case base::SpeechPart::NOUN:
      return suffixes.at(NOUN)->getPositionsSize(clsNum);
    case base::SpeechPart::VERB:
      return suffixes.at(VERB)->getPositionsSize(clsNum);
    case base::SpeechPart::ADJ:
      if(shrtPos != base::MorphClass::UNKNOWN_POS){
        return suffixes.at(SHRTADJ)->getPositionsSize(clsNum);
      }else {
        return suffixes.at(ADJ)->getPositionsSize(clsNum);
      }
    default:
      return 1;
  }
}
std::vector<WordForm> SufProcessor::getAllFormsByDictForm(const std::string& normalForm, const base::MorphClass& cls) const {
  std::vector<WordForm> result;
  if(cls.getSpeechPart() == base::SpeechPart::ADJ
    && cls.getShortAdjPos() != base::MorphClass::UNKNOWN_POS) {
      std::shared_ptr<ShrtAdjCollection> col = std::static_pointer_cast<ShrtAdjCollection>(suffixes.at(SHRTADJ)); //Dialing with
      std::string suf = col->getFullFormSuffix(cls.getClassNumber(), cls.getShortAdjPos()); //short form;
      std::string stem = normalForm.substr(0,normalForm.length() - suf.length());
      std::vector<std::string> forms = getAllFormsByStem(stem,cls);
      result.resize(forms.size());
      for(std::size_t i = 0; i < forms.size(); ++i) {
        base::MorphClass current(cls);
        current.setPosition(i);
        result[i] = {forms[i],current};
      }
      if(cls.getClassNumber() != 0) { //Not short form only
        base::MorphClass full(cls);
        full.setShortAdjPos(base::MorphClass::UNKNOWN_POS);
        std::vector<WordForm> fullForms = getAllFormsByDictForm(normalForm,full);
        result.insert(result.end(),fullForms.begin(),fullForms.end());
      }
  } else {
    std::string stem = getStemByNormalForm(normalForm,cls);
    std::vector<std::string> forms = getAllFormsByStem(stem,cls);
    result.resize(forms.size());
    for(std::size_t i = 0; i < forms.size(); ++i) {
      base::MorphClass current(cls);
      current.setPosition(i);
      result[i] = {forms[i],current};
    }
  }
  return result;
}

}
