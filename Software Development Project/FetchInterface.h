#ifndef FETCHINTERFACE_H
#define FETCHINTERFACE_H

#include <vector>
#include <QString>

class Fetchable {
public:
    virtual std::vector<double> fetch(QString starttime, QString endtime) =0;
};

#endif // FETCHINTERFACE_H
