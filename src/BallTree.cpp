#include "BallTree.h"

#include <list>
#include <set>

#include "MyUtils.hpp"
#include "Util.h"

bool fulla(BallTree* bola) {
    if ((bola->getDreta() == nullptr) && (bola->getEsquerre() == nullptr) && (bola->getCoordenades().size() > 0))
        return true;
    else
        return false;
}

Coordinate nodeMesProperRec(Coordinate pdi, Coordinate& Q, BallTree* bola) {
    double distancia1 = 0.0, distancia2 = 0.0;
    double min = 10000;
    int index = 0;
    std::vector<double> distancies;
    std::vector<Coordinate> nodes;
    Coordinate centre;
    BallTree* esq;
    BallTree* dret;

    nodes = bola->getCoordenades();
    centre = Util::calcularPuntCentral(nodes);
    distancia1 = Util::DistanciaHaversine(centre, pdi);

    for (int i = 0; i < nodes.size(); i++) {
        distancies.push_back(Util::DistanciaHaversine(nodes[i], pdi));
    }

    for (int i = 0; i < distancies.size(); i++) {
        if (distancies[i] < min) {
            min = distancies[i];
            index = i;
        }
    }

    Q.lat = nodes[index].lat;
    Q.lon = nodes[index].lon;

    distancia2 = Util::DistanciaHaversine(centre, Q);

    if ((distancia1 - bola->getRadi()) > distancia2) {
        return Q;
    }

    if (fulla(bola) == true) {
        return Q;
    } else {
        esq = bola->getEsquerre();
        dret = bola->getDreta();

        distancia1 = Util::DistanciaHaversine(esq->getPivot(), pdi);
        distancia2 = Util::DistanciaHaversine(dret->getPivot(), pdi);

        if (distancia2 < distancia1) {
            nodeMesProperRec(pdi, Q, esq);
        } else {
            nodeMesProperRec(pdi, Q, dret);
        }

        return Q;
    }
}

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
    auto coords_clone = std::vector<Coordinate>(coordenades);
    construirArbreRec(this, coordenades);

    this->setArrel(new BallTree());
    this->getArrel()->setCoordenades(coords_clone);
    this->getArrel()->setPivot(this->getPivot());
    this->getArrel()->setRadius(this->getRadi());
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

Coordinate BallTree::nodeMesProper(Coordinate pdi, Coordinate& Q, BallTree* bola) {
    double distancia1 = 0.0, distancia2 = 0.0;
    double min = 10000;
    int index = 0;
    std::vector<double> distancies;
    std::vector<Coordinate> nodes;
    Coordinate centre;
    BallTree* esq = new BallTree;
    BallTree* dret = new BallTree;

    nodes = bola->getCoordenades();
    centre = Util::calcularPuntCentral(nodes);
    distancia1 = Util::DistanciaHaversine(centre, pdi);

    for (int i = 0; i < nodes.size(); i++) {
        distancies.push_back(Util::DistanciaHaversine(nodes[i], pdi));
    }

    for (int i = 0; i < distancies.size(); i++) {
        if (distancies[i] < min) {
            min = distancies[i];
            index = i;
        }
    }

    Q.lat = nodes[index].lat;
    Q.lon = nodes[index].lon;

    distancia2 = Util::DistanciaHaversine(centre, Q);

    if ((distancia1 - bola->getRadi()) > distancia2) {
        return Q;
    }

    if (fulla(bola) == true) {
        return Q;
    } else {
        esq = bola->getEsquerre();
        dret = bola->getDreta();

        distancia1 = Util::DistanciaHaversine(esq->getPivot(), pdi);
        distancia2 = Util::DistanciaHaversine(dret->getPivot(), pdi);

        if (distancia2 < distancia1) {
            nodeMesProperRec(pdi, Q, esq);
        } else {
            nodeMesProperRec(pdi, Q, dret);
        }

        return Q;
    }
}
