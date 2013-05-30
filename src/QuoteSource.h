/*
 * QuoteSource.h
 *
 *  Created on: May 24, 2013
 *      Author: devfom
 */

#ifndef QUOTESOURCE_H_
#define QUOTESOURCE_H_

#include <QObject>
#include <bb/cascades/CustomControl>
#include <QString>

class QNetworkAccessManager;
class QNetworkReply;
class Quote;

class QuoteSource : public QObject
{
	Q_OBJECT
public:
	explicit QuoteSource(QObject * parent = 0);

	Q_PROPERTY(Quote * quote READ quote NOTIFY quoteChanged)
	Quote * quote() const { return m_pQuote; }

	Q_INVOKABLE void refresh();

signals:
	void quoteChanged();

private slots:
	void onRequestFinished();
	void onRequestError(QNetworkReply::NetworkError);

private:
	Quote * m_pQuote;
	QNetworkAccessManager *m_pNetworkManager;
	QNetworkRequest m_request;
	QUrl m_enUrl;
	QUrl m_ruUrl;
};

#endif /* QUOTESOURCE_H_ */
