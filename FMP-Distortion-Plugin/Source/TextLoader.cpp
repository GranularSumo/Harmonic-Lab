/*
  ==============================================================================

    TextLoader.cpp
    Created: 7 Feb 2024 10:45:59am
    Author:  zeush

  ==============================================================================
*/

#include "TextLoader.h"

void TextLoader::setAlgorithm(juce::String algorithm)
{
    if (algorithm == "Softclipper")
    {
        algorithmDescription =  "This is the Softclipper algorithm.\n\n"
                                "Softclipping effectively compresses the dynamic range of the signal, and creates a warmer sound. "
                                "When a sine wave is input, the output will exhibit a fuller, rounded sound with added harmonics, but without the abrupt clipping "
                                "or intense distortions that can make a sound feel overly aggressive or digitally distorted. "
                                "In this process, some odd-order harmonics are introduced, mainly in the low mids which is where the 'warmth' comes from. "
                                "As you increase the drive it will introduce some of these odd - order harmonics higher up the register. "
                                "The Softclipper algorithm is a simple, yet effective, distortion algorithm that is used in many guitar pedals and audio processors.\n\n "

   
            					"Characteristics of Audio Output:\n\n"
                                "1. Produces a warmer, smoother distortion compared to hard clipping.\n"
                                "2. Adds harmonics in a subtle manner, enriching the sound without overwhelming it.\n"
                                "3. Retains musical dynamics to a greater extent, preventing the harshness typical of more extreme distortion.\n\n"

                                "Ideal For:\n\n"
                                "Anything requiring a subtle, warm distortion to enhance body and presence without sacrificing tone quality.\n\n"
                                "Drums, where a touch of saturation can add warmth and depth without overpowering the mix.\n\n"
                                "Bass lines that need to be thickened up without losing clarity or becoming muddy.\n\n"
                                "Vocals or other melodic content where a touch of saturation is desired to add character and depth, without introducing unwanted artifacts or overpowering the mix.\n\n";
    }
    else if (algorithm == "Broken Softclipper")
    {
        algorithmDescription = "This is the Broken Softclipper Algorithm.\n\n"
                                "The Broken Softclipper takes the concept of soft clipping and adds a layer of complexity and randomness by blending in white noise with the original signal. "
                                "This isn't an algorithm that you will probably come across in other distortion plugins as I created it to emulate a sound design trick that I frequently do to add an analogue feel to digital synths. "
                                "The result combines the warmth and smoothness of soft clipping with the textured, unpredictable character of white noise.\n\n"

                                "Characteristics of Audio Output:\n\n"
                                "1. Adds a layer of texture and randomness to the distortion, creating a more complex and unique sound.\n"
                                "2. Retains the warmth and smoothness of soft clipping, while adding a layer of grit and character.\n"
                                "3. The white noise component can add a sense of space and depth to the sound, making it feel more organic and alive.\n\n"

                                "Ideal For:\n\n"
                                "Adding lofi or analogue style character.\n\n"
                                "Creating unique, textured sounds that stand out in a mix.\n\n"
                                "Adding warmth to the low-end whilst also bringing out energy in the high-end";
    }
    else if (algorithm == "Hardclipper")
    {
        algorithmDescription = "This is the Hardclip Algorithm.\n\n"
                                "Hardclipping essentially cuts off the top and bottom of the input signal, creating a flat line on the top and bottom of the waveform. as you increase the drive the input signal gets louder and as a result, " 
                                "more of the top and bottom get cut off, effectively turning a simple sine wave into a square wave. "
                                "This introduces a lot of odd-oder harmonics to the signal, and it does not do this in a subtle way at all, creating a very raw and loud tone that adds a lot of high end to the sound.\n\n"

                                "Characteristics of Audio Output:\n\n"
                                "1. Produces a raw, aggressive distortion with a lot of odd-order harmonics.\n"
                                "2. The sound is very loud and in your face, with a lot of energy and presence.\n"
                                "3. The distortion is very noticeable and can be quite harsh, making it ideal for aggressive, high-energy music.\n\n"

                                "Ideal For:\n\n"
                                "Creating a raw, aggressive tone.\n\n"
                                "Adding a lot of high-end energy to a sound, making it stand out in a mix.\n\n"
                                "Creating a very loud, in-your-face sound that demands attention.\n\n";
    }
    else if (algorithm == "Wavefolder")
    {
		algorithmDescription = "This is the Wavefolder Algorithm.\n\n"
								"The Wavefolder algorithm is a complex distortion algorithm that is capable of creating a wide range of unique and interesting sounds. "
								"It works by folding the waveform back on itself, creating a series of peaks and troughs that add a lot of harmonics to the signal. "
								"The result is a sound that is rich and complex, with a lot of movement and character. "
								"The Wavefolder is capable of creating a wide range of sounds, from subtle, warm distortion to wild, unpredictable textures.\n\n"

								"Characteristics of Audio Output:\n\n"
								"1. Produces a rich, complex sound with a lot of movement and character.\n"
								"2. The sound can range from subtle, warm distortion to wild, unpredictable textures.\n"
								"3. The Wavefolder is capable of creating a wide range of unique and interesting sounds.\n\n"

								"Ideal For:\n\n"
								"Creating unique, textured sounds that stand out in a mix.\n\n"
								"Adding warmth and character to a sound.\n\n"
								"Creating unpredictable, evolving textures that add depth and movement to a mix.\n\n";
	}
    else if (algorithm == "Foldback")
    {
        algorithmDescription = "This is the Foldback Algorithm.\n\n"
                                "The Foldback is an innovative distortion algorithm that intricately blends "
                                "wavefolding and soft clipping effects with a feedback mechanism. "
                                "This process introduces feedback from the output back into the input, "
                                "enriching the sound with complex harmonics and textures. The effect ranges from "
                                "subtle nuances to intense, richly textured soundscapes, making the Foldback "
                                "algorithm a versatile tool for creative sound design. Its ability to dynamically "
                                "alter the audio signal provides a wide palette of sonic possibilities, from "
                                "evolving textures to intricate harmonic layers.\n\n"

                                "Characteristics of Audio Output:\n\n"
                                "1. Delivers a dynamic, richly textured sound with complex harmonics.\n"
                                "2. Offers a spectrum of effects, from subtle textural nuances to intense, "
                                "rich soundscapes.\n"
                                "3. Perfect for creating a wide range of unique and engaging sounds, adding "
                                "depth and movement to the audio.\n\n"

                                "Ideal For:\n\n"
                                "Sound designers and musicians seeking innovative sound textures and dynamic "
                                "sonic landscapes.\n\n"
                                "Enhancing electronic music and experimental compositions with unique, "
                                "evolving character.\n\n"
                                "Adding complexity and a distinctive edge to a variety of sounds, ensuring they "
                                "stand out in a mix with unparalleled depth.\n\n";
    }
    else if (algorithm == "Assymetric Softclipper")
    {
        algorithmDescription = "This is the Assymetric Soft Clipper Algorithm.\n\n"
                                "The Assymetric Soft Clipper takes a novel approach to distortion by adding a "
                                "slight twist to the traditional soft clipping process. It introduces a "
                                "dcOffset, or a constant shift, before the signal undergoes soft clipping and "
                                "then subtracts this offset after the process. This adjustment creates an "
                                "assymetry in how the audio signal is processed, leading to a unique distortion "
                                "character that differs from symmetric soft clipping. The effect enriches the "
                                "sound with a distinctive warmth and depth, adding subtle complexity to the "
                                "harmonics without introducing harshness.\n\n"

                                "Characteristics of Audio Output:\n\n"
                                "1. Produces a warm, nuanced distortion with a unique tonal character.\n"
                                "2. Enhances the audio with subtle asymmetrical harmonics, adding depth.\n"
                                "3. Offers a fresh take on soft clipping, ideal for a variety of musical "
                                "styles and instruments.\n\n"

                                "Ideal For:\n\n"
                                "Musicians and producers looking for a subtle, yet distinctive, distortion "
                                "effect.\n\n"
                                "Adding character to guitars, keyboards, and other melodic instruments without "
                                "overpowering their natural sound.\n\n"
                                "Creative sound design, where nuanced textures and tonal complexity can "
                                "significantly impact the overall audio experience.\n\n";
    }
    else if (algorithm == "Bias Shaper")
    {
        algorithmDescription = "This is the Bias Shaper Algorithm.\n\n"
                                "The Bias Shaper is a dynamic distortion effect that applies a unique form of "
                                "processing to the audio signal. It intelligently alters its approach based on "
                                "the signal's amplitude. For signals exceeding a certain level, it applies a "
                                "standard soft clipping. However, for quieter signals, it introduces a bias "
                                "adjustment before soft clipping, shifting the signal upwards, then subtracts "
                                "this bias post-clipping. This technique creates a variable distortion effect "
                                "that adapts to the input signal, offering a richer, more complex sound than "
                                "traditional distortion methods.\n\n"

                                "Characteristics of Audio Output:\n\n"
                                "1. Yields a versatile distortion effect that varies with the input signal's "
                                "amplitude.\n"
                                "2. For louder signals, it provides a straightforward soft clipping warmth.\n"
                                "3. Quieter signals are enriched with additional harmonics for a fuller sound.\n\n"

                                "Ideal For:\n\n"
                                "Adding depth and warmth to a wide range of instruments, particularly those "
                                "with dynamic playing styles.\n\n"
                                "Enhancing the character of audio tracks in a mix, offering both subtle texture "
                                "and more pronounced distortion effects.\n\n"
                                "Creative sound design, where the interplay of dynamics and distortion can "
                                "create engaging and evolving textures.\n\n";
    }
    else if (algorithm == "Bias Folder")
    {

    }
    else if (algorithm == "BitCrusher")
    {
        algorithmDescription = "This is the Bitcrush Algorithm.";
    }
    else if (algorithm == "SquareFolder")
    {
        algorithmDescription = "This is the Squarefold Algorithm.";
    }
    else if (algorithm == "WaveShaper")
    {
        algorithmDescription = "This is the Waveshaper Algorithm.";
    }
    else if (algorithm == "Feedback-Waveshaper")
    {
        algorithmDescription = "This is the Feedback-Waveshaper Algorithm.";
    }
    else if (algorithm == "Downsample")
    {
        algorithmDescription = "This is the Downsample Algorithm.";
    }

}

