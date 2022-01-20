#ifndef FMI_H
#define FMI_H

#include "FetchInterface.h"


class FMI : public Fetchable
{
enum InfoType {
    TEMPERATURE,
    WIND,
    CLOUDINESS,
    TEMPERATUREFORECAST,
    WINDFORECAST
};

public:
    FMI();
    std::vector<double> fetch(QString starttime, QString endtime) override;
    void updateDataType(QString button);
    void setLocation(QString location);

private:
    InfoType info_type_ = TEMPERATURE;
    QString location_ = "Helsinki";
};

#endif // FMI_H
