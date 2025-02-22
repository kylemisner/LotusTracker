#ifndef UNTAPPED_H
#define UNTAPPED_H

#include "api/untappedapi.h"
#include "entity/eventplayercourse.h"
#include "entity/matchdetails.h"
#include "untappedmatchdescriptor.h"

#include <QFile>
#include <QJsonObject>
#include <QObject>
#include <QStack>

class Untapped : public QObject
{
    Q_OBJECT
private:
    UntappedAPI *untappedAPI;
    EventPlayerCourse eventPlayerCourse;
    QString tempDir;
    QJsonObject matchDescriptor;
    MatchDetails matchDetails;
    UntappedMatchDescriptor untappedMatchDescriptor;
    void setupUntappedAPIConnections();
    void prepareMatchLogFile(QStack<QString> matchLogMsgs);
    void prepareMatchDescriptor(QString timestamp, QString uploadToken);
    QByteArray getUploadData();

public:
    explicit Untapped(QObject *parent = nullptr);
    void checkForUntappedUploadToken();
    void setEventPlayerCourse(EventPlayerCourse eventPlayerCourse);
    void uploadMatchToUntapped(MatchDetails matchDetails, QStack<QString> matchLogMsgs);

signals:

private slots:
    void onS3PutInfo(QString putUrl, QString timestamp);

public slots:
};

#endif // UNTAPPED_H
