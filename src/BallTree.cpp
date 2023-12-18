#include "BallTree.h"

#include <list>
#include <set>

#include "MyUtils.hpp"
#include "Util.h"

bool isLeaf(BallTree *ball) {
  bool isLeaf = false;

  bool isRightNodeNull = ball->getDreta() == nullptr;
  bool isLeftNodeNull = ball->getEsquerre() == nullptr;
  bool isBallEmpty = !ball->getCoordenades().empty();

  if (isRightNodeNull && isLeftNodeNull && isBallEmpty)
    isLeaf = true;

  return isLeaf;
}

void construirArbreRec(BallTree *self, const std::vector<Coordinate> &coords) {
  const size_t size = coords.size();
  self->getCoordenades() = coords;
  if (size <= 1)
    return;

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

void BallTree::construirArbre(const std::vector<Coordinate> &coordenades) {
  auto coords_clone = std::vector<Coordinate>(coordenades);
  construirArbreRec(this, coordenades);

  this->setArrel(new BallTree());
  this->getArrel()->setCoordenades(coords_clone);
  this->getArrel()->setPivot(this->getPivot());
  this->getArrel()->setRadius(this->getRadi());
}

void BallTree::inOrdre(std::vector<std::list<Coordinate>> &out) {
  // TODO: TASCA 2
  const auto left = this->getEsquerre();
  if (left != nullptr)
    left->inOrdre(out);

  out.push_back(std::list<Coordinate>(this->getCoordenades().cbegin(),
                                      this->getCoordenades().cend()));

  const auto right = this->getDreta();
  if (right != nullptr)
    right->inOrdre(out);
}

void BallTree::preOrdre(std::vector<std::list<Coordinate>> &out) {
  // TODO: TASCA 2
  out.push_back(std::list<Coordinate>(this->getCoordenades().cbegin(),
                                      this->getCoordenades().cend()));

  const auto left = this->getEsquerre();
  if (left != nullptr)
    left->preOrdre(out);

  const auto right = this->getDreta();
  if (right != nullptr)
    right->preOrdre(out);
}

void BallTree::postOrdre(std::vector<std::list<Coordinate>> &out) {
  // TODO: TASCA 2
  const auto left = this->getEsquerre();
  if (left != nullptr)
    left->postOrdre(out);

  const auto right = this->getDreta();
  if (right != nullptr)
    right->postOrdre(out);

  out.push_back(std::list<Coordinate>(this->getCoordenades().cbegin(),
                                      this->getCoordenades().cend()));
}

Coordinate BallTree::nodeMesProper(Coordinate pdi, Coordinate &Q,
                                   BallTree *bola) {
  double dist1, dist2, minDistance = 10000;
  BallTree *leftBall, *rightBall;
  std::vector<double> distances;
  std::vector<Coordinate> nodes;
  Coordinate center;
  int it = 0;

  dist1 = Util::DistanciaHaversine(center, pdi);
  center = Util::calcularPuntCentral(nodes);
  nodes = bola->getCoordenades();

  for (auto node : nodes) {
    distances.push_back(Util::DistanciaHaversine(node, pdi));
  }

  for (int i = 0; i < distances.size(); i++) {
    if (distances[i] < minDistance) {
      minDistance = distances[i];
      it = i;
    }
  }

  Q.lon = nodes[it].lon;
  Q.lat = nodes[it].lat;
  dist2 = Util::DistanciaHaversine(center, Q);

  if (!isLeaf(bola) && (dist1 - bola->getRadi()) <= dist2) {
    leftBall = bola->getEsquerre();
    rightBall = bola->getDreta();

    dist1 = Util::DistanciaHaversine(leftBall->getPivot(), pdi);
    dist2 = Util::DistanciaHaversine(rightBall->getPivot(), pdi);

    if (dist2 < dist1) {
      nodeMesProper(pdi, Q, leftBall);
    } else {
      nodeMesProper(pdi, Q, rightBall);
    }
  }

  return Q;
}
