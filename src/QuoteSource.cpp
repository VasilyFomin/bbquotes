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
	static const QString API_URL_EN = "http://api.forismatic.com/api/1.0/?method=getQuote&format=json&key=&lang=en";
}

QuoteSource::QuoteSource(QObject * parent)
: QObject(parent)
{
	m_pQuote = new Quote(this);
	m_pNetworkManager = new QNetworkAccessManager(this);
	connect(m_pNetworkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onRequestFinished(QNetworkReply*)));
}

void QuoteSource::refresh()
{
	qDebug() << "Process...";
	QByteArray requestParams = "method=getQuote&format=json&lang=en";
//	QNetworkRequest request(QUrl(API_URL_EN));
	m_pNetworkManager->get(QNetworkRequest(QUrl(API_URL_EN)));
}

void QuoteSource::onRequestFinished(QNetworkReply* pReply)
{
	if (pReply->error() != QNetworkReply::NoError)
		return;

	qDebug() << "onRequestFinished";
	bb::data::JsonDataAccess jda;
	QVariant rawQuoteData = jda.loadFromBuffer(pReply->readAll());
	QVariantMap quoteObjectMap = rawQuoteData.toMap();

	m_pQuote->setQuoteText(quoteObjectMap["quoteText"].toString());
	m_pQuote->setQuoteAuthor(quoteObjectMap["quoteAuthor"].toString());
	m_pQuote->setQuoteLink(quoteObjectMap["quoteLink"].toString());

	emit quoteChanged();
}