juce::String TextLoader::getAlgorithmDescription(juce::String algorithm)
{
    setAlgorithm(algorithm);
    return algorithmDescription;
}

juce::AttributedString TextLoader::createSoftclipperDescription() {
    juce::AttributedString attrStr;

    // Title
    attrStr.append("----------------------------------------------------------------------------------------------------------------------------\n", juce::Font(plainTextSize, juce::Font::bold));
    attrStr.append("Softclipper\n", juce::Font(titleTextSize, juce::Font::bold));
    attrStr.append("----------------------------------------------------------------------------------------------------------------------------\n", juce::Font(plainTextSize, juce::Font::bold));


    // Algorithm description
    attrStr.append("The Softclipper gently rounds out the peaks of audio signals, preventing them from exceeding a preset threshold. This technique smooths out the waveform, offering a less aggressive form of distortion compared to hard clipping.\n\n", juce::Font(plainTextSize));


    // Characteristics
    attrStr.append("___________________________________________________________________________________________________________________________\n\n", juce::Font(plainTextSize));
    attrStr.append("Sound Characteristics:\n\n", juce::Font(header1Size, juce::Font::bold));
    attrStr.append("* Adds warmth to sounds clipping the peaks of the sound in a way that smoothes out the transition.\n\n", juce::Font(plainTextSize));
    attrStr.append("* Introduces some new harmonic content, generally focused in the low mids.\n\n", juce::Font(plainTextSize));


    // Comparison
    attrStr.append("___________________________________________________________________________________________________________________________\n\n", juce::Font(plainTextSize));
    attrStr.append("Comparative Listening:\n\n", juce::Font(header1Size, juce::Font::bold));
    attrStr.append("Try comparing the Softclipper's effect with the Hardclipper. Notice how the softclipper creates a much softer sounding output than the harsh hardclipping does.\n\n", juce::Font(plainTextSize));


    return attrStr;
}

