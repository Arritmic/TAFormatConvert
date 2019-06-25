#ifndef TADBFACEDATATYPES_H
#define TADBFACEDATATYPES_H

#include <string>
#include <vector>
#include <ctime>
#include <cstdio>
#include <string>
#include <cassert>
#include <map>



#ifndef __TAPoint__DEF__
#define __TAPoint__DEF__
    typedef struct
    {
        int x; /**< X-coordinate */
        int y; /**< Y-coordinate */
    } TAPoint;
#endif

#ifndef __TAPointF__DEF__
#define __TAPointF__DEF__
    typedef struct
    {
        float x; /**< X-coordinate */
        float y; /**< Y-coordinate */
    } TAPointF;
#endif

/**
 * @brief Structure for rectangle (for example detected face coordinates)
 */
#ifndef __VDRect__DEF__
#define __VDRect__DEF__
typedef struct _TARect
{
    int x; /**< X-coordinate (left)*/
    int y; /**< Y-coordinate (right)*/
    int width; /**< Y-coordinate (top)*/
    int height; /**< Y-coordinate (bottom)*/
} TARect;
#endif

/**
Enumeration for gender measurements.
*/
#ifndef __TAGendertype__DEF__
#define __TAGendertype__DEF__
    typedef enum _TAGendertype {
        UnknownGender=0, /**< Unable to measure */
        Female, /**< Female category */
        Male /**< Make category*/
    } TAGendertype;
#endif

/**
Enumeration for pets measurements.
*/
#ifndef __TAPettype__DEF__
#define __VDPettype__DEF__
typedef enum _TAPettype {
    UnknownPet=0, /**< Unable to measure */
    Cat, /**< Cat category */
    Dog /**< Dog category*/
} TAPettype;
#endif


// Struct partially taken from DLIB library for saving the results in the xml in its format.
// Added new variables.
struct box
{
    /*!
        WHAT THIS OBJECT REPRESENTS
            This object represents an annotated rectangular area of an image.
            It is typically used to mark the location of an object such as a
            person, car, etc.
            The main variable of interest is rect.  It gives the location of
            the box.  All the other variables are optional.
    !*/

    box(
            ) :
        difficult(false),
        truncated(false),
        occluded(false),
        ignore(false),
        pose(0),
        detection_score(0),
        angle(0),
        gender(UnknownGender),
        pet(UnknownPet),
        age(-1)
    {}

    box (
            const TARect& rect_
            ) :
        rect(rect_),
        difficult(false),
        truncated(false),
        occluded(false),
        ignore(false),
        pose(0),
        detection_score(0),
        angle(0),
        gender(UnknownGender),
        pet(UnknownPet),
        age(-1)
    {}

    TARect rect;
    std::vector<TAPointF> landmarks;
    std::map<std::string, TAPoint> parts;

    // optional fields
    std::string label;
    bool difficult;
    bool truncated;
    bool occluded;
    bool ignore;
    double pose;
    double detection_score;

    // The angle of the object in radians.  Positive values indicate that the
    // object at the center of the box is rotated clockwise by angle radians.  A
    // value of 0 would indicate that the object is in its "standard" upright pose.
    // Therefore, to make the object appear upright we would have to rotate the
    // image counter-clockwise by angle radians.
    double angle;

    TAGendertype gender;
    TAPettype pet;
    int age;

    bool has_label() const { return label.size() != 0; }
    /*!
        ensures
            - returns true if label metadata is present and false otherwise.
    !*/
};


struct image
{
    /*!
            WHAT THIS OBJECT REPRESENTS
                This object represents an annotated image.
        !*/

    image() {}
    image(const std::string& f) : filename(f),
                                  tag(false)
    {}

    std::string filename;
    std::vector<box> boxes;
    bool tag;
};

#endif // TADBFACEDATATYPES_H
