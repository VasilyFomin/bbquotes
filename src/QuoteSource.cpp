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

#include <bb/data/JsonDataAccess>

#include "Quote.h"
#include "QuoteSource.h"

namespace {
	int getRandomKey(int beginRange, int endRange)
	{
		return qrand() % ((endRange + 1) - beginRange) + beginRange;
	}
}

QuoteSource::QuoteSource(QObject * parent)
: QObject(parent)
{
	m_pQuote = new Quote(this);
	m_pNetworkManager = new QNetworkAccessManager(this);

	m_enUrl = QUrl("http://api.forismatic.com/api/1.0/");
	m_enUrl.addQueryItem("method", "getQuote");
	m_enUrl.addQueryItem("format", "json");
	m_enUrl.addQueryItem("lang", "en");
	m_enUrl.addQueryItem("key", QString::number(getRandomKey(0, 99999)));

	m_ruUrl = QUrl("http://api.forismatic.com/api/1.0/");
	m_ruUrl.addQueryItem("method", "getQuote");
	m_ruUrl.addQueryItem("format", "json");
	m_ruUrl.addQueryItem("lang", "ru");
	m_ruUrl.addQueryItem("key", QString::number(getRandomKey(0, 99999)));
}

void QuoteSource::refresh()
{
	qDebug() << m_enUrl;
	QNetworkRequest request(m_enUrl);
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
	qDebug() << data;

	bb::data::JsonDataAccess jda;
	QVariant rawQuoteData = jda.loadFromBuffer(data);
	QVariantMap quoteObjectMap = rawQuoteData.toMap();

	m_pQuote->setQuoteText(quoteObjectMap["quoteText"].toString());
	m_pQuote->setQuoteAuthor(quoteObjectMap["quoteAuthor"].toString());
	m_pQuote->setQuoteLink(quoteObjectMap["quoteLink"].toString());

	emit quoteChanged();

	pReply->deleteLater();
}

void QuoteSource::onRequestError(QNetworkReply::NetworkError networkError)
{
	qDebug() << networkError;
}

