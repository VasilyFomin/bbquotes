/*
 * Quote.h
 *
 *  Created on: May 25, 2013
 *      Author: devfom
 */

#ifndef QUOTE_H_
#define QUOTE_H_

#include <QObject>
#include <QString>

class Quote : public QObject
{
	Q_OBJECT
public:
	explicit Quote(QObject * parent = 0);

	Q_PROPERTY(QString quoteText READ quoteText WRITE setQuoteText NOTIFY quoteTextChanged);
	QString quoteText() const { return m_quoteText; }
	void setQuoteText(QString value);

	Q_PROPERTY(QString quoteLink READ quoteLink WRITE setQuoteLink NOTIFY quoteLinkChanged);
	QString quoteLink() const { return m_quoteLink; }
	void setQuoteLink(QString value);

	Q_PROPERTY(QString quoteAuthor READ quoteAuthor WRITE setQuoteAuthor NOTIFY quoteAuthorChanged);
	QString quoteAuthor() const { return m_quoteAuthor; }
	void setQuoteAuthor(QString value);

signals:
	void quoteTextChanged();
	void quoteLinkChanged();
	void quoteAuthorChanged();

private:
	QString m_quoteText;
	QString m_quoteLink;
	QString m_quoteAuthor;
};

#endif /* QUOTE_H_ */