juce::AttributedString TextLoader::createBrokenSoftclipperDescription() {
    juce::AttributedString attrStr;

    // Title
    attrStr.append("----------------------------------------------------------------------------------------------------------------------------\n", juce::Font(plainTextSize, juce::Font::bold));
    attrStr.append("Broken Softclipper\n", juce::Font(titleTextSize, juce::Font::bold));
    attrStr.append("----------------------------------------------------------------------------------------------------------------------------\n", juce::Font(plainTextSize, juce::Font::bold));

    // Algorithm description
    attrStr.append("The Broken Softclipper algorithm blends random noise with the input signal before applying soft clipping. This process modulates the audio dynamically, the distortion slider controls not only the drive of the saturator but also how much noise is mixed in with the signal.\n\n", juce::Font(plainTextSize));

    // Characteristics
    attrStr.append("___________________________________________________________________________________________________________________________\n\n", juce::Font(plainTextSize));
    attrStr.append("Sound Characteristics:\n\n", juce::Font(header1Size, juce::Font::bold));
    attrStr.append("* Blends traditional soft clipping with a textured noise layer, adding complexity and grit.\n\n", juce::Font(plainTextSize));
    attrStr.append("* The noise modulation introduces variability in the clipping effect, producing a less predictable and more 'broken' audio texture.\n\n", juce::Font(plainTextSize));

    // Comparison
    attrStr.append("___________________________________________________________________________________________________________________________\n\n", juce::Font(plainTextSize));
    attrStr.append("Comparative Listening:\n\n", juce::Font(header1Size, juce::Font::bold));
    attrStr.append("Compare the Broken Softclipper's output with the standard Softclipper. Notice how the addition of noise modulation changes the smoothness of the soft clipping, creating a more chaotic and textured sound.\n\n", juce::Font(plainTextSize));

    return attrStr;
}

