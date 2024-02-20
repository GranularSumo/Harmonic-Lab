/*
  ==============================================================================

    SvgPathManager.cpp
    Created: 15 Feb 2024 3:54:58pm
    Author:  zeush

  ==============================================================================
*/

#include "SvgPathManager.h"

void SvgPathManager::setCurrentPath(PathType newPath)
{
    currentPath = newPath;
    repaint();
}

SvgPathManager::PathType SvgPathManager::getPath(int index)
{
    switch (index)
    {
    case 1: return SvgPathManager::softclip;
    case 2: return SvgPathManager::brokenSoftclip;
    case 3: return SvgPathManager::hardclip;
    case 4: return SvgPathManager::wavefold;
    case 5: return SvgPathManager::feedbackWavefold;
    case 6: return SvgPathManager::asymetricSoftclip;
    case 7: return SvgPathManager::biasShape;
    case 8: return SvgPathManager::biasFold;
    case 9: return SvgPathManager::foldCrush;
    case 10: return SvgPathManager::dualPathBitFold;
    case 11: return SvgPathManager::bitcrush;
    case 12: return SvgPathManager::squarefold;
    case 13: return SvgPathManager::downsample;
    default:
        break;
    }
}


void SvgPathManager::paint(juce::Graphics& g)
{

    auto bounds = getLocalBounds();

    // draws the box around the pathSelector
    g.setColour(juce::Colour::fromString("#ff222939"));
    g.fillRect(bounds.toFloat());

    // Draw lines based on the component's local bounds
    g.setColour(juce::Colour::fromString("#ff1F2127"));
    g.drawLine(0, 0, bounds.getWidth(), 0); // Top horizontal line
    g.drawLine(0, 1, bounds.getWidth(), 1);
    g.setColour(juce::Colour::fromString("#ff47526D"));
    g.drawLine(0, bounds.getHeight(), bounds.getWidth(), bounds.getHeight()); // Bottom horizontal line


    switch (currentPath)
    {
    case SvgPathManager::sine:
        drawSine(g);
        break;
    case SvgPathManager::softclip:
        drawSoftclip(g);
        break;
    case SvgPathManager::brokenSoftclip:
        drawBrokenSoftclip(g);
        break;
    case SvgPathManager::hardclip:
        drawHardclip(g);
        break;
    case SvgPathManager::wavefold:
        drawWavefold(g);
        break;
    case SvgPathManager::feedbackWavefold:
        drawFeedbackWavefold(g);
        break;

    case SvgPathManager::asymetricSoftclip:
        drawAsymetricSoftclip(g);
        break;
    case SvgPathManager::biasShape:
        drawBiasShape(g);
        break;
    case SvgPathManager::biasFold:
        drawBiasFold(g);
        break;
    case SvgPathManager::foldCrush:
        drawFoldcrush(g);
        break;
    case SvgPathManager::dualPathBitFold:
        drawDualPathBitfold(g);
        break;
    case SvgPathManager::bitcrush:
        drawBitcrush(g);
        break;
    case SvgPathManager::squarefold:
        drawSquarefold(g);
        break;
    case SvgPathManager::downsample:
        drawDownsample(g);
        break;
    default:
        break;
    }
}

void SvgPathManager::drawPath(juce::Graphics& g, const unsigned char* pathData, size_t dataSize)
{

    juce::Path path;
    path.loadPathFromData(pathData, dataSize);

    auto compBounds = getLocalBounds().toFloat();
    const float padding = compBounds.getHeight() * 0.2f;
    juce::Rectangle<float> adjustedBounds = compBounds.reduced(padding);
    auto pathBounds = path.getBounds();

    float scaleX = adjustedBounds.getWidth() / pathBounds.getWidth();
    float scaleY = adjustedBounds.getHeight() / pathBounds.getHeight();
    float scale = std::min(scaleX, scaleY);

    float translateX = adjustedBounds.getX() + (adjustedBounds.getWidth() - (pathBounds.getWidth() * scale)) / 2 - (pathBounds.getX() * scale);
    float translateY = adjustedBounds.getY() + (adjustedBounds.getHeight() - (pathBounds.getHeight() * scale)) / 2 - (pathBounds.getY() * scale);

    juce::AffineTransform transform = juce::AffineTransform::scale(scale).translated(translateX, translateY);
    path.applyTransform(transform);

    g.setColour(juce::Colours::white);
    juce::PathStrokeType strokeType(3.0f);
    g.strokePath(path, strokeType);
}

void SvgPathManager::drawSine(juce::Graphics& g)
{
    static const unsigned char pathData[] = { 110,109,40,214,148,64,196,28,154,66,98,3,122,224,64,204,245,140,66,34,176,13,65,70,107,126,66,146,230,74,65,253,112,102,66,98,164,231,90,65,142,51,96,66,208,87,123,65,76,80,88,66,50,67,142,65,34,233,92,66,98,209,133,166,65,33,225,100,66,64,0,176,65,189,
45,115,66,24,156,187,65,196,92,127,66,98,82,196,221,65,168,225,147,66,212,150,240,65,38,113,169,66,1,73,12,66,92,25,189,66,98,235,226,16,66,171,211,192,66,15,251,21,66,70,11,198,66,24,80,32,66,152,119,198,66,98,206,177,42,66,113,226,197,66,71,180,47,
66,145,161,192,66,96,87,52,66,28,215,188,66,98,224,184,74,66,39,195,166,66,124,152,83,66,188,60,142,66,200,159,105,66,197,45,112,66,98,169,101,110,66,25,51,104,66,7,80,115,66,68,55,93,66,188,7,126,66,252,134,91,66,98,147,36,132,66,21,242,91,66,185,192,
134,66,57,71,102,66,106,7,137,66,27,146,109,66,98,28,90,146,66,122,215,136,66,25,252,150,66,62,157,156,66,62,97,158,66,194,96,175,66,98,227,158,161,66,57,233,182,66,137,48,164,66,6,88,191,66,78,169,170,66,218,13,197,66,98,164,144,173,66,55,177,199,66,
191,8,178,66,13,46,198,66,190,27,180,66,77,95,195,66,98,7,42,187,66,68,176,186,66,127,55,190,66,3,215,175,66,29,23,194,66,134,177,165,66,98,1,113,195,66,130,215,161,66,191,191,196,66,12,250,157,66,241,14,198,66,195,28,154,66,101,0,0 };

    drawPath(g, pathData, sizeof(pathData));
}

