#ifndef TADBFORMATCONVERT_H
#define TADBFORMATCONVERT_H

#include <string>
#include <vector>
#include <ctime>
#include <cstdio>
#include <string>
#include <cassert>
#include <map>

#include "tadbfacedatatypes.h"




class TADBFormatConvert
{
public:
    void TADBFormatConvert();
    bool txt2DlibXml(std::string txt_file, std::string xml_file);
    void setNumberOfLandmarks(int number_of_landmarks);


private:
    std::string input_file;
    std::string outfile_file;
    std::vector<image> images;
    std::string name; // Name of the database
    std::string comment;

    // Face detector variables

    // Landmarks variables
    int number_of_landmarks;


    // Internal functions
    bool readTxtFile(FILE * input);
    bool writeDlibXMLFile(FILE * output);

};

#endif // TADBFORMATCONVERT_H
