/* <===<===<===<===<===<===<===<===<===~===>===>===>===>===>===>===>===>===>
 * File Name:    Pi0.cpp
 * Author:       Xin-Xin MA, Hao-Kai SUN <- Modified from Psi2StoHHHAlg
 * Created:      2019-10-21 Mon 17:17:51 CST
 * <<=====================================>>
 * Last Updated: 2019-12-11 Wed 13:58:31 CST
 *           By: Hao-Kai SUN
 *     Update #: 14
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
#include "EvtRecEvent/EvtRecPi0.h"

#include "GaudiKernel/Bootstrap.h"
#include "GaudiKernel/IJobOptionsSvc.h"
#include "GaudiKernel/ISvcLocator.h"
#include "GaudiKernel/PropertyMgr.h"

#include "BesStdSelector/Pi0.h"

BesStdSelector::Pi0::Pi0() {
    IJobOptionsSvc* jobSvc;
    Gaudi::svcLocator()->service("JobOptionsSvc", jobSvc);

    PropertyMgr m_propMgr;

    /*
     * BESIII standard pi0 selection requirement:
     *   M(pi0) > 0.115 GeV and M(pi0) < 0.150 GeV, chi^2 < 200
     *
     * usually, we perform such cut directly in the programme. Hence, we will
     * lose the side-band region of pi0. If you want study the effect caused by
     * the background of pi0 meson, please loose the cut on mass and chisq.
     * May be use the below lose cut:
     *   M(pi0) > 0.098 GeV and M(pi0) < 0.165 GeV, chi^2 < 2500
     *
     * The pi0 reconstruction efficiency could be found in the link
     * https://hnbes3.ihep.ac.cn//HyperNews/get/AUX/2016/09/29/22.27-95277-pi0eff_v4.pdf
     */
    m_propMgr.declareProperty("MinMass", m_minMass = 0.115);
    m_propMgr.declareProperty("MaxMass", m_maxMass = 0.150);
    m_propMgr.declareProperty("MaxChisq", m_maxChisq = 200.0);
    m_propMgr.declareProperty("CutOnMag", m_CutOnMag = false);
    m_propMgr.declareProperty("MinP4Rho", m_minRho = 0.0);

    jobSvc->setMyProperties("Pi0Selector", &m_propMgr);
}

bool BesStdSelector::Pi0::operator()(CDPi0& aPi0) {
    EvtRecPi0* pi0 = const_cast<EvtRecPi0*>(aPi0.navPi0());
    // The `CDPi0` also has a member named mass, which is the mass of pi0 after
    // 1C fit.However,  after 1C, the mass will become a constant,
    //  i.e 0.13497...
    // So we must use the unconstraint mass from `EvtRecPi0`
    double mass = pi0->unconMass();
    double chi2 = pi0->chisq();
    if ((mass <= m_minMass) || (mass >= m_maxMass) || (chi2 >= m_maxChisq))
        return false;

    // rho() is a member function of HepLorentzVector, return the magnitude of
    // the momentum, i.e rho() = sqrt(px^2 + py^2 + pz^2)
    if (m_CutOnMag) {
        if (aPi0.p4().rho() < m_minRho) return false;
    }
    return true;
}

BesStdSelector::Pi0 pi0Selector;
/* ===================================================================<<< */
/* ========================= Pi0.cpp ends here ========================== */
