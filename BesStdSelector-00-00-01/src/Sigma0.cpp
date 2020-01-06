/* <===<===<===<===<===<===<===<===<===~===>===>===>===>===>===>===>===>===>
 * File Name:    Sigma0.cpp
 * Author:       Xin-Xin MA, Hao-Kai SUN <- Modified from Psi2StoHHHAlg
 * Created:      2019-10-21 Mon 19:07:28 CST
 * <<=====================================>>
 * Last Updated: 2019-12-11 Wed 14:00:33 CST
 *           By: Hao-Kai SUN
 *     Update #: 11
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

#include "EventModel/EventHeader.h"
#include "EventModel/EventModel.h"
#include "EvtRecEvent/EvtRecEvent.h"
#include "EvtRecEvent/EvtRecTrack.h"
#include "ParticleID/ParticleID.h"

#include "OmegaXiKAlg/selector/Sigma0.hpp"

BesStdSelector::Sigma0::Sigma0()
    : m_minMass(1.161)
    , m_maxMass(1.222)
    , m_minMassTight(1.179)
    , m_maxMassTight(1.203)
{
    IJobOptionsSvc* jobSvc;
    Gaudi::svcLocator()->service("JobOptionsSvc", jobSvc);

    PropertyMgr m_propMgr;

    m_propMgr.declareProperty("MinMass", m_minMass);
    m_propMgr.declareProperty("MaxMass", m_maxMass);
    m_propMgr.declareProperty("MinMassTight", m_minMassTight);
    m_propMgr.declareProperty("MaxMassTight", m_maxMassTight);

    jobSvc->setMyProperties("OmegaXiKSelectorSigma0", &m_propMgr);
}

bool BesStdSelector::Sigma0::operator()(CDDecay& aSigma0)
{
    aSigma0.setUserTag(1);
    double mass = aSigma0.mass();
    if ((mass <= m_minMass) || (mass >= m_maxMass)) return false;

    if (mass < m_minMassTight || mass > m_maxMassTight) aSigma0.setUserTag(2);

    return true;
}

BesStdSelector::Sigma0 omegaXiKSelectorSigma0;
/* ===================================================================<<< */
/* ======================== Sigma0.cpp ends here ======================== */