juce::AttributedString TextLoader::createHardclipperDescription() {
    juce::AttributedString attrStr;

    // Title
    attrStr.append("----------------------------------------------------------------------------------------------------------------------------\n", juce::Font(plainTextSize, juce::Font::bold));
    attrStr.append("HardClipper\n", juce::Font(titleTextSize, juce::Font::bold));
    attrStr.append("----------------------------------------------------------------------------------------------------------------------------\n", juce::Font(plainTextSize, juce::Font::bold));

    // Algorithm description
    attrStr.append("The HardClipper algorithm sharply limits the audio signal, cutting off peaks that exceed a certain threshold to maintain levels within a set range. The distortion slider adjusts the 'drive' and therefore how quickly the signal reaches the threshold.\n\n", juce::Font(plainTextSize));

    // Characteristics
    attrStr.append("___________________________________________________________________________________________________________________________\n\n", juce::Font(plainTextSize));
    attrStr.append("Sound Characteristics:\n\n", juce::Font(header1Size, juce::Font::bold));
    attrStr.append("* Creates a strong, aggressive distortion by severely clipping the peaks of the waveform.\n\n", juce::Font(plainTextSize));
    attrStr.append("* Enhances the presence and perceived loudness of the audio by pushing the waveform to its limits.\n\n", juce::Font(plainTextSize));
    attrStr.append("* Introduces a significant amount of harmonic content, especially in the higher frequencies, due to the sharp clipping edges.\n\n", juce::Font(plainTextSize));

    // Comparison
    attrStr.append("___________________________________________________________________________________________________________________________\n\n", juce::Font(plainTextSize));
    attrStr.append("Comparative Listening:\n\n", juce::Font(header1Size, juce::Font::bold));
    attrStr.append("Listen to how the HardClipper contrasts with the Softclipper. While the Softclipper gently rounds the peaks, the HardClipper cuts them off abruptly, resulting in a much more pronounced and harsh distortion.\n\n", juce::Font(plainTextSize));

    return attrStr;
}

juce::AttributedString TextLoader::createWavefolderDescription() {
    juce::AttributedString attrStr;

    // Title
    attrStr.append("----------------------------------------------------------------------------------------------------------------------------\n", juce::Font(plainTextSize, juce::Font::bold));
    attrStr.append("Wavefolder\n", juce::Font(titleTextSize, juce::Font::bold));
    attrStr.append("----------------------------------------------------------------------------------------------------------------------------\n", juce::Font(plainTextSize, juce::Font::bold));

    // Algorithm description
    attrStr.append("The Wavefolder algorithm manipulates the audio signal by folding it back on itself whenever it exceeds a certain threshold. This folding process continues each time the signal exceeds these limits, significantly altering its waveform and creating rich, complex harmonics.\n\n", juce::Font(plainTextSize));

    // Characteristics
    attrStr.append("___________________________________________________________________________________________________________________________\n\n", juce::Font(plainTextSize));
    attrStr.append("Sound Characteristics:\n\n", juce::Font(header1Size, juce::Font::bold));
    attrStr.append("* Produces intricate harmonic content by repeatedly folding the waveform.\n\n", juce::Font(plainTextSize));
    attrStr.append("* Creates a rich, evolving sonic texture, significantly altering the original sound's timbre.\n\n", juce::Font(plainTextSize));
    attrStr.append("* Can vary from subtle to extreme transformations, depending on the drive level and input signal. The higher you push the drive the more the upper harmonics are emphasised so you lose some of the fundamental of the input signal.\n\n", juce::Font(plainTextSize));

    // Comparison
    attrStr.append("___________________________________________________________________________________________________________________________\n\n", juce::Font(plainTextSize));
    attrStr.append("Comparative Listening:\n\n", juce::Font(header1Size, juce::Font::bold));
    attrStr.append("Compare the Wavefolder's effect with the Hardclipper and Softclipper. While clippers cut or round off peaks, the Wavefolder folds them back, introducing more complex and textural differences in sound. try pushing the input gain higher to push the wavefolder even further!\n\n", juce::Font(plainTextSize));

    return attrStr;
}

