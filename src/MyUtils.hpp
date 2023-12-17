#pragma once

#include <stdexcept>
#include <string>

#include "./binary_map.hpp"
#include "./parser.hpp"
#include "Common.h"

inline bool string_contains(const std::string& haystack, const std::string& needle) {
    return haystack.find(needle) != std::string::npos;
}

inline std::vector<Coordinate> getNodeCoords(const EntryParser& parser, const binary_map<unsigned long, Coordinate>& pool) {
    const auto children = &parser.node.fills;
    std::vector<Coordinate> result;

    for (auto it = children->cbegin(); it != children->cend(); it++) {
        if (it->first == "nd") {
            for (auto jt = it->second.cbegin(); jt != it->second.cend(); jt++) {
                if (jt->first == "ref") {
                    const auto key = std::stoul(jt->second);

                    try {
                        result.push_back(pool.at(key));
                    } catch (const std::out_of_range&) {
                    }

                    break;
                }
            }
        }
    }

    return result;
}
