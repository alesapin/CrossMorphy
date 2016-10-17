#ifndef TAGCONVERTER_H_
#define TAGCONVERTER_H_
#include "MorphChars.h"
#include "MorphClass.h"
#include "MorphClassContainer.h"
namespace base {
    Tag convertClassToTag(const MorphClass& cls);
    MorphClassContainer convertTagToClasses(Tag t);
}
#endif //TAGCONVERTER_H_
