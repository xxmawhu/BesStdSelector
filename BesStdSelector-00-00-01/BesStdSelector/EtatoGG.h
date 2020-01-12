/* <===<===<===<===<===<===<===<===<===~===>===>===>===>===>===>===>===>===>
 * File Name:    EtatoGG.hpp
 * Author:       Xin-Xin MA, Hao-Kai SUN
 * Created:      2019-09-07 Sat 18:16:44 CST
 * <<=====================================>>
 * Last Updated: 2019-11-18 Mon 19:32:18 CST
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
#ifndef BesStdSelector_ETATOGG_HPP
#define BesStdSelector_ETATOGG_HPP

#include "BesDChain/CDEta.h"
#include "DecayChain/Function/DCSelectionFunction.h"
#include "BesStdSelector/BesStdSelector.h"

class BesStdSelector::EtatoGG : public DCSelectionFunction<CDEta> {
   public:
    EtatoGG();

    bool operator()(CDEta& aEta);

   private:
    EtatoGG(const EtatoGG&);
    const EtatoGG& operator=(const EtatoGG&);

    double m_minMass;
    double m_maxMass;
    double m_maxChisq;
};

#endif /* BesStdSelector_ETATOGG_HPP */
/* ===================================================================<<< */
/* ============== EtatoGG.hpp ends here ============== */
