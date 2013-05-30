// Default empty project template
import bb.cascades 1.0
import devfom.quotes.data 1.0

// creates one page with a label
Page {
    Container {        
        layout: DockLayout { }
        
        attachedObjects: [
        	QuoteSource {
        	    id: quoteSource
        	    onQuoteChanged: {
        	        console.log("onQuoteChanged");
        	        console.log(quoteSource.quote.quoteAuthor);
                    console.log(quoteSource.quote.quoteText);
                    console.log(quoteSource.quote.quoteLink);
                    
//                    quoteAuthor.text = quoteSource.quote.quoteAuthor;
//        	        quoteText.text = quoteSource.quote.quoteText;
//                    quoteLink.text = quoteSource.quote.quoteLink;      
					quoteBubble.quoteText = quoteSource.quote.quoteText;
					quoteBubble.quoteAuthor = quoteSource.quote.quoteAuthor;
                }
        	}        	
        ]
        QuoteBubble {
            id: quoteBubble
            horizontalAlignment: HorizontalAlignment.Center
            verticalAlignment: VerticalAlignment.Top
        }
        Container {
            layout: StackLayout {
                orientation: LayoutOrientation.LeftToRight
            }
            horizontalAlignment: HorizontalAlignment.Fill
            verticalAlignment: VerticalAlignment.Bottom
            
            Button {
                id: refreshButton
                text: "Refresh"
                onClicked: {
                    quoteSource.refresh()
                }
            }
           
            Button {
                id: wikipediaButton
                text: "Wiki"
                onClicked: {
                    if (quoteSource.quote.quoteAuthor != null)
                    {
                        console.log("quoteAuthor not null");
//                        blackberry.invoke.invoke(
//                        {
//                            target: "sys.browser",
//                            uri: 
//                        });
                    }
                }
            }
            Button {
                id: quotePageButton
                text: "Link"
                onClicked: {
                    if (quoteSource.quote.quoteLink != null)
                    {
                        console.log("quoteLink not null");
                        var blogpage = goToWebView.createObject();                        
                        navigationPane.push(blogpage);
                    }    
                }
            }
        }
        
    }    
}

