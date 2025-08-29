import QtQuick
import QtQuick.Particles

Rectangle {
	id: solarSystemRectangle
	width: 10
	height: 10
	color: "yellow"
	radius: 180

	MouseArea {
		id: circleMouseArea
		anchors.fill: parent
		onClicked: {
			solarSystemRectangle.color = "red"
		}
	}
	function setSystemPosition(systemX, systemY) {
		x = systemX;
		y = systemY;
	}
}