juce::AttributedString TextLoader::createFoldbackDescription() {
    juce::AttributedString attrStr;

    // Title
    attrStr.append("----------------------------------------------------------------------------------------------------------------------------\n", juce::Font(plainTextSize, juce::Font::bold));
    attrStr.append("Foldback Algorithm\n", juce::Font(titleTextSize, juce::Font::bold));
    attrStr.append("----------------------------------------------------------------------------------------------------------------------------\n", juce::Font(plainTextSize, juce::Font::bold));

    // Algorithm description
    attrStr.append("The Foldback algorithm builds on the wavefolder by adding a feedback loop. It combines the output of a wavefolder and a soft clipper, both influenced by previous outputs, to dynamically alter the sound. This recursive interaction adds depth and complex texture to the audio signal.\n\n", juce::Font(plainTextSize));

    // Characteristics
    attrStr.append("___________________________________________________________________________________________________________________________\n\n", juce::Font(plainTextSize));
    attrStr.append("Sound Characteristics:\n\n", juce::Font(header1Size, juce::Font::bold));
    attrStr.append("* Produces a richly textured sound similar to the wavefolder but maintains emphasis on the fundemental as you push the drive higher.\n\n", juce::Font(plainTextSize));
    attrStr.append("* Enhances harmonic complexity, layering the original signal with a distorted signal that is constantly being fed back into itself.\n\n", juce::Font(plainTextSize));
    attrStr.append("* Can introduce a wide range of outcomes from subtle harmonic changes to intense, chaotic distortions.\n\n", juce::Font(plainTextSize));

    // Comparison
    attrStr.append("___________________________________________________________________________________________________________________________\n\n", juce::Font(plainTextSize));
    attrStr.append("Comparative Listening:\n\n", juce::Font(header1Size, juce::Font::bold));
    attrStr.append("Explore how the Foldback differs from basic wavefolding or clipping algorithms. Notice that as you push the 'drive' higher the fundamental frequency remains consistent but you still get the interesting harmonic overtones that wavefolding introduces.\n\n", juce::Font(plainTextSize));

    return attrStr;
}






//====================================================================================================================================================================================================
// these are the asymmetric algorithms

juce::AttributedString TextLoader::createAsymmetricSoftclipperDescription() {
    juce::AttributedString attrStr;

    // Title
    attrStr.append("----------------------------------------------------------------------------------------------------------------------------\n", juce::Font(plainTextSize, juce::Font::bold));
    attrStr.append("Asymmetric SoftClipper\n", juce::Font(titleTextSize, juce::Font::bold));
    attrStr.append("----------------------------------------------------------------------------------------------------------------------------\n", juce::Font(plainTextSize, juce::Font::bold));

    // Algorithm description
    attrStr.append("The Asymmetric SoftClipper algorithm introduces a subtle yet distinct twist to softclipping by adding a DC offset before the clipping process and then subtracting it afterward. This alteration causes the clipping to behave differently on the waveform's positive and negative swings, creating a unique harmonic character.\n\n", juce::Font(plainTextSize));

    // Characteristics
    attrStr.append("___________________________________________________________________________________________________________________________\n\n", juce::Font(plainTextSize));
    attrStr.append("Sound Characteristics:\n\n", juce::Font(header1Size, juce::Font::bold));
    attrStr.append("* Adds a unique warmth and body to the sound by altering the symmetry of clipping.\n\n", juce::Font(plainTextSize));
    attrStr.append("* Enhances harmonic complexity, particularly enriching the audio with more odd harmonics than the softclipper would usually add.\n\n", juce::Font(plainTextSize));
    attrStr.append("* Can subtly alter the tonal balance, giving it a slightly different texture compared to symmetric clipping.\n\n", juce::Font(plainTextSize));

    // Comparison
    attrStr.append("___________________________________________________________________________________________________________________________\n\n", juce::Font(plainTextSize));
    attrStr.append("Comparative Listening:\n\n", juce::Font(header1Size, juce::Font::bold));
    attrStr.append("Compare the Asymmetric SoftClipper with a standard SoftClipper. Notice the difference in how many odd/even harmonics get introduced between the two? its subtle but sometimes asymmetrical clipping can sound more pleasing and musical.\n\n", juce::Font(plainTextSize));

    return attrStr;
}

