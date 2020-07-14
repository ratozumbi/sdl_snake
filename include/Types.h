//
// Created by Rato Zumbi on 09/07/2020.
//

#ifndef ENJOIADO_TYPES_H
#define ENJOIADO_TYPES_H

enum class PiceType{
    black = 0,
    white,
    pink,
    blue,
    orange,
    _LAST
};
const PiceType piceTypeToEnum[5] = {PiceType::black, PiceType::white, PiceType::pink, PiceType::blue, PiceType::orange};

#endif //ENJOIADO_TYPES_H
