/* Copyright (c) 2012 Research In Motion Limited.
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 * http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
import bb.cascades 1.0

// This is the speech bubble with the quote and the name underneath it.

Container {
    id: quoteBubble
    property string quoteAuthor
    //property alias pendingFirstName: editName.firstName
    //property alias pendingLastName: editName.lastName

    property alias quoteText: longText.text
    
    topPadding: 20
    bottomPadding: topPadding
    rightPadding: topPadding
    leftPadding: topPadding

    // The actual quote
    Container {
        horizontalAlignment: HorizontalAlignment.Center
        layout: DockLayout {
        }

        // The bubble image behind the quote. Since the image will scale due to
        // different lengths of the quote a nine-sliced image is used to ensure
        // only the middle part (the white area) is scaled (see images/border_bubble.amd).
        ImageView {
            imageSource: "asset:///images/border_bubble.amd"
            verticalAlignment: VerticalAlignment.Fill
            horizontalAlignment: HorizontalAlignment.Fill
        }

        // TextArea that is put in a Container to add padding around it
        Container {
            topPadding: 54
            bottomPadding: 85
            rightPadding: 30
            leftPadding: rightPadding
            
            TextArea {
                id: longText
                preferredWidth: 520
                editable: false
                textStyle.color: Color.create("#262626");
            }
        } // Text area Container
    } // Quote Container

    // The name of the person who wrote/said the quote
    Container {
        topPadding: 15
        layout: DockLayout {
        }
        Label {
            id: nameLabel

            // The person behind the quote who's first and last name are data bound in C++.
            text: quoteBubble.quoteAuthor
            textStyle.base: quoteStyleLightBody.style
        }       
    } // Name Container
}// Main Container
