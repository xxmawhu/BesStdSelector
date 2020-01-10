/* ====================================================
#   Copyright (C)2019 All rights reserved.
#
#   Author        : Xin-Xin MA
#   Email         : xxmawhu@163.com
#   File Name     : ElectronSelector.h
#   Created Time  : 2019-10-23 15:38
#   Last Modified : 2019-10-25 19:41
#   Describe      :
#
# ====================================================*/

#ifndef BeSelector_Electron_SELECTOR_H
#define BeSelector_Electron_SELECTOR_H

#include "BesDChain/CDElectron.h"
#include "DecayChain/Function/DCSelectionFunction.h"

class BeSelectorElectronSelector : public DCSelectionFunction<CDElectron> {

   public:
    BeSelectorElectronSelector();

    bool operator()(CDElectron &aEle);
    // inline void setcharge(int chr) { m_charge = chr; }

   private:
    BeSelectorElectronSelector(const BeSelectorElectronSelector &);
    const BeSelectorElectronSelector &operator=(
        const BeSelectorElectronSelector &);

    int m_charge;
    int m_pidtype;

    double m_VrCut;
    double m_VzCut;
    double m_CosThetaCut;

    double m_minEvP;

    bool m_PID;
    bool m_VCut;
    bool m_CutEvP;
};

extern BeSelectorElectronSelector electronSelector;

#endif
