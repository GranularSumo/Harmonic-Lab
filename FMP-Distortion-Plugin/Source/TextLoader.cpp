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
    attrStr.append("The Softclipper Algorithm.\n", juce::Font(titleTextSize, juce::Font::bold));
    attrStr.append("----------------------------------------------------------------------------------------------------------------------------\n", juce::Font(plainTextSize, juce::Font::bold));

    // Body Text
    attrStr.append("Softclipping effectively compresses the dynamic range of the signal, and creates a warmer sound. "
        "When a sine wave is input, the output will exhibit a fuller, rounded sound with added harmonics, but without the abrupt clipping "
        "or intense distortions that can make a sound feel overly aggressive or digitally distorted. "
        "In this process, some odd-order harmonics are introduced, mainly in the low mids which is where the 'warmth' comes from. "
        "As you increase the drive it will introduce some of these odd-order harmonics higher up the register. "
        "The Softclipper algorithm is a simple, yet effective, distortion algorithm that is used in many guitar pedals and audio processors.\n\n",
        juce::Font(plainTextSize));

    // Subheaders and Lists
    attrStr.append("___________________________________________________________________________________________________________________________\n\n", juce::Font(plainTextSize));
    attrStr.append("Characteristics of Audio Output:\n\n", juce::Font(header1Size, juce::Font::bold));

    attrStr.append("1. Produces a warmer, smoother distortion compared to hard clipping.\n"
        "2. Adds harmonics in a subtle manner, enriching the sound without overwhelming it.\n"
        "3. Retains musical dynamics to a greater extent, preventing the harshness typical of more extreme distortion.\n\n",
        juce::Font(plainTextSize));

    attrStr.append("___________________________________________________________________________________________________________________________\n\n", juce::Font(plainTextSize));
    attrStr.append("Ideal For:\n\n", juce::Font(header1Size, juce::Font::bold));
    attrStr.append("Anything requiring a subtle, warm distortion to enhance body and presence without sacrificing tone quality.\n\n"
        "Drums, where a touch of saturation can add warmth and depth without overpowering the mix.\n\n"
        "Bass lines that need to be thickened up without losing clarity or becoming muddy.\n\n"
        "Vocals or other melodic content where a touch of saturation is desired to add character and depth, without introducing unwanted artifacts or overpowering the mix.\n\n",
        juce::Font(plainTextSize));

    return attrStr;
}

juce::AttributedString TextLoader::createBrokenSoftclipperDescription() {
    juce::AttributedString attrStr;

    // Title
    attrStr.append("----------------------------------------------------------------------------------------------------------------------------\n", juce::Font(plainTextSize, juce::Font::bold));
    attrStr.append("The Broken Softclipper Algorithm.\n", juce::Font(titleTextSize, juce::Font::bold));
    attrStr.append("----------------------------------------------------------------------------------------------------------------------------\n", juce::Font(plainTextSize, juce::Font::bold));

    // Body Text
    attrStr.append("The Broken Softclipper takes the concept of soft clipping and adds a layer of complexity and randomness by blending in white noise with the original signal. "
        "This isn't an algorithm that you will probably come across in other distortion plugins as I created it to emulate a sound design trick that I frequently do to add an analogue feel to digital synths. "
        "The result combines the warmth and smoothness of soft clipping with the textured, unpredictable character of white noise.\n\n",
        juce::Font(plainTextSize));

    // Subheaders and Lists
    attrStr.append("___________________________________________________________________________________________________________________________\n\n", juce::Font(plainTextSize));
    attrStr.append("Characteristics of Audio Output:\n\n", juce::Font(header1Size, juce::Font::bold));
    attrStr.append("1. Adds a layer of texture and randomness to the distortion, creating a more complex and unique sound.\n"
        "2. Retains the warmth and smoothness of soft clipping, while adding a layer of grit and character.\n"
        "3. The white noise component can add a sense of space and depth to the sound, making it feel more organic and alive.\n\n",
        juce::Font(plainTextSize));

    attrStr.append("___________________________________________________________________________________________________________________________\n\n", juce::Font(plainTextSize));
    attrStr.append("Ideal For:\n\n", juce::Font(header1Size, juce::Font::bold));
    attrStr.append("Adding lofi or analogue style character.\n\n"
        "Creating unique, textured sounds that stand out in a mix.\n\n"
        "Adding warmth to the low-end whilst also bringing out energy in the high-end.\n\n",
        juce::Font(plainTextSize));

    return attrStr;
}

