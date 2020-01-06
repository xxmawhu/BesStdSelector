/* ====================================================
#   Copyright (C)2019 All rights reserved.
#
#   Author        : Xin-Xin MA
#   Email         : xxmawhu@163.com
#   File Name     : BeSelectorEtatoGGSelector.cxx
#   Created Time  : 2019-10-23 15:35
#   Last Modified : 2019-10-23 15:35
#   Describe      :
#
# ====================================================*/

#include "GaudiKernel/Bootstrap.h"
#include "GaudiKernel/IJobOptionsSvc.h"
#include "GaudiKernel/ISvcLocator.h"
#include "GaudiKernel/PropertyMgr.h"

#include "EvtRecEvent/EvtRecEtaToGG.h"
#include "BeSelector/Selector/BeSelectorEtatoGGSelector.h"

BeSelectorEtatoGGSelector::BeSelectorEtatoGGSelector() {
    IJobOptionsSvc* jobSvc;
    Gaudi::svcLocator()->service("JobOptionsSvc", jobSvc);

    PropertyMgr m_propMgr;

    m_propMgr.declareProperty("EtaMinMassCut", m_minMass = 0.40);
    m_propMgr.declareProperty("EtaMaxMassCut", m_maxMass = 0.70);
    m_propMgr.declareProperty("EtaMaxChisqCut", m_maxChisq = 2500);

    jobSvc->setMyProperties("BeSelectorEtatoGGSelector", &m_propMgr);
}

bool BeSelectorEtatoGGSelector::operator()(CDEta& aEta) {

    aEta.setUserTag(1);
    EvtRecEtaToGG* eta = const_cast<EvtRecEtaToGG*>(aEta.navEta());

    double mass = eta->unconMass();
    double chi2 = eta->chisq();
    if ((mass <= m_minMass) || (mass >= m_maxMass) || (chi2 >= m_maxChisq))
        return false;

    return true;
}

BeSelectorEtatoGGSelector beSelectorEtatoGGSelector;
