/* <===<===<===<===<===<===<===<===<===~===>===>===>===>===>===>===>===>===>
 * File Name:    Photon.hpp
 * Author:       Xin-Xin MA, Hao-Kai SUN
 * Created:      2019-09-07 Sat 14:48:46 CST
 * <<=====================================>>
 * Last Updated: 2019-12-02 Mon 09:52:30 CST
 *           By: Hao-Kai SUN
 *     Update #: 33
 * <<======== COPYRIGHT && LICENSE =======>>
 *
 * Copyright © 2019 SUN Hao-Kai <spin.hk@outlook.com>. All rights reserved.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GNU Emacs.  If not, see <https://www.gnu.org/licenses/>.
 *
 * ============================== CODES ==============================>>> */
#ifndef OMEGAXIK_SELECTOR_PHOTON_HPP
#define OMEGAXIK_SELECTOR_PHOTON_HPP

#include "OmegaXiKAlg/Namespace.hpp"
// #include "BesDChain/BesDCSelector.h"
// #include "BesDChain/CDPhoton.h"
#include "OmegaXiKAlg/selector/DCSFBase.hpp"

#include "EvtRecEvent/EvtRecPi0.h"

class OmegaXiKSLT::Photon : public BDCSPhoton {
   public:
    Photon();

    bool operator()(CDPhoton& aPhoton);
    void setPi0s(std::vector<const EvtRecPi0*> m_pi0s);
    inline bool vetoPi0() { return m_vetoPi0; }
    inline void setEnergy(double e) { m_energy = e; }

   private:
    Photon(const Photon&);
    const Photon& operator=(const Photon&);

    double m_energy;

    bool m_useBarrelEndcap;
    double m_maxCosThetaBarrel;
    double m_minBarrelEnergy;
    double m_minCosThetaEndcap;
    double m_maxCosThetaEndcap;
    double m_minEndcapEnergy;

    bool m_useTDC;     // Time-to-Digital-Converter, from EMC
    double m_minTime;  // interval: 50ns
    double m_maxTime;
    double m_deltaTime;

    bool m_useDang;  // angle between gamma shower and charged track
    double m_minDang;

    bool m_vetoPi0;  // for non-single photon
    double m_minPi0Mass;
    double m_maxPi0Mass;
    double m_maxPi0Chisq;

    bool FromPi0(int id, const std::vector<const EvtRecPi0*>& m_pi0s);
    std::vector<const EvtRecPi0*> m_pi0s;
};

extern OmegaXiKSLT::Photon omegaXiKSelectorPhoton;

#endif /* OMEGAXIK_SELECTOR_PHOTON_HPP */
/* ===================================================================<<< */
/* ======================== Photon.hpp ends here ======================== */
