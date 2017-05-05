//
// Created by mac on 5/05/17.
//

#ifndef PROJECT_RESPONSE_HPP
#define PROJECT_RESPONSE_HPP

//---------------------------------------//
//Wrapper for results of entailment check
//---------------------------------------//

class Response {
public:
    bool Result = false;
    int ModalsInfered = 0;
    Response(int mods, bool res) : ModalsInfered(mods), Result(res) {};
};



#endif //PROJECT_RESPONSE_HPP
