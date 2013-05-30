/*
 * Quote.cpp
 *
 *  Created on: May 25, 2013
 *      Author: devfom
 */

#include "Quote.h"

Quote::Quote(QObject* parent)
: QObject(parent)
{
}

void Quote::setQuoteText(QString value)
{
	if (m_quoteText != value)
	{
		m_quoteText = value;
		emit quoteTextChanged();
	}
}

void Quote::setQuoteLink(QString value)
{
	if (m_quoteLink != value)
	{
		m_quoteLink = value;
		emit quoteLinkChanged();
	}
}

void Quote::setQuoteAuthor(QString value)
{
	if (m_quoteAuthor != value)
	{
		m_quoteAuthor = value;
		emit quoteAuthorChanged();
	}
}
