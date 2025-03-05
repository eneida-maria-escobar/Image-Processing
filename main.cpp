#include <iostream>

#include <algorithm>

#include <fstream>

#include <vector>

#include <math.h>

#include <sstream>

#include "Image.h"

using namespace std;

bool doesFileEndInTGA(string
    const& fileName);
bool checkExists(string
    const& fileName);
bool inputValidation(int argc_, char* argv_[]);
void thisIsBadDebug(int& check);
bool doesFileEndInTGA(string
    const& fileName) {
    //The basis of this code can be found at 
    string extension = ".tga";
    int extensionLength = extension.length();
    int fileLength = fileName.length();

    if (fileName.length() < extension.length()) {
        return false;
    }
    else if (fileName.length() < 0) {
        return false;
    }
    else {
        extension = ".tga";
        bool extensionEnd = (0 == fileName.compare(fileName.length() - extension.length(), extension.length(), extension));
        bool trueChecker = extensionEnd;
        if (trueChecker == 0)
        {
            trueChecker = false;
        }
        else
        {
            trueChecker = true;
        }
        return extensionEnd;
    }
}

bool checkExists(string
    const& fileName) {
    bool fileOpen = true;
    ifstream throwawayfile;
    throwawayfile.open(fileName);
    if (throwawayfile.is_open()) {
        return fileOpen;
    }
    else {
        bool fileClosed = false;
        return fileClosed;
    }
    return false;
}

bool inputValidation(int argc_, char* argv_[]) {
    return false;
}

void push_back(vector<Image::Pixel> &updateMe, Image::Pixel keepTrack)
{
    updateMe.push_back(keepTrack);
}

void multiplyCommand(Image& trackingImage, string additionalImage) {
    ifstream image;
    Image secondImage(additionalImage);
    int normalization = 0;
    vector < Image::Pixel > UpdatedVectorPixels;
    normalization = 255;
    for (unsigned int i = 0; i < secondImage.pixelData.size(); i++) {
        char redPixelValue = 0;
        redPixelValue = round(((double)trackingImage.pixelData[i].Red * (double)secondImage.pixelData[i].Red) / normalization);
        char greenPixelValue = 0;
        greenPixelValue = round(((double)trackingImage.pixelData[i].Green * (double)secondImage.pixelData[i].Green) / normalization);
        char bluePixelValue = 0;
        bluePixelValue = round(((double)trackingImage.pixelData[i].Blue * (double)secondImage.pixelData[i].Blue) / normalization);

        Image::Pixel outputPixels(redPixelValue, greenPixelValue, bluePixelValue);
        push_back(UpdatedVectorPixels,outputPixels);
        image.close();
    }
    trackingImage.pixelData = UpdatedVectorPixels;

}
void testAddBlue();

void subtractCommand(Image& trackingImage, string additionalImage) {
    Image botL(additionalImage);
    vector < Image::Pixel > UpdatedVectorPixels;
    for (unsigned int i = 0; i < botL.pixelData.size(); i++) {
        unsigned char topLRC, topLGC, topLBC;
        topLRC = ((trackingImage.pixelData[i].Red));
        topLGC = ((trackingImage.pixelData[i].Green));
        topLBC = ((trackingImage.pixelData[i].Blue));

        if (((int)(botL.pixelData[i].Red)) > topLRC) {
            topLRC = 0;
        }
        else {
            topLRC -= ((int)(botL.pixelData[i].Red));
        }
        if (((int)(botL.pixelData[i].Green)) > topLGC) {
            topLGC = 0;
        }
        else {
            topLGC -= ((int)(botL.pixelData[i].Green));
        }
        if (((int)(botL.pixelData[i].Blue)) > topLBC) {
            topLBC = 0;
        }
        else {
            topLBC -= ((int)(botL.pixelData[i].Blue));
        }

        Image::Pixel outputPixels(topLRC, topLGC, topLBC);
        push_back(UpdatedVectorPixels,outputPixels);

    }
    trackingImage.pixelData = UpdatedVectorPixels;
}