juce::AttributedString TextLoader::createHardclipperDescription() {
    juce::AttributedString attrStr;

    // Title
    attrStr.append("----------------------------------------------------------------------------------------------------------------------------\n", juce::Font(plainTextSize, juce::Font::bold));
    attrStr.append("The Hardclipper Algorithm.\n", juce::Font(titleTextSize, juce::Font::bold));
    attrStr.append("----------------------------------------------------------------------------------------------------------------------------\n", juce::Font(plainTextSize, juce::Font::bold));

    // Body Text
    attrStr.append("Hardclipping essentially cuts off the top and bottom of the input signal, creating a flat line on the top and bottom of the waveform. As you increase the drive, the input signal gets louder, and as a result, "
        "more of the top and bottom get cut off, effectively turning a simple sine wave into a square wave. "
        "This introduces a lot of odd-order harmonics to the signal, and it does not do this in a subtle way at all, creating a very raw and loud tone that adds a lot of high end to the sound.\n\n",
        juce::Font(plainTextSize));

    // Subheaders and Lists
    attrStr.append("___________________________________________________________________________________________________________________________\n\n", juce::Font(plainTextSize));
    attrStr.append("Characteristics of Audio Output:\n\n", juce::Font(header1Size, juce::Font::bold));
    attrStr.append("1. Produces a raw, aggressive distortion with a lot of odd-order harmonics.\n"
        "2. The sound is very loud and in your face, with a lot of energy and presence.\n"
        "3. The distortion is very noticeable and can be quite harsh, making it ideal for aggressive, high-energy music.\n\n",
        juce::Font(plainTextSize));

    attrStr.append("___________________________________________________________________________________________________________________________\n\n", juce::Font(plainTextSize));
    attrStr.append("Ideal For:\n\n", juce::Font(header1Size, juce::Font::bold));
    attrStr.append("Creating a raw, aggressive tone.\n\n"
        "Adding a lot of high-end energy to a sound, making it stand out in a mix.\n\n"
        "Creating a very loud, in-your-face sound that demands attention.\n\n",
        juce::Font(plainTextSize));

    return attrStr;
}

juce::AttributedString TextLoader::createWavefolderDescription() {
    juce::AttributedString attrStr;

    // Title
    attrStr.append("----------------------------------------------------------------------------------------------------------------------------\n", juce::Font(plainTextSize, juce::Font::bold));
    attrStr.append("The Wavefolder Algorithm.\n", juce::Font(titleTextSize, juce::Font::bold));
    attrStr.append("----------------------------------------------------------------------------------------------------------------------------\n", juce::Font(plainTextSize, juce::Font::bold));

    // Body Text
    attrStr.append("The Wavefolder algorithm is a complex distortion algorithm that is capable of creating a wide range of unique and interesting sounds. "
        "It works by folding the waveform back on itself, creating a series of peaks and troughs that add a lot of harmonics to the signal. "
        "The result is a sound that is rich and complex, with a lot of movement and character. "
        "The Wavefolder is capable of creating a wide range of sounds, from subtle, warm distortion to wild, unpredictable textures.\n\n",
        juce::Font(plainTextSize));

    // Subheaders and Lists
    attrStr.append("___________________________________________________________________________________________________________________________\n\n", juce::Font(plainTextSize));
    attrStr.append("Characteristics of Audio Output:\n\n", juce::Font(header1Size, juce::Font::bold));
    attrStr.append("1. Produces a rich, complex sound with a lot of movement and character.\n"
        "2. The sound can range from subtle, warm distortion to wild, unpredictable textures.\n"
        "3. The Wavefolder is capable of creating a wide range of unique and interesting sounds.\n\n",
        juce::Font(plainTextSize));

    attrStr.append("___________________________________________________________________________________________________________________________\n\n", juce::Font(plainTextSize));
    attrStr.append("Ideal For:\n\n", juce::Font(header1Size, juce::Font::bold));
    attrStr.append("Creating unique, textured sounds that stand out in a mix.\n\n"
        "Adding warmth and character to a sound.\n\n"
        "Creating unpredictable, evolving textures that add depth and movement to a mix.\n\n",
        juce::Font(plainTextSize));

    return attrStr;
}

