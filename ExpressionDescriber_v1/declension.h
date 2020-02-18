#ifndef DECLENSION_H
#define DECLENSION_H
#include <QObject>
#include <QHash>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QNetworkAccessManager>
#include <QTextCodec>
#include <QJsonDocument>
#include <QJsonObject>

class Declension : QObject
{

public:
    enum Declensions {I,R,D,V,T,P};

    Declension();
    QHash<QString, QStringList> cache;
    QString getDeclension(QString word, Declensions decl);
    ~Declension();

};

#endif // DECLENSION_H
