#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "../Common.h"
#include "../PuntDeInteresBase.h"

class EntryParser {
   private:
    XmlElement& node;

   public:
    EntryParser() = delete;
    EntryParser(XmlElement& node) : node(node){};

    const std::string& getName() const {
        return this->node.id_element;
    }

    const std::string* getAttribute(const std::string& key) const {
        const auto attrs = &this->node.atributs;
        for (auto attr = attrs->cbegin(); attr != attrs->cend(); attr++) {
            if (attr->first == key) {
                return &attr->second;
            }
        }
        return nullptr;
    }

    const std::string* getTag(const std::string& k) const {
        const auto children = &this->node.fills;

        for (auto it = children->cbegin(); it != children->cend(); it++) {
            if (it->first == "tag") {
                bool correctKey = false;
                const std::string* value = nullptr;

                for (auto jt = it->second.cbegin(); jt != it->second.cend(); jt++) {
                    correctKey |= jt->first == "k" && jt->second == k;
                    if (jt->first == "v") {
                        value = &jt->second;
                    }

                    if (correctKey && value != nullptr) return value;
                }
            }
        }

        return nullptr;
    }

    std::vector<PuntDeInteresBase*> getNodeRefs(std::vector<std::unique_ptr<PuntDeInteresBase>>& pool) const {
        const auto children = &this->node.fills;
        std::vector<PuntDeInteresBase*> result;

        for (auto it = children->cbegin(); it != children->cend(); it++) {
            if (it->first == "way") {
                for (auto jt = it->second.cbegin(); jt != it->second.cend(); jt++) {
                    if (jt->first == "ref") {
                        const auto key = std::stoul(jt->second);

                        for (auto kt = pool.begin(); kt != pool.end(); kt++) {
                            if ((*kt)->id == key) {
                                result.push_back((*kt).get());
                                break;
                            }
                        }

                        break;
                    }
                }
            }
        }

        return result;
    }
};