void SvgPathManager::drawSoftclip(juce::Graphics& g)
{
    static const unsigned char pathData[] = { 110,109,195,160,215,66,93,50,152,66,98,169,207,216,66,113,21,140,66,164,32,216,66,7,196,126,66,245,89,220,66,134,166,103,66,98,233,255,222,66,225,151,90,66,182,135,230,66,243,87,88,66,128,153,236,66,52,217,87,66,98,237,236,242,66,159,196,87,66,49,19,
250,66,76,71,87,66,219,77,255,66,47,190,95,66,98,87,105,2,67,175,42,107,66,126,57,2,67,81,12,125,66,244,196,2,67,76,237,133,66,98,212,171,3,67,6,32,151,66,42,80,3,67,15,177,168,66,184,57,5,67,116,156,185,66,98,70,194,5,67,22,253,190,66,36,1,8,67,98,245,
194,66,46,156,10,67,242,177,195,66,98,33,65,14,67,113,232,196,66,57,37,18,67,48,30,197,66,177,169,21,67,99,137,194,66,98,166,64,25,67,244,146,191,66,221,165,25,67,23,76,182,66,76,26,26,67,189,138,175,66,98,192,64,27,67,193,216,156,66,211,203,26,67,70,
191,137,66,114,191,28,67,52,142,110,66,98,223,60,29,67,119,185,99,66,3,100,31,67,54,36,91,66,189,9,34,67,210,138,89,66,98,12,173,37,67,212,237,86,66,236,141,41,67,105,150,86,66,53,23,45,67,9,111,91,66,98,200,154,48,67,171,158,96,66,96,53,49,67,186,69,
114,66,250,159,49,67,10,99,127,66,98,30,222,50,67,94,209,146,66,41,87,50,67,10,99,166,66,86,93,52,67,208,72,185,66,98,50,222,52,67,168,168,190,66,106,8,55,67,21,216,194,66,147,167,57,67,7,162,195,66,98,46,75,61,67,24,237,196,66,128,44,65,67,33,26,197,
66,48,181,68,67,54,168,194,66,98,241,68,72,67,36,250,191,66,184,208,72,67,152,246,182,66,244,61,73,67,211,82,176,66,98,236,183,73,67,225,79,168,66,75,238,73,67,47,63,160,66,159,47,74,67,92,50,152,66,101,0,0 };

    drawPath(g, pathData, sizeof(pathData));
}