void overlayCommand(Image& trackingImage, string additionalImage) {
    Image botL(additionalImage);
    vector < Image::Pixel > UpdatedVectorPixels;
    unsigned char redPixelValue, bluePixelValue, greenPixelValue;

    for (unsigned int i = 0; i < botL.pixelData.size(); i++) {

        if (((botL.pixelData[i].Red) / 255.0) > 0.5) {
            redPixelValue = (((1 - (2.0 * (1 - botL.pixelData[i].Red / 255.0 ) * (1 - trackingImage.pixelData[i].Red / 255.0 ))) * 255.0 ) + 0.5f);
            //redPixelValue += 0.5f;
        }
        else {
            redPixelValue = (((2.0 * (botL.pixelData[i].Red / 255.0 ) * (trackingImage.pixelData[i].Red / 255.0)) * 255.0 ) + 0.5f); 
            //redPixelValue += 0.5f;
        }
        if (((botL.pixelData[i].Green) / 255.0) > 0.5) {
            greenPixelValue = (((1 - (2.0 * (1 - botL.pixelData[i].Green / 255.0 ) * (1 - trackingImage.pixelData[i].Green / 255.0 ))) * 255.0 ) +0.5f);
           // greenPixelValue += 0.5f;
        }
        else {
            greenPixelValue = (((2.0 * (botL.pixelData[i].Green / 255.0 ) * (trackingImage.pixelData[i].Green / 255.0)) * 255.0 ) + 0.5f); 
       //     greenPixelValue += 0.5f;
        }
        if (((botL.pixelData[i].Blue) / 255.0 ) > 0.5) {
            bluePixelValue = (((1 - (2.0 * (1 - botL.pixelData[i].Blue / 255.0 ) * (1 - trackingImage.pixelData[i].Blue / 255.0 ))) * 255.0 ) + 0.5f);
           // bluePixelValue += 0.5f;
        }
        else {
            bluePixelValue = (((2.0 * (botL.pixelData[i].Blue / 255.0 ) * (trackingImage.pixelData[i].Blue / 255.0)) * 255.0 ) + 0.5f); 	
            //bluePixelValue += 0.5f;
        }

        Image::Pixel outputImage(redPixelValue, greenPixelValue, bluePixelValue);
        push_back(UpdatedVectorPixels,outputImage);
    }
    trackingImage.pixelData = UpdatedVectorPixels;
}

void testImageEquality(string fileOne, string fileTwo)
{
    ifstream firstFile(fileOne);
    ifstream secondFile(fileTwo);

    Image firstImage(fileOne);
    Image secondImage(fileTwo);

    if (firstImage.pixelData.size() != secondImage.pixelData.size())
    {
        cout << "Images are not equal!";
    }
    else
    {
        cout << "Images are equal!" << endl;
    }

}

void screenCommand(Image& trackingImage, string additionalImage) {
    unsigned char redPixelValue, bluePixelValue, greenPixelValue;
    vector < Image::Pixel > UpdatedVectorPixels;

    Image topLayer(additionalImage);

    for (unsigned int i = 0; i < trackingImage.pixelData.size(); i++) {
        int screenValue = 255;
        redPixelValue = ((int)(round(screenValue - (((double)(screenValue - trackingImage.pixelData[i].Red)) * ((double)(screenValue - topLayer.pixelData[i].Red)) / screenValue))));
        greenPixelValue = ((int)(round(screenValue - (((double)(screenValue - trackingImage.pixelData[i].Green)) * ((double)(screenValue - topLayer.pixelData[i].Green)) / screenValue))));
        bluePixelValue = ((int)(round(screenValue - (((double)(screenValue - trackingImage.pixelData[i].Blue)) * ((double)(screenValue - topLayer.pixelData[i].Blue)) / screenValue))));
        if (redPixelValue == 255)
        {
            screenValue = 0;
        }
        if (greenPixelValue == 255)
        {
            screenValue = 0;
        }
        if (bluePixelValue == 255)
        {
            screenValue = 0;
        }

        Image::Pixel updatedPixel(redPixelValue, greenPixelValue, bluePixelValue);
        push_back(UpdatedVectorPixels,updatedPixel);
    }

    trackingImage.pixelData = UpdatedVectorPixels;
}

