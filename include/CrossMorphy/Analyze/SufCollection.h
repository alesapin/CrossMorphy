#ifndef SUF_COLLECTION_H_
#define SUF_COLLECTION_H_
#include <vector>
#include <iostream>
#include "Base/MorphClass.h"
namespace analyze {
class SufCollection {
protected:
  std::vector<std::vector<std::string>> data;
public:
  SufCollection(const std::vector<std::vector<std::string>>& d): data(d) {}
  virtual std::string getSuffix(const base::MorphClass& cls) const {
    return data[cls.getClassNumber()][cls.getPosition()];
  }
  std::size_t getClassesSize() const { return data.size(); }
  virtual std::size_t getPositionsSize(std::size_t clsNum) const {
    return data.size() < clsNum? 0 : data[clsNum].size();
  }
  virtual ~SufCollection(){};
};

class ShrtAdjCollection : public SufCollection {
private:
  const std::size_t SHRT_PACK_LEN = 5;
public:
  ShrtAdjCollection(const std::vector<std::vector<std::string>>& d): SufCollection(d) {}

  virtual std::string getSuffix(const base::MorphClass& cls) const override {
    std::size_t clNum = cls.getClassNumber();
    std::size_t pos = cls.getPosition();
    std::size_t shrtPos = cls.getShortAdjPos();
    std::size_t base = shrtPos * SHRT_PACK_LEN;
    return data[clNum][base + pos + 1];
  }
  std::string getFullFormSuffix(std::size_t clsNum,std::size_t shortAdjPos) const {
    std::size_t base = shortAdjPos * SHRT_PACK_LEN;
    return data[clsNum][base];
  }
  virtual std::size_t getPositionsSize(std::size_t clsNum) const override {
    return SHRT_PACK_LEN - 1;
  }
};
class AdjCollection : public SufCollection {
public:
  AdjCollection(const std::vector<std::vector<std::string>>& d): SufCollection(d) {}
  virtual std::size_t getPositionsSize(std::size_t clsNum) const {
    if(clsNum == 0) return 1;
    return data.size() < clsNum? 0 : data[clsNum].size();
  }
};

}
#endif //SUF_COLLECTION_H
