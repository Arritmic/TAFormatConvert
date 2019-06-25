#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
#include "tadbformatconvert.h"



int main()
{

    TADBFormatConvert converter;
    std::string input_txt = "/home/arritmic/PROYECTOS/DATABASES/OFFICIAL/base_trainset.txt";
    std::string output_xml = "/home/arritmic/PROYECTOS/DATABASES/OFFICIAL/base_trainset.xml";
    converter.txt2DlibXml(input_txt, output_xml);

    return EXIT_SUCCESS;
}
