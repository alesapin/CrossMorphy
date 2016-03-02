#ifndef SUF_PROCESSOR_H_
#define SUF_PROCESSOR_H_
#include <map>
#include <stdexcept>
#include "SufCollection.h"
#include "Base/MorphChars.h"
#include "Base/MorphClass.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <memory>
namespace analyze {
struct WordForm {
  std::string form;
  base::MorphClass cls;
  std::string getForm() const {
    return form;
  }
  base::MorphClass getClass() const {
    return cls;
  }
};
class SufProcessor {
private:
  static const std::string NOUN;
  static const std::string VERB;
  static const std::string ADJ;
  static const std::string SHRTADJ;

  std::map<std::string,std::shared_ptr<SufCollection>> suffixes;
public:
  SufProcessor() {};
  std::string getSuffix(const base::MorphClass& cls) const;
  std::string getSuffix(base::SpeechPart sp, std::size_t classNum, std::size_t pos = 0,
    std::size_t shrtPos = base::MorphClass::UNKNOWN_POS) const;
  std::string getStemByNormalForm(const std::string& normalForm, const base::MorphClass& cls) const;
  std::string getStemByForm(const std::string& form, const base::MorphClass& cls) const;
  std::vector<std::string> getAllFormsByStem(const std::string& stem, const base::MorphClass& cls) const;
  std::vector<WordForm> getAllFormsByDictForm(const std::string& normalForm, const base::MorphClass& cls) const;
  std::size_t getNumberOfForms(base::SpeechPart p,std::size_t clsNum, std::size_t shrtPos = base::MorphClass::UNKNOWN_POS) const;
  static void loadSufProcessor(const std::string& filepath, SufProcessor& prc);
};
}
#endif //SUF_PROCESSOR_H_