juce::AttributedString TextLoader::createFoldbackDescription() {
    juce::AttributedString attrStr;

    // Title
    attrStr.append("----------------------------------------------------------------------------------------------------------------------------\n", juce::Font(plainTextSize, juce::Font::bold));
    attrStr.append("The Foldback Algorithm.\n", juce::Font(titleTextSize, juce::Font::bold));
    attrStr.append("----------------------------------------------------------------------------------------------------------------------------\n", juce::Font(plainTextSize, juce::Font::bold));

    // Body Text
    attrStr.append("The Foldback is an innovative distortion algorithm that intricately blends "
        "wavefolding and soft clipping effects with a feedback mechanism. "
        "This process introduces feedback from the output back into the input, "
        "enriching the sound with complex harmonics and textures. The effect ranges from "
        "subtle nuances to intense, richly textured soundscapes, making the Foldback "
        "algorithm a versatile tool for creative sound design. Its ability to dynamically "
        "alter the audio signal provides a wide palette of sonic possibilities, from "
        "evolving textures to intricate harmonic layers.\n\n",
        juce::Font(plainTextSize));

    // Subheaders and Lists
    attrStr.append("___________________________________________________________________________________________________________________________\n\n", juce::Font(plainTextSize));
    attrStr.append("Characteristics of Audio Output:\n\n", juce::Font(header1Size, juce::Font::bold));
    attrStr.append("1. Delivers a dynamic, richly textured sound with complex harmonics.\n"
        "2. Offers a spectrum of effects, from subtle textural nuances to intense, rich soundscapes.\n"
        "3. Perfect for creating a wide range of unique and engaging sounds, adding depth and movement to the audio.\n\n",
        juce::Font(plainTextSize));

    attrStr.append("___________________________________________________________________________________________________________________________\n\n", juce::Font(plainTextSize));
    attrStr.append("Ideal For:\n\n", juce::Font(header1Size, juce::Font::bold));
    attrStr.append("Sound designers and musicians seeking innovative sound textures and dynamic sonic landscapes.\n\n"
        "Enhancing electronic music and experimental compositions with unique, evolving character.\n\n"
        "Adding complexity and a distinctive edge to a variety of sounds, ensuring they stand out in a mix with unparalleled depth.\n\n",
        juce::Font(plainTextSize));

    return attrStr;
}






//====================================================================================================================================================================================================
// these are the asymmetric algorithms

juce::AttributedString TextLoader::createAsymmetricSoftclipperDescription() {
    juce::AttributedString attrStr;

    // Title
    attrStr.append("----------------------------------------------------------------------------------------------------------------------------\n", juce::Font(plainTextSize, juce::Font::bold));
    attrStr.append("The Asymmetric Soft Clipper Algorithm.\n", juce::Font(titleTextSize, juce::Font::bold));
    attrStr.append("----------------------------------------------------------------------------------------------------------------------------\n", juce::Font(plainTextSize, juce::Font::bold));

    // Body Text
    attrStr.append("The Asymmetric Soft Clipper takes a novel approach to distortion by adding a "
        "slight twist to the traditional soft clipping process. It introduces a "
        "dcOffset, or a constant shift, before the signal undergoes soft clipping and "
        "then subtracts this offset after the process. This adjustment creates an "
        "asymmetry in how the audio signal is processed, leading to a unique distortion "
        "character that differs from symmetric soft clipping. The effect enriches the "
        "sound with a distinctive warmth and depth, adding subtle complexity to the "
        "harmonics without introducing harshness.\n\n",
        juce::Font(plainTextSize));

    // Subheaders and Lists
    attrStr.append("___________________________________________________________________________________________________________________________\n\n", juce::Font(plainTextSize));
    attrStr.append("Characteristics of Audio Output:\n\n", juce::Font(header1Size, juce::Font::bold));
    attrStr.append("1. Produces a warm, nuanced distortion with a unique tonal character.\n"
        "2. Enhances the audio with subtle asymmetrical harmonics, adding depth.\n"
        "3. Offers a fresh take on soft clipping, ideal for a variety of musical styles and instruments.\n\n",
        juce::Font(plainTextSize));

    attrStr.append("___________________________________________________________________________________________________________________________\n\n", juce::Font(plainTextSize));
    attrStr.append("Ideal For:\n\n", juce::Font(header1Size, juce::Font::bold));
    attrStr.append("Musicians and producers looking for a subtle, yet distinctive, distortion effect.\n\n"
        "Adding character to guitars, keyboards, and other melodic instruments without overpowering their natural sound.\n\n"
        "Creative sound design, where nuanced textures and tonal complexity can significantly impact the overall audio experience.\n\n",
        juce::Font(plainTextSize));

    return attrStr;
}

