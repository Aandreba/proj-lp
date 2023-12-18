#include "BallTree.h"

#include <set>

#include "MyUtils.hpp"
#include "Util.h"

void BallTree::construirArbre(const std::vector<Coordinate>& coordenades) {
    std::set<SortedCoordinate> coordinates;

    // Remove equal coordinates
    for (auto coord : coordenades) {
        coordinates.insert(SortedCoordinate{coord, INF});
    }

    construirArbreRec(this, coordinates.cbegin(), coordinates.cend());
}

void BallTree::inOrdre(std::vector<std::list<Coordinate>>& out) {
    // TODO: TASCA 2
    const auto left = this->getEsquerre();
    const auto right = this->getDreta();
}
void BallTree::preOrdre(std::vector<std::list<Coordinate>>& out) {
    // TODO: TASCA 2
}

void BallTree::postOrdre(std::vector<std::list<Coordinate>>& out) {
    // TODO: TASCA 2
}

Coordinate BallTree::nodeMesProper(Coordinate targetQuery, Coordinate& Q, BallTree* ball) {
    // TODO: TASCA 3
}

class SortedCoordinate {
   public:
    Coordinate coord;
    double dist;

    inline bool operator<(const SortedCoordinate& other) {
        return dist < other.dist;
    };

    inline bool operator>(const SortedCoordinate& other) {
        return dist > other.dist;
    };
};

void construirArbreRec(BallTree* self, std::set<SortedCoordinate>::const_iterator start, std::set<SortedCoordinate>::const_iterator end) {
    const size_t size = std::distance(start, end);
    if (size == 0) return;

    // Calculate pivot/centroid
    Coordinate mean{0., 0.};
    for (auto coord = start; coord != end; coord++) {
        mean.lat += coord->coord.lat;
        mean.lon += coord->coord.lon;
    }
    self->setPivot(Coordinate{mean.lat / size, mean.lon / size});

    // Calculate mean distance
    std::set<SortedCoordinate> distances;
    for (auto coord = start; coord != end; coord++) {
        const double dist = Util::DistanciaHaversine(coord->coord, self->getPivot());
        if (dist == 0) {
            self->getCoordenades().push_back(coord->coord);
            continue;
        }
        distances.insert(SortedCoordinate{coord->coord, dist});
    }

    // Split
    self->setRadius(std::next(distances.cend(), -1)->dist);
    const auto midpoint = std::next(distances.cbegin(), distances.size() / 2);

    self->setEsquerre(new BallTree());
    construirArbreRec(self->getEsquerre(), distances.cbegin(), midpoint);

    self->setDreta(new BallTree());
    construirArbreRec(self->getDreta(), midpoint, distances.cend());
}
