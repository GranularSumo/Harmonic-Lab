/*
  ==============================================================================

    Parameters.cpp
    Created: 20 Feb 2024 12:57:47pm
    Author:  zeush

  ==============================================================================
*/

#include "Parameters.h"


Dsp::Algorithm parameterInfo::indexToAlgorithm(int index)
{
    switch (index)
    {
    case 0: return Dsp::Algorithm::softclip;
    case 1: return Dsp::Algorithm::brokenSoftclip;
    case 2: return Dsp::Algorithm::hardclip;
    case 3: return Dsp::Algorithm::wavefold;
    case 4: return Dsp::Algorithm::foldback;
    case 5: return Dsp::Algorithm::asymetricSoftclip;
    case 6: return Dsp::Algorithm::biasShape;
    case 7: return Dsp::Algorithm::biasFold;
    case 8: return Dsp::Algorithm::foldCrush;
    case 9: return Dsp::Algorithm::dualPathBitFold;
    case 10: return Dsp::Algorithm::bitcrush;
    case 11: return Dsp::Algorithm::squarefold;
    case 12: return Dsp::Algorithm::downsample;

    default:
        break;
    }
}
