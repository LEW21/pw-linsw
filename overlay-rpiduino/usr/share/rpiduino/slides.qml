import QtQuick 2.0
import Synergy 1.0
import Hipsta 1.0

Item {
	id: screen
	height: 600
	width: 800
	property int lineHeight: 0.5*Math.min(0.1*height, 0.06*width)

	Mouse {id: hipsta}

	QtObject {
		id: rpi
		property color color: "#E30B5C"
	}

	QtObject {
		id: ard
		property color color: "#00979C"
	}

	VisualItemModel
	{
		id: slides
		Slide
		{
			Item {
				anchors.verticalCenter: parent.verticalCenter
				anchors.left: parent.left
				anchors.right: parent.right
				height: 2*screen.lineHeight
				Row {
					anchors.fill: parent
					TextP
					{
						text: "Raspberry Pi"
						height: parent.height
						width: parent.width/2
						horizontalAlignment: Text.AlignHCenter
					}
					TextP
					{
						text: "Arduino"
						height: parent.height
						width: parent.width/2
						horizontalAlignment: Text.AlignHCenter
					}
				}

				TextP
				{
					text: "&"
					anchors.fill: parent
					horizontalAlignment: Text.AlignHCenter
				}
			}
		}

		Slide
		{
			Column
			{
				anchors.verticalCenter: parent.verticalCenter
				anchors.left: parent.left
				anchors.right: parent.right
				spacing: 0.8*screen.lineHeight
				Item
				{
					width: parent.width
					height: 3*screen.lineHeight
					TextP
					{
						text: "Outline"
						height: 2*screen.lineHeight
						width: parent.width
						horizontalAlignment: Text.AlignHCenter
					}
				}
				TextP
				{
					text: "1. Electronics for human beings"
					width: parent.width
					horizontalAlignment: Text.AlignHCenter
				}
				Row {
					width: parent.width
					Column {
						width: parent.width/2

						Column {
							anchors.horizontalCenter: parent.horizontalCenter
							width: Math.max(out_2.paintedWidth, out_3.paintedWidth, out_4.paintedWidth)
							spacing: 0.4*screen.lineHeight
							TextP { id: out_2; text: "2. What's a Raspberry Pi?" }
							TextP { id: out_3; text: "3. Possible applications" }
							TextP { id: out_4; text: "4. Working example" }
						}
					}
					Column {
						width: parent.width/2

						Column {
							anchors.horizontalCenter: parent.horizontalCenter
							width: Math.max(out_5.paintedWidth, out_6.paintedWidth, out_7.paintedWidth)
							spacing: 0.4*screen.lineHeight
							TextP { id: out_5; text: "5. What's an Arduino?" }
							TextP { id: out_6; text: "6. Possible applications" }
							TextP { id: out_7; text: "7. Working example" }
						}
					}
				}
				Column {
					spacing: 0.4*screen.lineHeight
					width: parent.width
					TextP
					{
						text: "8. Synergy"
						width: parent.width
						horizontalAlignment: Text.AlignHCenter
					}
					TextP
					{
						text: "9. Summary"
						width: parent.width
						horizontalAlignment: Text.AlignHCenter
					}
				}
			}
		}

		TitleSlide { about: rpi; text: "Raspberry Pi" }

		ImageSlide { about: rpi; source: "rpi.png" }

		ImageSlide { about: rpi; source: "rpi_radio.jpg" }
		ImageSlide { about: rpi; source: "rpi_home.jpg" }
		ImageSlide { about: rpi; source: "rpi_picade.jpg" }
		ImageSlide { about: rpi; source: "rpi_mobile.jpg" }
		ImageSlide { about: rpi; source: "rpi_calendar.jpg" }
		ImageSlide { about: rpi; source: "rpi_car.jpg" }
		ImageSlide { about: rpi; source: "rpi_supercomputer.jpg" }
		ImageSlide { about: rpi; source: "rpi_coffee.jpg" }
		ImageSlide { about: rpi; source: "rpi_feeder.jpg" }
		ImageSlide { about: rpi; source: "rpi_moose.jpg" }
		ImageSlide { about: rpi; source: "rpi_r2.jpg" }

		TitleSlide { about: rpi; text: "Working example" }

		TitleSlide { about: ard; text: "Arduino" }

		ImageSlide { about: ard; source: "ard.png" }

		ImageSlide { about: ard; source: "ard_cube.jpg" }
		ImageSlide { about: ard; source: "ard_arducopter.jpg" }
		ImageSlide { about: ard; source: "ard_cat_laser.jpg" }
		ImageSlide { about: ard; source: "ard_greenhouse.jpg" }
		ImageSlide { about: ard; source: "ard_metane.jpg" }
		ImageSlide { about: ard; source: "ard_pony.jpg" }

		TitleSlide { about: ard; text: "Working example" }

		ImageSlide { about: ard; source: "ard_example.png" }
		ImageSlide { about: ard; source: "ard_schema.png" }

		TitleSlide { text: "Synergy" }

		Slide
		{
			SerialMonitor { id: serialmon }

			Column
			{
				width: parent.width
				anchors.verticalCenter: parent.verticalCenter

				Item {
					width: parent.width
					height: screen.lineHeight
					Row {
						anchors.fill: parent
						TextP
						{
							text: "Luminosity"
							height: parent.height
							width: parent.width/2
							horizontalAlignment: Text.AlignHCenter
						}
						TextP
						{
							text: "Temperature"
							height: parent.height
							width: parent.width/2
							horizontalAlignment: Text.AlignHCenter
						}
					}
				}
				Item {
					width: parent.width
					height: 2*screen.lineHeight
					Row {
						anchors.fill: parent
						TextP
						{
							text: serialmon.luminosity
							height: parent.height
							width: parent.width/2
							horizontalAlignment: Text.AlignHCenter
						}
						TextP
						{
							text: serialmon.temperature
							height: parent.height
							width: parent.width/2
							horizontalAlignment: Text.AlignHCenter
						}
					}
				}
			}
		}

		ImageSlide { source: "synergy_ard.png" }

		Slide
		{
			Column
			{
				anchors.verticalCenter: parent.verticalCenter
				anchors.left: parent.left
				anchors.right: parent.right
				spacing: 0.8*screen.lineHeight
				Item
				{
					width: parent.width
					height: 3*screen.lineHeight
					TextP
					{
						text: "Summary"
						height: 2*screen.lineHeight
						width: parent.width
						horizontalAlignment: Text.AlignHCenter
					}
				}
			}
		}

		Slide
		{
			Item {
				anchors.centerIn: parent
				height: 0.8*screen.height
				width: 0.9*screen.width
				Row {
					anchors.fill: parent
					spacing: 0.1*screen.width
					Image
					{
						source: "rpi.png"
						height: parent.height
						width: 0.4*screen.width
						horizontalAlignment: Text.AlignHCenter
						fillMode: Image.PreserveAspectFit
					}
					Image
					{
						source: "ard.png"
						height: parent.height
						width: 0.4*screen.width
						horizontalAlignment: Text.AlignHCenter
						fillMode: Image.PreserveAspectFit
					}
				}
			}
		}
	}

	Row {
		anchors.fill: parent
		Rectangle
		{
			color: rpi.color
			height: parent.height
			width: parent.width/2
		}
		Rectangle
		{
			color: ard.color
			height: parent.height
			width: parent.width/2
		}
	}

	ListView {
		anchors.fill: parent
		model: slides
		snapMode: ListView.SnapOneItem
		id: slidesView
		highlightMoveVelocity: 1000
	}

	MouseArea {
		anchors.fill: parent
		acceptedButtons: Qt.AllButtons

		onClicked: {
			if (mouse.button == Qt.LeftButton)
				slidesView.currentIndex--;
			if (mouse.button == Qt.RightButton)
				slidesView.currentIndex++;
			if (mouse.button == Qt.MidButton)
				slidesView.currentIndex = 0;

			hipsta.displayedValue = slidesView.currentIndex;
		}
	}
}
