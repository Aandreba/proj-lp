#pragma once

#include <limits>
#include <tuple>
#include <vector>

#include "Common.h"
#include "Util.h"

class GrafSolucio {
   public:
    GrafSolucio() {}

    size_t addCoordinate(Coordinate coord) {
        const size_t idx = this->nodes.size();
        this->nodes.push_back(coord);
        return idx;
    }

    void addEdge(size_t src, size_t dst) {
        this->edges.resize(std::max(src, this->edges.size()));
        std::vector<double> &row = this->edges[src];

        row.resize(std::max(dst, row.size()), INF);
        row[dst] = Util::DistanciaHaversine(this->nodes.at(src), this->nodes.at(dst));
    }

   private:
    static const double INF = std::numeric_limits<double>::infinity();

    std::vector<Coordinate> nodes;
    // rows --> source, cols --> destination
    std::vector<std::vector<double>> edges;
};