juce::AttributedString TextLoader::createBiasShaperDescription() {
    juce::AttributedString attrStr;

    // Title
    attrStr.append("----------------------------------------------------------------------------------------------------------------------------\n", juce::Font(plainTextSize, juce::Font::bold));
    attrStr.append("The Bias Shaper Algorithm.\n", juce::Font(titleTextSize, juce::Font::bold));
    attrStr.append("----------------------------------------------------------------------------------------------------------------------------\n", juce::Font(plainTextSize, juce::Font::bold));

    // Body Text
    attrStr.append("The Bias Shaper is a dynamic distortion effect that applies a unique form of "
        "processing to the audio signal. It intelligently alters its approach based on "
        "the signal's amplitude. For signals exceeding a certain level, it applies a "
        "standard soft clipping. However, for quieter signals, it introduces a bias "
        "adjustment before soft clipping, shifting the signal upwards, then subtracts "
        "this bias post-clipping. This technique creates a variable distortion effect "
        "that adapts to the input signal, offering a richer, more complex sound than "
        "traditional distortion methods.\n\n",
        juce::Font(plainTextSize));

    // Subheaders and Lists
    attrStr.append("___________________________________________________________________________________________________________________________\n\n", juce::Font(plainTextSize));
    attrStr.append("Characteristics of Audio Output:\n\n", juce::Font(header1Size, juce::Font::bold));
    attrStr.append("1. Yields a versatile distortion effect that varies with the input signal's amplitude.\n"
        "2. For louder signals, it provides a straightforward soft clipping warmth.\n"
        "3. Quieter signals are enriched with additional harmonics for a fuller sound.\n\n",
        juce::Font(plainTextSize));

    attrStr.append("___________________________________________________________________________________________________________________________\n\n", juce::Font(plainTextSize));
    attrStr.append("Ideal For:\n\n", juce::Font(header1Size, juce::Font::bold));
    attrStr.append("Adding depth and warmth to a wide range of instruments, particularly those with dynamic playing styles.\n\n"
        "Enhancing the character of audio tracks in a mix, offering both subtle texture and more pronounced distortion effects.\n\n"
        "Creative sound design, where the interplay of dynamics and distortion can create engaging and evolving textures.\n\n",
        juce::Font(plainTextSize));

    return attrStr;
}

juce::AttributedString TextLoader::createBiasFolderDescription() {
    juce::AttributedString attrStr;

    // Title
    attrStr.append("----------------------------------------------------------------------------------------------------------------------------\n", juce::Font(plainTextSize, juce::Font::bold));
    attrStr.append("The BiasFolder Algorithm.\n", juce::Font(titleTextSize, juce::Font::bold));
    attrStr.append("----------------------------------------------------------------------------------------------------------------------------\n", juce::Font(plainTextSize, juce::Font::bold));

    // Body Text
    attrStr.append("The BiasFolder represents a novel approach in dynamic waveform manipulation, seamlessly blending the properties of wavefolding and feedback mechanisms. "
        "By integrating a bias shift into the wavefolding process, it enriches the audio signal with intricate textures and harmonics. "
        "The algorithm employs a feedback loop, incorporating previous outputs to influence current processing, resulting in a sound that is both rich and evolving. "
        "This blend of saturation and soft clipping, followed by feedback-driven modulation, offers a wide palette of sonic possibilities, from gentle, nuanced distortions to complex, layered textures.\n\n",
        juce::Font(plainTextSize));

    // Subheaders and Lists
    attrStr.append("___________________________________________________________________________________________________________________________\n\n", juce::Font(plainTextSize));
    attrStr.append("Characteristics of Audio Output:\n\n", juce::Font(header1Size, juce::Font::bold));
    attrStr.append("1. Delivers a rich tapestry of sound, dense with harmonics and texture.\n"
        "2. Offers a unique blend of saturation and feedback, creating evolving sonic landscapes.\n"
        "3. Employs dynamic processing to adapt to the input signal, producing a varied range of effects from subtle to intense.\n\n",
        juce::Font(plainTextSize));

    attrStr.append("___________________________________________________________________________________________________________________________\n\n", juce::Font(plainTextSize));
    attrStr.append("Ideal For:\n\n", juce::Font(header1Size, juce::Font::bold));
    attrStr.append("Innovative sound design, where the exploration of unique textures and sonic complexity is key.\n\n"
        "Electronic and experimental music, providing a tool for artists to sculpt distinctive aural landscapes.\n\n"
        "Instruments and voices that benefit from rich, harmonic saturation and depth, enhancing the overall mix.\n\n",
        juce::Font(plainTextSize));

    return attrStr;
}

