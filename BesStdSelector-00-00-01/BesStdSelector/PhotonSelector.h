/* ====================================================
#   Copyright (C)2019 All rights reserved.
#
#   Author        : Xin-Xin MA
#   Email         : xxmawhu@163.com
#   File Name     : BeSelectorPhotonSelector.h
#   Created Time  : 2019-10-23 15:47
#   Last Modified : 2019-10-23 15:47
#   Describe      :
#
# ====================================================*/

#ifndef BeSelector_PHOTON_SELECTOR_H
#define BeSelector_PHOTON_SELECTOR_H

#include "BesDChain/CDPhoton.h"
#include "BesDChain/BesDCSelector.h"
#include "EvtRecEvent/EvtRecPi0.h"
#include <iostream>
using std::vector;

class BeSelectorPhotonSelector : public BesDCSelector<CDPhoton> {
   public:
    BeSelectorPhotonSelector();

    bool operator()(CDPhoton& aPhoton);
    void setPi0s(vector<const EvtRecPi0*> m_pi0s);
    inline void SetEnergy(double e) { m_energy = e; }

   private:
    double m_energy;
    bool m_vetoPi0;
    bool FromPi0(int id, vector<const EvtRecPi0*> m_pi0s);
    vector<const EvtRecPi0*> m_pi0s;

    BeSelectorPhotonSelector(const BeSelectorPhotonSelector&);
    const BeSelectorPhotonSelector& operator=(const BeSelectorPhotonSelector&);

    double m_minEnergy;

    bool m_useBarrelEndcap;
    double m_maxCosThetaBarrel;
    double m_minCosThetaEndcap;
    double m_maxCosThetaEndcap;
    double m_minEndcapEnergy;

    bool m_applyTimeCut;
    double m_minTime;
    double m_maxTime;
    double m_deltaTime;

    bool m_applyDangCut;
    double m_minDang;
};

extern BeSelectorPhotonSelector beSelectorPhotonSelector;

#endif
