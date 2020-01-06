/* <===<===<===<===<===<===<===<===<===~===>===>===>===>===>===>===>===>===>
 * File Name:    Kaon.hpp
 * Author:       Xin-Xin MA, Hao-Kai SUN
 * Created:      2019-09-07 Sat 11:21:03 CST
 * <<=====================================>>
 * Last Updated: 2019-11-30 Sat 18:48:00 CST
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
#ifndef BesStdSelector_KAON_HPP
#define BesStdSelector_KAON_HPP

#include "BesStdSelector/Namespace.hpp"
// #include "BesDChain/CDChargedKaon.h"
// #include "DecayChain/Function/DCSelectionFunction.h"
#include "BesStdSelector/selector/DCSFBase.hpp"

class BesStdSelector::Kaon : public DCSFKaon {
   public:
    Kaon(const std::string& JvcName = "OmegaXiKSelectorKaon",
         const double& VrCut = 1.0, const double& VzCut = 10.0);

    bool operator()(CDChargedKaon& aKaon);

    // RecMdcKalTrack::setPidType(RecMdcKalTrack::kaon);
    // class RecMdcKalTrack : public DstMdcKalTrack {};
    // DstMdcKalTrack::kaon = 3;
    void setPIDType(int type) { m_pidtype = type; }

   private:
    Kaon(const Kaon&);
    const Kaon& operator=(const Kaon&);

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
    bool m_rejectPion;
    bool m_rejectProton;

    bool m_useLikelihood;
    bool m_useNeuronNetwork;
    std::vector<double> m_neuronNetworkValCut;
};

extern BesStdSelector::Kaon omegaXiKSelectorKaonPrimary;
extern BesStdSelector::Kaon omegaXiKSelectorKaonAll;

#endif /* BesStdSelector_KAON_HPP */
/* ===================================================================<<< */
/* ========================= Kaon.hpp ends here ========================= */
