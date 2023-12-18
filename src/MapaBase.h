#pragma once

#include "CamiBase.h"
#include "Common.h"
#include "PuntDeInteresBase.h"

class MapaBase {
   public:
    // Metodes afegir de la primera part.
    virtual void getPdis(std::vector<PuntDeInteresBase *> &) = 0;
    virtual void getCamins(std::vector<CamiBase *> &) = 0;
    virtual void parsejaXmlElements(std::vector<XmlElement> &xmlElements) = 0;
    virtual CamiBase *buscaCamiMesCurt(PuntDeInteresBase *desde, PuntDeInteresBase *a) = 0;
};
