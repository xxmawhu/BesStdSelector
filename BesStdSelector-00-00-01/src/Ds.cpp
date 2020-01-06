/* <===<===<===<===<===<===<===<===<===~===>===>===>===>===>===>===>===>===>
 * File Name:    Ds.cpp
 * Author:       Xin-Xin MA, Hao-Kai SUN
 * Created:      2019-10-19 Sat 16:05:50 CST
 * <<=====================================>>
 * Last Updated: 2019-12-11 Wed 13:47:36 CST
 *           By: Hao-Kai SUN
 *     Update #: 43
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
#include "CLHEP/Vector/LorentzVector.h"
#include "CLHEP/Vector/ThreeVector.h"

#include "GaudiKernel/Bootstrap.h"
#include "GaudiKernel/IJobOptionsSvc.h"
#include "GaudiKernel/ISvcLocator.h"
#include "GaudiKernel/PropertyMgr.h"

#include "OmegaXiKAlg/selector/Ds.hpp"

using CLHEP::Hep3Vector;
using CLHEP::HepLorentzVector;

OmegaXiKSLT::Ds::Ds()
    : m_Ecm(4.178 / 2.0)
    , m_useMassCut(false)
    , m_minMass(1.90)
    , m_maxMass(2.04)
    , m_useRecCut(true)
    , m_minRecMass(2.0)
    , m_maxRecMass(2.2)
{
    IJobOptionsSvc* jobSvc;
    Gaudi::svcLocator()->service("JobOptionsSvc", jobSvc);

    PropertyMgr m_propMgr;

    m_propMgr.declareProperty("UseMassCut", m_useMassCut);
    m_propMgr.declareProperty("MinMass", m_minMass);
    m_propMgr.declareProperty("MaxMass", m_maxMass);

    m_propMgr.declareProperty("UseRecMassCut", m_useRecCut);
    m_propMgr.declareProperty("MinRecMass", m_minRecMass);
    m_propMgr.declareProperty("MaxRecMass", m_maxRecMass);

    jobSvc->setMyProperties("OmegaXiKSelectorDs", &m_propMgr);
}

bool OmegaXiKSLT::Ds::operator()(CDDecay& aDs) {
    if (m_useMassCut) {
        double mass = aDs.mass();
        if (mass < m_minMass || mass > m_maxMass) return false;
    }

    if (m_useRecCut) {
        HepLorentzVector p4beam(0, 0, 0, m_Ecm);
        HepLorentzVector p4Ds = aDs.p4();
        p4Ds.boost(-0.011, 0, 0);
        double mrec = (p4beam - p4Ds).m();
        if (mrec < m_minRecMass || mrec > m_maxRecMass) return false;
    }

    return true;
}

OmegaXiKSLT::Ds omegaXiKSelectorDs;
/* ===================================================================<<< */
/* ========================== Ds.cpp ends here ========================== */
