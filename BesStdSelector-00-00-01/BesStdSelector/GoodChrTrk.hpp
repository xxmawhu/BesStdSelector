/* <===<===<===<===<===<===<===<===<===~===>===>===>===>===>===>===>===>===>
 * File Name:    GoodChrTrk.hpp
 * Author:       Xin-Xin MA, Hao-Kai SUN
 * Created:      2019-09-07 Sat 18:24:11 CST
 * <<=====================================>>
 * Last Updated: 2019-11-18 Mon 20:10:00 CST
 *           By: Hao-Kai SUN
 *     Update #: 10
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
#ifndef OMEGAXIK_SELECTOR_GOODCHRTRK_HPP
#define OMEGAXIK_SELECTOR_GOODCHRTRK_HPP

#include "OmegaXiKAlg/Namespace.hpp"
// #include "BesDChain/CDElectron.h"
// #include "DecayChain/Function/DCSelectionFunction.h"
#include "OmegaXiKAlg/selector/DCSFBase.hpp"

class OmegaXiKSLT::GoodChrTrk : public DCSFElectron
{
  public:
    GoodChrTrk();

    bool operator()(CDElectron& aGCT);
    inline void setCharge(int chr) { m_charge = chr; }

  private:
    GoodChrTrk(const GoodChrTrk&);
    const GoodChrTrk& operator=(const GoodChrTrk&);

    int m_charge;

    double m_VrCut;
    double m_VzCut;
    double m_CosThetaCut;
};

extern OmegaXiKSLT::GoodChrTrk omegaXiKSelectorGoodChrTrk;

#endif /* OMEGAXIK_SELECTOR_GOODCHRTRK_HPP */
/* ===================================================================<<< */
/* ============ GoodChrTrk.hpp ends here ============= */