void SvgPathManager::drawBrokenSoftclip(juce::Graphics& g)
{
    static const unsigned char pathData[] = { 110,109,140,131,53,193,204,214,18,194,98,66,200,36,193,62,148,48,194,104,181,29,193,168,227,57,194,148,208,21,193,160,143,60,194,98,9,70,17,193,25,25,62,194,18,215,8,193,28,72,66,194,225,18,3,193,166,219,69,194,98,67,16,221,192,38,153,82,194,186,73,206,
192,78,223,85,194,241,102,192,192,10,80,85,194,98,162,169,184,192,48,0,85,194,112,84,178,192,123,170,85,194,112,84,178,192,122,202,86,194,98,112,84,178,192,97,5,91,194,248,86,141,192,178,236,97,194,88,181,114,192,170,108,97,194,98,136,81,89,192,89,27,
97,194,9,65,75,192,34,201,97,194,9,65,75,192,51,84,99,194,98,9,65,75,192,217,165,100,194,21,153,54,192,134,102,102,194,249,89,29,192,65,57,103,194,98,229,26,4,192,252,11,104,194,110,220,195,191,48,225,105,194,250,208,162,191,237,75,107,194,98,100,109,
125,191,59,216,108,194,202,154,220,190,115,223,109,194,96,235,3,62,115,223,109,194,98,139,32,36,63,115,223,109,194,120,100,179,63,102,37,110,194,202,198,232,63,229,122,110,194,98,208,252,19,64,27,224,110,194,85,235,36,64,148,137,110,194,85,235,36,64,
214,130,109,194,98,85,235,36,64,154,150,108,194,91,83,54,64,22,39,108,194,165,232,78,64,212,117,108,194,98,152,63,102,64,151,192,108,194,177,141,128,64,214,46,108,194,172,176,133,64,172,45,107,194,98,184,111,144,64,168,19,105,194,134,6,177,64,162,158,
101,194,38,190,193,64,209,206,100,194,98,60,27,200,64,185,127,100,194,8,210,213,64,17,233,97,194,22,56,224,64,69,14,95,194,98,218,166,234,64,23,49,92,194,245,207,251,64,140,221,89,194,208,64,3,65,140,221,89,194,98,50,149,8,65,140,221,89,194,133,241,12,
65,24,191,88,194,133,241,12,65,252,96,87,194,98,133,241,12,65,6,149,84,194,158,221,23,65,154,65,78,194,5,15,44,65,153,91,69,194,98,174,224,66,65,90,77,59,194,78,234,79,65,247,140,45,194,51,165,97,65,58,214,12,194,98,46,200,113,65,63,32,222,193,231,201,
134,65,47,162,173,193,84,201,143,65,47,162,173,193,98,89,166,145,65,47,162,173,193,173,44,147,65,84,252,170,193,173,44,147,65,215,191,167,193,98,173,44,147,65,90,131,164,193,115,230,148,65,12,79,161,193,119,2,151,65,242,160,160,193,98,108,30,153,65,216,
242,159,193,65,216,154,65,113,74,157,193,65,216,154,65,242,184,154,193,98,65,216,154,65,114,39,152,193,247,110,157,65,212,136,149,193,243,152,160,65,173,230,148,193,98,239,194,163,65,137,68,148,193,165,89,166,65,167,235,145,193,165,89,166,65,102,175,
143,193,98,165,89,166,65,110,96,141,193,119,224,168,65,242,158,139,193,224,50,172,65,242,158,139,193,98,169,152,175,65,242,158,139,193,233,252,178,65,211,42,137,193,183,74,180,65,31,196,133,193,98,188,202,181,65,106,218,129,193,222,77,184,65,228,67,128,
193,195,221,187,65,113,250,128,193,98,54,204,190,65,175,144,129,193,51,50,193,65,152,60,129,193,51,50,193,65,144,63,128,193,98,51,50,193,65,1,26,124,193,33,71,216,65,98,32,124,193,29,235,222,65,169,67,128,193,98,29,142,225,65,101,35,129,193,44,112,229,
65,253,75,129,193,43,140,231,65,234,157,128,193,98,32,168,233,65,161,223,127,193,245,97,235,65,43,67,129,193,245,97,235,65,12,144,131,193,98,245,97,235,65,236,220,133,193,166,161,237,65,250,49,136,193,72,97,240,65,215,190,136,193,98,234,32,243,65,180,
75,137,193,97,136,249,65,98,171,142,193,130,156,254,65,232,175,148,193,98,82,216,1,66,111,180,154,193,139,154,4,66,221,160,159,193,160,111,5,66,221,160,159,193,98,184,68,6,66,221,160,159,193,14,243,6,66,92,236,160,193,14,243,6,66,134,129,162,193,98,14,
243,6,66,176,22,164,193,218,1,9,66,173,106,172,193,185,133,11,66,72,3,181,193,98,83,61,18,66,130,248,203,193,246,46,20,66,96,16,220,193,6,25,26,66,47,215,22,194,98,10,117,28,66,225,30,39,194,48,10,33,66,3,87,58,194,79,182,36,66,107,91,67,194,98,57,134,
40,66,172,183,76,194,239,179,43,66,192,56,83,194,148,72,45,66,125,229,84,194,98,91,20,46,66,100,189,85,194,112,90,47,66,148,232,87,194,57,29,48,66,62,183,89,194,98,2,224,48,66,232,133,91,194,228,163,50,66,2,59,93,194,99,9,52,66,147,130,93,194,98,229,
110,53,66,36,202,93,194,92,152,55,66,49,60,96,194,78,215,56,66,203,241,98,194,98,67,22,58,66,101,167,101,194,22,226,59,66,227,222,103,194,40,213,60,66,227,222,103,194,98,57,200,61,66,227,222,103,194,21,143,62,66,252,131,104,194,21,143,62,66,198,77,105,
194,98,21,143,62,66,143,23,106,194,230,72,64,66,208,5,107,194,226,100,66,66,57,95,107,194,98,222,128,68,66,161,184,107,194,172,58,70,66,152,121,108,194,172,58,70,66,6,12,109,194,98,172,58,70,66,116,158,109,194,196,119,71,66,201,214,109,194,79,251,72,
66,52,137,109,194,98,218,126,74,66,157,59,109,194,48,19,76,66,179,132,109,194,212,125,76,66,151,43,110,194,98,213,1,77,66,47,250,110,194,130,80,78,66,185,204,110,194,103,150,80,66,41,157,109,194,98,123,108,82,66,237,167,108,194,54,186,84,66,72,223,107,
194,235,180,85,66,72,223,107,194,98,165,175,86,66,72,223,107,194,195,124,87,66,161,39,107,194,195,124,87,66,42,71,106,194,98,195,124,87,66,179,102,105,194,133,23,89,66,2,119,104,194,142,13,91,66,133,50,104,194,98,238,143,93,66,227,218,103,194,211,95,
95,66,202,7,102,194,101,43,97,66,231,9,98,194,98,147,146,98,66,64,235,94,194,224,217,100,66,167,1,92,194,163,59,102,66,4,145,91,194,98,102,157,103,66,97,32,91,194,216,190,104,66,4,119,89,194,216,190,104,66,198,223,87,194,98,216,190,104,66,135,72,86,194,
187,155,105,66,27,180,84,194,189,169,106,66,13,93,84,194,98,183,183,107,66,0,6,84,194,162,148,108,66,58,50,82,194,162,148,108,66,142,77,80,194,98,162,148,108,66,227,104,78,194,90,83,109,66,86,220,76,194,117,60,110,66,86,220,76,194,98,143,37,111,66,86,
220,76,194,188,235,112,66,18,12,74,194,193,45,114,66,190,155,70,194,98,195,111,115,66,107,43,67,194,236,64,117,66,84,198,62,194,113,55,118,66,139,215,60,194,98,13,165,120,66,233,247,55,194,160,87,125,66,168,220,31,194,154,202,126,66,162,214,16,194,98,
159,180,128,66,164,91,235,193,109,46,133,66,12,162,171,193,201,175,135,66,12,162,171,193,98,83,35,136,66,12,162,171,193,216,129,136,66,223,33,169,193,216,129,136,66,113,19,166,193,98,216,129,136,66,2,5,163,193,2,30,137,66,146,179,158,193,226,220,137,
66,233,122,156,193,98,195,155,138,66,65,66,154,193,15,93,139,66,42,200,149,193,108,138,139,66,11,136,146,193,98,201,183,139,66,236,71,143,193,105,90,140,66,25,159,140,193,201,243,140,66,25,159,140,193,98,41,141,141,66,25,159,140,193,50,126,143,66,238,
93,137,193,77,68,145,66,155,99,133,193,98,105,10,147,66,74,105,129,193,47,126,149,66,134,35,122,193,88,183,150,66,26,123,119,193,98,1,159,152,66,141,87,115,193,132,47,153,66,12,212,115,193,18,166,154,66,103,222,122,193,98,152,150,155,66,216,99,127,193,
5,163,156,66,244,245,128,193,144,250,156,66,70,63,128,193,98,23,82,157,66,47,17,127,193,185,153,157,66,31,238,127,193,185,153,157,66,186,52,129,193,98,185,153,157,66,104,114,130,193,199,118,158,66,21,36,133,193,246,132,159,66,86,49,135,193,98,55,191,
161,66,249,133,139,193,205,49,166,66,187,53,158,193,60,110,168,66,34,162,172,193,98,96,115,171,66,28,29,192,193,149,217,173,66,97,47,225,193,58,83,175,66,149,213,5,194,98,160,32,176,66,172,94,5,194,190,102,177,66,250,200,4,194,206,76,177,66,99,213,3,
194,98,52,71,174,66,232,117,186,193,186,9,173,66,44,158,167,193,236,253,169,66,56,160,152,193,98,102,139,169,66,208,108,150,193,99,191,168,66,73,120,143,193,119,56,168,66,127,43,137,193,98,124,177,167,66,181,222,130,193,53,153,166,66,207,18,118,193,130,
201,165,66,137,134,111,193,98,207,249,164,66,67,250,104,193,221,79,164,66,251,153,97,193,221,79,164,66,88,34,95,193,98,221,79,164,66,182,170,92,193,49,170,163,66,119,242,87,193,178,223,162,66,92,165,84,193,98,52,21,162,66,62,88,81,193,135,111,161,66,
109,105,73,193,135,111,161,66,110,4,67,193,98,135,111,161,66,157,20,59,193,214,175,160,66,224,87,53,193,120,19,159,66,64,240,48,193,98,62,199,157,66,190,99,45,193,116,116,156,66,184,11,39,193,151,34,156,66,77,215,34,193,98,136,41,155,66,96,12,22,193,
19,24,152,66,52,115,25,193,252,76,151,66,107,51,40,193,108,240,153,150,66,168,52,53,193,108,183,167,149,66,131,51,41,193,98,139,34,149,66,73,153,34,193,96,135,148,66,60,89,28,193,5,79,148,66,216,79,27,193,98,201,122,147,66,119,104,23,193,18,31,146,66,
123,186,37,193,218,10,146,66,118,52,51,193,98,107,250,145,66,205,36,62,193,95,204,145,66,59,122,63,193,48,56,145,66,227,75,57,193,98,215,126,144,66,227,143,49,193,25,116,144,66,43,148,49,193,139,94,143,66,161,8,58,193,98,89,194,142,66,177,202,62,193,
140,66,142,66,254,218,68,193,140,66,142,66,46,130,71,193,98,140,66,142,66,96,41,74,193,21,158,141,66,222,84,78,193,17,213,140,66,98,198,80,193,98,72,69,139,66,111,162,85,193,27,196,134,66,180,72,135,193,133,172,133,66,240,159,149,193,98,250,75,133,66,
155,147,154,193,66,132,132,66,188,58,162,193,175,240,131,66,141,161,166,193,98,37,72,130,66,77,75,179,193,155,235,128,66,118,14,199,193,54,184,127,66,35,220,225,193,98,38,236,118,66,73,131,40,194,82,32,116,66,170,67,53,194,177,73,112,66,124,77,55,194,
98,183,77,111,66,74,211,55,194,139,127,110,66,118,94,57,194,139,127,110,66,162,187,58,194,98,139,127,110,66,160,206,62,194,231,14,107,66,89,186,67,194,222,44,98,66,73,92,76,194,98,49,76,94,66,250,32,80,194,3,80,86,66,28,126,84,194,239,5,84,66,50,24,84,
194,98,55,167,82,66,53,219,83,194,21,188,81,66,197,181,84,194,21,188,81,66,200,56,86,194,98,21,188,81,66,86,156,87,194,47,223,80,66,121,6,89,194,48,209,79,66,134,93,89,194,98,51,195,78,66,147,180,89,194,72,230,77,66,36,72,89,194,72,230,77,66,139,108,
88,194,98,72,230,77,66,120,143,86,194,7,201,74,66,125,88,86,194,180,106,73,66,102,29,88,194,98,150,209,72,66,93,227,88,194,80,100,72,66,22,185,88,194,87,76,72,66,155,174,87,194,98,240,54,72,66,155,193,86,194,199,107,70,66,139,182,85,194,202,79,68,66,
34,93,85,194,98,206,51,66,66,186,3,85,194,0,122,64,66,84,71,84,194,0,122,64,66,121,186,83,194,98,0,122,64,66,160,45,83,194,47,192,62,66,136,3,83,194,51,164,60,66,241,92,83,194,98,235,98,57,66,234,230,83,194,105,206,56,66,248,138,83,194,105,206,56,66,
19,253,80,194,98,105,206,56,66,86,85,79,194,240,240,55,66,60,179,77,194,55,226,54,66,244,91,77,194,98,137,171,52,66,62,165,76,194,5,77,45,66,14,137,68,194,5,77,45,66,26,208,66,194,98,5,77,45,66,153,45,66,194,23,16,44,66,126,61,64,194,188,140,42,66,166,
129,62,194,98,191,56,36,66,108,65,55,194,139,179,31,66,70,14,37,194,50,45,26,66,6,43,249,193,98,233,42,24,66,83,188,219,193,192,5,22,66,213,206,194,193,216,104,21,66,238,197,193,193,98,240,203,20,66,5,189,192,193,44,102,19,66,170,111,184,193,213,77,18,
66,231,82,175,193,98,126,53,17,66,36,54,166,193,150,156,15,66,170,211,157,193,42,193,14,66,244,176,156,193,98,192,229,13,66,63,142,155,193,52,187,11,66,131,108,147,193,215,240,9,66,224,158,138,193,98,125,38,8,66,61,209,129,193,146,143,5,66,204,211,111,
193,177,47,4,66,144,57,105,193,98,211,207,2,66,87,159,98,193,208,29,0,66,76,145,85,193,171,100,252,65,206,54,76,193,98,182,141,248,65,81,220,66,193,179,4,244,65,48,53,59,193,158,80,242,65,48,53,59,193,98,148,156,240,65,48,53,59,193,198,55,239,65,188,
129,56,193,198,55,239,65,159,52,53,193,98,198,55,239,65,129,231,49,193,0,126,237,65,13,52,47,193,252,97,235,65,13,52,47,193,98,2,70,233,65,13,52,47,193,50,140,231,65,151,128,44,193,50,140,231,65,122,51,41,193,98,50,140,231,65,243,184,35,193,95,39,226,
65,130,160,33,193,167,84,213,65,182,31,34,193,98,172,177,210,65,237,57,34,193,105,137,208,65,128,181,32,193,105,137,208,65,180,192,30,193,98,105,137,208,65,149,169,22,193,129,199,192,65,41,198,27,193,202,169,188,65,24,51,37,193,98,183,66,186,65,159,179,
42,193,145,216,182,65,13,52,47,193,67,19,181,65,13,52,47,193,98,245,77,179,65,13,52,47,193,11,219,177,65,254,205,50,193,11,219,177,65,206,52,55,193,98,11,219,177,65,160,155,59,193,69,33,176,65,145,53,63,193,65,5,174,65,145,53,63,193,98,76,233,171,65,
145,53,63,193,119,47,170,65,79,180,66,193,119,47,170,65,224,249,70,193,98,119,47,170,65,113,63,75,193,53,183,168,65,210,176,79,193,79,235,166,65,96,217,80,193,98,110,31,165,65,237,1,82,193,53,165,160,65,60,145,91,193,49,248,156,65,213,23,102,193,98,45,
75,153,65,108,158,112,193,55,220,147,65,171,231,126,193,42,229,144,65,133,235,130,193,98,34,238,141,65,53,99,134,193,82,124,139,65,162,227,138,193,120,118,139,65,120,236,140,193,98,83,112,139,65,78,245,142,193,172,253,136,65,230,204,148,193,60,5,134,
65,4,232,153,193,98,220,180,123,65,234,241,167,193,131,79,99,65,248,182,218,193,197,135,81,65,243,213,9,194,98,187,229,60,65,26,226,42,194,141,237,45,65,246,136,56,194,37,12,24,65,68,66,62,194,98,185,240,17,65,64,219,63,194,146,241,12,65,218,247,65,194,
146,241,12,65,154,243,66,194,98,146,241,12,65,91,239,67,194,3,126,9,65,143,4,69,194,250,69,5,65,155,91,69,194,98,12,14,1,65,168,178,69,194,196,52,251,64,207,76,71,194,196,52,251,64,13,235,72,194,98,196,52,251,64,228,181,74,194,197,218,243,64,52,195,75,
194,4,101,232,64,51,156,75,194,98,93,12,222,64,254,120,75,194,154,54,211,64,121,95,76,194,28,81,208,64,100,156,77,194,98,188,107,205,64,79,217,78,194,150,236,193,64,155,220,79,194,13,197,182,64,155,220,79,194,98,126,157,171,64,155,220,79,194,74,40,158,
64,182,252,80,194,255,220,152,64,216,92,82,194,98,195,145,147,64,250,188,83,194,172,3,133,64,21,221,84,194,196,9,113,64,21,221,84,194,98,66,12,88,64,21,221,84,194,229,153,67,64,26,55,85,194,229,153,67,64,27,165,85,194,98,229,153,67,64,29,19,86,194,136,
73,19,64,140,105,86,194,62,121,176,63,45,101,86,194,98,210,125,233,62,198,96,86,194,112,23,153,190,118,250,85,194,16,45,153,190,193,129,85,194,98,55,67,153,190,11,9,85,194,97,129,31,191,158,232,84,194,103,96,130,191,178,57,85,194,98,29,0,181,191,196,
138,85,194,114,107,222,191,142,75,85,194,114,107,222,191,51,173,84,194,98,114,107,222,191,218,14,84,194,204,211,15,192,88,40,82,194,116,177,55,192,18,116,80,194,98,206,219,128,192,253,73,77,194,148,250,180,192,11,88,70,194,208,99,201,192,71,219,65,194,
98,131,165,207,192,38,123,64,194,166,182,217,192,204,231,62,194,207,194,223,192,242,90,62,194,98,112,152,241,192,144,187,60,194,110,180,14,193,145,4,47,194,143,7,23,193,158,216,37,194,98,72,70,27,193,95,43,33,194,58,83,32,193,117,196,27,194,217,64,34,
193,122,215,25,194,98,115,46,36,193,126,234,23,194,242,221,44,193,88,188,9,194,224,141,53,193,246,168,244,193,99,101,0,0 };

    drawPath(g, pathData, sizeof(pathData));
}

