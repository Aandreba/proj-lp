#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "./Common.h"
#include "./PuntDeInteresBase.h"

class EntryParser {
   public:
    XmlElement& node;

   public:
    EntryParser() = delete;
    EntryParser(XmlElement& node) : node(node){};

    PuntDeInteresBase parseBase() const {
        auto name = this->getTag("name");
        auto lat = this->getAttribute("lat");
        auto lon = this->getAttribute("lon");

        std::string m_name = "";
        Coordinate m_coord = {0.0, 0.0};

        if (name != nullptr) {
            m_name = *name;
        }

        if (lat != nullptr) {
            m_coord.lat = std::stod(*lat);
        }

        if (lon != nullptr) {
            m_coord.lon = std::stod(*lon);
        }

        return PuntDeInteresBase(m_coord, m_name);
    }

    unsigned long getId() const {
        unsigned long id_res = 0;

        auto id = this->getAttribute("id");
        if (id != nullptr) {
            id_res = std::stoul(*id);
        }

        return id_res;
    }

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
};
