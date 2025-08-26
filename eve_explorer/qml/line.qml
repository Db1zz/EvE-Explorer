import QtQuick.Shapes
import QtQuick

Rectangle {
	id: line
	height: 2
	color: "green"

	function setLine(startX, startY, endX, endY) {
        var dx = endX - startX;
        var dy = endY - startY;
		width = Math.sqrt(dx*dx + dy*dy);
        rotation = Math.atan2(dy, dx) * (180 / Math.PI);
		x = startX + (dx / 2) - width / 2;
		y = startY + (dy / 2) - height / 2;
	}
	Rectangle {
		anchors.left: parent.left
		anchors.top: parent.top
		color: "yellow"
	}
}

