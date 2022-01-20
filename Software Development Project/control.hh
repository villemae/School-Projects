#ifndef CONTROL_HH
#define CONTROL_HH

#include <memory>
#include <QObject>
#include <QQuickItem>

class Model;
class View;

class Control : public QObject
{
    Q_OBJECT

public:
    explicit Control(std::shared_ptr<Model> model,
                            std::shared_ptr<View> view,
                            QObject* parent = nullptr);

    Q_INVOKABLE void setStartDate(QString s);
    Q_INVOKABLE void setEndDate(QString e);
    Q_INVOKABLE void setCity(QString c);

    Q_INVOKABLE int getTimeInterval();

    Q_INVOKABLE void fmiButtonClicked(QString button);
    Q_INVOKABLE void fingridButtonClicked(QString button);
    Q_INVOKABLE double getData(int index);
    Q_INVOKABLE double getFingridData(int index);

    Q_INVOKABLE int length();
    Q_INVOKABLE int productionLength();
    Q_INVOKABLE int splitProductionLength();
    Q_INVOKABLE int getMaxTemperature();
    Q_INVOKABLE int getMinTemperature();



private:
    std::shared_ptr<Model> model_;
    std::shared_ptr<View> view_;
    QString startTime_;
    QString endTime_;
    QString buttonClicked_;

    std::map<QString, std::vector<double>> fmi_datasets_;
    std::map<QString, std::vector<double>> fingrid_datasets_;
};

#endif // CONTROL_HH
