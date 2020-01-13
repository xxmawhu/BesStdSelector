/* <===<===<===<===<===<===<===<===<===~===>===>===>===>===>===>===>===>===>
 * File Name:    Proton.hpp
 * Author:       Xin-Xin MA, Hao-Kai SUN
 * Created:      2019-10-21 Mon 18:49:10 CST
 * <<=====================================>>
 * Last Updated: 2019-12-01 Sun 15:38:40 CST
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
#ifndef BesStdSelector_PROTON_HPP
#define BesStdSelector_PROTON_HPP
#include <string>
#include "DecayChain/Function/DCSelectionFunction.h"
#include "BesDChain/CDProton.h"
#include "BesStdSelector/BesStdSelector.h"
using BesStdSelector::Proton;

class Proton : public DCSelectionFunction<CDProton> {
   public:
    Proton(const std::string& JvcName = "primaryProtonSelector",
           const double& VrCut = 1.0, const double& VzCut = 10.0);
    string getName(){
        return "test";
    }

    bool operator()(CDProton& aProton);

    // RecMdcKalTrack::setPidType(RecMdcKalTrack::proton);
    // class RecMdcKalTrack : public DstMdcKalTrack {};
    // DstMdcKalTrack::proton = 4;

    // It's not necessary to set the pid type
    // void setPIDType(int type) { m_pidtype = type; }

   private:
    Proton(const Proton&);
    const Proton& operator=(const Proton&);

    // int m_pidtype;

    bool m_useMag;
    double m_minMag;

    double m_VrCut;
    double m_VzCut;
    double m_CosThetaCut;

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
    bool m_rejectPionKaon;
    bool m_rejectElectron;

    bool m_useLikelihood;
    bool m_useNeuronNetwork;
    std::vector<double> m_neuronNetworkValCut;
};
#endif /* BesStdSelector_PROTON_HPP */
/* ===================================================================<<< */
/* ======================== Proton.hpp ends here ======================== */
