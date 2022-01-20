#ifndef MODEL_HH
#define MODEL_HH

#include "FetchInterface.h"
#include <map>
#include <memory>
#include <vector>
#include <fstream>

class Model
{

public:
    Model();

    QString getText() const;
    std::vector<double> generateFMIData(QString button);
    std::vector<double> generateFingridData(QString button);
    void setStartDate(QString s);
    void setEndDate(QString e);
    void setCity(QString city);
    int countTimeInterval();
    void saveData(std::vector<double> data);
    std::vector<double> readSavedData();

    double calculatePercentage(QString button);


private:
    double calculateAverage(std::vector<double> data);

    QString buttonClickedText_;
    std::map<QString, std::shared_ptr<Fetchable>> data_sources_;
    QString startTime_;
    QString endTime_;

};

#endif // MODEL_HH
