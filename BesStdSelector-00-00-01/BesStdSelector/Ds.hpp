/* <===<===<===<===<===<===<===<===<===~===>===>===>===>===>===>===>===>===>
 * File Name:    Ds.hpp
 * Author:       Xin-Xin MA, Hao-Kai SUN
 * Created:      2019-09-06 Fri 15:57:15 CST
 * <<=====================================>>
 * Last Updated: 2019-12-08 Sun 19:48:20 CST
 *           By: Hao-Kai SUN
 *     Update #: 42
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
#ifndef OMEGAXIK_SELECTOR_DS_HPP
#define OMEGAXIK_SELECTOR_DS_HPP

#include "OmegaXiKAlg/Namespace.hpp"
// #include "BesDChain/CDDecay.h"
// #include "DecayChain/Function/DCSelectionFunction.h"
#include "OmegaXiKAlg/selector/DCSFBase.hpp"

class OmegaXiKSLT::Ds : public DCSFDecay {
   public:
    Ds();

    inline void setBeamE(double ebeam) { m_Ecm = ebeam; }

    bool operator()(CDDecay& aDs);

   private:
    Ds(const Ds&);

    const Ds& operator=(const Ds&);

    double m_Ecm;

    bool m_useMassCut;
    double m_minMass;
    double m_maxMass;

    bool m_useRecCut;
    double m_minRecMass;
    double m_maxRecMass;

    bool m_useDeltaECut;
    double m_MinDeltaE;
    double m_MaxDeltaE;
};

extern OmegaXiKSLT::Ds omegaXiKSelectorDs;

#endif /* OMEGAXIK_SELECTOR_DS_HPP */
/* ===================================================================<<< */
/* ================ Ds.hpp ends here ================= */
