#pragma once

class ICompetition {
public:
    virtual ~ICompetition() = default;

    virtual void Simulation() = 0;
};