void combineCommand(Image& allRed, string allGreen, string allBlue) {
    Image greenObject(allGreen);
    Image blueObject(allBlue);
    vector < Image::Pixel > UpdatedVectorPixels;
    for (unsigned int i = 0; i < allRed.pixelData.size(); i++) {
        unsigned char redPixelValue;
        redPixelValue = allRed.pixelData[i].Red;
        unsigned char greenPixelValue;
        greenPixelValue = greenObject.pixelData[i].Green;
        unsigned char bluePixelValue;
        bluePixelValue = blueObject.pixelData[i].Blue;

        Image::Pixel redJuicer(redPixelValue, greenPixelValue, bluePixelValue);

        UpdatedVectorPixels.push_back(redJuicer);
    }
    allRed.pixelData = UpdatedVectorPixels;
}

void flipCommand(Image& trackingImage) {
    vector < Image::Pixel > pixelVectorFinal;
    int numPixels = 0;
    std::reverse(pixelVectorFinal.begin(), pixelVectorFinal.end());
    for (unsigned int i = 0; i < trackingImage.pixelData.size(); i++) {
        unsigned char redPixelValue;
        redPixelValue = trackingImage.pixelData[i].Red;
        unsigned char greenPixelValue;
        greenPixelValue = trackingImage.pixelData[i].Green;
        unsigned char bluePixelValue;
        bluePixelValue = trackingImage.pixelData[i].Blue;

        Image::Pixel updatedPixel(redPixelValue, greenPixelValue, bluePixelValue);
        pixelVectorFinal.push_back(updatedPixel);
    }

    std::reverse(pixelVectorFinal.begin(), pixelVectorFinal.end());
    trackingImage.pixelData = pixelVectorFinal;
}

void onlyredCommand(Image& trackingImage) {
    vector < Image::Pixel > UpdatedVectorPixels;

    for (unsigned int i = 0; i < trackingImage.pixelData.size(); i++) {
        unsigned char redPixelValue;
        redPixelValue = ((trackingImage.pixelData[i].Red));
        if (redPixelValue < 0)
        {
            trackingImage.pixelData.clear();
        }
        Image::Pixel allRed(redPixelValue, redPixelValue, redPixelValue);
        vector<Image::Pixel> testVector;
        push_back(testVector, allRed);
        UpdatedVectorPixels.push_back(allRed);
    }
    trackingImage.pixelData = UpdatedVectorPixels;
}

void onlygreenCommand(Image& trackingImage) {
    vector < Image::Pixel > UpdatedVectorPixels;

    for (unsigned int i = 0; i < trackingImage.pixelData.size(); i++) {
        unsigned char greenPixelValue;
        greenPixelValue = ((trackingImage.pixelData[i].Green));
        if (greenPixelValue < 0)
        {
            trackingImage.pixelData.clear();
        }
        Image::Pixel allGreen(greenPixelValue, greenPixelValue, greenPixelValue);
        vector<Image::Pixel> testVector;
        push_back(testVector, allGreen);
        UpdatedVectorPixels.push_back(allGreen);
        
    }
    trackingImage.pixelData = UpdatedVectorPixels;
}

void onlyblueCommand(Image& trackingImage) {
    vector < Image::Pixel > UpdatedVectorPixels;

    for (unsigned int i = 0; i < trackingImage.pixelData.size(); i++) {
        unsigned char bluePixelValue;
        bluePixelValue = ((trackingImage.pixelData[i].Blue));
        if (bluePixelValue < 0)
        {
            trackingImage.pixelData.clear();
        }
        Image::Pixel allBlue(bluePixelValue, bluePixelValue, bluePixelValue);
        vector<Image::Pixel> testVector;
        push_back(testVector, allBlue);
        UpdatedVectorPixels.push_back(allBlue);
    }
    trackingImage.pixelData = UpdatedVectorPixels;
}

