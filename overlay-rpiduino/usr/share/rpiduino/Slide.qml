import QtQuick 2.0

Item
{
	width: screen.width
	height: screen.height

	property QtObject about

	Rectangle
	{
		anchors.fill: parent
		color: about ? about.color : "transparent"
		visible: about
	}
}
