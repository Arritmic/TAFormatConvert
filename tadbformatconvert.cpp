#include "tadbformatconvert.h"

TADBFormatConvert::TADBFormatConvert()
{
    this->number_of_landmarks = 68; // default ibug standar.
    this->name = "";
    this->comment = "";
}

bool TADBFormatConvert::txt2DlibXml(std::string txt_file, std::string xml_file)
{

    // Input file //
    FILE *fd = fopen(txt_file.c_str(), "r");
    assert(fd);

    printf("Reading data from txt input file %s...\n", txt_file.c_str());
    if(readTxtFile(fd))
    {
        return EXIT_FAILURE;
    }
    fclose(fd);


    // Output file //
    FILE *fw = fopen(xml_file.c_str(), "w");
    assert(fw);

    printf("Writing data in xml dlib output file %s...\n", xml_file.c_str());
    if(writeDlibXMLFile(fw))
    {
        printf("Error writing landmarks in the file %s.\n", xml_file.c_str());
        return EXIT_FAILURE;
    }
    fclose(fw);


    return EXIT_SUCCESS;
}

void TADBFormatConvert::setNumberOfLandmarks(int number_of_landmarks)
{
    this->number_of_landmarks = number_of_landmarks;
}

bool TADBFormatConvert::readTxtFile(FILE * input)
{


    int N; // Number of images in the txt file.
    fscanf(input, "%d", &N);

    images.resize(N);

    char img_path[256];
    double bbox_in[4];
    std::vector<double> x(number_of_landmarks), y(number_of_landmarks);
    double xpass;
    double ypass;

    for (int i = 0; i < N; i++)
    {

        fscanf(input, "%s", img_path);
        for (int j = 0; j < 4; j++) {
            fscanf(input, "%lf", &bbox_in[j]);
        }

        // For not loading the first 28 landmark points from the 68 model. For training the 40points model.
        if(number_of_landmarks == 40){
            for (int j = 0; j < 28; j++) {
                fscanf(input, "%lf%lf", &xpass, &ypass);
            }
        }

        for (int j = 0; j < number_of_landmarks; j++) {

            fscanf(input, "%lf%lf", &x[j], &y[j]);
        }




        TARect tempRect;
        tempRect.x = bbox_in[0];
        tempRect.y = bbox_in[1];
        tempRect.width = bbox_in[2];
        tempRect.height = bbox_in[3];

        box tempBox = box(tempRect);


        TAPointF tempPoint;
        for (int j = 0; j < number_of_landmarks; j++) {
            tempPoint.x = x[j];
            tempPoint.y = y[j];
            tempBox.landmarks.push_back(tempPoint);
        }

        if(tempBox.landmarks.size() != number_of_landmarks)
        {
            printf("Error reading landmarks in image %s.\n", img_path);
            return EXIT_FAILURE;
        }

        image tempImage;
        tempImage.filename = std::string(img_path);
        tempImage.boxes.push_back(tempBox);
        images[i] = tempImage;
    }

    return EXIT_SUCCESS;
}

bool TADBFormatConvert::writeDlibXMLFile(FILE *output)
{

    fprintf(output,"<?xml version='1.0' encoding='ISO-8859-1'?>\n");
    fprintf(output,"<?xml-stylesheet type='text/xsl' href='image_metadata_stylesheet.xsl'?>\n");
    fprintf(output,"<dataset>\n");
    fprintf(output,"<name>%s</name>\n", this->name.c_str());
    fprintf(output,"<comment>%s</comment>\n", this->comment.c_str());
    fprintf(output,"<images>\n");
    for (unsigned long i = 0; i < images.size(); ++i)
    {
        fprintf(output,"  <image file='%s'>\n", images.at(i).filename.c_str());

        // save all the boxes
        for (unsigned long j = 0; j < images.at(i).boxes.size(); ++j)
        {
            const box& b = images.at(i).boxes.at(j);
            fprintf(output,"    <box top='%d' left='%d' width='%d' height='%d'", b.rect.y, b.rect.x, b.rect.width, b.rect.height);
            if (b.age != -1)
                fprintf(output," age='%d'", b.age);
            if (b.gender != UnknownGender)
            {
                if (b.gender == Female)
                     fprintf(output," gender='female'");
                else
                   fprintf(output," gender='male'");
            }

           fprintf(output,">\n");

            if(!b.landmarks.empty())
            {
                for(unsigned int l = 0; l < number_of_landmarks; l++)
                {
                   std::string index;
                   if(l<10) index = "0" + std::to_string(l);
                   else index = std::to_string(l);
                   fprintf(output,"      <part name='%s' x='%d' y='%d'/>\n", index.c_str(), (int)b.landmarks.at(l).x, (int)b.landmarks.at(l).y);
                }
            }
            fprintf(output,"    </box>\n");
        }



        fprintf(output,"  </image>\n");


    }
    fprintf(output,"</images>\n");
    fprintf(output,"</dataset>");

    return EXIT_SUCCESS;

}
