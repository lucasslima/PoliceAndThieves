#ifndef BLOCK_H
#define BLOCK_H


class Block
{
public:
    Block(double maxSpeed, bool isSolid);
    virtual ~Block();
    double getMAXSPEED() const;
    bool getIS_SOLID() const;
    const double BOCK_SIZE = 10;
protected:
    const double MAXSPEED;
    const bool IS_SOLID;
};

#endif // BLOCK_H
