/* ====================================================
#   Copyright (C)2020 All rights reserved.
#
#   Author        : Xin-Xin MA
#   Email         : xxmawhu@163.com
#   File Name     : BesStdSelector.h
#   Create Time   : 2020-01-06 14:37
#   Last Modified : 2020-01-06 14:37
#   Describe      :
#
# ====================================================*/
#ifndef _BESSTDSELECTOR_H
#define _BESSTDSELECTOR_H
namespace BesStdSelector {
class GoodChrTrk;
class Photon;
class Electron;
class Kaon;
class Proton;
class Pion;

class Lambda;
class Ks;

class Pi0;
class EtatoGG;
class EtatoPiPiPi0;
class EtaP;

class Sigma0;
class CombinateParticle;

extern Proton primaryProton;
extern Proton secondaryProtonSelector;
extern Kaon primaryKaon;
extern Kaon secondaryKaonSelector;
extern Pion primaryPion;
extern Pion secondaryPionSelector;
extern Electron primaryElectron;
extern Electron secondaryElectronSelector;

extern CombinateParticle omegaSelector;
extern CombinateParticle Xi0Selector;
extern CombinateParticle XipSelector;
extern CombinateParticle Sigma0Selector;
extern CombinateParticle SimgapSelector;
extern CombinateParticle OmegaSelector;
}
#endif  // _BESSTDSELECTOR_H
