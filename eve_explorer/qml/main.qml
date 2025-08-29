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
		property real xMapPosNew;
		property real yMapPosNew;

		transform: Scale {
			id: mapScale
			property real xScaleNew;
			property real yScaleNew;
		}

		ParallelAnimation {
			id: zoomAnimation
			property real animationSpeed: 50
			NumberAnimation {target: mapScale; property: "xScale"; to: mapScale.xScaleNew; duration: zoomAnimation.animationSpeed; easing.type: Easing.Linear}
			NumberAnimation {target: mapScale; property: "yScale"; to: mapScale.yScaleNew; duration: zoomAnimation.animationSpeed; easing.type: Easing.Linear}
			NumberAnimation {target: eveUniverseMap; property: "x"; to: eveUniverseMap.xMapPosNew; duration: zoomAnimation.animationSpeed; easing.type: Easing.Linear}
			NumberAnimation {target: eveUniverseMap; property: "y"; to: eveUniverseMap.yMapPosNew; duration: zoomAnimation.animationSpeed; easing.type: Easing.Linear}
		}

		function animateZoom(xScale, yScale, xMapPos, yMapPos) {
			zoomAnimation.stop();

			eveUniverseMap.xMapPosNew = xMapPos;
			eveUniverseMap.yMapPosNew = yMapPos;

			mapScale.xScaleNew = xScale;
			mapScale.yScaleNew = yScale;

			zoomAnimation.start();
		}

		Component.onCompleted: {
			generateEveUniverseMap();
		}

		function generateStargates(solarSystemStargates, solarSystemObject) {
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

		function generateEveUniverseMap() {
			var solarSystemComponent =  Qt.createComponent("mapSolarSystemObject.qml");
			var count = 0;
			for (var ss of solarSystems) {
				var solarSystemObject = solarSystemComponent.createObject(eveUniverseMap);
				solarSystemObject.setSystemPosition(ss.position.x * systemOffset, -ss.position.z * systemOffset);
				var solarSystemStargates = ss.getStargates();
				generateStargates(solarSystemStargates, solarSystemObject);
				if (count == 5430) {
					break;
				}
				++count;
			}
		}
	}
	MouseArea {
		id: mouse
		anchors.fill: parent
		drag.target: eveUniverseMap
		drag.axis: Drag.XAxis | Drag.YAxis
		propagateComposedEvents: true
		hoverEnabled: true
		onWheel: (wheel)=> {
            const zoomStep = wheel.angleDelta.y > 0 ? 1.5 : 0.5;
            const cursorX = wheel.x;
            const cursorY = wheel.y;
            const oldX = (cursorX - eveUniverseMap.x) / mapScale.xScale;
            const oldY = (cursorY - eveUniverseMap.y) / mapScale.yScale;
			var xScale = mapScale.xScale * zoomStep;
			var yScale = mapScale.yScale * zoomStep;
			var xMapPosNew = cursorX - oldX * xScale;
			var yMapPosNew = cursorY - oldY * yScale;
			eveUniverseMap.animateZoom(
				xScale, yScale,
				xMapPosNew, yMapPosNew
			);
		}
	}
}
