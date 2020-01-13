/* <===<===<===<===<===<===<===<===<===~===>===>===>===>===>===>===>===>===>
 * File Name:    Lambda.cpp
 * Author:       Xin-Xin MA, Hao-Kai SUN
 * Created:      2019-10-21 Mon 14:24:15 CST
 * <<=====================================>>
 * Last Updated: 2019-12-18 Wed 21:56:44 CST
 *           By: Hao-Kai SUN
 *     Update #: 25
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
#include "GaudiKernel/Bootstrap.h"
#include "GaudiKernel/IJobOptionsSvc.h"
#include "GaudiKernel/ISvcLocator.h"
#include "GaudiKernel/PropertyMgr.h"

#include "EvtRecEvent/EvtRecVeeVertex.h"
#include "ParticleID/ParticleID.h"

#include "HadronInfo/LamInfo.h"

#include "BesStdSelector/Lambda.h"

BesStdSelector::Lambda::Lambda() {
    IJobOptionsSvc* jobSvc;
    Gaudi::svcLocator()->service("JobOptionsSvc", jobSvc);

    PropertyMgr m_propMgr;

    m_propMgr.declareProperty("MinMass", m_minMass = 1.095);
    m_propMgr.declareProperty("MaxMass", m_maxMass = 1.135);
    m_propMgr.declareProperty("MaxChisq", m_maxChisq = 200);

    // We strongly recommend you don't cut on the decay length
    m_propMgr.declareProperty("Use2ndVFit", m_use2ndVFit = false);
    m_propMgr.declareProperty("MaxVFitChisq", m_maxVFitChisq = 200);

    m_propMgr.declareProperty("UseFlightSig", m_useFlightSig = false);
    m_propMgr.declareProperty("MinFlightSig", m_minFlightSig = 2.0);

    jobSvc->setMyProperties("OmegaXiKSelectorLambda", &m_propMgr);
}

bool BesStdSelector::Lambda::operator()(CDDecay& aLambda) {
    // Need the package HadronInfo
    LamInfo lamInfo(aLambda.decay());
    // lamInfo.calculate();

    double mass = lamInfo.m();
    if ((mass <= m_minMass) || (mass >= m_maxMass)) return false;

    if (lamInfo.vtxChi2() > m_maxChisq) return false;

    if (m_use2ndVFit) {
        if (lamInfo.chisq() > m_maxVFitChisq) return false;
    }

    if (m_useFlightSig) {
        if (lamInfo.decayLengthRatio() < m_minFlightSig) return false;
    }

    // Must update the moentum of Lambda candiate, the raw momentum of Lambda is
    // just sum of protons' and pion's, the vertex fit can improve the
    // resolution significancely
    aLambda.setP4(lamInfo.p4());

    return true;
}
BesStdSelector::Lambda lambdaSelector;
/* ===================================================================<<< */
/* ======================== Lambda.cpp ends here ======================== */
