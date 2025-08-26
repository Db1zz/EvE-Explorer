import QtQuick
import QtQuick.Window
import QtQuick.Controls
import MyLib
import QtQuick.Shapes

Window {
	id: mainWindow
	width: screen.width
	height: screen.height
	visible: true
	color: "black"

	Item {
		id: eveUniverseMap
		property var systemOffset: 5e-15
		Component.onCompleted: {
			var solarSystemComponent =  Qt.createComponent("mapSolarSystemObject.qml");
			for (var ss of solarSystems) {
				var solarSystemObject = solarSystemComponent.createObject(eveUniverseMap);
				solarSystemObject.setSystemPosition(ss.position.x * systemOffset, -ss.position.z * systemOffset);
				var solarSystemStargates = ss.getStargates();
				for (var solarSystemStargate of solarSystemStargates) {
					if (!childAt(solarSystemObject.x, solarSystemObject.y)) {
						continue;
					}
					var lineComponent = Qt.createComponent("line.qml");
					var destPointX = solarSystemStargate.destinationSolarSystemPosition.x * systemOffset;
					var destPointY = -solarSystemStargate.destinationSolarSystemPosition.z * systemOffset;
					var lineObject = lineComponent.createObject(eveUniverseMap);
					lineObject.setLine(
						solarSystemObject.x,
						solarSystemObject.y,
						destPointX,
						destPointY);
				}
			}
		}
	}
	MouseArea {
		anchors.fill: parent
		drag.target: eveUniverseMap
		drag.axis: Drag.XAxis | Drag.YAxis
		propagateComposedEvents: true
	}
}
