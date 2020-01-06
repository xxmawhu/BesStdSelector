/* ====================================================
#   Copyright (C)2019 All rights reserved.
#
#   Author        : Xin-Xin MA
#   Email         : xxmawhu@163.com
#   File Name     : BeSelectorPi0Selector.cxx
#   Created Time  : 2019-10-23 15:36
#   Last Modified : 2019-10-23 15:36
#   Describe      :
#
# ====================================================*/

#include "BeSelector/Selector/BeSelectorPi0Selector.h"

BeSelectorPi0Selector::BeSelectorPi0Selector() {
    IJobOptionsSvc* jobSvc;
    Gaudi::svcLocator()->service("JobOptionsSvc", jobSvc);

    PropertyMgr m_propMgr;

    m_propMgr.declareProperty("Pi0MinMassCut", m_minMass = 0.098);
    m_propMgr.declareProperty("Pi0MaxMassCut", m_maxMass = 0.165);
    m_propMgr.declareProperty("Pi0MaxChisqCut", m_maxChisq = 2500);
    m_propMgr.declareProperty("MinP", m_minP = 0);

    jobSvc->setMyProperties("BeSelectorPi0Selector", &m_propMgr);
}

bool BeSelectorPi0Selector::operator()(CDPi0& aPi0) {

    aPi0.setUserTag(1);
    EvtRecPi0* pi0 = const_cast<EvtRecPi0*>(aPi0.navPi0());

    double mass = pi0->unconMass();
    double chi2 = pi0->chisq();
    if ((mass <= m_minMass) || (mass >= m_maxMass) || (chi2 >= m_maxChisq))
        return false;

    if ((aPi0.p4()).rho() < m_minP) return false;

    if (mass < 0.115 || mass > 0.150) aPi0.setUserTag(2);

    return true;
}

BeSelectorPi0Selector beSelectorPi0Selector;
