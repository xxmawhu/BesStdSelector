/* <===<===<===<===<===<===<===<===<===~===>===>===>===>===>===>===>===>===>
 * File Name:    Omega.cpp
 * Author:       Xin-Xin MA, Hao-Kai SUN
 * Created:      2019-10-21 Mon 14:26:41 CST
 * <<=====================================>>
 * Last Updated: 2019-12-17 Tue 17:07:05 CST
 *           By: Hao-Kai SUN
 *     Update #: 19
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
#include "HadronInfo/OmegaInfo.hpp"
#include "VertexFit/IVertexDbSvc.h"
#include "VertexFit/SecondVertexFit.h"
#include "VertexFit/VertexFit.h"

#include "OmegaXiKAlg/selector/Omega.hpp"

BesStdSelector::Omega::Omega()
    : m_minMass(1.550)
    , m_maxMass(1.850)
    , m_maxChisq(400)
    , m_use2ndVFit(false)
    , m_maxVFitChisq(400)
    , m_useFlightSig(false)
    , m_minFlightSig(2.0)
{
    IJobOptionsSvc* jobSvc;
    Gaudi::svcLocator()->service("JobOptionsSvc", jobSvc);

    PropertyMgr m_propMgr;

    // Phys.Rev.Lett.54.628, 1985
    m_propMgr.declareProperty("MinMass", m_minMass); // 1672 1642
    m_propMgr.declareProperty("MaxMass", m_maxMass); // 1672 1702
    m_propMgr.declareProperty("MaxChisq", m_maxChisq);

    m_propMgr.declareProperty("Use2ndVFit", m_use2ndVFit);
    m_propMgr.declareProperty("MaxVFitChisq", m_maxVFitChisq);

    m_propMgr.declareProperty("UseFlightSig", m_useFlightSig);
    m_propMgr.declareProperty("MinFlightSig", m_minFlightSig);

    jobSvc->setMyProperties("Omega", &m_propMgr);
}

bool BesStdSelector::Omega::operator()(CDDecay& aOmega)
{
    aOmega.setUserTag(3334);

    // Need the package HadronInfo
    OmegaInfo omegaInfo(aOmega);

    double mass = omegaInfo.m();
    if (mass < m_minMass || mass > m_maxMass) return false;
    if (omegaInfo.vtxChisq() > m_maxChisq) return false;

    if (m_use2ndVFit) {
        if (omegaInfo.chisq() > m_maxVFitChisq) return false;
    }

    if (m_useFlightSig) {
        if (omegaInfo.decayLengthRatio() < m_minFlightSig) return false;
    }

    aOmega.setP4(omegaInfo.p4()); // Update the p4 of Omega to vertex fitted!

    return true;
}

BesStdSelector::Omega omegaXiKSelectorOmega;
/* ===================================================================<<< */
/* ======================== Omega.cpp ends here ========================= */
