/* <===<===<===<===<===<===<===<===<===~===>===>===>===>===>===>===>===>===>
 * File Name:    Pion.hpp
 * Author:       Xin-Xin MA, Hao-Kai SUN
 * Created:      2019-10-21 Mon 17:21:51 CST
 * <<=====================================>>
 * Last Updated: 2019-11-30 Sat 18:41:21 CST
 *           By: Hao-Kai SUN
 *     Update #: 12
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
#ifndef OMEGAXIK_SELECTOR_PION_HPP
#define OMEGAXIK_SELECTOR_PION_HPP

#include "OmegaXiKAlg/Namespace.hpp"
// #include "BesDChain/CDChargedPion.h"
// #include "DecayChain/Function/DCSelectionFunction.h"
#include "OmegaXiKAlg/selector/DCSFBase.hpp"

class OmegaXiKSLT::Pion : public DCSFPion {
   public:
    Pion(const std::string& JvcName = "OmegaXiKSelectorPion",
         const double& VrCut = 1.0, const double& VzCut = 10.0);

    bool operator()(CDChargedPion& aPion);

    // RecMdcKalTrack::setPidType(RecMdcKalTrack::pion);
    // class RecMdcKalTrack : public DstMdcKalTrack {};
    // DstMdcKalTrack::pion = 2;
    void setPIDType(int type) { m_pidtype = type; }

   private:
    Pion(const Pion&);
    const Pion& operator=(const Pion&);

    int m_pidtype;

    bool m_useMag;
    double m_minMag;

    double m_VrCut;
    double m_VzCut;
    double m_CosThetaCut;

    bool m_useSimplePID;
    bool m_usePID;

    bool m_useDedx;
    bool m_useTof1;
    bool m_useTof2;
    bool m_useTofE;
    bool m_useTofQ;
    bool m_useEmc;
    bool m_useMuc;
    bool m_useTof;
    bool m_useTofC;
    bool m_useTofCorr;

    bool m_usePIDProb;
    double m_minPIDProb;
    bool m_rejectKaon;
    bool m_rejectProton;

    bool m_useLikelihood;
    bool m_useNeuronNetwork;
    std::vector<double> m_neuronNetworkValCut;
};

extern OmegaXiKSLT::Pion omegaXiKSelectorPionPrimary;
extern OmegaXiKSLT::Pion omegaXiKSelectorPionAll;

#endif /* OMEGAXIK_SELECTOR_PION_HPP */
/* ===================================================================<<< */
/* ========================= Pion.hpp ends here ========================= */