void addRedCommand(Image& trackingImage, int value) {
    vector < Image::Pixel > UpdatedVectorPixels;

    for (unsigned int i = 0; i < trackingImage.pixelData.size(); i++) {
        unsigned char allRed;
        allRed = trackingImage.pixelData[i].Red;
        unsigned char allGreen;
        allGreen = trackingImage.pixelData[i].Green;
        unsigned char allBlue;
        allBlue = trackingImage.pixelData[i].Blue;
        if ((allRed + value) < 0) {
            allRed = 0;
        }
        else if (value < 0 && (allRed + value < 0))
        {
            allRed = 0;
        }
        else if (allRed >= (256 - value)) {
            allRed = 255;
        }
        else if (value > 255)
        {
            allRed = 255;
        }
        else {
            allRed = allRed + value;
        }
        Image::Pixel keepTrack(allRed, allGreen, allBlue);
        trackingImage.pixelData[i] = keepTrack;
        push_back(UpdatedVectorPixels,keepTrack);
    }

    trackingImage.pixelData = UpdatedVectorPixels;
}

void addGreenCommand(Image& trackingImage, int value) {
    vector < Image::Pixel > UpdatedVectorPixels;

    for (unsigned int i = 0; i < trackingImage.pixelData.size(); i++) {
        unsigned char allRed;
        allRed = trackingImage.pixelData[i].Red;
        unsigned char allGreen;
        allGreen = trackingImage.pixelData[i].Green;
        unsigned char allBlue;
        allBlue = trackingImage.pixelData[i].Blue;;
        if ((allGreen + value) < 0) {
            allGreen = 0;
        }
        else if (allGreen >= (256 - value)) {
            allGreen = 255;
        }
        else if (value < 0 && (allGreen + value < 0))
        {
            allGreen = 0;
        }
        else if (value > 255)
        {
            allGreen = 255;
        }
        else {
            allGreen = allGreen + value;
        }
        Image::Pixel keepTrack(allRed, allGreen, allBlue);
        trackingImage.pixelData[i] = keepTrack;
        push_back(UpdatedVectorPixels,keepTrack);
    }

    trackingImage.pixelData = UpdatedVectorPixels;
}

void testAddBlue()
{
    vector<Image::Pixel> tester;
    Image first("input/car.tga");
    Image second("input/car.tga");
    for (unsigned int i = 0; i < first.pixelData.size(); i++)
    {
        first.pixelData[i].Blue += 200;
        second.pixelData[i].Blue += 200;
    }
    cout << first.pixelData[0].Blue;
}

void addBlueCommand(Image& trackingImage, int value) {
    vector < Image::Pixel > UpdatedVectorPixels;

    for (unsigned int i = 0; i < trackingImage.pixelData.size(); i++) {
        unsigned char allRed;
        allRed = trackingImage.pixelData[i].Red;
        unsigned char allGreen;
        allGreen = trackingImage.pixelData[i].Green;
        unsigned char allBlue;
        allBlue = trackingImage.pixelData[i].Blue;
        if ((allBlue + value) < 0) {
            allBlue = 0;
        }
        else if (allBlue >= (256 - value)) {
            allBlue = 255;
        }
        else if (value < 0 && (allBlue + value < 0))
        {
            allBlue = 0;
        }
        else if (value > 255)
        {
            allBlue = 255;
        }
        else {
            allBlue = allBlue + value;
        }
        Image::Pixel keepTrack(allRed, allGreen, allBlue);
        trackingImage.pixelData[i] = keepTrack;
        push_back(UpdatedVectorPixels,keepTrack);
    }

    trackingImage.pixelData = UpdatedVectorPixels;
}

 void thisIsBadDebug(int& check)
{
    cout << "This code should not be running";
    cout << endl;
    cout << "If this code is running, we have an error!";
    cout << "The error is at value " << check;
}

