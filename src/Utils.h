//
// Copyright (c) 2020, Fabian Frey
// All rights reserved.
//

#ifndef WEATHERSTATION_UTILS_H
#define WEATHERSTATION_UTILS_H

std::string doubleToString(double number)
{
    std::ostringstream stream;
    stream << number;
    return stream.str();
}

#endif //WEATHERSTATION_UTILS_H
