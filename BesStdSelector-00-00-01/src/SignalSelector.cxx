/* ====================================================
#   Copyright (C)2019 All rights reserved.
#
#   Author        : Xin-Xin Ma
#   Email         : xxmawhu@163.com
#   File Name     : BeSelectorSignalSelector.cxx
#   Last Modified : 2019-10-23 10:00
#   Describe      :
#
# ====================================================*/

#include "BeSelector/Selector/BeSelectorSignalSelector.h"
using CLHEP::Hep3Vector;
using CLHEP::HepLorentzVector;
using std::cout;
using std::endl;

BeSelectorSignalSelector::BeSelectorSignalSelector() {
    IJobOptionsSvc* jobSvc;
    Gaudi::svcLocator()->service("JobOptionsSvc", jobSvc);

    PropertyMgr m_propMgr;
    m_propMgr.declareProperty("UseMassCuts", m_useMbcCuts = false);
    m_propMgr.declareProperty("MinMass", m_minMass = 1.90);
    m_propMgr.declareProperty("MaxMass", m_maxMass = 2.04);
    m_propMgr.declareProperty("UseRecMassCuts", m_useRecCuts = false);
    m_propMgr.declareProperty("MinRecMass", m_minRecMass = 2.0);
    m_propMgr.declareProperty("MaxRecMass", m_maxRecMass = 2.2);

    jobSvc->setMyProperties("BeSelectorSignalSelector", &m_propMgr);
    m_beamE = 4.178 / 2;
}

bool BeSelectorSignalSelector::operator()(CDDecay& aDs) {
    if (m_useMbcCuts) {
        double mass = aDs.mass();
        if (mass < m_minMass || mass > m_maxMass) return false;
    }
    if (m_useRecCuts) {
        HepLorentzVector p4beam(0, 0, 0, 2 * m_beamE);
        HepLorentzVector p4Ds = aDs.p4();
        p4Ds.boost(-0.011, 0, 0);
        double mrec = (p4beam - p4Ds).m();
        if (mrec < m_minRecMass || mrec > m_maxRecMass) {
            return false;
        }
    }
    return true;
}

BeSelectorSignalSelector beSelectorSignalSelector;
