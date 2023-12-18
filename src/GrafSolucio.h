#pragma once

#include <limits>
#include <tuple>
#include <vector>

#include "CamiBase.h"
#include "Common.h"
#include "MyUtils.hpp"
#include "Util.h"

class GrafSolucio {
   public:
    GrafSolucio() {}
    GrafSolucio(std::vector<Coordinate> coords) : nodes(coords) {}
    GrafSolucio(CamiBase& way) {
        this->nodes = way.getCamiCoords();
        for (size_t i = 1; i < this->nodes.size(); i++) {
            addEdge(i - 1, i);
        }
    }

    size_t addCoordinate(Coordinate coord) {
        const size_t idx = this->nodes.size();
        this->nodes.push_back(coord);
        return idx;
    }

    void addEdge(size_t src, size_t dst) {
        this->edges.resize(std::max(src + 1, this->edges.size()));
        std::vector<double>& row = this->edges[src];

        row.resize(std::max(dst + 1, row.size()), INF);
        row[dst] = Util::DistanciaHaversine(this->nodes.at(src), this->nodes.at(dst));
    }

   private:
    std::vector<Coordinate> nodes;
    // rows --> source, cols --> destination
    std::vector<std::vector<double>> edges;
};