juce::AttributedString TextLoader::createFoldCrusherDescription() {
    juce::AttributedString attrStr;

    // Title
    attrStr.append("----------------------------------------------------------------------------------------------------------------------------\n", juce::Font(plainTextSize, juce::Font::bold));
    attrStr.append("The FoldCrusher Algorithm.\n", juce::Font(titleTextSize, juce::Font::bold));
    attrStr.append("----------------------------------------------------------------------------------------------------------------------------\n", juce::Font(plainTextSize, juce::Font::bold));

    // Body Text
    attrStr.append("The FoldCrusher algorithm is a sophisticated hybrid effect that merges the characteristics of wavefolding and bit crushing to process audio signals. "
        "This innovative algorithm selectively applies wavefolding to positive amplitudes while deploying bit crushing effects on negative amplitudes, creating a diverse range of sonic textures. "
        "The wavefolding aspect incorporates feedback to enrich the signal with complex harmonics, whereas the bit crushing introduces quantized, digital distortion for an edgy, raw sound. "
        "This dual approach allows for a unique distortion effect that can vary from subtle coloration to aggressive tonal transformation, depending on the input signal.\n\n",
        juce::Font(plainTextSize));

    // Subheaders and Lists
    attrStr.append("___________________________________________________________________________________________________________________________\n\n", juce::Font(plainTextSize));
    attrStr.append("Characteristics of Audio Output:\n\n", juce::Font(header1Size, juce::Font::bold));
    attrStr.append("1. Combines the warmth and complexity of wavefolding with the gritty, digital edge of bit crushing.\n"
        "2. Provides dynamic processing that responds uniquely to the amplitude of the input signal.\n"
        "3. Creates a versatile range of sounds, from subtle harmonic enhancements to intense, distorted textures.\n\n",
        juce::Font(plainTextSize));

    attrStr.append("___________________________________________________________________________________________________________________________\n\n", juce::Font(plainTextSize));
    attrStr.append("Ideal For:\n\n", juce::Font(header1Size, juce::Font::bold));
    attrStr.append("Musicians and producers seeking innovative distortion effects that offer both analog warmth and digital harshness.\n\n"
        "Sound designers looking to explore new textures and sonic territories, especially in electronic and experimental music.\n\n"
        "Instruments and tracks that benefit from a dramatic, characterful transformation, adding depth and interest to the mix.\n\n",
        juce::Font(plainTextSize));

    return attrStr;
}