void SvgPathManager::drawHardclip(juce::Graphics& g)
{
    static const unsigned char pathData[] = { 110,109,115,244,212,66,119,70,19,67,98,243,51,213,66,35,121,11,67,95,198,212,66,121,137,3,67,48,88,213,66,193,164,247,66,98,78,97,226,66,217,92,247,66,19,114,239,66,170,156,247,66,223,125,252,66,133,135,247,66,98,212,94,255,66,87,151,247,66,220,34,1,
67,74,104,247,66,109,145,2,67,244,168,247,66,98,212,213,2,67,67,78,5,67,102,163,2,67,114,244,14,67,203,184,2,67,81,127,24,67,98,158,213,2,67,240,141,30,67,250,134,2,67,124,186,36,67,152,232,2,67,190,182,42,67,98,166,55,7,67,147,225,42,67,211,142,11,67,
208,187,42,67,174,224,15,67,77,201,42,67,98,108,136,19,67,175,186,42,67,171,53,23,67,204,226,42,67,152,218,26,67,111,181,42,67,98,71,31,27,67,189,239,31,67,157,237,26,67,162,13,21,67,84,3,27,67,230,60,10,67,98,116,22,27,67,146,114,5,67,3,226,26,67,1,
150,0,67,116,37,27,67,222,174,247,66,98,95,4,31,67,164,83,247,66,184,235,34,67,56,164,247,66,132,205,38,67,9,135,247,66,98,61,229,42,67,4,162,247,66,85,2,47,67,29,87,247,66,66,23,51,67,66,172,247,66,98,212,120,51,67,252,164,1,67,25,42,51,67,218,164,7,
67,206,70,51,67,105,134,13,67,98,224,91,51,67,120,62,23,67,190,42,51,67,214,16,33,67,19,110,51,67,101,184,42,67,98,173,145,56,67,127,224,42,67,178,186,61,67,244,188,42,67,52,224,66,67,94,201,42,67,98,19,177,69,67,170,191,42,67,68,132,72,67,126,218,42,
67,232,83,75,67,139,186,42,67,98,38,156,75,67,53,5,35,67,34,102,75,67,61,17,27,67,198,133,75,67,116,70,19,67,101,0,0 };

    drawPath(g, pathData, sizeof(pathData));
}

