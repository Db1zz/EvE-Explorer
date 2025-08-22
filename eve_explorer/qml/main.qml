import QtQuick
import QtQuick.Window
import QtQuick.Controls
import MyLib

Window {
	id: mainWindow
	width: screen.width
	height: screen.height
	visible: true
	color: "black"

	Canvas {
		id: staticEveUniverseMap
		width: 5000
		height: 5000
		visible: false
		property real offsetX: width / 2
		property real offsetY: height / 2
		property real mapScale: 4e-15
		property bool isPainted: false
		renderStrategy: Canvas.Threaded

		onPaint: {
			var ctx = getContext("2d")
			drawMap(ctx)
			isPainted = true
		}

		function drawMap(ctx) {
			ctx.fillStyle = Qt.rgba(200,200,0,255)
			for (var solarSystem of solarSystems) {
				ctx.ellipse(
					solarSystem.position.x * mapScale + offsetX,
					-solarSystem.position.z * mapScale + offsetY,
					2, 2)
			}
			ctx.fill()
			mapEveUniverse.requestPaint()
		}

	}

	Canvas {
		id: mapEveUniverse
		width: 5000
		height: 5000
		x: -(mainWindow.height / 2)
		y: -(mainWindow.width / 2)
		z:0

		onPaint: {
			if (staticEveUniverseMap.isPainted) {
				var ctx = getContext("2d")
				ctx.reset()
				ctx.drawImage(staticEveUniverseMap, 0, 0)
			}
		}

		Component.onCompleted: {
			staticEveUniverseMap.requestPaint()
		}

		Canvas {
			id: rndm
			width:50 
			height:50
			property real diameter: 20
			z:1

			onPaint: {
				var ctx = getContext("2d")
				drawClickPoint(ctx);
			}

			function drawClickPoint(ctx) {
				ctx.fillStyle = Qt.rgba(255, 255, 255, 255)
				ctx.ellipse(0, 0, diameter, diameter)
				ctx.fill()
			}
		}

		MouseArea {
			anchors.fill: parent
			drag.target: mapEveUniverse
			drag.axis: Drag.XAxis | Drag.YAxis
			onClicked: {
				rndm.x = mouseX - rndm.diameter / 2
				rndm.y = mouseY - rndm.diameter / 2
				rndm.requestPaint()
			}
		}
	}

}
