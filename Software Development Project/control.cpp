#include "control.hh"
#include "model.hh"
#include "view.hh"

#include <string>
#include <iostream>

Control::Control(std::shared_ptr<Model> model,
                 std::shared_ptr<View> view,
                 QObject* parent) :
    QObject{ parent },
    model_{ model },
    view_{ view }
{
    fmi_datasets_ = {
        {"temperature", {}},
        {"cloudiness", {}},
        {"wind", {}},
        {"windForecast", {}},
        {"temperatureForecast", {}}
    };

    fingrid_datasets_ = {
        {"productionForecast", {}},
        {"windProductionForecast", {}},
        {"production", {}},
        {"consumption", {}},
        {"windProduction", {}},
        {"nuclearProduction", {}},
        {"hydroProduction", {}},
        {"powerforecast", {}}
    };
}

void Control::fmiButtonClicked(QString button)
{
    buttonClicked_ = button;
    std::vector<double> data = model_->generateFMIData(button);

    fmi_datasets_.at(buttonClicked_) = data;

    view_->fmiDataGenerated(button);
}

void Control::fingridButtonClicked(QString button)
{
    buttonClicked_ = button;

    std::vector<double> data = model_->generateFingridData(button);

    fingrid_datasets_.at(buttonClicked_) = data;

    view_->fingridDataGenerated(button);
}

void Control::setStartDate(QString s)
{
    QString time = "T00:00:00Z";
    model_->setStartDate(s + time);
}

void Control::setEndDate(QString e)
{
    QString time = "T23:59:59Z";
    model_->setEndDate(e + time);
}

void Control::setCity(QString c)
{
    model_->setCity(c);
    std::cout << "city: " + c.toStdString()<<std::endl;
}

int Control::getTimeInterval()
{
    std::cout << startTime_.toStdString() << std::endl;
    return model_->countTimeInterval();
    //view_->timeIntervalSet();
}


double Control::getData(int index)
{
    return fmi_datasets_.at(buttonClicked_).at(index);
}


double Control::getFingridData(int index)
{
    return fingrid_datasets_.at(buttonClicked_).at(index);
}


int Control::length()
{
    return fmi_datasets_.at(buttonClicked_).size();
}


int Control::productionLength()
{
    return fingrid_datasets_.at(buttonClicked_).size();
}

int Control::splitProductionLength()
{
    int length = productionLength();
    int result = (length/100);
    return result;
}


int Control::getMaxTemperature()
{
    std::vector<double>::iterator result;
    result = std::max_element(fmi_datasets_.at(buttonClicked_).begin(),
                              fmi_datasets_.at(buttonClicked_).end());

    return int(*result);
}


int Control::getMinTemperature()
{
    std::vector<double>::iterator result;
    result = std::min_element(fmi_datasets_.at(buttonClicked_).begin(),
                              fmi_datasets_.at(buttonClicked_).end());

    return int(*result);
}