void SvgPathManager::drawBitcrush(juce::Graphics& g)
{
    static const unsigned char pathData[] = { 110,109,32,246,222,66,221,1,86,67,98,220,127,223,66,42,1,83,67,19,61,222,66,1,47,79,67,26,164,223,66,246,157,76,67,98,122,41,225,66,246,157,76,67,219,174,226,66,234,157,76,67,59,52,228,66,246,157,76,67,98,13,190,228,66,68,157,73,67,18,123,227,66,34,203,
69,67,47,226,228,66,5,58,67,67,98,216,169,230,66,20,58,67,67,127,113,232,66,243,57,67,67,38,57,234,66,15,58,67,67,98,102,195,234,66,118,57,64,67,100,127,233,66,19,103,60,67,38,231,234,66,17,214,57,67,98,19,73,243,66,77,214,57,67,25,171,251,66,20,214,
57,67,130,6,2,67,41,214,57,67,98,170,75,2,67,148,214,60,67,139,169,1,67,143,169,64,67,134,93,2,67,247,57,67,67,98,129,65,3,67,27,58,67,67,125,37,4,67,248,57,67,67,122,9,5,67,15,58,67,67,98,111,78,5,67,171,58,70,67,207,172,4,67,33,13,74,67,129,96,5,67,
236,157,76,67,98,81,35,6,67,247,157,76,67,32,230,6,67,239,157,76,67,240,168,7,67,246,157,76,67,98,213,237,7,67,166,158,79,67,90,76,7,67,230,112,83,67,247,255,7,67,221,1,86,67,98,205,194,8,67,218,1,86,67,164,133,9,67,230,1,86,67,122,72,10,67,221,1,86,
67,98,117,141,10,67,127,2,89,67,196,235,9,67,234,212,92,67,129,159,10,67,200,101,95,67,98,118,131,11,67,195,101,95,67,107,103,12,67,215,101,95,67,95,75,13,67,195,101,95,67,98,152,144,13,67,82,102,98,67,124,238,12,67,200,56,102,67,115,162,13,67,179,201,
104,67,98,67,220,17,67,118,201,104,67,44,22,22,67,178,201,104,67,251,79,26,67,154,201,104,67,98,38,149,26,67,45,201,101,67,6,243,25,67,73,246,97,67,2,167,26,67,210,101,95,67,98,248,138,27,67,194,101,95,67,239,110,28,67,205,101,95,67,230,82,29,67,195,
101,95,67,98,229,151,29,67,38,101,92,67,73,246,28,67,182,146,88,67,247,169,29,67,230,1,86,67,98,197,108,30,67,217,1,86,67,148,47,31,67,223,1,86,67,98,242,31,67,220,1,86,67,98,72,55,32,67,46,1,83,67,203,149,31,67,232,46,79,67,105,73,32,67,245,157,76,67,
98,57,12,33,67,246,157,76,67,9,207,33,67,231,157,76,67,216,145,34,67,245,157,76,67,98,202,214,34,67,75,157,73,67,54,53,34,67,3,203,69,67,235,232,34,67,4,58,67,67,98,222,204,35,67,20,58,67,67,209,176,36,67,240,57,67,67,195,148,37,67,14,58,67,67,98,236,
217,37,67,121,57,64,67,211,55,37,67,1,103,60,67,214,235,37,67,16,214,57,67,98,159,37,42,67,76,214,57,67,117,95,46,67,18,214,57,67,61,153,50,67,40,214,57,67,98,92,222,50,67,157,214,60,67,110,60,50,67,104,169,64,67,65,240,50,67,248,57,67,67,98,56,212,51,
67,23,58,67,67,48,184,52,67,250,57,67,67,40,156,53,67,14,58,67,67,98,20,225,53,67,178,58,70,67,143,63,53,67,2,13,74,67,49,243,53,67,235,157,76,67,98,2,182,54,67,244,157,76,67,211,120,55,67,239,157,76,67,165,59,56,67,245,157,76,67,98,139,128,56,67,163,
158,79,67,14,223,55,67,232,112,83,67,165,146,56,67,220,1,86,67,98,117,85,57,67,218,1,86,67,69,24,58,67,228,1,86,67,20,219,58,67,220,1,86,67,98,9,32,59,67,126,2,89,67,104,126,58,67,227,212,92,67,29,50,59,67,195,101,95,67,98,21,22,60,67,200,101,95,67,14,
250,60,67,213,101,95,67,6,222,61,67,195,101,95,67,98,43,35,62,67,89,102,98,67,28,129,61,67,187,56,102,67,12,53,62,67,184,201,104,67,98,144,102,66,67,118,201,104,67,40,152,70,67,181,201,104,67,172,201,74,67,155,201,104,67,98,211,14,75,67,51,201,101,67,
192,108,74,67,72,246,97,67,179,32,75,67,221,101,95,67,98,171,4,76,67,181,101,95,67,165,232,76,67,216,101,95,67,158,204,77,67,196,101,95,67,98,154,17,78,67,45,101,92,67,230,111,77,67,161,146,88,67,172,35,78,67,231,1,86,67,98,194,238,78,67,217,1,86,67,
217,185,79,67,222,1,86,67,240,132,80,67,221,1,86,67,101,0,0 };

    drawPath(g, pathData, sizeof(pathData));
}

