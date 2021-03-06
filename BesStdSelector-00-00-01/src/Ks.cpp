/* <===<===<===<===<===<===<===<===<===~===>===>===>===>===>===>===>===>===>
 * File Name:    Ks.cpp
 * Author:       Xin-Xin MA, Hao-Kai SUN
 * Created:      2019-10-21 Mon 12:53:07 CST
 * <<=====================================>>
 * Last Updated: 2019-12-18 Wed 21:57:00 CST
 *           By: Hao-Kai SUN
 *     Update #: 29
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
#include "VertexFit/IVertexDbSvc.h"
#include "VertexFit/SecondVertexFit.h"
#include "VertexFit/VertexFit.h"

// #include "HadronInfo/KsInfo.hpp"

#include "BesStdSelector/Ks.h"

BesStdSelector::Ks::Ks() {
    IJobOptionsSvc* jobSvc;
    Gaudi::svcLocator()->service("JobOptionsSvc", jobSvc);

    PropertyMgr m_propMgr;

    m_propMgr.declareProperty("MinMass", m_minMass = 0.470);
    m_propMgr.declareProperty("MaxMass", m_maxMass = 0.530);
    m_propMgr.declareProperty("MaxChisq", m_maxChisq = 200);

    // We strongly suggest you do not cut any second vertex fit informations
    // in the program!!
    // m_propMgr.declareProperty("Use2ndVFit", m_use2ndVFit=false);
    // m_propMgr.declareProperty("MaxVFitChisq", m_maxVFitChisq=200)
    // m_propMgr.declareProperty("MinFlightSigma", m_minFlightSig=2.0);

    jobSvc->setMyProperties("StdKsSelector", &m_propMgr);
}

bool BesStdSelector::Ks::operator()(CDKs& aKs) {
    EvtRecVeeVertex* navKshort = const_cast<EvtRecVeeVertex*>(aKs.navKshort());

    double mass = navKshort->mass();
    if (mass < m_minMass || mass > m_maxMass) return false;
    if (navKshort->chi2() > m_maxChisq) return false;

    // if (m_use2ndVFit) {
    //     // if the ks does not meet the criteria, the information from
    //     // the secondary vertex fit will not be filled (default = -999)
    //     if (aKsInfo.chi2() > m_maxVFitChisq) return false;
    //     if (aKsInfo.decayLengthRatio() < m_minFlightSig) return false;
    // }
    //
    // aKs.setP4(aKsInfo.p4());

    return true;
}

BesStdSelector::Ks BesStdSelector::ksSelector;
/* ===================================================================<<< */
/* ========================== Ks.cpp ends here ========================== */