void scaleRedCommand(Image& trackingImage, int value) {
    vector < Image::Pixel > UpdatedVectorPixels;

    for (unsigned int i = 0; i < trackingImage.pixelData.size(); i++) {
        unsigned char allRed;
        allRed = ((int)(trackingImage.pixelData[i].Red));
        unsigned char allGreen;
        allGreen = ((int)(trackingImage.pixelData[i].Green));
        unsigned char allBlue;
        allBlue = ((int)(trackingImage.pixelData[i].Blue));
        if (value == 0) {
            allRed = allRed * value;
        }
        else if (allRed > (255 / value)) {
            if (value == 0)
            {
                thisIsBadDebug(value);
            }
            allRed = 255;
        }
        else {
            allRed = allRed * value;
        }
        Image::Pixel keepTrack(allRed, allGreen, allBlue);
        push_back(UpdatedVectorPixels,keepTrack);
    }
    trackingImage.pixelData = UpdatedVectorPixels;
}

void scaleGreenCommand(Image& trackingImage, int value) {
    vector < Image::Pixel > UpdatedVectorPixels;

    for (unsigned int i = 0; i < trackingImage.pixelData.size(); i++) {
        unsigned char allRed;
        allRed = ((int)(trackingImage.pixelData[i].Red));
        unsigned char allGreen;
        allGreen = ((int)(trackingImage.pixelData[i].Green));
        unsigned char allBlue;
        allBlue = ((int)(trackingImage.pixelData[i].Blue));
        if (value == 0) {
            allGreen = allGreen * value;
        }
        else if (allGreen > (255 / value)) {
            if (value == 0)
            {
                thisIsBadDebug(value);
            }
            allGreen = 255;
        }
        else {
            allGreen = allGreen * value;
        }
        Image::Pixel keepTrack(allRed, allGreen, allBlue);
        push_back(UpdatedVectorPixels,keepTrack);
    }
    trackingImage.pixelData = UpdatedVectorPixels;
}

void scaleBlueCommand(Image& trackingImage, int value) {
    vector < Image::Pixel > UpdatedVectorPixels;

    for (unsigned int i = 0; i < trackingImage.pixelData.size(); i++) {
        unsigned char allRed;
        allRed = ((int)(trackingImage.pixelData[i].Red));
        unsigned char allGreen;
        allGreen = ((int)(trackingImage.pixelData[i].Green));
        unsigned char allBlue;
        allBlue = ((int)(trackingImage.pixelData[i].Blue));
        if (value == 0) {
            allBlue = allBlue * value;
        }
        else if (allBlue > (255 / value)) {
            if (value == 0)
            {
                thisIsBadDebug(value);
            }
            allBlue = 255;
        }
        else {
            allBlue = allBlue * value;
        }
        Image::Pixel keepTrack(allRed, allGreen, allBlue);
        push_back(UpdatedVectorPixels,keepTrack);
    }
    trackingImage.pixelData = UpdatedVectorPixels;
}

