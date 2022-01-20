#ifndef FINGRID_H
#define FINGRID_H

#include "FetchInterface.h"
#include <map>

class Fingrid : public Fetchable
{
    //map to save information which button fetches which data
    std::map<QString, QString> const API_ids = {
        {"powerforecast", "165"},
        {"productionForecast", "242"},
        {"windProductionForecast", "245"},
        {"production", "74"},
        {"consumption", "193"},
        {"windProduction", "75"},
        {"nuclearProduction", "188"},
        {"hydroProduction", "191"}
    };

public:
    Fingrid();

    /* Fetch data from API from time period between starttime-endtime
     * Fetched data depends on value of id_
     * Return vector including all the fetched values*/
    std::vector<double> fetch(QString starttime, QString endtime) override;

    //Update id_
    void updateDataType(QString button);

private:

    QString id_;
};

#endif // FINGRID_H
