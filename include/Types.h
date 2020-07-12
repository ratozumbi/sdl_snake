//
// Created by Rato Zumbi on 09/07/2020.
//

#ifndef GAME_TYPES_H
#define GAME_TYPES_H

enum class PiceType{
    black = 0,
    white,
    pink,
    blue,
    orange,
    _LAST
};
const PiceType PiceTypeToEnum[5] = {PiceType::black,PiceType::white,PiceType::pink,PiceType::blue,PiceType::orange};

#endif //GAME_TYPES_H