juce::AttributedString TextLoader::createDualPathBitFolderDescription() {
    juce::AttributedString attrStr;

    // Title
    attrStr.append("----------------------------------------------------------------------------------------------------------------------------\n", juce::Font(plainTextSize, juce::Font::bold));
    attrStr.append("The Dual Path Bit Folder Algorithm.\n", juce::Font(titleTextSize, juce::Font::bold));
    attrStr.append("----------------------------------------------------------------------------------------------------------------------------\n", juce::Font(plainTextSize, juce::Font::bold));

    // Body Text
    attrStr.append("The Dual Path Bit Folder algorithm stands out with its innovative processing method, targeting the signal's amplitude to dictate its path. "
        "For positive amplitudes, it utilizes square folding to introduce symmetrical harmonics and enrich the signal with a warm, rounded texture. "
        "Conversely, negative amplitudes undergo a transformative journey through downsampling and feedback wavefolding, culminating in a texture-rich and harmonically complex output. "
        "This dual-path processing yields a multifaceted distortion effect capable of delivering both sharp, digital artifacts and smooth, analog warmth within a single framework.\n\n",
        juce::Font(plainTextSize));

    // Subheaders and Lists
    attrStr.append("___________________________________________________________________________________________________________________________\n\n", juce::Font(plainTextSize));
    attrStr.append("Characteristics of Audio Output:\n\n", juce::Font(header1Size, juce::Font::bold));
    attrStr.append("1. Offers a distinctive blend of digital and analog distortion characteristics.\n"
        "2. Adapts dynamically to the input signal's amplitude, providing a rich variety of textural outcomes.\n"
        "3. Engages listeners with an intricate interplay of crisp, edgy tones and smooth, enveloping harmonics.\n\n",
        juce::Font(plainTextSize));

    attrStr.append("___________________________________________________________________________________________________________________________\n\n", juce::Font(plainTextSize));
    attrStr.append("Ideal For:\n\n", juce::Font(header1Size, juce::Font::bold));
    attrStr.append("Experimentation with complex sound design, offering a broad palette of textures.\n\n"
        "Music production where versatility and depth of distortion are desired, from subtle coloration to overt intensity.\n\n"
        "Applications requiring a unique signature sound, combining clarity and depth in harmonics.\n\n",
        juce::Font(plainTextSize));

    return attrStr;
}


//========================================================================================================================================================================================================
// these are the quantization algorithms



juce::AttributedString TextLoader::createBitCrusherDescription() {
    juce::AttributedString attrStr;

    // Title
    attrStr.append("----------------------------------------------------------------------------------------------------------------------------\n", juce::Font(plainTextSize, juce::Font::bold));
    attrStr.append("The Bit Crusher Algorithm.\n", juce::Font(titleTextSize, juce::Font::bold));
    attrStr.append("----------------------------------------------------------------------------------------------------------------------------\n", juce::Font(plainTextSize, juce::Font::bold));

    // Body Text
    attrStr.append("The Bit Crusher algorithm is a nod to the gritty, lo-fi sounds of early digital audio gear. "
        "By deliberately reducing the bit depth of audio signals, it introduces quantization noise and a distinctively raw texture. "
        "This process mimics the character of vintage digital effects, imbuing tracks with a nostalgic feel. "
        "The algorithm's unique ability to blend modern audio fidelity with retro digital artifacts makes it a versatile tool for producers looking to add character and edge to their music.\n\n",
        juce::Font(plainTextSize));

    // Subheaders and Lists
    attrStr.append("___________________________________________________________________________________________________________________________\n\n", juce::Font(plainTextSize));
    attrStr.append("Characteristics of Audio Output:\n\n", juce::Font(header1Size, juce::Font::bold));
    attrStr.append("1. Introduces quantization noise and digital distortion, creating a gritty, lo-fi sound.\n"
        "2. Mimics the sonic character of vintage digital hardware and effects.\n"
        "3. Adds texture and depth through the deliberate introduction of digital artifacts.\n\n",
        juce::Font(plainTextSize));

    attrStr.append("___________________________________________________________________________________________________________________________\n\n", juce::Font(plainTextSize));
    attrStr.append("Ideal For:\n\n", juce::Font(header1Size, juce::Font::bold));
    attrStr.append("Producers seeking to infuse their tracks with the nostalgic, lo-fi quality of vintage digital audio.\n\n"
        "Sound design applications where digital distortion and aliasing can add a unique flavor to effects and transitions.\n\n"
        "Musical genres that embrace the raw, edgy textures of digital artifacts, such as electronic music, hip-hop, and experimental soundscapes.\n\n",
        juce::Font(plainTextSize));

    return attrStr;
}