void SvgPathManager::drawSquarefold(juce::Graphics& g)
{
    static const unsigned char pathData[] = { 110,109,168,252,221,66,122,77,135,67,108,41,172,225,66,122,77,135,67,108,41,172,225,66,178,150,137,67,108,19,107,227,66,178,150,137,67,108,19,107,227,66,57,142,122,67,108,85,116,235,66,57,142,122,67,108,134,72,237,66,62,83,130,67,108,48,136,1,67,62,83,
130,67,108,48,136,1,67,21,83,132,67,108,218,156,2,67,21,83,132,67,108,218,156,2,67,45,185,122,67,108,248,76,5,67,45,185,122,67,108,248,76,5,67,154,235,118,67,108,178,26,6,67,154,235,118,67,108,178,26,6,67,2,124,135,67,108,134,181,8,67,2,124,135,67,108,
134,181,8,67,14,74,133,67,108,146,230,9,67,14,74,133,67,108,146,230,9,67,109,155,145,67,108,152,114,13,67,109,155,145,67,108,155,85,14,67,76,143,140,67,108,186,71,25,67,76,143,140,67,108,186,71,25,67,238,164,138,67,108,3,64,26,67,238,164,138,67,108,3,
64,26,67,175,76,145,67,108,42,62,29,67,175,76,145,67,108,42,62,29,67,189,108,147,67,108,19,26,30,67,189,108,147,67,108,19,26,30,67,28,106,135,67,108,49,202,32,67,28,106,135,67,108,49,202,32,67,42,138,137,67,108,59,251,33,67,42,138,137,67,108,59,251,33,
67,125,199,122,67,108,201,99,37,67,125,199,122,67,108,131,49,38,67,222,43,130,67,108,160,35,49,67,222,43,130,67,108,160,35,49,67,21,83,132,67,108,219,98,50,67,21,83,132,67,108,219,98,50,67,178,163,122,67,108,49,111,53,67,178,163,122,67,108,49,111,53,
67,235,249,118,67,108,26,75,54,67,235,249,118,67,108,26,75,54,67,243,98,135,67,108,105,9,57,67,243,98,135,67,108,105,9,57,67,135,95,133,67,108,82,229,57,67,135,95,133,67,108,82,229,57,67,228,108,145,67,108,162,134,61,67,228,108,145,67,108,162,134,61,
67,156,157,140,67,108,24,42,73,67,156,157,140,67,108,24,42,73,67,237,164,138,67,108,3,6,74,67,237,164,138,67,108,124,12,75,67,161,119,145,67,108,207,53,77,67,161,119,145,67,108,207,53,77,67,121,119,147,67,108,218,102,78,67,121,119,147,67,108,218,102,
78,67,216,116,135,67,108,174,1,81,67,216,116,135,67,101,0,0 };

    drawPath(g, pathData, sizeof(pathData));
}

void SvgPathManager::drawWavefold(juce::Graphics& g)
{
    static const unsigned char pathData[] = { 110,109,201,201,175,64,87,223,33,67,108,164,58,33,65,204,106,9,67,98,164,58,33,65,204,106,9,67,56,82,99,65,91,220,27,67,207,2,139,65,164,145,27,67,98,141,92,164,65,239,70,27,67,138,147,200,65,53,0,10,67,138,147,200,65,53,0,10,67,108,90,80,10,66,167,143,
58,67,98,90,80,10,66,167,143,58,67,44,55,23,66,118,192,41,67,55,15,39,66,145,164,40,67,98,79,231,54,66,174,136,39,67,162,215,69,66,63,248,58,67,162,215,69,66,63,248,58,67,108,46,222,107,66,114,196,9,67,98,46,222,107,66,114,196,9,67,243,254,120,66,134,
175,27,67,116,165,132,66,164,145,27,67,98,110,203,140,66,196,115,27,67,175,207,147,66,99,211,9,67,175,207,147,66,99,211,9,67,108,16,124,166,66,183,128,58,67,98,16,124,166,66,183,128,58,67,145,123,172,66,145,164,40,67,108,50,181,66,117,194,40,67,98,67,
233,189,66,85,224,40,67,160,121,196,66,107,203,58,67,160,121,196,66,107,203,58,67,108,0,0,207,66,187,122,31,67,101,0,0 };

    drawPath(g, pathData, sizeof(pathData));
}

void SvgPathManager::drawFeedbackWavefold(juce::Graphics& g)
{
    static const unsigned char pathData[] = { 110,109,39,32,2,65,94,105,89,67,108,219,149,14,65,60,126,69,67,108,173,77,50,65,205,189,79,67,108,118,131,88,65,135,113,67,67,108,188,127,136,65,206,41,79,67,98,188,127,136,65,206,41,79,67,9,41,138,65,186,244,76,67,166,91,154,65,46,2,77,67,98,70,142,
170,65,159,15,77,67,146,55,172,65,228,162,79,67,146,55,172,65,228,162,79,67,108,118,113,205,65,156,86,67,67,108,80,203,225,65,110,223,79,67,108,232,60,243,65,129,119,69,67,108,244,173,0,66,101,3,110,67,108,60,6,10,66,52,162,99,67,108,91,41,19,66,75,144,
111,67,108,209,38,35,66,190,222,99,67,98,209,38,35,66,190,222,99,67,244,91,35,66,186,228,101,67,197,20,44,66,186,228,101,67,98,145,205,52,66,186,228,101,67,56,162,53,66,97,0,100,67,56,162,53,66,97,0,100,67,108,56,193,67,66,168,184,111,67,108,79,35,78,
66,167,175,99,67,108,202,113,86,66,31,10,110,67,108,199,32,94,66,221,85,69,67,108,143,217,102,66,18,183,79,67,108,220,49,112,66,156,160,67,67,108,128,37,127,66,158,95,79,67,98,128,37,127,66,158,95,79,67,201,139,129,66,68,123,77,67,78,36,132,66,137,116,
77,67,98,212,188,134,66,219,109,77,67,222,181,136,66,64,129,79,67,222,181,136,66,64,129,79,67,108,112,127,144,66,226,153,67,67,108,82,123,149,66,180,216,79,67,108,142,162,153,66,107,72,69,67,108,118,95,157,66,31,10,110,67,108,114,214,161,66,144,128,99,
67,108,233,236,166,66,168,184,111,67,108,39,76,174,66,144,202,99,67,98,39,76,174,66,144,202,99,67,121,182,174,66,209,201,101,67,75,248,178,66,233,248,101,67,98,26,58,183,66,254,39,102,67,4,191,183,66,237,242,99,67,4,191,183,66,237,242,99,67,108,107,83,
191,66,30,198,111,67,108,145,255,195,66,191,148,99,67,108,71,198,200,66,78,30,110,67,108,172,34,205,66,95,65,88,67,101,0,0 };

    drawPath(g, pathData, sizeof(pathData));
}