juce::AttributedString TextLoader::createBiasShaperDescription() {
    juce::AttributedString attrStr;

    // Title
    attrStr.append("----------------------------------------------------------------------------------------------------------------------------\n", juce::Font(plainTextSize, juce::Font::bold));
    attrStr.append("Bias Shaper\n", juce::Font(titleTextSize, juce::Font::bold));
    attrStr.append("----------------------------------------------------------------------------------------------------------------------------\n", juce::Font(plainTextSize, juce::Font::bold));

    // Algorithm description
    attrStr.append("The Bias Shaper algorithm is designed to apply soft clipping differently based on the signal's amplitude. For positive peaks in the signal that exceed a specific threshold, it applies a standard soft clipping. For the negative peaks, it introduces a bias before soft clipping and removes it afterward, enhancing the effect of the clipping on the negative portion of the wave.\n\n", juce::Font(plainTextSize));

    // Characteristics
    attrStr.append("___________________________________________________________________________________________________________________________\n\n", juce::Font(plainTextSize));
    attrStr.append("Sound Characteristics:\n\n", juce::Font(header1Size, juce::Font::bold));
    attrStr.append("* Very similar to the asymmetric softclipper but has a slightly harsher sound.\n\n", juce::Font(plainTextSize));
    attrStr.append("* Can subtly or significantly alter the harmonic content, depending on how the input signal interacts with the biasing process.\n\n", juce::Font(plainTextSize));

    // Comparison
    attrStr.append("___________________________________________________________________________________________________________________________\n\n", juce::Font(plainTextSize));
    attrStr.append("Comparative Listening:\n\n", juce::Font(header1Size, juce::Font::bold));
    attrStr.append("Compare the Bias Shaper to the asymmetric softclipper, the differences are quite subtle but the Bias Shaper tends to sound a bit harsher with slightly more prominent upper harmonic content.\n\n", juce::Font(plainTextSize));

    return attrStr;
}

juce::AttributedString TextLoader::createBiasFolderDescription() {
    juce::AttributedString attrStr;

    // Title
    attrStr.append("----------------------------------------------------------------------------------------------------------------------------\n", juce::Font(plainTextSize, juce::Font::bold));
    attrStr.append("BiasFolder\n", juce::Font(titleTextSize, juce::Font::bold));
    attrStr.append("----------------------------------------------------------------------------------------------------------------------------\n", juce::Font(plainTextSize, juce::Font::bold));

    // Algorithm description
    attrStr.append("The BiasFolder algorithm applies a bias to the audio signal before processing it through a feedback wavefolder, and then removing the bias post-processing.\n\n", juce::Font(plainTextSize));

    // Characteristics
    attrStr.append("___________________________________________________________________________________________________________________________\n\n", juce::Font(plainTextSize));
    attrStr.append("Sound Characteristics:\n\n", juce::Font(header1Size, juce::Font::bold));
    attrStr.append("* Creates a different sounding wavefolding effects by applying a pre-processing bias, increasing the complexity of the sound.\n\n", juce::Font(plainTextSize));
    attrStr.append("* Generates richer, more textured harmonics as the wavefolding interacts more intensely with the biased signal.\n\n", juce::Font(plainTextSize));
    attrStr.append("* Offers a unique sonic character that varies significantly with the input level.\n\n", juce::Font(plainTextSize));

    // Comparison
    attrStr.append("___________________________________________________________________________________________________________________________\n\n", juce::Font(plainTextSize));
    attrStr.append("Comparative Listening:\n\n", juce::Font(header1Size, juce::Font::bold));
    attrStr.append("Compare the BiasFolder with traditional wavefolding techniques. Focus on the depth and range of the textures produced by the BiasFolder, particularly noting how the bias changes the overall sound complexity.\n\n", juce::Font(plainTextSize));

    return attrStr;
}

juce::AttributedString TextLoader::createFoldCrusherDescription() {
    juce::AttributedString attrStr;

    // Title
    attrStr.append("----------------------------------------------------------------------------------------------------------------------------\n", juce::Font(plainTextSize, juce::Font::bold));
    attrStr.append("FoldCrusher\n", juce::Font(titleTextSize, juce::Font::bold));
    attrStr.append("----------------------------------------------------------------------------------------------------------------------------\n", juce::Font(plainTextSize, juce::Font::bold));

    // Algorithm description
    attrStr.append("The FoldCrusher algorithm is a hybrid effect that employs feedback wavefolding for the positive peaks in the signal and bit crushing for the negative peaks.\n\n", juce::Font(plainTextSize));

    // Characteristics
    attrStr.append("___________________________________________________________________________________________________________________________\n\n", juce::Font(plainTextSize));
    attrStr.append("Sound Characteristics:\n\n", juce::Font(header1Size, juce::Font::bold));
    attrStr.append("* Very interesting and slightly unpredictable hybrid effect.\n\n", juce::Font(plainTextSize));
    attrStr.append("* Yields highly dynamic and expressive results, with the wavefolding enriching the positive halves and bit crushing adding digital aliasing to the negative halves of the waveform.\n", juce::Font(plainTextSize));

    // Comparison
    attrStr.append("___________________________________________________________________________________________________________________________\n\n", juce::Font(plainTextSize));
    attrStr.append("Comparative Listening:\n\n", juce::Font(header1Size, juce::Font::bold));
    attrStr.append("Experiment with comparing the FoldCrusher's effects to standalone feedback wavefolding and bit crushing. Notice the unique interplay of textures and dynamics that emerge when these processes are applied conditionally based on the signal's polarity.\n\n", juce::Font(plainTextSize));

    return attrStr;
}

