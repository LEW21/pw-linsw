import QtQuick 2.0

Slide
{
	Image
	{
		id: image
		height: 0.8*screen.height
		width: 0.8*screen.width
		fillMode: Image.PreserveAspectFit
		anchors.centerIn: parent
	}

	property alias source: image.source
}