void SvgPathManager::drawAsymetricSoftclip(juce::Graphics& g)
{
    static const unsigned char pathData[] = { 110,109,41,252,204,66,201,57,29,194,98,139,89,205,66,164,35,60,194,104,1,206,66,150,2,97,194,125,110,210,66,4,205,115,194,98,225,244,213,66,165,153,129,194,218,65,226,66,120,164,121,194,21,64,231,66,138,150,113,194,98,6,152,242,66,152,141,99,194,190,
235,254,66,36,162,88,194,55,33,5,67,153,215,74,194,98,56,36,9,67,130,99,61,194,248,123,8,67,222,99,39,194,213,1,9,67,201,100,20,194,98,255,202,9,67,6,210,242,193,231,54,10,67,216,93,188,193,197,26,11,67,153,159,134,193,98,81,11,14,67,18,125,69,193,87,
186,18,67,24,116,158,193,185,210,19,67,86,157,182,193,98,210,195,23,67,254,251,250,193,222,47,23,67,100,11,36,194,180,96,24,67,176,156,72,194,98,44,55,25,67,238,60,89,194,116,160,24,67,29,168,116,194,177,133,27,67,92,230,122,194,98,181,117,31,67,173,
29,128,194,64,248,34,67,217,78,113,194,237,143,38,67,219,163,108,194,98,105,184,43,67,36,233,97,194,171,28,49,67,118,94,88,194,2,208,53,67,58,152,74,194,98,136,74,58,67,211,219,54,194,36,247,57,67,15,136,26,194,4,124,58,67,103,168,1,194,98,87,28,59,67,
7,29,217,193,246,107,59,67,235,114,174,193,11,69,60,67,205,146,132,193,98,50,71,63,67,166,102,71,193,224,11,67,67,82,114,162,193,203,155,68,67,86,174,181,193,98,42,0,72,67,0,125,227,193,157,199,71,67,66,90,12,194,116,136,72,67,118,215,37,194,101,0,0 };

    drawPath(g, pathData, sizeof(pathData));
}

void SvgPathManager::drawBiasShape(juce::Graphics& g)
{
    static const unsigned char pathData[] = { 110,109,2,233,88,67,42,177,12,194,98,6,68,89,67,28,220,40,194,76,34,89,67,80,182,69,194,250,26,92,67,40,253,96,194,98,63,84,95,67,32,69,114,194,100,174,103,67,227,80,96,194,164,75,108,67,141,204,91,194,98,9,112,113,67,194,158,82,194,141,225,120,67,127,
195,75,194,205,147,122,67,13,52,58,194,98,154,29,126,67,64,43,13,194,220,217,125,67,22,214,188,193,71,13,129,67,76,14,71,193,98,94,110,130,67,202,153,6,193,120,28,131,67,40,57,122,193,62,65,131,67,224,122,137,193,98,90,159,132,67,42,210,239,193,171,195,
132,67,92,212,43,194,4,71,134,67,185,225,94,194,98,6,61,135,67,229,241,112,194,64,99,139,67,122,175,100,194,201,94,141,67,38,97,94,194,98,83,71,144,67,110,44,84,194,20,180,147,67,44,33,76,194,8,197,149,67,24,155,60,194,98,113,169,151,67,241,99,41,194,
13,28,151,67,119,199,18,194,230,149,151,67,61,196,251,193,98,207,11,152,67,64,130,199,193,103,231,151,67,62,119,145,193,38,101,153,67,230,15,62,193,98,232,41,155,67,234,93,29,193,102,13,155,67,15,80,132,193,44,113,155,67,11,139,144,193,98,130,26,156,
67,209,121,196,193,121,114,156,67,132,218,248,193,15,225,156,67,82,140,22,194,101,0,0 };

    drawPath(g, pathData, sizeof(pathData));
}

void SvgPathManager::drawBiasFold(juce::Graphics& g)
{
    static const unsigned char pathData[] = { 110,109,156,134,163,67,132,202,246,193,98,195,207,163,67,119,33,25,194,233,24,164,67,172,221,54,194,15,98,164,67,226,153,84,194,98,175,145,164,67,62,104,95,194,149,168,165,67,195,212,108,194,0,56,166,67,203,174,91,194,98,166,48,167,67,175,184,75,194,
192,14,168,67,102,77,59,194,52,236,168,67,238,227,42,194,98,111,160,169,67,178,234,58,194,203,157,171,67,180,216,76,194,226,186,173,67,196,149,68,194,98,59,134,175,67,166,133,60,194,55,156,176,67,3,140,44,194,56,133,177,67,181,127,29,194,98,238,158,178,
67,90,60,44,194,164,184,179,67,254,248,58,194,89,210,180,67,163,181,73,194,98,218,157,182,67,56,16,33,194,42,39,184,67,214,144,236,193,89,248,183,67,158,115,148,193,98,171,53,184,67,158,81,130,193,193,167,183,67,112,59,35,193,159,146,184,67,69,49,38,
193,98,11,123,187,67,191,12,115,193,198,92,188,67,248,177,188,193,209,53,188,67,148,75,249,193,98,50,65,188,67,222,248,25,194,162,48,188,67,38,79,55,194,214,6,188,67,226,153,84,194,98,88,80,188,67,216,147,96,194,69,223,189,67,14,29,110,194,233,99,190,
67,90,148,90,194,98,75,89,191,67,70,243,74,194,162,51,192,67,12,218,58,194,18,12,193,67,246,189,42,194,98,145,249,193,67,15,254,55,194,191,221,195,67,206,36,82,194,73,205,197,67,17,117,65,194,98,40,83,199,67,143,101,53,194,61,137,200,67,36,186,38,194,
149,183,201,67,64,36,24,194,98,75,202,202,67,66,244,40,194,1,221,203,67,68,196,57,194,183,239,204,67,68,148,74,194,98,46,82,206,67,241,240,49,194,54,248,207,67,196,63,25,194,195,105,208,67,28,125,251,193,98,162,114,208,67,121,244,193,193,59,100,208,67,
10,107,136,193,97,90,208,67,0,199,29,193,98,99,67,211,67,150,238,126,193,35,234,211,67,144,23,204,193,101,235,211,67,125,134,7,194,101,0,0 };

    drawPath(g, pathData, sizeof(pathData));
}

