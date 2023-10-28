#pragma once

#include <string>

#include "../Common.h"

class NodeParser {
   private:
    XmlElement& node;

   public:
    NodeParser() = delete;
    NodeParser(XmlElement& node) : node(node){};

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
                std::string* value = nullptr;

                for (auto jt = it->second.begin(); jt != it->second.end(); jt++) {
                    if (correctKey && jt->first == "v") {
                        return &jt->second;
                    }
                    correctKey |= jt->first == "k" && jt->second == k;
                }
            }
        }
        return nullptr;
    }
};
