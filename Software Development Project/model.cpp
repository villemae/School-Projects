#include "model.hh"
#include "fingrid.h"
#include "fmi.h"
#include <QDebug>
#include <iostream>

Model::Model()
{
    std::shared_ptr<Fingrid> pfingrid = std::make_shared<Fingrid>();
    std::shared_ptr<FMI> pfmi = std::make_shared<FMI>();

    data_sources_.insert({"Fingrid", pfingrid});
    data_sources_.insert({"FMI", pfmi});
}

QString Model::getText() const
{
    std::cout<<buttonClickedText_.toStdString()<<std::endl;
    return  buttonClickedText_;
}

std::vector<double> Model::generateFMIData(QString button)
{
    std::vector<double> data;
    std::shared_ptr<FMI> pfmi = std::dynamic_pointer_cast<FMI>(data_sources_.at("FMI"));
    pfmi->updateDataType(button);
    data = data_sources_["FMI"]->fetch(startTime_, endTime_);

    buttonClickedText_ = button;
    buttonClickedText_ += QString::fromStdString(" button clicked");

    return data;
}

std::vector<double> Model::generateFingridData(QString button)
{
    std::vector<double> data = {};
    std::shared_ptr<Fingrid> pfin = std::dynamic_pointer_cast<Fingrid>(data_sources_.at("Fingrid"));
    pfin->updateDataType(button);
    data = data_sources_["Fingrid"]->fetch(startTime_, endTime_);

    buttonClickedText_ = button;
    buttonClickedText_ += QString::fromStdString(" button clicked");

    return data;
}

void Model::setStartDate(QString s)
{
    startTime_ = s;
}

void Model::setEndDate(QString e)
{
    endTime_ = e;
}

void Model::setCity(QString city)
{
    std::shared_ptr<FMI> pfmi = std::dynamic_pointer_cast<FMI>(data_sources_.at("FMI"));
    pfmi->setLocation(city);
}

int Model::countTimeInterval()
{
    return 0;
}

void Model::saveData(std::vector<double> data)
{
    std::ofstream save_file("save_file.txt");
    for (auto value : data) {
        save_file << value << std::endl;
    }
    save_file.close();
}

std::vector<double> Model::readSavedData()
{
    std::vector<double> data;
    std::ifstream save_file("save_file.txt");
    if (not save_file) {
            return {};
        }
    std::string row = "";
    while (getline(save_file, row)) {
        data.push_back(stod(row));
    }
    save_file.close();
    return data;
}

double Model::calculateAverage(std::vector<double> data)
{
    double sum = 0;
    for (auto value : data) {
        sum += value;
    }
    double mean = sum/data.size();

    return mean;
}

double Model::calculatePercentage(QString button)
{
    std::vector<double> data = generateFingridData(button);
    std::vector<double> overall_data = generateFingridData("production");

    double production = calculateAverage(data);
    double overall_production = calculateAverage(overall_data);

    return production / overall_production * 100;
}