juce::AttributedString TextLoader::createDualPathBitFolderDescription() {
    juce::AttributedString attrStr;

    // Title
    attrStr.append("----------------------------------------------------------------------------------------------------------------------------\n", juce::Font(plainTextSize, juce::Font::bold));
    attrStr.append("Dual Path Bit Folder\n", juce::Font(titleTextSize, juce::Font::bold));
    attrStr.append("----------------------------------------------------------------------------------------------------------------------------\n", juce::Font(plainTextSize, juce::Font::bold));

    // Algorithm description
    attrStr.append("The Dual Path Bit Folder algorithm is wild and unpredictable. For positive peaks in the wave, it applies the SquareFolding algorithm, while for negative peaks, it combines feedback wavefolding with downsampling.\n\n", juce::Font(plainTextSize));

    // Characteristics
    attrStr.append("___________________________________________________________________________________________________________________________\n\n", juce::Font(plainTextSize));
    attrStr.append("Sound Characteristics:\n\n", juce::Font(header1Size, juce::Font::bold));
    attrStr.append("* Creates highly dynamic sound textures by employing two different folding techniques based on signal polarity, whilst also downsampling to get some weird aliasing artifacts.\n\n", juce::Font(plainTextSize));
    attrStr.append("* Offers a unique blend of digital and analog-like distortions, making it ideal for innovative sound design and experimentation.\n\n", juce::Font(plainTextSize));

    // Comparison
    attrStr.append("___________________________________________________________________________________________________________________________\n\n", juce::Font(plainTextSize));
    attrStr.append("Comparative Listening:\n\n", juce::Font(header1Size, juce::Font::bold));
    attrStr.append("Compare the Dual Path Bit Folder's effects to those of traditional folding or bit crushing methods. Focus on the distinct differences in texture and timbre.\n\n", juce::Font(plainTextSize));

    return attrStr;
}


//========================================================================================================================================================================================================
// these are the quantization algorithms



juce::AttributedString TextLoader::createBitCrusherDescription() {
    juce::AttributedString attrStr;

    // Title
    attrStr.append("----------------------------------------------------------------------------------------------------------------------------\n", juce::Font(plainTextSize, juce::Font::bold));
    attrStr.append("BitCrusher\n", juce::Font(titleTextSize, juce::Font::bold));
    attrStr.append("----------------------------------------------------------------------------------------------------------------------------\n", juce::Font(plainTextSize, juce::Font::bold));

    // Algorithm description
    attrStr.append("The BitCrusher algorithm deliberately reduces the audio signal's resolution by decreasing the number of amplitude levels available, a process known as quantization. This effect is controlled by the distortion slider, which adjusts the granularity of these levels, leading to a distinctive lo-fi, digital distortion.\n\n", juce::Font(plainTextSize));

    // Characteristics
    attrStr.append("___________________________________________________________________________________________________________________________\n\n", juce::Font(plainTextSize));
    attrStr.append("Sound Characteristics:\n\n", juce::Font(header1Size, juce::Font::bold));
    attrStr.append("* Introduces a gritty, 'crushed' texture to the audio, typical of early digital audio gear.\n\n", juce::Font(plainTextSize));
    attrStr.append("* Creates noticeable quantization noise and artifacts that can add a retro, digital edge to modern tracks.\n\n", juce::Font(plainTextSize));
    attrStr.append("* The effect varies with the 'alpha' which is controlled by the distortion slider, from subtle digital roughness to extreme, crunchy distortion.\n\n", juce::Font(plainTextSize));

    // Comparison
    attrStr.append("___________________________________________________________________________________________________________________________\n\n", juce::Font(plainTextSize));
    attrStr.append("Comparative Listening:\n\n", juce::Font(header1Size, juce::Font::bold));
    attrStr.append("Compare the BitCrusher's effects to those of traditional analog distortion types such as softclipping. Note the distinctively digital character of the BitCrusher's distortion, marked by its pronounced artifacts and reduced dynamic range, contrasted with the smoother, more continuous distortion that softclipping brings.\n\n", juce::Font(plainTextSize));

    return attrStr;
}