juce::AttributedString TextLoader::createDownSamplerDescription() {
    juce::AttributedString attrStr;

    // Title
    attrStr.append("----------------------------------------------------------------------------------------------------------------------------\n", juce::Font(plainTextSize, juce::Font::bold));
    attrStr.append("The DownSampler Algorithm.\n", juce::Font(titleTextSize, juce::Font::bold));
    attrStr.append("----------------------------------------------------------------------------------------------------------------------------\n", juce::Font(plainTextSize, juce::Font::bold));

    // Body Text
    attrStr.append("The DownSampler algorithm offers a creative twist on digital audio processing by reducing the sample rate of audio signals. "
        "This method, known as decimation, alters the sonic character by introducing aliasing artifacts and a distinctive spatial texture. "
        "DownSampling is not just about reducing fidelity; it's a tool for creative expression, allowing producers to explore the sonic qualities of low-resolution audio. "
        "This algorithm bridges the gap between vintage digital charm and contemporary sound design, offering a palette of unique auditory textures.\n\n",
        juce::Font(plainTextSize));

    // Subheaders and Lists
    attrStr.append("___________________________________________________________________________________________________________________________\n\n", juce::Font(plainTextSize));
    attrStr.append("Characteristics of Audio Output:\n\n", juce::Font(header1Size, juce::Font::bold));
    attrStr.append("1. Introduces aliasing artifacts, creating complex, harmonically rich textures.\n"
        "2. Produces a distinctive spatial character through reduced sample rate effects.\n"
        "3. Facilitates creative exploration of low-resolution audio's sonic properties.\n\n",
        juce::Font(plainTextSize));

    attrStr.append("___________________________________________________________________________________________________________________________\n\n", juce::Font(plainTextSize));
    attrStr.append("Ideal For:\n\n", juce::Font(header1Size, juce::Font::bold));
    attrStr.append("Crafting unique, textural soundscapes in electronic and experimental music.\n\n"
        "Retro gaming sound effects, where low fidelity is both a nostalgic callback and a practical necessity.\n\n"
        "Sound designers and musicians looking to blend digital imperfections with high-fidelity recordings for a distinctive audio experience.\n\n",
        juce::Font(plainTextSize));

    return attrStr;
}

juce::AttributedString TextLoader::createSquareFolderDescription() {
    juce::AttributedString attrStr;

    // Title
    attrStr.append("----------------------------------------------------------------------------------------------------------------------------\n", juce::Font(plainTextSize, juce::Font::bold));
    attrStr.append("The SquareFolder Algorithm.\n", juce::Font(titleTextSize, juce::Font::bold));
    attrStr.append("----------------------------------------------------------------------------------------------------------------------------\n", juce::Font(plainTextSize, juce::Font::bold));

    // Body Text
    attrStr.append("At the heart of the SquareFolder algorithm lies a unique approach to sound processing, marrying the gritty, digital distortion of bit crushing with the nonlinear harmonics introduced by wave folding. "
        "This algorithm first applies a bit crushing effect to reduce the audio signal's bit depth, introducing quantization noise and digital artifacts. "
        "The processed signal is then subjected to wave folding, a technique that reflects the waveform back upon itself whenever it exceeds a certain threshold, adding complex overtones and enhancing the signal's harmonic content. "
        "The result is a sound that combines the raw, edgy qualities of digital distortion with the rich, intricate textures of analog synthesis.\n\n",
        juce::Font(plainTextSize));

    // Subheaders and Lists
    attrStr.append("___________________________________________________________________________________________________________________________\n\n", juce::Font(plainTextSize));
    attrStr.append("Characteristics of Audio Output:\n\n", juce::Font(header1Size, juce::Font::bold));
    attrStr.append("1. Introduces a rich palette of harmonics through wave folding, adding depth and complexity.\n"
        "2. Incorporates quantization noise and digital artifacts, providing a gritty edge.\n"
        "3. Merges the distinct qualities of digital and analog distortion for a unique sonic character.\n\n",
        juce::Font(plainTextSize));

    attrStr.append("___________________________________________________________________________________________________________________________\n\n", juce::Font(plainTextSize));
    attrStr.append("Ideal For:\n\n", juce::Font(header1Size, juce::Font::bold));
    attrStr.append("Synth leads and basses, where the enhanced harmonics can cut through the mix.\n\n"
        "Experimental sound design, offering new textures and timbres.\n\n"
        "Creating aggressive, attention-grabbing effects in electronic music production.\n\n",
        juce::Font(plainTextSize));

    return attrStr;
}