/* ====================================================
#   Copyright (C)2020 All rights reserved.
#
#   Author        : Xin-Xin MA
#   Email         : xxmawhu@163.com
#   File Name     : TypicalTag.cpp
#   Create Time   : 2020-01-16 14:35
#   Last Modified : 2020-01-16 14:35
# ====================================================*/

#include "GaudiKernel/Bootstrap.h"
#include "GaudiKernel/IJobOptionsSvc.h"
#include "GaudiKernel/ISvcLocator.h"
#include "GaudiKernel/PropertyMgr.h"

#include "EvtRecEvent/EvtRecVeeVertex.h"
#include "VertexFit/IVertexDbSvc.h"
#include "VertexFit/SecondVertexFit.h"
#include "VertexFit/VertexFit.h"

// #include "HadronInfo/TypicalTagInfo.hpp"

#include "BesStdSelector/TypicalTag.h"
#include <string>
using BesStdSelector::TypicalTag;

TypicalTag::TypicalTag(const std::string& svcname) {
    IJobOptionsSvc* jobSvc;
    Gaudi::svcLocator()->service("JobOptionsSvc", jobSvc);

    PropertyMgr m_propMgr;

    // the Four quantities `mass`, `mbc`, `deltaE`, `recmass` are highly
    // relatived, you can only use two of them. Before decision, please check
    // the correlation between one and another.
    m_propMgr.declareProperty("CutMass", m_cutMass = false);
    m_propMgr.declareProperty("MinMass", m_minMass = 0);
    m_propMgr.declareProperty("MaxMass", m_maxMass = 5);

    // Here, we assume that
    // 1. two bodys decay
    // 2. two bodys with same mass, such as J/psi -> Sigma0 anti-Sigma0
    // So the energy of the tag is equal to half of Ecm. It's the reason why
    // we call the mass as Mbc "beam constraint mass"
    m_propMgr.declareProperty("CutMbc", m_cutMbc = false);
    m_propMgr.declareProperty("MinMbc", m_minMass = 0);
    m_propMgr.declareProperty("MaxMbc", m_maxMass = 5);

    // The deltaE is defined as E_tag - Ebeam,
    // where the Ebeam = 0.5 * Ecm
    // if the two badys' mass are not same, you can stil use the
    // deltaE cut, but please notice that the peak is not around zero.
    m_propMgr.declareProperty("CutDeltaE", m_cutDeltaE = false);
    m_propMgr.declareProperty("MinDeltaE", m_minDeltaE = -0.15);
    m_propMgr.declareProperty("MaxDeltaE", m_maxDeltaE = 0.15);

    // Also miss mass
    m_propMgr.declareProperty("CutRecMass", m_cutRecMass = false);
    m_propMgr.declareProperty("MinRecMass", m_minRecMass = 0);
    m_propMgr.declareProperty("MaxRecMass", m_maxRecMass = 5);

    jobSvc->setMyProperties(svcname, &m_propMgr);
}

bool TypicalTag::operator()(CDDecay& aTypicalTag) {
    if (m_cutMass) {
        double mass = aTypicalTag.mass();
        if (mass < m_minMass || mass > m_maxMass) return false;
    }
    if (m_cutMbc) {
        HepLorentzVector p4 = aTypicalTag.p4();
        p4.setE(m_Ecm / 2);
        double mass = p4.m();
        if (mass < m_minMbc || mass > m_maxMbc) return false;
    }

    if (m_cutDeltaE) {
        double deltaE = aTypicalTag.p4().e() - m_Ecm * 0.5;
        if (deltaE < m_minDeltaE || deltaE > m_maxDeltaE) return false;
    }

    if (m_cutRecMass) {
        HepLorentzVector p4 = aTypicalTag.p4();
        HepLorentzVector p4Beam(m_Ecm * 0.011, 0, 0, m_Ecm);
        double recmass = (p4Beam - p4).m();
        if (recmass < m_minRecMass || recmass > m_maxRecMass) return false;
    }
    return true;
}

TypicalTag BesStdSelector::typicalTagSelector("TypicalTagCandidate");
