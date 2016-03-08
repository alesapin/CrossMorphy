#ifndef PARSED_H_
#define PARSED_H_

#include "Base/MorphChars.h"
#include "Base/ITagPrinter.h"
#include <string>
#include <memory>
#include <iostream>
#include "TagPrinter/CrossLexTagPrinter.h"

namespace analyze {
    class Parsed {
    private:
        std::shared_ptr<base::ITagPrinter> printer;
        std::string form;
        std::string normalForm;
        base::SpeechPart sp;
        base::Tag tag;
    public:
        explicit Parsed(std::shared_ptr<base::ITagPrinter> p) : printer(
                p) { };

        Parsed(const std::string &f, const std::string &nf, base::SpeechPart s, base::Tag t,
               std::shared_ptr<base::ITagPrinter> tp) : form(f), normalForm(nf),
                                                        sp(s), tag(t), printer(tp) { }

        void setForm(const std::string &f) { form = f; }

        void setNormalForm(const std::string &nf) { normalForm = nf; }

        void setSpeechPart(base::SpeechPart p) { sp = p; }

        void setTag(base::Tag t) { tag = t; }

        void setTagPrinter(std::shared_ptr<base::ITagPrinter> p) { printer = p; }

        std::string getForm() const { return form; }

        std::string getNormalForm() const { return normalForm; }

        base::SpeechPart getSpeechPart() const { return sp; }

        base::Tag getTag() const { return tag; }

        std::shared_ptr<base::ITagPrinter> getTagPrinter() { return printer; }

        std::vector<std::string> tagToVector() const { return printer->toStringVector(tag); }

        friend std::ostream &operator<<(std::ostream &os, const Parsed &p) {
            os << "[form: " << p.form << ", normal form: "
            << p.normalForm << ", speech part: " << base::toString(p.sp) << ", tags=("
            << p.printer->toString(p.tag)<<")]";
            return os;
        }
    };
}
#endif //PARSED_H_
