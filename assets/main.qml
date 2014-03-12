
import bb.cascades 1.2

Page {
    signal addItem(string itemName);
    property int itemCount : 1
    Container {
        Button {
            text: "Add Item " + itemCount
            onClicked: {
                addItem("item " + itemCount);
                itemCount++;
            }
        }
    	ListView {
         objectName: "listView"
         }
    }
}
