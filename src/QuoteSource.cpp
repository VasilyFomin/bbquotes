/*
 * QuoteSource.cpp
 *
 *  Created on: May 24, 2013
 *      Author: devfom
 */

#include <QDebug>
#include <QtNetwork/qnetworkaccessmanager.h>
#include <QtNetwork/qnetworkrequest.h>
#include <QtNetwork/qnetworkreply.h>
#include <QUrl>
#include <QtXml/QDomDocument>
#include <QtXml/QDomNodeList>

#include <bb/data/JsonDataAccess>
#include <bb/data/XmlDataAccess>

#include "Quote.h"
#include "QuoteSource.h"

namespace {
	static const QString API_BASE_URL = "http://api.forismatic.com/api/1.0/";

	int getRandomKey(int beginRange, int endRange)
	{
		return qrand() % ((endRange + 1) - beginRange) + beginRange;
	}

	bool parseQuoteRawData(QByteArray data, Quote* pOutQuote)
	{
		if (!pOutQuote || data.isEmpty())
			return false;

		bb::data::XmlDataAccess xda;
		QVariantMap xdaDataMap = xda.loadFromBuffer(data).toMap();
		if (xda.hasError())
		{
			qDebug() << xda.error();
			return false;
		}

		QVariantMap quoteMap = xdaDataMap["quote"].toMap();

		qDebug() << quoteMap["quoteText"];
		qDebug() << quoteMap["quoteAuthor"];
		qDebug() << quoteMap["quoteLink"];

		pOutQuote->setQuoteText(quoteMap["quoteText"].toString());
		pOutQuote->setQuoteAuthor(quoteMap["quoteAuthor"].toString());
		pOutQuote->setQuoteLink(quoteMap["quoteLink"].toString());

		return true;
	}
}

QuoteSource::QuoteSource(QObject * parent)
: QObject(parent)
{
	m_pQuote = new Quote(this);
	m_pNetworkManager = new QNetworkAccessManager(this);
}

Quote* QuoteSource::quote() const
{
	qDebug() << "in quote";
	return m_pQuote;
}

void QuoteSource::refresh()
{
	QUrl url = QUrl(API_BASE_URL);
	url.addQueryItem("method", "getQuote");
	url.addQueryItem("format", "xml");
	url.addQueryItem("lang", "en");
	url.addQueryItem("key", QString::number(getRandomKey(0, 99999)));
	qDebug() << url;

	QNetworkRequest request(url);
	QNetworkReply * pReply = m_pNetworkManager->get(request);
	connect(pReply, SIGNAL(finished()), this, SLOT(onRequestFinished()));
	connect(pReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(onRequestError(QNetworkReply::NetworkError)));
}

void QuoteSource::onRequestFinished()
{
	QNetworkReply *pReply = qobject_cast<QNetworkReply*>(sender());
	if (pReply->error() != QNetworkReply::NoError)
		return;

	qDebug() << "onRequestFinished";
	QByteArray data = pReply->readAll();

	if (parseQuoteRawData(data, m_pQuote))
	{
		qDebug() << m_pQuote->quoteText();
		qDebug() << m_pQuote->quoteAuthor();
		qDebug() << m_pQuote->quoteLink();

		emit quoteChanged();
	}

	pReply->deleteLater();
}

void QuoteSource::onRequestError(QNetworkReply::NetworkError networkError)
{
	qDebug() << networkError;
}

