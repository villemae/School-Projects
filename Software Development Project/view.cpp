#include "view.hh"
#include "model.hh"
#include<QtMath>
#include <QtCharts/QBarSet>


View::View(std::shared_ptr<Model> model,
                   QObject* parent) :
    QObject{ parent },
    model_{model}
{
}

QString View::getText() const
{
    return model_->getText();
}

void View::fmiDataGenerated(QString button)
{
    if(button == "temperature") {
        emit temperatureDataChanged();
    } else if(button == "cloudiness") {
        emit cloudinessDataChanged();
    } else if(button == "wind") {
        emit windDataChanged();
    } else if(button == "windForecast") {
        emit windForecastDataChanged();
    } else if(button == "temperatureForecast") {
        emit temperatureForecastDataChanged();
    } else if(button == "productionForecast") {
        emit productionForecastDataChanged();

    }
}

void View::fingridDataGenerated(QString button)
{
    if(button == "production") {
        emit productionDataChanged();
    } else if (button == "consumption"){
        emit consumptionDataChanged();
    } else if (button == "windProduction"){
        emit windProductionDataChanged();
    } else if (button == "hydroProduction"){
        emit waterDataChanged();
    } else if (button == "nuclearProduction"){
        emit nuclearDataChanged();
    } else if (button == "productionForecast"){
        emit productionForecastDataChanged();
    } else if (button == "powerforecast"){
        emit powerForecastDataChanged();
    } else {
        emit productionDataChanged();
    }

}