int main(int argc, char* argv[]) {
    bool continueProgram = true;
    bool endPlace = false;
    string outputFileDirectory;
    if ((argc < 2)) {
        cout << "Project 2: Image Processing, Spring 2023";
        cout << endl;
        cout << endl;
        cout << "Usage:";
        cout << endl;
        cout << "\t./project2.out [output] [firstImage] [method] [...]";
        continueProgram = false;
        endPlace = false;
    }
    else if ((argc == 2) && (string(argv[1]) == "--help")) {
        cout << "Project 2: Image Processing, Spring 2023";
        cout << endl;
        cout << endl;
        cout << "Usage:";
        cout << endl;
        cout << "\t./project2.out [output] [firstImage] [method] [...]";
        continueProgram = false;
        endPlace = false;
    }
    else {
        if (continueProgram) {
            outputFileDirectory = argv[1];
            if (!doesFileEndInTGA(outputFileDirectory)) {
                cout << "Invalid file name.";
                continueProgram = false;
                endPlace = false;
            }
            else {
                if (continueProgram) {
                    if (argc < 3 || !doesFileEndInTGA(string(argv[2]))) {
                        cout << "Invalid file name.";
                        continueProgram = false;
                        endPlace = false;
                    }
                    else if (argc < 3 || !checkExists(string(argv[2]))) {
                        cout << "File does not exist.";
                        continueProgram = false;
                        endPlace = false;
                    }
                    else {
                        if (argc < 4) {
                            cout << "Invalid method name.";
                            continueProgram = false;
                            endPlace = false;
                        }
                        else {
                            for (unsigned int i = 3; i < argc; i++) {
                                if (string(argv[i]) == "multiply" || string(argv[i]) == "subtract" || string(argv[i]) == "overlay" || string(argv[i]) == "screen") {
                                    if (i == (argc - 1)) {
                                        cout << "Missing argument.";
                                        continueProgram = false;
                                        endPlace = false;
                                        break;
                                    }
                                    if (!doesFileEndInTGA(argv[i + 1])) {
                                        cout << "Invalid argument, invalid file name.";
                                        continueProgram = false;
                                        endPlace = false;
                                        break;
                                    }
                                    if (!checkExists(argv[i + 1])) {
                                        cout << "Invalid argument, file does not exist.";
                                        continueProgram = false;
                                        endPlace = false;
                                        break;
                                    }

                                    i++;
                                }
                                
                                else if (string(argv[i]) == "addred" || string(argv[i]) == "addgreen" || string(argv[i]) == "addblue") {
                                    if (i == (argc - 1)) {
                                        if (argc - 1 == 0)
                                        {
                                            cout << "Missing argument.";
                                        }
                                        cout << "Missing argument.";
                                        continueProgram = false;
                                        endPlace = false;
                                        break;
                                    }
                                    try {
                                        int throwawayValue = 0;
                                        throwawayValue = stoi(argv[i + 1]);

                                    }
                                    catch (std::invalid_argument) {
                                        cout << "Invalid argument, expected number.";
                                        continueProgram = false;
                                        endPlace = false;
                                        break;
                                    }
                                    i++; 
                                }
                                else if (string(argv[i]) == "scalered" || string(argv[i]) == "scalegreen" || string(argv[i]) == "scaleblue")
                                {
                                    if (i == (argc - 1)) {
                                        if (argc - 1 == 0)
                                        {
                                            cout << "Missing argument.";
                                        }
                                        cout << "Missing argument.";
                                        continueProgram = false;
                                        endPlace = false;
                                        break;
                                    }
                                    try {
                                        int scaleFac = 0;
                                        scaleFac = stoi(argv[i + 1]);

                                    }
                                    catch (std::invalid_argument) {
                                        cout << "Invalid argument, expected number.";
                                        continueProgram = false;
                                        endPlace = false;
                                        break;
                                    }
                                    i++;
                                }
                                else if (string(argv[i]) == "combine") 
                                {
                                    if (i == (argc - 1)) {
                                        cout << "Missing argument.";
                                        continueProgram = false;
                                        endPlace = false;
                                        break;
                                    }
                                    if (i == (argc - 2))
                                    {
                                        cout << "Missing argument.";
                                        endPlace = false;
                                        continueProgram = false;
                                    }
                                    if (!doesFileEndInTGA(argv[i + 1])) {
                                        cout << "Invalid argument, invalid file name.";
                                        continueProgram = false;
                                        endPlace = false;
                                        break;
                                    }
                                    if (!checkExists(argv[i + 1])) {
                                        cout << "Invalid argument, file does not exist.";
                                        continueProgram = false;
                                        endPlace = false;
                                        break;
                                    }
                                    if (!doesFileEndInTGA(argv[i + 2])) {
                                        cout << "Invalid argument, invalid file name.";
                                        continueProgram = false;
                                        endPlace = false;
                                        break;
                                    }
                                    if (!checkExists(argv[i + 2])) {
                                        cout << "Invalid argument, file does not exist.";
                                        continueProgram = false;
                                        endPlace = false;
                                        break;
                                    }
                                    i += 2;
                                }
                                else if (string(argv[i]) == "flip" || string(argv[i]) == "onlyred" || string(argv[i]) == "onlyblue" || string(argv[i]) == "onlygreen")
                                {

                                }
                                else {
                                    cout << "Invalid method name.";
                                    continueProgram = false;
                                    endPlace = false;
                                    break;
                                }

                            }
                        }
                    }
                }
            }
        }

    }

    if (continueProgram) {
        Image trackingImage(argv[2]);
        for (unsigned int i = 3; i < argc; i++) {
            if (string(argv[i]) == "multiply") {
                cout << "Attempting multiply!" << endl;
                multiplyCommand(trackingImage, argv[i + 1]);
                cout << "Multiply sucessful!" << endl;
                i++;
            }
            else if (string(argv[i]) == "subtract") {
                cout << "Attempting subtract!" << endl;
                subtractCommand(trackingImage, argv[i + 1]);
                cout << "Subtract successful!" << endl;
                i++;
            }
            else if (string(argv[i]) == "overlay") {
                cout << "Attempting overlay!" << endl;
                overlayCommand(trackingImage, argv[i + 1]);
                cout << "Overlay sucessful!" << endl;
                i++;
            }
            else if (string(argv[i]) == "screen") {
                cout << "Attempting screen!" << endl;
                screenCommand(trackingImage, argv[i + 1]);
                cout << "Screen sucessful!" << endl;
                i++;
            }
            else if (string(argv[i]) == "combine") {
                cout << "Attempting combination!" << endl;
                combineCommand(trackingImage, argv[i + 1], argv[i + 2]);
                cout << "Combination successful!" << endl;
                i += 2;
            }
            else if (string(argv[i]) == "onlyred") {
                cout << "Attempting to get red channel!" << endl;
                onlyredCommand(trackingImage);
                cout << "Sucessfully got red channel!" << endl;
            }
            else if (string(argv[i]) == "onlygreen") {
                cout << "Attempting to get green channel!" << endl;
                onlygreenCommand(trackingImage);
                cout << "Sucessfully got green channel!" << endl;
            }
            else if (string(argv[i]) == "onlyblue") {
                cout << "Attempting to get blue channel!" << endl;
                onlyblueCommand(trackingImage);
                cout << "Sucessfully got blue channel!" << endl;
            }
            else if (string(argv[i]) == "flip") {
                cout << "Attempting flip!" << endl;
                flipCommand(trackingImage);
                cout << "Successfully flipped!" << endl;
            }
            else if (string(argv[i]) == "addred") {
                cout << "Adding to red channel!" << endl;
                addRedCommand(trackingImage, stoi(argv[i + 1]));
                cout << "Successfully added to red channel!" << endl;
                i++;
            }
            else if (string(argv[i]) == "addgreen") {
                cout << "Adding to green channel!" << endl;
                addGreenCommand(trackingImage, stoi(argv[i + 1]));
                cout << "Successfully added to green channel!" << endl;
                i++;
            }
            else if (string(argv[i]) == "addblue") {
                cout << "Adding to blue channel!" << endl;
                addBlueCommand(trackingImage, stoi(argv[i + 1]));
                cout << "Successfully added to blue channel!" << endl;
                i++;
            }
            else if (string(argv[i]) == "scalered") {
                cout << "Scaling red channel!" << endl;
                scaleRedCommand(trackingImage, stoi(argv[i + 1]));
                cout << "Sucessfully scaled red channel";
                i++;
            }
            else if (string(argv[i]) == "scalegreen") {
                cout << "Scaling green channel!" << endl;
                scaleGreenCommand(trackingImage, stoi(argv[i + 1]));
                cout << "Sucessfully scaled green channel";
                i++;
            }
            else if (string(argv[i]) == "scaleblue") {
                cout << "Scaling blue channel!" << endl;
                scaleBlueCommand(trackingImage, stoi(argv[i + 1]));
                cout << "Sucessfully scaled blue channel";
                i++;
            }
        }
        trackingImage.writeImage("input", outputFileDirectory, trackingImage.pixelData); 
    }

    return 0;
}
