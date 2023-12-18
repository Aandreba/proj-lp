#include "BallTree.h"

#include <list>
#include <set>

#include "MyUtils.hpp"
#include "Util.h"

void construirArbreRec(BallTree* self, const std::vector<Coordinate>& coords) {
    const size_t size = coords.size();
    self->getCoordenades() = coords;
    if (size <= 1) return;

    // Calculate pivot/centroid
    Coordinate mean{0., 0.};
    for (auto coord : coords) {
        mean.lat += coord.lat;
        mean.lon += coord.lon;
    }
    self->setPivot(Coordinate{mean.lat / (double)size, mean.lon / (double)size});

    // Calculate distance from mean
    Coordinate alpha;
    double max_dist = NEG_INF;

    for (auto coord : coords) {
        const double dist = Util::DistanciaHaversine(coord, self->getPivot());
        if (dist > max_dist) {
            alpha = coord;
            max_dist = dist;
        }
    }
    self->setRadius(max_dist);

    // Calculate distance from max
    Coordinate beta;
    max_dist = NEG_INF;

    for (auto coord : coords) {
        const double dist = Util::DistanciaHaversine(coord, alpha);
        if (dist > max_dist) {
            beta = coord;
            max_dist = dist;
        }
    }

    std::vector<Coordinate> left;
    std::vector<Coordinate> right;

    for (auto coord : coords) {
        const double d1 = Util::DistanciaHaversine(coord, alpha);
        const double d2 = Util::DistanciaHaversine(coord, beta);

        if (d1 >= d2)
            left.push_back(coord);
        else
            right.push_back(coord);
    }

    self->setEsquerre(new BallTree());
    self->getEsquerre()->setArrel(self);
    construirArbreRec(self->getEsquerre(), left);

    self->setDreta(new BallTree());
    self->getDreta()->setArrel(self);
    construirArbreRec(self->getDreta(), right);
}

void BallTree::construirArbre(const std::vector<Coordinate>& coordenades) {
    construirArbreRec(this, coordenades);
}

void BallTree::inOrdre(std::vector<std::list<Coordinate>>& out) {
    // TODO: TASCA 2
    const auto left = this->getEsquerre();
    if (left != nullptr) left->inOrdre(out);

    out.push_back(std::list<Coordinate>(this->getCoordenades().cbegin(), this->getCoordenades().cend()));

    const auto right = this->getDreta();
    if (right != nullptr) right->inOrdre(out);
}

void BallTree::preOrdre(std::vector<std::list<Coordinate>>& out) {
    // TODO: TASCA 2
    out.push_back(std::list<Coordinate>(this->getCoordenades().cbegin(), this->getCoordenades().cend()));

    const auto left = this->getEsquerre();
    if (left != nullptr) left->preOrdre(out);

    const auto right = this->getDreta();
    if (right != nullptr) right->preOrdre(out);
}

void BallTree::postOrdre(std::vector<std::list<Coordinate>>& out) {
    // TODO: TASCA 2
    const auto left = this->getEsquerre();
    if (left != nullptr) left->postOrdre(out);

    const auto right = this->getDreta();
    if (right != nullptr) right->postOrdre(out);

    out.push_back(std::list<Coordinate>(this->getCoordenades().cbegin(), this->getCoordenades().cend()));
}

Coordinate BallTree::nodeMesProper(Coordinate targetQuery, Coordinate& Q, BallTree* ball) {
    // TODO: TASCA 3
}
