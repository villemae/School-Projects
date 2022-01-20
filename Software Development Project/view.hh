#ifndef VIEW_HH
#define VIEW_HH

#include <memory>
#include <QObject>
#include <QPointF>

class Model;

class View : public QObject
{
    Q_OBJECT

    //Q_PROPERTY(QVector<double> temperatureData READ temperatureData NOTIFY temperatureDataChanged)


public:
    explicit View(std::shared_ptr<Model> model,
                      QObject* parent = nullptr);

    QString getText() const;

    void fingridDataGenerated(QString button);
    void fmiDataGenerated(QString button);
    void timeIntervalSet();

    /*QVector<double> temperatureData() const {
        return temperature_data_;

    }
    QVector<double> productionData() const {
        return production_data_;
    }
*/


signals:

    void intervalChanged();

    // FMI
    void temperatureDataChanged();
    void cloudinessDataChanged();
    void windDataChanged();
    void windForecastDataChanged();
    void temperatureForecastDataChanged();


    //Fingrid
    void productionDataChanged();
    void consumptionDataChanged();
    void windProductionDataChanged();
    void nuclearDataChanged();
    void waterDataChanged();
    void productionForecastDataChanged();
    void powerForecastDataChanged();


private:
        std::shared_ptr<Model> model_;
        QVector<double> temperature_data_;
        QVector<double> production_data_;
        QVector<double> cloudiness_data_;


};

#endif // VIEW_HH