juce::AttributedString TextLoader::createDownSamplerDescription() {
    juce::AttributedString attrStr;

    // Title
    attrStr.append("----------------------------------------------------------------------------------------------------------------------------\n", juce::Font(plainTextSize, juce::Font::bold));
    attrStr.append("DownSampler\n", juce::Font(titleTextSize, juce::Font::bold));
    attrStr.append("----------------------------------------------------------------------------------------------------------------------------\n", juce::Font(plainTextSize, juce::Font::bold));

    // Algorithm description
    attrStr.append("The DownSampler algorithm reduces the sample rate of an audio signal, effectively thinning out the audio data based on the 'alpha' that is controlled by the drive slider. This parameter controls the degree of downsampling, from minimal to significant reduction, simulating the effect of lower fidelity digital audio. The process also integrates a bit crusher and soft clipper to enhance the texture and flavor of the reduced sample rate effect.\n\n", juce::Font(plainTextSize));

    // Characteristics
    attrStr.append("___________________________________________________________________________________________________________________________\n\n", juce::Font(plainTextSize));
    attrStr.append("Sound Characteristics:\n\n", juce::Font(header1Size, juce::Font::bold));
    attrStr.append("* Produces a characteristic 'steppy' or 'grainy' texture, typical of vintage digital audio with reduced sample rates.\n\n", juce::Font(plainTextSize));
    attrStr.append("* Introduces digital artifacts and aliasing, adding a unique, sometimes harsh texture to the sound.\n\n", juce::Font(plainTextSize));
    attrStr.append("* The combination of downsampling, bit crushing, and soft clipping creates complex, richly textured audio effects that can vary widely depending on the settings.\n\n", juce::Font(plainTextSize));

    // Comparison
    attrStr.append("___________________________________________________________________________________________________________________________\n\n", juce::Font(plainTextSize));
    attrStr.append("Comparative Listening:\n\n", juce::Font(header1Size, juce::Font::bold));
    attrStr.append("Compare the effects of the DownSampler with a standard high-resolution digital audio file. Notice how the reduction in sample rate alters the clarity and detail of the sound, offering a distinctly digital character that can be creatively used in modern music production.\n\n", juce::Font(plainTextSize));

    return attrStr;
}

juce::AttributedString TextLoader::createSquareFolderDescription() {
    juce::AttributedString attrStr;

    // Title
    attrStr.append("----------------------------------------------------------------------------------------------------------------------------\n", juce::Font(plainTextSize, juce::Font::bold));
    attrStr.append("Square Folder\n", juce::Font(titleTextSize, juce::Font::bold));
    attrStr.append("----------------------------------------------------------------------------------------------------------------------------\n", juce::Font(plainTextSize, juce::Font::bold));

    // Algorithm description
    attrStr.append("The Square Folder algorithm processes audio by initially applying a bit crushing effect to reduce the signal's resolution dramatically. This crushed signal is then passed through a wavefolder, which manipulates the waveform by folding it back on itself whenever it exceeds a certain threshold. This combination enhances the harmonic complexity and introduces unique textural characteristics to the sound.\n\n", juce::Font(plainTextSize));

    // Characteristics
    attrStr.append("___________________________________________________________________________________________________________________________\n\n", juce::Font(plainTextSize));
    attrStr.append("Sound Characteristics:\n\n", juce::Font(header1Size, juce::Font::bold));
    attrStr.append("* Introduces a rich palette of harmonics through wave folding, adding depth and complexity.\n", juce::Font(plainTextSize));
    attrStr.append("* Incorporates quantization noise and digital artifacts from bit crushing, providing a gritty edge.\n\n", juce::Font(plainTextSize));

    // Comparison
    attrStr.append("___________________________________________________________________________________________________________________________\n\n", juce::Font(plainTextSize));
    attrStr.append("Comparative Listening:\n\n", juce::Font(header1Size, juce::Font::bold));
    attrStr.append("Experiment with comparing the Square Folder's effects to those of traditional wavefolding or bit crushing methods alone. Focus on the interaction between the added digital artifacts and the complex overtones produced by wavefolding. Notice how the combination affects the overall texture and timbre.\n\n", juce::Font(plainTextSize));

    return attrStr;
}
