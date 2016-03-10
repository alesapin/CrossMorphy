#include "Base/TagConverter.h"
namespace base {
    namespace {
        const std::size_t VERB_TAGS_SIZE = 13; //TODO, really 15 values
        const std::size_t ADJ_TAGS_SIZE = 24;
        const std::size_t SADJ_TAGS_SIZE = 4;
        const std::size_t PRON_TAGS_SIZE = 12;

        const base::Tag PRON_TAGS[PRON_TAGS_SIZE] = {
                Tag::FP | Tag::SG | Tag::OVERALL, Tag::FP | Tag::PL | Tag::OVERALL,
                Tag::SP | Tag::SG | Tag::OVERALL, Tag::SP | Tag::PL | Tag::OVERALL,
                Tag::TP | Tag::SG | Tag::MASC, Tag::TP | Tag::SG | Tag::MASC,
                Tag::TP | Tag::SG | Tag::FEM, Tag::TP | Tag::SG | Tag::FEM,
                Tag::TP | Tag::SG | Tag::NEUT, Tag::TP | Tag::SG | Tag::NEUT,
                Tag::TP | Tag::PL | Tag::NEUT, Tag::TP | Tag::PL | Tag::NEUT,
        };

        const base::Tag SHRT_ADJ_TAGS[SADJ_TAGS_SIZE] = {
                Tag::SHRT | Tag::MASC | Tag::SG,
                Tag::SHRT | Tag::FEM | Tag::SG,
                Tag::SHRT | Tag::NEUT | Tag::SG,
                Tag::SHRT | Tag::UNDEF | Tag::PL
        };

        const base::Tag ADJ_TAGS[ADJ_TAGS_SIZE] = {
                Tag::MASC | Tag::NOM | Tag::SG, Tag::MASC | Tag::GEN | Tag::SG,
                Tag::MASC | Tag::DAT | Tag::SG, Tag::MASC | Tag::ACC | Tag::SG,
                Tag::MASC | Tag::INS | Tag::SG, Tag::MASC | Tag::PRE | Tag::SG,
                Tag::FEM | Tag::NOM | Tag::SG, Tag::FEM | Tag::GEN | Tag::SG,
                Tag::FEM | Tag::DAT | Tag::SG, Tag::FEM | Tag::ACC | Tag::SG,
                Tag::FEM | Tag::INS | Tag::SG, Tag::FEM | Tag::PRE | Tag::SG,
                Tag::NEUT | Tag::NOM | Tag::SG, Tag::NEUT | Tag::GEN | Tag::SG,
                Tag::NEUT | Tag::DAT | Tag::SG, Tag::NEUT | Tag::ACC | Tag::SG,
                Tag::NEUT | Tag::INS | Tag::SG, Tag::NEUT | Tag::PRE | Tag::SG,
                Tag::UNDEF | Tag::NOM | Tag::PL, Tag::UNDEF | Tag::GEN | Tag::PL,
                Tag::UNDEF | Tag::DAT | Tag::PL, Tag::UNDEF | Tag::ACC | Tag::PL,
                Tag::UNDEF | Tag::INS | Tag::PL, Tag::UNDEF | Tag::PRE | Tag::PL
        };
        const base::Tag VERB_TAGS[VERB_TAGS_SIZE] = {
            Tag::INF,
            Tag::SG | Tag::UNDEF | Tag::PAST | Tag::INDC,
            Tag::SG | Tag::UNDEF | Tag::PAST | Tag::INDC,
            Tag::SG | Tag::UNDEF | Tag::PAST | Tag::INDC,
            Tag::PL | Tag::UNDEF | Tag::PAST | Tag::INDC,
            Tag::SG | Tag::FP | Tag::NPAST | Tag::INDC,
            Tag::SG | Tag::SP | Tag::NPAST | Tag::INDC,
            Tag::SG | Tag::TP | Tag::NPAST | Tag::INDC,
            Tag::PL | Tag::FP | Tag::NPAST | Tag::INDC,
            Tag::PL | Tag::SP | Tag::NPAST | Tag::INDC,
            Tag::PL | Tag::TP | Tag::NPAST | Tag::INDC,
            Tag::SG | Tag::UNDEF | Tag::UNDEF | Tag::IMPR,
            Tag::PL | Tag::UNDEF | Tag::UNDEF | Tag::IMPR
        };

    }

    Tag convertClassToTag(const MorphClass& cls) {
        Tag result = Tag::NOTAG;
        switch (cls.getSpeechPart()) {
            case SpeechPart::NOUN:
                result |= (Tag::CASE_START << cls.getPosition());
                result |= cls.getGender();
                result |= cls.getNumber();
                return result;
            case SpeechPart::VERB:
                if(cls.getPosition() < VERB_TAGS_SIZE) {
                    return VERB_TAGS[cls.getPosition()];
                }
                break;
            case SpeechPart::ADJ:
                if(cls.getShortAdjPos() != base::MorphClass::UNKNOWN_POS) {
                    if(cls.getPosition() < SADJ_TAGS_SIZE) {
                        return SHRT_ADJ_TAGS[cls.getPosition()];
                    }
                } else {
                    if(cls.getPosition() < ADJ_TAGS_SIZE){
                        return ADJ_TAGS[cls.getPosition()];
                    }
                }
                break;
            case SpeechPart::PRON:
                result |= (Tag::CASE_START << cls.getPosition());
                result |= PRON_TAGS[cls.getClassNumber()];
                return result;
            default:
                return Tag::UNDEF; //TODO Change to IMMUT
        }
        return Tag::UNDEF;
    }
    MorphClassContainer convertTagToClasses(Tag t) {
        //TODO
    }
}