void SvgPathManager::drawFoldcrush(juce::Graphics& g)
{
    static const unsigned char pathData[] = { 110,109,60,135,218,67,54,233,240,193,108,129,151,218,67,217,99,38,194,108,90,143,220,67,224,75,35,194,108,173,246,220,67,34,10,102,194,108,146,183,221,67,253,1,65,194,108,249,49,222,67,188,53,102,194,108,172,217,222,67,233,72,59,194,108,86,130,223,67,
76,163,94,194,108,126,56,224,67,30,254,51,194,108,16,77,225,67,212,234,86,194,98,16,77,225,67,212,234,86,194,16,149,225,67,78,46,63,194,167,214,226,67,119,4,62,194,98,62,24,228,67,159,218,60,194,152,97,228,67,217,22,74,194,152,97,228,67,217,22,74,194,
108,77,15,229,67,92,216,29,194,108,247,51,230,67,150,218,66,194,108,35,207,230,67,109,179,26,194,108,75,114,231,67,12,1,63,194,108,252,247,231,67,16,140,22,194,108,9,155,232,67,147,244,54,194,108,214,0,233,67,87,59,229,193,108,35,168,234,67,108,28,236,
193,108,82,40,235,67,210,168,36,193,108,105,127,242,67,61,234,175,193,108,110,71,242,67,216,99,38,194,108,218,137,244,67,132,154,33,194,108,144,159,244,67,119,241,101,194,108,1,71,245,67,40,183,63,194,108,41,7,246,67,191,19,102,194,108,24,132,246,67,
42,120,59,194,108,198,17,247,67,74,163,94,194,108,71,247,247,67,112,39,51,194,108,196,11,249,67,145,84,86,194,98,196,11,249,67,145,84,86,194,104,178,249,67,207,164,62,194,144,132,250,67,202,250,61,194,98,184,86,251,67,196,80,61,194,105,201,251,67,246,
127,73,194,105,201,251,67,246,127,73,194,108,193,255,252,67,217,214,29,194,108,38,202,253,67,244,194,66,194,108,177,61,254,67,224,234,24,194,108,188,20,255,67,68,112,63,194,108,239,121,255,67,139,45,22,194,108,210,32,0,68,63,21,55,194,108,170,37,0,68,
84,73,224,193,108,150,56,1,68,65,3,234,193,108,66,95,1,68,34,86,33,193,108,56,251,4,68,146,105,173,193,108,138,251,4,68,243,218,0,194,101,0,0 };

    drawPath(g, pathData, sizeof(pathData));
}

void SvgPathManager::drawDualPathBitfold(juce::Graphics& g)
{
    static const unsigned char pathData[] = { 110,109,167,66,8,68,146,163,240,193,98,167,66,8,68,146,163,240,193,158,5,9,68,40,24,94,194,233,119,9,68,215,114,96,194,98,52,234,9,68,129,205,98,194,21,34,10,68,150,153,19,194,124,69,11,68,242,197,22,194,98,227,104,12,68,75,242,25,194,216,19,13,68,66,
194,68,194,216,19,13,68,66,194,68,194,98,216,19,13,68,66,194,68,194,226,29,14,68,33,115,163,193,198,56,14,68,88,17,114,193,98,170,83,14,68,100,60,29,193,132,123,14,68,26,70,57,193,132,123,14,68,26,70,57,193,98,132,123,14,68,26,70,57,193,27,22,16,68,206,
110,142,193,235,61,17,68,167,206,155,193,98,187,101,18,68,117,46,169,193,3,199,19,68,191,238,185,193,3,199,19,68,191,238,185,193,98,3,199,19,68,191,238,185,193,200,54,20,68,128,138,87,194,64,3,21,68,14,98,94,194,98,184,207,21,68,158,57,101,194,5,173,
21,68,171,63,21,194,62,21,23,68,108,164,22,194,98,119,125,24,68,42,9,24,194,221,212,24,68,104,32,69,194,221,212,24,68,104,32,69,194,98,221,212,24,68,104,32,69,194,11,195,25,68,177,129,226,193,174,212,25,68,6,119,160,193,98,80,230,25,68,191,216,60,193,
214,43,26,68,145,147,60,193,214,43,26,68,145,147,60,193,98,214,43,26,68,145,147,60,193,63,103,26,68,243,122,116,193,73,207,28,68,4,76,151,193,98,84,55,31,68,137,90,180,193,189,195,31,68,74,217,184,193,189,195,31,68,74,217,184,193,108,120,245,31,68,102,
225,32,194,101,0,0 };

    drawPath(g, pathData, sizeof(pathData));

}

void SvgPathManager::drawDownsample(juce::Graphics& g)
{
    static const unsigned char pathData[] = { 110,109,214,86,134,64,178,176,134,67,108,127,53,143,64,245,16,128,67,108,99,74,186,64,245,16,128,67,108,99,74,186,64,86,123,124,67,108,16,11,242,64,86,123,124,67,108,16,11,242,64,163,91,121,67,108,14,254,197,65,163,91,121,67,108,14,254,197,65,242,238,
124,67,108,88,63,212,65,242,238,124,67,108,88,63,212,65,245,16,128,67,108,197,166,223,65,245,16,128,67,108,197,166,223,65,50,200,142,67,108,103,44,239,65,50,200,142,67,108,103,44,239,65,132,38,146,67,108,196,66,250,65,132,38,146,67,108,196,66,250,65,
93,182,147,67,108,192,169,66,66,93,182,147,67,108,192,169,66,66,226,28,146,67,108,118,93,72,66,226,28,146,67,108,118,93,72,66,127,102,144,67,108,139,151,77,66,127,102,144,67,108,139,151,77,66,220,235,132,67,108,137,62,84,66,220,235,132,67,108,137,62,
84,66,248,132,124,67,108,88,234,96,66,248,132,124,67,108,88,234,96,66,139,120,121,67,108,149,209,143,66,139,120,121,67,108,149,209,143,66,199,190,124,67,108,173,234,149,66,199,190,124,67,108,173,234,149,66,178,176,134,67,108,161,244,153,66,178,176,134,
67,108,161,244,153,66,132,38,146,67,108,113,249,159,66,132,38,146,67,108,113,249,159,66,0,192,147,67,108,199,227,191,66,0,192,147,67,108,199,227,191,66,132,38,146,67,108,30,50,197,66,132,38,146,67,108,30,50,197,66,236,180,142,67,108,41,174,200,66,236,
180,142,67,108,41,174,200,66,202,147,134,67,101,0,0 };

    drawPath(g, pathData, sizeof(pathData));
}
