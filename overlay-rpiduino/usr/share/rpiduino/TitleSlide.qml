import QtQuick 2.0

Slide
{
	TextP
	{
		id: text
		height: 2*screen.lineHeight
		width: parent.width
		horizontalAlignment: Text.AlignHCenter
		anchors.verticalCenter: parent.verticalCenter
	}

	property alias text: text.text
}
